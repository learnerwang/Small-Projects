#include "mainwindow.h"
#include "ui_mainwindow.h"

DWORD WINAPI WorkerThread(LPVOID lpParam);
DWORD WINAPI acceptThread(LPVOID s);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    nowClient=0;
    numClient=0;
    ui->startButton->setEnabled(false);
    ui->closeButton->setEnabled(true);
    ui->textBrowser->clear();
    WSADATA  Ws;
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
        qDebug()<<"Init Windows Socket Failed::"<<GetLastError();
        exit(1);
    }

    //Get HostIP
    char lv_name[50];
    gethostname(lv_name,50);
    hostent * lv_pHostent;
    lv_pHostent = gethostbyname(lv_name);
    ui->textBrowser_2->setText(inet_ntoa(*(struct in_addr *)*lv_pHostent->h_addr_list));

    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if ( ServerSocket == INVALID_SOCKET )
    {
        qDebug()<<"Create Socket Failed::"<<GetLastError();
        ui->textBrowser->append(QString("Create Socket Failed::"+GetLastError()));
        exit(1);
    }

    sockaddr_in LocalAddr;
    LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_addr.S_un.S_addr= htonl(INADDR_ANY);
    LocalAddr.sin_port = htons(6000);
    memset(LocalAddr.sin_zero, 0x00, 8);

    //Bind Socket
    int Ret = bind(ServerSocket, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
    if ( Ret != 0 )
    {
        qDebug()<<"Bind Socket Failed::"<<GetLastError();
        ui->textBrowser->append(QString("Bind Socket Failed::"+GetLastError()));
        exit(1);
    }

    Ret = listen(ServerSocket, 10);
    if ( Ret != 0 )
    {
        qDebug()<<"listen Socket Failed::"<<GetLastError();
        ui->textBrowser->append(QString("listen Socket Failed::"+GetLastError()));
        exit(1);
    }

    qDebug()<<"服务端已经启动，等待客户端连接！";
    ui->textBrowser->append(QString("服务端已经启动，等待客户端连接！"));

    HANDLE acThread = NULL;
    acThread = CreateThread(NULL, 0, acceptThread, (LPVOID)this, 0, NULL);
    if ( acThread == NULL )
    {
        qDebug()<<"Create acceptThread Failed!";
        ui->textBrowser->append(QString("Create acceptThread Failed!"));
        return;
    }
    CloseHandle(acThread);
}

void MainWindow::on_closeButton_clicked()
{
    ui->closeButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->textBrowser_2->clear();
    ui->textBrowser->append(QString("服务器已经关闭！"));
    closesocket(ServerSocket);
    WSACleanup();
}

DWORD WINAPI acceptThread(LPVOID s)
{
    MainWindow *sw = static_cast<MainWindow*>(s);

    SOCKET ClientSocket;
    struct sockaddr_in ClientAddr;

    CreateThread(NULL, 0, WorkerThread, (LPVOID)s, 0, NULL);

    while ( true )
    {

        int AddrLen = sizeof(ClientAddr);
        ClientSocket = accept(sw->ServerSocket, (struct sockaddr*)&ClientAddr, &AddrLen);
        if ( ClientSocket == INVALID_SOCKET )
        {
            //sw->ui->textBrowser->append("")
            break;
        }

        sw->ui->textBrowser->append(QString("客户端连接::%1:%2").arg(inet_ntoa(ClientAddr.sin_addr)).arg(ClientAddr.sin_port));
        sw->ClientSocket[(sw->nowClient+sw->numClient)%2]=ClientSocket;
        sw->ready[(sw->nowClient+sw->numClient)%2]=false;
        sw->numClient++;
        if (sw->numClient == 1)
        {
            sw->send_.Msg='A';
            sw->color[(sw->nowClient+sw->numClient-1)%2]='B';
            ::send(ClientSocket,(const char *)&sw->send_,sizeof(MsgInfo),0);
        }
        else
        {
            int now=(sw->nowClient+sw->numClient)%2;
            if (sw->color[now]=='B')
                {
                    sw->color[(now+1)%2]='W';
                    sw->send_.Msg='b';
                }
            else
                {
                    sw->color[(now+1)%2]='B';
                    sw->send_.Msg='a';
                }
            ::send(ClientSocket,(const char *)&sw->send_,sizeof(MsgInfo),0);
            sw->send_.Msg='O';
            ::send(sw->ClientSocket[now],(const char *)&sw->send_,sizeof(MsgInfo),0);
        }
    }

    return 1;
}

