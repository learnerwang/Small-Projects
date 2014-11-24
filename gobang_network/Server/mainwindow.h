#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <winSock2.h>
#include <QDebug>
#include <Windows.h>
#define PORT 8080
#define IP_ADDRESS "127.0.0.1"

typedef struct{
    char point[15][15];
    int x,y;
    char Msg;
    char message[100];
}MsgInfo;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    SOCKET ServerSocket;
    SOCKET ClientSocket[2];
    int nowClient;
    int numClient;
    char color[2];
    bool ready[2];
    char point1[15][15],point2[15][15],point3[15][15];
    MsgInfo send_,receive_;

public slots:
    void on_startButton_clicked();
    void on_closeButton_clicked();
};

#endif // MAINWINDOW_H
