#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <vector>

#define MAX_ANSWERS 4

class Question{
    private:
    int _rightAnswer, _qid;
    std::string _content;
    std::vector<std::string> _answers;

    public:
    Question(){};
    Question(int id, std::string content);
    Question(int id, std::string content, std::vector<std::string> answers, int correctAnswer);

    bool verifyAnswer(int i);
    int getID();

    void addAnswers(std::vector<std::string> answers, int rightAnswer);
    void addAnswer(std::string content, bool isRight);
    
    std::string toString();

    std::string getContent(){ return this->_content; };
    std::vector<std::string> getAnswers(){ return this->_answers; };

    static Question parseString(std::string qstr);
};

#endif