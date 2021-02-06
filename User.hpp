#ifndef USER_HPP
#define USER_HPP

#include <string>

class User{
private:
    std::string username;
    int uid;
    double score = 0.0;

public:
    
    User(int uid);
    std::string getRankingEntry();

    void updateScore(double x) { this->score += x; }
    void setNick(std::string nick) { this->username = nick; }
    
    double getScore() { return this->score; }
    std::string getUsername() { return this->username; }
    int id() { return this->uid; }

    bool operator< (User& other) { return this->score > other.getScore(); }
};

#endif