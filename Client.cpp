#include "Client.hpp"
#include "Question.hpp"

#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <error.h>
#include <iostream>
#include <fcntl.h>
#include <sstream>
#include <iomanip>

Client::Client(){
    this->window = new ClientWindow(this);
    this->_connected = false;

    QMetaObject::invokeMethod(window, "show");
}

void Client::run(){
    std::thread([this]{
        // event loop listening for incoming questions
        while(true){
            char buffer[255], header;
            int nRead = read(this->_socket, &header, 1);
            if(nRead > 0){
                if(header == '#'){
                    header = 0;

                    // read first 3 bytes containg size of message
                    read(this->_socket, &buffer, 3);
                    ssize_t size = atoi(buffer);

                    char* message = (char *) malloc(size+2);
                    read(this->_socket, message, size+1);

                    std::string msgStr = std::string(message);


                    switch(msgStr[0]){
                        case '?' : {
                            Question q = Question::parseString(msgStr.substr(1));

                            qRegisterMetaType<Question>("Question");
                            QMetaObject::invokeMethod(window, "displayQuestion", Q_ARG(Question, q));

                            this->currentQuestion = q;

                            break;
                        }
                        case '&' : {
                            // registration confirmation/denial
                            if(msgStr[1] == '1') {
                                QMetaObject::invokeMethod(window, "enableQuiz");
                            }
                            if(msgStr[1] == '0') {
                                qRegisterMetaType<std::string>("std::string");
                                QMetaObject::invokeMethod(window, "displayErrorMessage", Q_ARG(std::string, std::string("Ten nick jest już zajęty, wprowadź inny nick")));
                            }

                            break;
                        }
                        case '=' : {
                            int result = std::stoi(msgStr.substr(1,2));
                            QMetaObject::invokeMethod(window, "checkAndDisplayResult", Q_ARG(int, result));
                            
                            break;
                        }
                        case '%' : {
                            msgStr = msgStr.substr(1, msgStr.find(";"));

                            qRegisterMetaType<std::string>("std::string");
                            QMetaObject::invokeMethod(window, "viewRank", Q_ARG(std::string, msgStr));

                            break;
                        }
                        default : {
                            break;
                        }
                    }

                    memset(message, 0, size+2);
                    free(message);
                }
            }
        }

    }).detach();
}

void Client::conn(std::string ip, std::string port, std::string nick){
    addrinfo *resolved, hints={.ai_flags=0, .ai_family=AF_INET, .ai_socktype=SOCK_STREAM};
    int res = getaddrinfo(ip.c_str(), port.c_str(), &hints, &resolved);

    if(res || !resolved) error(1,0,"getaddrinfo: %s", gai_strerror(res));

    this->_socket = socket(resolved->ai_family, resolved->ai_socktype, 0);
    if(this->_socket == -1) {error(1, errno, "socket failed"); return; }

    res = connect(this->_socket, resolved->ai_addr, resolved->ai_addrlen);
	if(res) {
        qRegisterMetaType<std::string>("std::string");
        QMetaObject::invokeMethod(window, "displayErrorMessage", Q_ARG(std::string, std::string("Nie udało się połączyć. Sprawdź wprowadzone dane.")));
        return;
    }

    this->_connected = true;
    freeaddrinfo(resolved);

    this->registerUsername(nick);

    this->run();
}

void Client::registerUsername(std::string nick){
    std::stringstream ss; ss <<"+" <<nick <<";"; 
    std::string str = ss.str(); ss.str(""); 
    ss <<"#" <<std::setfill('0') <<std::setw(3) <<str.length() <<str;
    str = ss.str();

    const char* message = str.c_str();
    ssize_t size = strlen(message);
    write(this->_socket, message, size);
}

void Client::sendResponse(int aid){
    int qid = this->window->getCurrentQuestionID();
    std::stringstream ss;
    ss <<"?" <<qid <<":" <<aid <<";";
    std::string str = ss.str();
    ss.str(""); ss <<"#" <<std::setfill('0') <<std::setw(3) <<str.length() <<str;
    str = ss.str();
    const char* response = str.c_str();
    ssize_t size = strlen(response);
    write(this->_socket, response, size);
}