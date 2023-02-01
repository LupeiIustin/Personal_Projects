#ifndef NOTYHELPER_DEFINES_H
#define NOTYHELPER_DEFINES_H

#define OK "OK"
#define NOT_OK "NOK"
#define ALREADY_EXISTS "ALREADY_EXISTS"
#define ACCOUNT_CREATED "CREATED"
#define NO_ALERT "NO_ALERT"

#include <string>
#include <unistd.h>

static std::string read_string(int sock){
    int message_size = 0;
    read(sock, &message_size, sizeof(int));
    std::string message(message_size, '\0');
    read(sock, message.data(), message_size);
    return message;
}

static void write_string(const std::string & message, int sock){
    int message_size = message.size();
    write(sock, &message_size, sizeof(int));
    write(sock, message.c_str(), message_size);
}
#endif //NOTYHELPER_DEFINES_H
