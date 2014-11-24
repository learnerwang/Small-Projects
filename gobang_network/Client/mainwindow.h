#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <dialog.h>
#include <winsock2.h>
#include <Windows.h>
#include <QDebug>
#include <QtGui>

#define PORT 8080

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
    void paintEvent(QPaintEvent *p);
    Dialog *myDialog;
    Ui::MainWindow *ui;
    WSADATA  Ws;
    SOCKET ClientSocket;
    QString str;
    QTimer *time;
    bool start,ready,oppo;
    int hui,he, huiq;
    int win,lose,ping;
    QPixmap white,black;
    struct sockaddr_in ServerAddr;
    char color;
    bool f;
    int change;
    int rx,ry;
    int lastx,lasty;
    char point[15][15];
    MsgInfo send_,receive_;
    void closeEvent(QCloseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void changecolor();

public slots:
    void on_linkButton_clicked();
    void on_startButton_clicked();
    void on_changeButton_clicked();
    void on_sendButton_clicked();
    void on_loseButton_clicked();
    void on_heButton_clicked();
    void on_huiButton_clicked();
    void changetime();
};

#endif // MAINWINDOW_H
