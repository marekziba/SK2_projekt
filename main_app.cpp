#include "ClientWindow.h"
#include "Client.hpp"
#include "serverwindow.h"

#include <QApplication>
#include <unistd.h>
#include <thread>
#include <cstring>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(argc > 1 && (!strcmp(argv[1], "--server") || !strcmp(argv[1], "-s")) ){
        Server* srv = new Server();
        int x = a.exec();
        delete srv;
        return x;
    } else if(argc > 1 && (!strcmp(argv[1], "--client") || !strcmp(argv[1], "-c")) ){
        Client c = Client();
        return a.exec();
    } else {
        printf("Usage: %s -s (--server) to run server, %s -c (--client) to run client\n", argv[0], argv[0]);
    }
}
