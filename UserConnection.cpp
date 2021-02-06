#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <fcntl.h>

#include "UserConnection.hpp"

UserConnection::UserConnection(Server* srv, int uid){
    this->srv = srv;
    this->uid = uid;
}

void UserConnection::disconnect(){
    std::cout <<"Disconnecting user " <<uid <<"\n";
    shutdown(this->socket, SHUT_RDWR);
    close(this->socket);
}

UserConnection::~UserConnection(){
    this->disconnect();
}

void UserConnection::listen(int socket, sockaddr_in addr){
    this->socket = socket;

    std::stringstream ss; ss <<"Hello user " <<uid <<"!\n";
    const char* response = ss.str().c_str();
    ssize_t len = strlen(response);
    write(this->socket, response, len);
    char received[255], header;

    while(true){
        //  handle responses from users
        int nRead = read(this->socket, &header, 1);
        if(nRead > 0){
            printf("From user %d: %s\n", this->uid, received);

            if(header == '#'){
                header = 0;

                read(this->socket, received, 3);
                ssize_t size = atoi(received);

                char* message = (char*) malloc(size+2);
                read(this->socket, message, size + 1);

                std::string msgStr = std::string(message);

                switch(msgStr[0]){
                    case '?' : {
                        int qid, aid;

                        qid = std::stoi(msgStr.substr(1, msgStr.find(':')));
                        msgStr.erase(0, msgStr.find(':') + 1);
                        aid = std::stoi(msgStr.substr(0, msgStr.length() - 1));

                        this->srv->registerAnswer(this->uid, qid, aid);
                        break;
                    }
                    case '+' : {
                        this->srv->registerUser(this->uid, msgStr);

                        break;
                    }
                    default: {
                        break;
                    }
                }

                free(message);
            }

            memset(received,0,255);
        }
        if(nRead == 0){
            // user disconnected
            std::cout <<"User " <<this->uid <<" disconnected\n";
            break;
        }
    }
}

void UserConnection::sendMessage(std::string message){
    const char* msg = message.c_str();
    ssize_t size = message.length();
    
    write(this->socket, msg, size);
}