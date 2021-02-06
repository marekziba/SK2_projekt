#include "User.hpp"

#include <sstream>

User::User(int uid){
    this->uid = uid;
    this->username = "";
}

std::string User::getRankingEntry(){
    if(this->username != ""){
        std::stringstream ss;
        ss <<this->username <<"," <<this->score <<":";
        return ss.str();
    } else { return std::string(""); }
}