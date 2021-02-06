#include "Server.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

Server::Server(){
    this-> running = false;
    this->_qtime = 10;

    this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{
        .sin_family =   AF_INET, 
        .sin_port   =   htons(5000), 
        .sin_addr   =   {htonl(INADDR_ANY)}
        };
    const int one = 1;
    setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    bind(this->_socket, (sockaddr*) &addr, sizeof(addr));

    this->_window = new ServerWindow(this);

    QMetaObject::invokeMethod(_window, "show");
}

Server::~Server(){
    for(UserConnection* u : this->users){
        delete u;
    }
    this->users.clear();

    std::cout <<"Server shutting down..." <<"\n";
    close(this->_socket);
}

void Server::run(){
    int i = 0;
    listen(this->_socket,SOMAXCONN);
    this->running = true;

    while(true){
        sockaddr_in psi{};
        socklen_t len = sizeof(psi);
        int clientSocket = accept(this->_socket, (sockaddr*) &psi, &len);
        UserConnection* u = new UserConnection(this, i);
        
        std::thread([u, clientSocket, psi]{u->listen(clientSocket, psi);}).detach();
        this->users.push_back(u);
        this->_userInfo.push_back(User(i));
        i++;
        
        QMetaObject::invokeMethod(_window, "updateUsersCount", Q_ARG(int, i));
    }
}

bool Server::isGameRunning(){
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->running;
}

void Server::activateQuestion(int qid){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->_activeQuestion = qid;
    if(qid >= 0){
        this->_qtimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    lock.unlock();

    if(qid >= 0){
        for(UserConnection* u : this->users){
            u->sendMessage(this->questions[qid].toString());
        }
    }
}

void Server::deactivateQuestion(){
    this->activateQuestion(-1);
}

int Server::getActiveQuestionID(){
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->_activeQuestion;
}

bool Server::validateAnswer(int qid, int aid){
    // get question and answer id from message 
    std::lock_guard<std::mutex> lock(this->mutex);
    if(qid != this->_activeQuestion){
        return false;
    }
    else{
        return this->questions[qid].verifyAnswer(aid);
    }
}

void Server::addQuestion(Question q){
    this->questions.push_back(q);
}

void Server::runQuestion(int qid){
    std::thread([this, qid]{
        this->activateQuestion(qid);
        
        sleep(this->_qtime);

        this->deactivateQuestion();
        
        this->sendRank();
        QMetaObject::invokeMethod(_window, "unlock");
    }).detach();
}

Question Server::getActiveQuestion(){
    int i = this->getActiveQuestionID();
    printf("Active question = %d\n", i);
    printf("Server has %ld questions\n", this->questions.size());
    return this->questions[i];
}

int Server::getQuestionCount(){
    return this->questions.size();
}

void Server::registerAnswer(int uid, int qid, int aid){
    uint64_t diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - this->_qtimestamp;
    double score;
    std::stringstream ss;
    if(validateAnswer(qid, aid)){
        score = 10 + (((double) this->_qtime - (diff/1000.0))/(double)this->_qtime)*90.0;
        ss <<"User " <<uid <<" responded with RIGHT answer in " <<diff/1000.0 <<" seconds, scoring "  <<score <<" points";
        this->users[uid]->sendMessage("#003=1;");
        this->_userInfo[uid].updateScore(score);
    }
    else{
        score = 0;
        ss <<"User " <<uid <<" responded with WRONG answer in " <<diff/1000.0 <<" seconds, scoring "  <<score <<" points";
        this->users[uid]->sendMessage("#003=0;");
    }

    qRegisterMetaType<std::string>("std::string");
    QMetaObject::invokeMethod(_window, "printInfo", Q_ARG(std::string, ss.str()));

}

void Server::registerUser(int uid, std::string nick){
    std::lock_guard<std::mutex> lock(this->mutex);
    nick = nick.substr(1, nick.length() - 2);

    for(int i = 0; i < this->_userInfo.size(); i++){
        if(i == uid) continue;
        if(this->_userInfo[i].getUsername() == nick){
            this->users[i]->sendMessage("#003&0;");
            return;
        }
    }

    this->_userInfo[uid].setNick(nick);
    this->users[uid]->sendMessage("#003&1;");
}

void Server::sendRank(){
    std::vector<User> usersCopy(this->_userInfo);

    std::sort(usersCopy.begin(), usersCopy.end());

    std::stringstream ss; ss <<"%";

    for(User u : usersCopy){
        ss <<u.getRankingEntry();
    }
    
    std::string str = ss.str(); str = str.substr(0, str.length() - 1); ss.str("");
    ss <<"#" <<std::setfill('0') <<std::setw(3) <<str.length() <<str <<";";
    str = ss.str();

    for(UserConnection* uc : this->users){
        uc->sendMessage(str);
    }
}