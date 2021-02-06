#ifndef USER_CONNECTION_HPP
#define USER_CONNECTION_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Server;

#include "Server.hpp"


class UserConnection{
    private:
    int printDebug = 1;
    int uid;
    int score;
    std::string _name;
    int socket;
    Server *srv;

    void disconnect();

    public:
    UserConnection(Server *srv, int uid);
    ~UserConnection();
    void listen(int socket, sockaddr_in addr);
    void sendMessage(std::string message);
};

#endif