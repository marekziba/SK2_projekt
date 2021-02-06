#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "Question.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>

ServerWindow::ServerWindow(Server* srv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    this->_srv = srv;
    this->ui->groupBox_2->setEnabled(false);
    this->ui->nextQuestionButton->setVisible(false);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_startButton_clicked()
{
    this->_srv->runQuestion(this->questionID);
    this->lock();
}

void ServerWindow::on_runButton_clicked()
{
    this->ui->groupBox_2->setEnabled(true);
    this->ui->groupBox->setEnabled(false);
    std::thread([this]{
        this->_srv->run();
    }).detach();
}

void ServerWindow::on_addQuestionButton_clicked()
{
    std::string content = this->ui->questionContent->text().toStdString();

    std::string a1, a2, a3, a4;
    a1 = this->ui->lineQuestion1->text().toStdString();
    a2 = this->ui->lineQuestion2->text().toStdString();
    a3 = this->ui->lineQuestion3->text().toStdString();
    a4 = this->ui->lineQuestion4->text().toStdString();
    int rq = this->ui->rightAnswerSelector->currentIndex();

    std::vector<std::string> answers = {a1, a2, a3, a4};

    Question q = Question(this->nQuestions, content, answers, rq);

    this->_srv->addQuestion(q);
    this->nQuestions = this->_srv->getQuestionCount();

    std::stringstream ss; ss <<"Questions defined: " <<this->nQuestions; 
    std::string questionsLabelStr = ss.str();

    this->ui->questionCountLabel->setText(QString(questionsLabelStr.c_str()));

    this->ui->questionContent->clear();
    this->ui->lineQuestion1->clear();
    this->ui->lineQuestion2->clear();
    this->ui->lineQuestion3->clear();
    this->ui->lineQuestion4->clear();
}

void ServerWindow::updateUsersCount(int n){
    std::stringstream ss; ss <<"<h4>" <<n <<" users joined</h4>"; 
    std::string userCountStr = ss.str();

    this->ui->userCounterLabel->setText(QString(userCountStr.c_str()));
    this->ui->userCounterLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void ServerWindow::printInfo(std::string info){
    this->ui->textEdit->append(QString(info.c_str()));
}

void ServerWindow::lock(){
    std::stringstream ss; ss <<"Running question..."; // <<this->questionID + 1 <<"...";
    this->ui->startButton->setText(ss.str().c_str());
    this->ui->startButton->setEnabled(false);
}

void ServerWindow::unlock(){
    if(this->questionID + 1 < this->nQuestions){
        std::stringstream ss; ss <<"Run next question!";
        this->ui->startButton->setEnabled(true);
        this->ui->startButton->setText(QString::fromStdString(ss.str()));
        this->questionID++;
    }
    else{
        this->ui->startButton->setText("Finished!");
    }
}