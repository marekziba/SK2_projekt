#include "ClientWindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

#include <thread>
#include <unistd.h>
#include <sstream>

ClientWindow::ClientWindow(Client* client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Kahut"));

    ui->questionContent->setText(QString("<h1>Czekanie na pytanie...</h1>"));
    ui->questionContent->setWordWrap(true);
    ui->questionContent->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->connectLabel->setText(QString("<h1>Połącz z serwerem</h1>"));
    ui->connectLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->rankingLabel->setText(QString("<h1>Ranking</h1>"));
    ui->rankingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->errorLabel->setText(QString(""));

    ui->answer1->setText("");
    ui->answer2->setText("");
    ui->answer3->setText("");
    ui->answer4->setText("");

    ui->answer1->setEnabled(false);
    ui->answer2->setEnabled(false);
    ui->answer3->setEnabled(false);
    ui->answer4->setEnabled(false);

    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);

    this->_client = client;

    connect(ui->answer1, &QPushButton::clicked, [this]{this->_client->sendResponse(0);});
    connect(ui->answer2, &QPushButton::clicked, [this]{this->_client->sendResponse(1);});
    connect(ui->answer3, &QPushButton::clicked, [this]{this->_client->sendResponse(2);});
    connect(ui->answer4, &QPushButton::clicked, [this]{this->_client->sendResponse(3);});

    connect(ui->connectButton, &QPushButton::clicked, [this]{this->clientConnect();});
}

void ClientWindow::enableQuiz(){
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(true);

    ui->groupBox->setEnabled(false);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::displayQuestion(Question q){
    int qid = q.getID();
    this->setCurrentQuestionID(qid);
    std::string content = std::string("<h1>") + q.getContent() + std::string("</h1>");
    this->ui->questionContent->setText(content.c_str());

    std::vector<std::string> answers = q.getAnswers();

    ui->answer1->setText(QString::fromStdString(answers[0]));
    ui->answer2->setText(QString::fromStdString(answers[1]));
    ui->answer3->setText(QString::fromStdString(answers[2]));
    ui->answer4->setText(QString::fromStdString(answers[3]));

    ui->answer1->setEnabled(true);
    ui->answer2->setEnabled(true);
    ui->answer3->setEnabled(true);
    ui->answer4->setEnabled(true);

    std::thread([this, qid]{
        sleep(10);

        QMetaObject::invokeMethod(this, "deactivateQuestion", Q_ARG(int, qid));
    }).detach();
}

void ClientWindow::deactivateQuestion(int qid){

    if(this->getCurrentQuestionID() == qid){
        this->ui->questionContent->setText(QString("<h1>Czekanie na pytanie...</h1>"));

        this->ui->answer1->setText("");
        this->ui->answer2->setText("");
        this->ui->answer3->setText("");
        this->ui->answer4->setText("");

        this->ui->answer1->setEnabled(false);
        this->ui->answer2->setEnabled(false);
        this->ui->answer3->setEnabled(false);
        this->ui->answer4->setEnabled(false);

        this->setCurrentQuestionID(-1);

        int status;
        if((status = this->checkWaiting()) >= 0){
            this->displayResult(status);
        }
    }
}

void ClientWindow::setCurrentQuestionID(int id){
    std::lock_guard<std::mutex> lock(this->mutex);
    this->currentQuestionID = id;
}

int ClientWindow::getCurrentQuestionID(){
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->currentQuestionID;
}

void ClientWindow::clientConnect(){
    this->ui->errorLabel->setText("");

    std::string addr, port, nick;
    
    addr = this->ui->ipInput->text().toStdString();
    port = this->ui->portInput->text().toStdString();
    nick = this->ui->nickInput->text().toStdString();

    if(!this->_client->connected()){
        this->_client->conn(addr, port, nick);
    } else {
        this->_client->registerUsername(nick);
    }
}

void ClientWindow::displayErrorMessage(std::string message){
    this->ui->errorLabel->setText(QString::fromStdString(message));
}

int ClientWindow::checkWaiting(){
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->resultWaiting;
}

void ClientWindow::setWaiting(int x){
    std::lock_guard<std::mutex> lock(this->mutex);
    this->resultWaiting = x;
}

void ClientWindow::checkAndDisplayResult(int result){
    if(this->getCurrentQuestionID() >= 0){
        this->setWaiting(result);
    }
    else {
        this->displayResult(result);
    }
}

void ClientWindow::displayResult(int result){
    if(result == 1){
        this->ui->questionContent->setText("<h1>Brawo!</h1>");
    } else if(result == 0){
        this->ui->questionContent->setText("<h1>Nie udało się :(</h1>");
    }
}

void ClientWindow::viewRank(std::string rankStr){
    this->ui->ranking->clear();

    int pos; std::vector<std::string> entries;

    while((pos = rankStr.find(":")) != std::string::npos){
        entries.push_back(rankStr.substr(0, pos));
        rankStr.erase(0, pos + 1);
    }
    if(rankStr.back() == ';') rankStr = rankStr.substr(0, rankStr.length() - 1);
    entries.push_back(rankStr);

    int i = 1; std::stringstream ss;
    for(std::string s : entries){
        int pos = s.find(","); 
        ss <<i <<".\t" <<s.substr(0, pos) <<"\t" <<s.substr(pos + 1);
        this->ui->ranking->append(QString::fromStdString(ss.str()));
        ss.str("");
        i++;
    }
}