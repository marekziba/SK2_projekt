#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "Question.hpp"

Question::Question(int id, std::string content)
    : _qid{id} 
    , _content{content}
{
    this->_rightAnswer = -1;
}

Question::Question(int id, std::string content, std::vector<std::string> answers, int rightAnswer)
    : _rightAnswer{rightAnswer}
    , _qid{id}
    , _content{content}
    , _answers{answers}
{ }

void Question::addAnswers(std::vector<std::string> answers,int rightAnswer){
    this->_answers = answers;
    this->_rightAnswer = rightAnswer;
}

int Question::getID(){  return this->_qid; }

bool Question::verifyAnswer(int i){ return i == this->_rightAnswer; }

void Question::addAnswer(std::string content, bool isRight){
    int n = this->_answers.size();
    if(n >= MAX_ANSWERS){ throw std::runtime_error("Maximum number of answers reached"); }
    this->_answers.push_back(content);
    if(isRight){
        if(this->_rightAnswer == -1){
            this->_rightAnswer = n + 1;
        }
        else{
            throw std::runtime_error("Question can have only one right answer");
        }
    }
}

std::string Question::toString(){
    std::stringstream ss; 
    ss <<this->_qid <<":" <<this->_content;
    for(std::string answer : this->_answers){
        ss <<":" <<answer; 
    }
    ss <<";";

    std::string str = ss.str();

    ss.str("");
    ss <<"#" <<std::setfill('0') <<std::setw(3) <<str.length() <<"?" <<str; 

    return ss.str();
}

Question Question::parseString(std::string qstr){
    int pos;

    std::vector<std::string> split;
    std::string fragment;
    while( (pos = qstr.find(":")) != std::string::npos){
        fragment = qstr.substr(0, pos);
        split.push_back(fragment);
        qstr.erase(0, pos + 1);
    }

    if( (pos = qstr.find(";")) != std::string::npos ) qstr = qstr.substr(0, pos);
    
    split.push_back(qstr);

    if(split.size() != 6){
        throw std::runtime_error("Question string invalid");
    }

    int qid = std::stoi(split[0]);
    std::string content = split[1];
    std::vector<std::string> answers;
    for(int i = 2; i < 6; i++){
        answers.push_back(split[i]);
    }

    Question q = Question(qid, content, answers, -1);

    return q;
}