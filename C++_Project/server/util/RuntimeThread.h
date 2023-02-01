#ifndef NOTYHELPER_RUNTIMETHREAD_H
#define NOTYHELPER_RUNTIMETHREAD_H
#include <string>
#include <list>
#include <vector>
#include "pthread.h"
#include "Socket.h"

enum class Request{
    LOGIN, CREATE_ACC, POST_NOTY, FETCH_NOTY, ALERT
};

struct noty{
    std::string username;
    std::string text;
    std::string deadline;
    bool is_sharable;
};

class RuntimeThread {
private:
    Socket sock;
    pthread_t thread_id;
    static inline std::list <RuntimeThread *> thread_list;
    static inline pthread_mutex_t list_mutex;
    std::string username;
    std::vector<std::string> notifs;

public:

    RuntimeThread(const Socket& s, pthread_t id);

    auto inline get_id(){
        return this->thread_id;
    }

    auto inline get_socket(){
        return this->sock;
    }

    void set_id(pthread_t id){
        this->thread_id = id;
    }

    static void add_thread ( RuntimeThread * thread );
    static void remove_thread ( RuntimeThread * thread );
    static void create_thread(RuntimeThread * thread, void * (*thread_initializer)(void *));
    static void * init_thread(void * args);

    static void run(RuntimeThread & arg);

    static Request to_request(const std::string& req);

    static void login(RuntimeThread & arg);
    static void create_account(RuntimeThread & arg);
    static int is_registered(const std::string& username, const std::string& password);
    static void add_user(const std::string & username, const std::string & password);
    static void post_noty(RuntimeThread & arg);
    static void fetch_noty(RuntimeThread & arg);
    static void alert(RuntimeThread & arg);
    static bool should_alert(const std::string& noty, const std::string& timestamp);

};


#endif //NOTYHELPER_RUNTIMETHREAD_H
