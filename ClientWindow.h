#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mutex>

class Client;

#include "Question.hpp"
#include "Client.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(Client* client, QWidget *parent = nullptr);
    ~ClientWindow();

    void setCurrentQuestionID(int id);
    int getCurrentQuestionID();

private:
    std::mutex mutex;
    Client* _client;
    Ui::ClientWindow *ui;
    int currentQuestionID = -1;
    int resultWaiting = -1;

    void clientConnect();
    int checkWaiting();
    void displayResult(int result);
    void setWaiting(int result);

private slots:
    void displayQuestion(Question q);
    void displayErrorMessage(std::string message);
    void deactivateQuestion(int qid);
    void enableQuiz();
    void checkAndDisplayResult(int result);
    void viewRank(std::string rankStr);
};
#endif // MAINWINDOW_H