DWORD WINAPI WorkerThread(LPVOID lpParam)
{
        int            i;
        fd_set         fdread;
        int            ret;
        struct timeval tv = {1, 0};
        char           szMessage[400];
        MainWindow* it = (MainWindow*) lpParam;
        while (true){
                if (it->numClient == 0)
                {
                        Sleep(100);
                        continue;
                }
                FD_ZERO(&fdread);
                for (i = 0; i<it->numClient; i++)
                {
                        FD_SET(it->ClientSocket[(i+it->nowClient)%2], &fdread);
                }

                // We only care read event
                ret = select(0, &fdread, NULL, NULL, &tv);

                if (ret == 0)
                {
                  // Timeout
                  continue;
                }

                for (i= 0 ; i<it->numClient;i++)
                {
                    memset(szMessage,0,sizeof(szMessage));
                    if (!FD_ISSET(it->ClientSocket[(i+it->nowClient)%2], &fdread)) continue;
                    ret=recv(it->ClientSocket[(i+it->nowClient)%2],szMessage,sizeof(szMessage),0);
                    if (ret==0||(ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
                    {
                        it->ui->textBrowser->append(QString("Client socket %1 closed.").arg(i));
                        closesocket(it->ClientSocket[(i+it->nowClient)%2]);
                        if (i==0) it->nowClient=(it->nowClient+1)%2;
                        it->numClient--;
                        if (it->numClient==1)
                        {
                            MsgInfo*b=(MsgInfo*)szMessage;
                            b->Msg='o';
                            ::send(it->ClientSocket[(i+it->nowClient)%2],(const char *)b,sizeof(MsgInfo),0);
                            if (it->color[(i+it->nowClient)%2]=='W')
                                it->color[(i+it->nowClient)%2]='B';
                            else it->color[(i+it->nowClient)%2]='W';
                        }
                        break;
                        //
                    }
                    else
                    {
                      MsgInfo *b = (MsgInfo*)szMessage;
                      if (b->Msg=='X')
                      {
                        int l,j,k;
                        bool win = false;
                        bool ping=true;
                        for (l=1;l<=13;l++)
                            for (j=1;j<=13;j++)
                                if (b->point[l][j]==0) {ping = false;break;}
                        if (ping)
                            {
                                int now=(i+it->nowClient+1)%2;
                                b->Msg='h';
                                ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                                ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                                break;
                            }
                        for (l=1;l<=13;l++)
                            for (j=1;j<=9;j++)
                                {
                                    bool flag=true;
                                    if (b->point[l][j]==0) continue;
                                    for (k=1;k<5;k++)
                                        if (b->point[l][j+k]!=b->point[l][j])
                                            {
                                                flag=false;
                                                break;
                                            }
                                    if (flag)
                                        {
                                            win=true;
                                            break;
                                        }
                                }
                        for (l=1;l<=9;l++)
                            for (j=1;j<=13;j++)
                                {
                                    bool flag=true;
                                    if (b->point[l][j]==0) continue;
                                    for (k=1;k<5;k++)
                                        if (b->point[l+k][j]!=b->point[l][j])
                                            {
                                                flag=false;
                                                break;
                                            }
                                    if (flag)
                                        {
                                            win=true;
                                            break;
                                        }
                                }
                        for (l=1;l<=13;l++)
                            for (j=1;j<=13;j++)
                            {
                                if (l+4>13 || j+4>13) continue;
                                bool flag=true;
                                if (b->point[l][j]==0) continue;
                                for (k=1;k<5;k++)
                                    if (b->point[l+k][j+k]!=b->point[l][j])
                                    {
                                        flag=false;
                                        break;
                                    }
                                if (flag)
                                    {
                                        win=true;
                                        break;
                                    }
                            }
                        for (l=1;l<=13;l++)
                            for (j=1;j<=13;j++)
                            {
                                if (l-4<1 || j+4>13) continue;
                                bool flag=true;
                                if (b->point[l][j]==0) continue;
                                for (k=1;k<5;k++)
                                    if (b->point[l-k][j+k]!=b->point[l][j])
                                    {
                                        flag=false;
                                        break;
                                    }
                                if (flag)
                                    {
                                        win=true;
                                        break;
                                    }
                            }
                        int now = (it->nowClient+i+1)%2;
                        if (win)
                            {
                                b->Msg = 'W';
                                ::send(it->ClientSocket[(i+it->nowClient)%2],(const char *)b,sizeof(MsgInfo),0);
                                b->Msg = 'L';
                                ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                                if (it->color[(i+it->nowClient)%2]=='W')
                                    it->color[(i+it->nowClient)%2]='B';
                                else it->color[(i+it->nowClient)%2]='W';
                                if (it->color[(i+it->nowClient+1)%2]=='W')
                                    it->color[(i+it->nowClient+1)%2]='B';
                                else it->color[(i+it->nowClient+1)%2]='W';
                            }
                        else
                            {
                                qDebug()<<now<<" "<<(i+it->nowClient)%2<<endl;
                                b->Msg = 'X';
                                it->ui->textBrowser->append(QString(now));
                                ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                            }
                        int i1,j1;
                        for (i1=0;i1<15;i1++)
                            for (j1=0;j1<15;j1++)
                                {

                                    it->point1[i1][j1]=it->point2[i1][j1];
                                    it->point2[i1][j1]=it->point3[i1][j1];
                                    it->point3[i1][j1]=b->point[i1][j1];
                                }
                    }
                      else if (b->Msg =='R')
                      {
                          int now=(i+it->nowClient)%2;
                          it->ready[now]=true;
                          if (it->ready[(now+1)%2]==true)
                          {
                               b->Msg='r';
                               ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                               ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                               it->ready[now]=false;
                               it->ready[(now+1)%2]=false;
                          }
                          else
                          {
                              b->Msg='R';
                              ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                          }
                      }
                      else if (b->Msg =='C')
                      {
                            int now=(i+it->nowClient+1)%2;
                            b->Msg='C';
                            ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='c')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='c';
                          it->ready[now]=false;
                          it->ready[(now+1)%2]=false;
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='H')
                      {
                            int now=(i+it->nowClient+1)%2;
                            b->Msg='H';
                            ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='h')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='h';
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                          if (it->color[(i+it->nowClient)%2]=='W')
                              it->color[(i+it->nowClient)%2]='B';
                          else it->color[(i+it->nowClient)%2]='W';
                          if (it->color[(i+it->nowClient+1)%2]=='W')
                              it->color[(i+it->nowClient+1)%2]='B';
                          else it->color[(i+it->nowClient+1)%2]='W';
                      }
                      else if (b->Msg =='i')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='i';
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='d')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='d';
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='S')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='S';
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                      }
                      else if (b->Msg =='L')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='l';
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          if (it->color[(i+it->nowClient)%2]=='W')
                              it->color[(i+it->nowClient)%2]='B';
                          else it->color[(i+it->nowClient)%2]='W';
                          if (it->color[(i+it->nowClient+1)%2]=='W')
                              it->color[(i+it->nowClient+1)%2]='B';
                          else it->color[(i+it->nowClient+1)%2]='W';
                      }
                      else if (b->Msg =='T')
                          {
                              int now=(i+it->nowClient+1)%2;
                              b->Msg='T';
                              ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                              if (it->color[(i+it->nowClient)%2]=='W')
                                  it->color[(i+it->nowClient)%2]='B';
                              else it->color[(i+it->nowClient)%2]='W';
                              if (it->color[(i+it->nowClient+1)%2]=='W')
                                  it->color[(i+it->nowClient+1)%2]='B';
                              else it->color[(i+it->nowClient+1)%2]='W';
                          }
                      else if (b->Msg =='U')
                          {
                              int now=(i+it->nowClient+1)%2;
                              b->Msg='U';
                              ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          }
                      else if (b->Msg =='u')
                      {
                          int now=(i+it->nowClient+1)%2;
                          b->Msg='u';
                          int i1,j1;
                          for (i1=0;i1<15;i1++)
                              for (j1=0;j1<15;j1++)
                                  b->point[i1][j1]=it->point1[i1][j1];
                          ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                          ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);

                      }
                      else if (b->Msg =='q')
                          {
                              int now=(i+it->nowClient+1)%2;
                              b->Msg='q';
                              ::send(it->ClientSocket[now],(const char *)b,sizeof(MsgInfo),0);
                              ::send(it->ClientSocket[(now+1)%2],(const char *)b,sizeof(MsgInfo),0);

                          }
                    }

                 }

        }
        return 0;
}
