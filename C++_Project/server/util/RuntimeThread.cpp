#include "RuntimeThread.h"
#include "defines.h"
#include <fstream>

void RuntimeThread::add_thread(RuntimeThread *thread) {
    pthread_mutex_lock(&list_mutex);
    thread_list.push_back(thread);
    pthread_mutex_unlock(&list_mutex);
}

void RuntimeThread::remove_thread(RuntimeThread *thread) {
    pthread_mutex_lock(&list_mutex);
    thread_list.remove(thread);
    delete thread;
    pthread_mutex_unlock(&list_mutex);
}

RuntimeThread::RuntimeThread(const Socket &s, pthread_t id) {
    this->sock = s;
    this->thread_id = id;
}

void RuntimeThread::create_thread(RuntimeThread *thread, void *(*thread_initializer)(void *)) {
    pthread_t thId;
    pthread_create(&thId, nullptr, thread_initializer, thread);
    thread->set_id(thId);
}

void *RuntimeThread::init_thread(void * args) {
    RuntimeThread::run(*((RuntimeThread *) args));
    close(((RuntimeThread *) args)->get_socket().get_descriptor());
    RuntimeThread::remove_thread((RuntimeThread *) args);
    return nullptr;
}

Request RuntimeThread::to_request(const std::string& req) {
    if (req == "login") return Request::LOGIN;
    if (req == "create") return Request::CREATE_ACC;
    if (req == "post_noty") return Request::POST_NOTY;
    if (req == "fetch_noty") return Request::FETCH_NOTY;
    if (req == "alert") return Request::ALERT;
}

#include <iostream>

void RuntimeThread::run(RuntimeThread & arg) {

    while (true) {
        if (arg.get_socket().get_descriptor() == -1)
            return;
        auto request = arg.get_socket().read_string();

        if (request.empty())
            continue;

        switch (to_request(request)) {
            case Request::LOGIN :
                login(arg);
                break;
            case Request::CREATE_ACC :
                create_account(arg);
                break;
            case Request::POST_NOTY:
                post_noty(arg);
                break;
            case Request::FETCH_NOTY:
                fetch_noty(arg);
                break;
            case Request::ALERT:
                alert(arg);
                break;
        }
    }
    return;
}

void RuntimeThread::login(RuntimeThread &arg) {
    auto username = arg.get_socket().read_string();
    auto password = arg.get_socket().read_string();
    if (0 == RuntimeThread::is_registered(username, password)) {
        arg.username = username;
        arg.get_socket().write_string(OK);
        return;
    }
    arg.get_socket().write_string(NOT_OK);
}

void RuntimeThread::create_account(RuntimeThread &arg) {
    auto username = arg.get_socket().read_string();
    auto password = arg.get_socket().read_string();
    std::cout << username << " " << password << '\n';
    switch (RuntimeThread::is_registered(username, password)) {
        case -1 :
            add_user(username, password);
            arg.username = username;
            arg.get_socket().write_string(ACCOUNT_CREATED);
            break;
        case 0 :
        case 1 :
            arg.get_socket().write_string(ALREADY_EXISTS);
            break;
    }

}

/**
 * Check if a user exists in database
 * @param username
 * @param password
 * @return 0 if the pair username password exists in database, 1 if the username exits but password is mismatched, -1 otherwise
 */
int RuntimeThread::is_registered(const std::string &username, const std::string &password) {
    std::ifstream fin(USERS_FILE_PATH);
    std::string u, p;
    while (fin >> u >> p) {
        if (u == username) {
            if (p == password) {
                fin.close();
                return 0;
            }
            fin.close();
            return 1;
        }
    }
    fin.close();
    return -1;
}

void RuntimeThread::add_user(const std::string &username, const std::string &password) {
    std::ofstream fout(USERS_FILE_PATH, std::fstream::app);
    fout << username << ' ' << password << '\n';
    fout.close();
}

void RuntimeThread::post_noty(RuntimeThread &arg) {
    std::string is_sharable = arg.get_socket().read_string();
    std::string noty = arg.get_socket().read_string();

    std::string path = NOTYS_FILE_PATH_PREFIX;

    if (is_sharable == "sharable")
        path.append("shared/notys.txt");
    else
        path.append(arg.username).append(".txt");

    std::ofstream fout(path, std::fstream::app);
    fout << noty << '\n';
    fout.close();
}

void RuntimeThread::fetch_noty(RuntimeThread &arg) {
    std::string path = NOTYS_FILE_PATH_PREFIX;
    std::string noty;
    std::vector<std::string> noty_list;
    arg.notifs.clear();

    std::ifstream fusr (path + arg.username + ".txt");
    while (std::getline(fusr, noty)){
        noty_list.push_back(noty);
    }
    fusr.close();

    arg.get_socket().write_string(std::to_string(noty_list.size()));
    for(const auto & i : noty_list){
        arg.get_socket().write_string(i);
        arg.notifs.push_back(i);
    }
    noty_list.clear();


    std::ifstream fall (path + "shared/notys.txt");
    while(std::getline(fall, noty)){
        noty_list.push_back(noty);
    }
    fall.close();

    arg.get_socket().write_string(std::to_string(noty_list.size()));
    for(const auto & i : noty_list){
        arg.get_socket().write_string(i);
        arg.notifs.push_back(i);
    }
}

void RuntimeThread::alert(RuntimeThread &arg) {
    std::string timestamp = arg.get_socket().read_string();
    std::string n = "";
    for (const auto &item: arg.notifs){
        if(should_alert(item, timestamp)) {
            n = item;
            break;
        }
    }

    if(!n.empty()){
        arg.get_socket().write_string(n);
        return;
    }
    arg.get_socket().write_string(NO_ALERT);
}

bool RuntimeThread::should_alert(const std::string& noty, const std::string& timestamp) {
    std::string deadline = noty.substr(noty.size() - 19);
    if(deadline==timestamp)
        return true;
    return false;
}

