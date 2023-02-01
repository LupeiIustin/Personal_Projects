#include <QApplication>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "gui/AppWidget.h"
#include "defines.h"

#define PORT 22520
#define ADDRESS "127.0.0.1"

static int create_connection();

int main(int argc, char *argv[]) {

    int sock = create_connection();
    if (sock == -1)
        return -1;

    QApplication a(argc, argv);
    AppWidget app(sock);
    app.resize(800,600);
    app.show();

    return QApplication::exec();
}

static int create_connection() {

    struct sockaddr_in server{};
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);
    server.sin_family = AF_INET;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == connect(sock, (struct sockaddr *) &server, sizeof(sockaddr_in)))
        return -1;

    return sock;
}
