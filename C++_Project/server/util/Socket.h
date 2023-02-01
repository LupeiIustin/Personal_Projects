#ifndef NOTYHELPER_SOCKET_H
#define NOTYHELPER_SOCKET_H

#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket{
private:
    int sock;
    bool is_connected;
    short port;
    std::string address;

public:

    void open(){
        sock = ::socket(AF_INET, SOCK_STREAM, 0);
    };

    void close(){
        this->sock = -1;
    }


    explicit Socket(int d = -1){
        this->sock = d;
    }

    explicit Socket(std::string const & address, const short port) : port(port), address(address){
        this->open();
        this->connect(address, port);
    }

    Socket(Socket const & socket){
        sock = dup(socket.sock);
        port = socket.port;
        address = socket.address;
        is_connected = socket.is_connected;
    }

    const int get_descriptor(){
        return this->sock;
    }

    void connect(const std::string & address, short port){
        if(sock == -1)
            open();
        sockaddr_in addr{};
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        addr.sin_port = htons(port);

        int status = ::connect(sock, (sockaddr *) & addr, sizeof(sockaddr_in));
        if(status == -1)
            return;
    }

    void bind(short port) {
        int opt = 1;
        int status = ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, & opt, sizeof(opt));

        if(status == -1)
            return;

        sockaddr_in addr{};
        addr.sin_addr.s_addr = htonl (INADDR_ANY );
        addr.sin_port = htons (port);
        addr.sin_family = AF_INET;

        status = ::bind (sock, ( sockaddr * ) & addr , sizeof ( sockaddr_in ) );

        if(status == -1)
            return;
    }

    void listen(int max_size){
        int status = ::listen(sock, max_size);
        if(status == -1)
            return;
    }

    Socket accept(){
        sockaddr_in client{};
        socklen_t size = sizeof(client);

        int status = ::accept(sock, (sockaddr *) & client, & size);
        if (status == -1) {
            throw std::exception();
        }

        auto clientSock = Socket(status);
        return clientSock;
    }

    std::string read_string(){
        int message_size = 0;
        read(sock, &message_size, sizeof(int));
        std::string message(message_size, '\0');
        read(sock, message.data(), message_size);
        return message;
    }

    void write_string(const std::string & message){
        int message_size = message.size();
        write(sock, &message_size, sizeof(int));
        write(sock, message.c_str(), message_size);
    }


};

#endif //NOTYHELPER_SOCKET_H
