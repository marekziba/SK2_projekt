#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "Server.hpp"

#include <QMainWindow>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(Server* srv, QWidget *parent = nullptr);
    ~ServerWindow();
    void lock();

private slots:

    void on_nextQuestionButton_clicked() {};

    void on_startButton_clicked();

    void on_runButton_clicked();

    void on_addQuestionButton_clicked();

    void unlock();

    void printInfo(std::string str);

    void updateUsersCount(int n);

private:
    Ui::ServerWindow *ui;

    Server* _srv;
    int nQuestions = 0;
    int questionID = 0;
};

#endif // SERVERWINDOW_H
