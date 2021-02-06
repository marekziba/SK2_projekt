#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <vector>
#include <mutex>

class UserConnection;
class ServerWindow;

#include "UserConnection.hpp"
#include "Question.hpp"
#include "serverwindow.h"
#include "User.hpp"

class Server{
    private:
    std::mutex mutex;
    ServerWindow* _window;
    int _socket;
    std::vector<UserConnection*> users;
    std::vector<Question> questions;
    bool running;
    int _activeQuestion = -1;
    int _qtime;  // time per question
    uint64_t _qtimestamp;
    std::vector<User> _userInfo;

    void activateQuestion(int qid);
    void deactivateQuestion();
    void sendRank();

    public:
    Server();
    ~Server();
    bool isGameRunning();
    void run();
    int getActiveQuestionID();
    bool validateAnswer(int qid, int aid);
    void registerAnswer(int uid, int qid, int aid);
    void addQuestion(Question q);
    void runQuestion(int qid);
    Question getActiveQuestion();
    int getQuestionCount();
    void registerUser(int uid, std::string name);
};

#endif