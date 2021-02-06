#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class ClientWindow;

#include "ClientWindow.h"

class Client{
    private:
    int _socket;
    ClientWindow* window;
    Question currentQuestion;
    bool _connected;

    public:
    Client();
    void setName(std::string name);
    void conn(std::string ip, std::string port, std::string nick);
    void run();
    void sendResponse(int aid);
    bool connected() { return this->_connected; };
    void registerUsername(std::string nick);
};

#endif