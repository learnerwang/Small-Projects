#include "mainwindow.h"
#include "ui_mainwindow.h"

DWORD WINAPI WorkerThread(LPVOID lpParam);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(640,420);
    myDialog = new Dialog();
    white = QPixmap(":/img/white.jpg");
    black = QPixmap(":/img/black.jpg");
    memset(point,0,sizeof(point));
    f=false;
    lastx=0;lasty=0;
    win=0;lose=0;ping=0;
    ready=false;
    oppo=false;
    hui=0;
    this->setMouseTracking(true);
    str="";
    time= new QTimer;
    start = false;
    time->start(1000);
    ui->centralWidget->setMouseTracking(true);
    ui->startButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->huiButton->setEnabled(false);
    ui->heButton->setEnabled(false);
    ui->loseButton->setEnabled(false);
    ui->changeButton->setEnabled(false);
    connect(time,SIGNAL(timeout()),this,SLOT(changetime()));
    color = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changetime()
{
    if (start)
    {
        if (f)
            {
                ui->timeEdit->setTime(ui->timeEdit->time().addSecs(-1));
                if (ui->timeEdit->time()==ui->timeEdit->minimumTime())
                {
                    //timeout!
                    send_.Msg='T';
                    int j=QMessageBox::information(this,"��ʱ","�㳬ʱ�ˣ�",QMessageBox::Yes);
                    start=false;
                    str="Lose";
                     ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
                }
            }
        else
            {
                ui->timeEdit_2->setTime(ui->timeEdit_2->time().addSecs(-1));
            }
    }
}

void MainWindow::changecolor()
{
    if (color=='W') color='B';
    else color='W';
    lastx=0;
    lasty=0;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    if (str!="")
        {
            if (str=="Win")
                {

                    str="";
                    win++;
                    ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                    ui->textBrowser->append("---Ӯ��һ��---");
                     start = false;ready=false;hui=0;
                     int j=QMessageBox::information(this,"Ӯ�ˣ�","��Ӯ�ˣ�",QMessageBox::Yes);

                    changecolor();
                }
            else if (str=="link")
                {
                    str="";
                    oppo=false;hui=0;ready=false;
                    if (start )
                        {
                            int k=QMessageBox::information(this,"�Է����ߣ�","�Է������ˣ�",QMessageBox::Yes);
                            ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                            ui->textBrowser->append("---Ӯ��һ��---");
                             start = false;ready=false;hui=0;
                             int j=QMessageBox::information(this,"Ӯ�ˣ�","��Ӯ�ˣ�",QMessageBox::Yes);

                            changecolor();
                        }

                }
            else if (str=="time")
                {
                    str="";
                    win++;
                    ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                    ui->textBrowser->append("---Ӯ��һ��---");
                    start = false;ready=false;hui=0;
                    int j=QMessageBox::information(this,"Ӯ�ˣ�","�Է���ʱ����Ӯ�ˣ�",QMessageBox::Yes);
                    changecolor();
                }
            else if (str=="Lose")
                {
                    str="";
                    lose++;
                    ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                    ui->textBrowser->append("---����һ��---");
                    start = false;ready=false;hui=0;
                    int j=QMessageBox::information(this,"���ˣ�","�����ˣ�",QMessageBox::Yes);

                    changecolor();
                }
            else if (str=="He")
                {
                    str="";
                    ping++;
                    ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                    ui->textBrowser->append("---����һ��---");
                    start = false;ready=false;
                    int j=QMessageBox::information(this,"�;֣�","�;֣�",QMessageBox::Yes);

                    changecolor();
                }
            else if (str=="change")
                {
                    str="";
                    int j=QMessageBox::information(this,"����","�Է�Ҫ�󽻻����ӣ��Ƿ�ͬ�⣿",QMessageBox::Yes|QMessageBox::No);
                    if (j==QMessageBox::Yes) change=1;
                    else change =2;
                }
            else if (str=="lose")
                {
                    str="";
                    win++;
                    ui->mylabel->setText(QString("%1ʤ%2��%3ƽ").arg(win).arg(lose).arg(ping));
                    ui->textBrowser->append("---Ӯ��һ��---");
                    start = false;ready=false;hui=0;
                    int j=QMessageBox::information(this,"Ӯ�ˣ�","�Է����䣬��Ӯ�ˣ�",QMessageBox::Yes);

                    changecolor();
                }
            else if (str=="he")
                {
                    str="";
                    int j=QMessageBox::information(this,"���","�Է�������ͣ��Ƿ�ͬ�⣿",QMessageBox::Yes|QMessageBox::No);
                    if (j==QMessageBox::Yes) he=1;
                    else he =2;
                }
            else if (str=="hui")
                {
                    str="";
                    int j=QMessageBox::information(this,"���","�Է�Ҫ����壬�Ƿ�ͬ�⣿",QMessageBox::Yes|QMessageBox::No);
                    if (j==QMessageBox::Yes) huiq=1;
                    else huiq =2;
                }
            else if (str=="error")
            {
                str="";
                ui->linkButton->setEnabled(true);

            }
            else
                {
                    ui->textBrowser->append(str);
                    str="";
                }
        }
    str="";
    if (start)
    {
        ui->startButton->setEnabled(false);
        ui->loseButton->setEnabled(true);
        ui->sendButton->setEnabled(true);
        ui->changeButton->setEnabled(false);
        if (hui==1)
            ui->huiButton->setEnabled(true);
        else ui->huiButton->setEnabled(false);
        ui->heButton->setEnabled(true);
    }
    else
    {
         if (ready)
            ui->startButton->setEnabled(false);
         else if (oppo) ui->startButton->setEnabled(true);
         else ui->startButton->setEnabled(false);
         ui->loseButton->setEnabled(false);
         if (oppo)
             ui->sendButton->setEnabled(true);
         else ui->sendButton->setEnabled(false);
         if (oppo)
             ui->changeButton->setEnabled(true);
         else ui->changeButton->setEnabled(false);
         ui->huiButton->setEnabled(false);
         ui->heButton->setEnabled(false);
    }
    if (color == 'W')
    {
        ui->myPic->setPixmap(white);
        ui->yourPic->setPixmap(black);
    }
    else if (color == 'B')
    {
        ui->myPic->setPixmap(black);
        ui->yourPic->setPixmap(white);
    }
    QPainter p(this);
    p.setBrush(Qt::yellow);
    p.drawRect(10,10,370,370);
    int i,j;
    for (i=0;i<14;i++)
        for (j=0;j<14;j++)
            p.drawRect(20+i*25,20+j*25,25,25);
    p.setBrush(Qt::black);
    p.drawEllipse(90,90,10,10);
    p.drawEllipse(90,290,10,10);
    p.drawEllipse(190,190,10,10);
    p.drawEllipse(290,290,10,10);
    p.drawEllipse(290,90,10,10);
    if (rx*ry!=0){
    if (color == 'B')
    {
        p.setBrush(Qt::black);
        p.setOpacity(0.5);
        p.drawEllipse(20+rx*25-10,20+ry*25-10,20,20);
        p.setOpacity(1);
    }
    else if (color == 'W')
    {
        p.setBrush(Qt::white);
        p.setOpacity(0.5);
        p.drawEllipse(20+rx*25-10,20+ry*25-10,20,20);
        p.setOpacity(1);
    }
    }
    for (i=1;i<=13;i++)
        for (j=1;j<=13;j++)
            if (point[i][j]=='W')
            {
                p.setBrush(Qt::white);
                p.drawEllipse(20+i*25-10,20+j*25-10,20,20);
            }
            else if (point[i][j]=='B')
            {
                p.setBrush(Qt::black);
                p.drawEllipse(20+i*25-10,20+j*25-10,20,20);
            }
    if (lastx*lasty!=0)
        {
            p.setPen(Qt::red);
            p.drawLine(20+lastx*25,20+lasty*25-5,20+lastx*25,20+lasty*25+5);
            p.drawLine(20+lastx*25-5,20+lasty*25,20+lastx*25+5,20+lasty*25);
            p.setPen(Qt::black);
        }
    //[i,j]:: (20+i*25-12,20+i*25-12,24,24)
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    int x1=ev->x();
    int y1=ev->y();
    rx=0;ry=0;
    for (int i1=1;i1<=13;i1++)
        for (int j1=1;j1<=13;j1++)
        {
            int x2=20+i1*25,y2=20+j1*25;
            if (abs(x1-x2)<=12 && abs(y1-y2)<=12)
                {
                    rx=i1;ry=j1;
                    update();
                    return;
                }
        }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if (f&&(point[rx][ry]==0)&&(rx*ry!=0))
    {
            send_.x=rx;
            send_.y=ry;
            point[rx][ry]=color;
            for (int i=0;i<15;i++)
                for (int j=0;j<15;j++)
                    send_.point[i][j]=point[i][j];
            send_.Msg='X';
            ui->textBrowser->append(QString("�������ӣ�[%1,%2]").arg(rx).arg(ry));
            ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
            start = true;
            hui=1;
            f=false;
            return;
    }
}

void MainWindow::on_startButton_clicked()
{
    ready=true;
    send_.Msg='R';
    ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
}

void MainWindow::on_linkButton_clicked()
{
    if (myDialog->exec()==QDialog::Rejected) return;

    QByteArray ba = myDialog->ip.toLatin1();
    const char * IP_ADDRESS = ba.data();
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
        qDebug()<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
        return ;
    }

    //Create Socket
    ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if ( ClientSocket == INVALID_SOCKET )
    {
        qDebug()<<"Create Socket Failed::"<<GetLastError()<<endl;
        ui->textBrowser->append("Create Socket Failed");
        return ;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(6000);
    memset(ServerAddr.sin_zero, 0x00, 8);

    int Ret = ::connect(ClientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
    if ( Ret == SOCKET_ERROR )
    {
        qDebug()<<"Connect Error::"<<GetLastError()<<endl;
        ui->textBrowser->append("Connect Error");
        return ;
    }
    else
    {
        qDebug()<<"���ӳɹ�! �ȴ���Ϣ����"<<endl;
        memset(point,0,sizeof(point));
        ui->textBrowser->append("���ӳɹ�!");
        CreateThread(NULL, 0, WorkerThread, (LPVOID)this, 0, NULL);
    }
    ui->linkButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->huiButton->setEnabled(false);
    ui->heButton->setEnabled(false);
    ui->loseButton->setEnabled(false);
    ui->changeButton->setEnabled(false);
}

void MainWindow::on_changeButton_clicked()
{
    int j=QMessageBox::information(this,"����","�Ƿ�Ҫ��Է��������ӣ�",QMessageBox::Yes|QMessageBox::No);
    if (j==QMessageBox::Yes)
        {
            send_.Msg='C';
            ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
        }
}

void MainWindow::on_heButton_clicked()
{
    int j=QMessageBox::information(this,"���","�Ƿ�Ҫ��Է���ͣ�",QMessageBox::Yes|QMessageBox::No);
    if (j==QMessageBox::Yes)
        {
            send_.Msg='H';
            ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
        }
}

void MainWindow::on_loseButton_clicked()
{
    int j=QMessageBox::information(this,"����","���Ҫ������",QMessageBox::Yes|QMessageBox::No);
    if (j==QMessageBox::Yes)
        {
            send_.Msg='L';
            ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
            str="Lose";
        }


}

void MainWindow::on_sendButton_clicked()
{
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    const char * sendMsg = ba.data();
    memset(send_.message,0,sizeof(send_.message));
    strcpy(send_.message,sendMsg);
    send_.Msg='S';
    ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
    ui->textBrowser->append(QString("��˵:%1").arg(QString(sendMsg)));
    ui->lineEdit->clear();
}

void MainWindow::on_huiButton_clicked()
{
    int j=QMessageBox::information(this,"����","ȷ��Ҫ������",QMessageBox::Yes|QMessageBox::No);
    if (j==QMessageBox::Yes)
        {
            send_.Msg='U';
            ::send(ClientSocket,(const char *)&send_,sizeof(MsgInfo),0);
        }
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    if (start)
    {
        int j=QMessageBox::warning(this,"�˳�","������Ϸ�С��˳�ϵͳ���ж��Է�Ϊʤ���Ƿ�ȷ���˳���",QMessageBox::Yes|QMessageBox::No);
        if (j==QMessageBox::Yes)
            ev->accept();
        else ev->ignore();
    }
    else
    {
        int j=QMessageBox::warning(this,"�˳�","���Ҫ�˳���",QMessageBox::Yes|QMessageBox::No);
        if (j==QMessageBox::Yes)
            ev->accept();
        else ev->ignore();
    }
}

DWORD WINAPI WorkerThread(LPVOID lpParam)
{
        int            i;
        int            ret;
        char           szMessage[400];
        MainWindow* it = (MainWindow*) lpParam;
        while (true){
               memset(szMessage,0,sizeof(szMessage));
               ret=::recv(it->ClientSocket,szMessage,sizeof(szMessage),0);
               if (ret==0||(ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
               {
                   it->ui->textBrowser->append(QString("��������Ͽ������������ӣ�"));
                   it->str="error";
                   closesocket(it->ClientSocket);
                   it->start=false;
                   it->ready=false;
                   it->oppo=false;
                   break;
                   //
                }
                else
                {
                   MsgInfo *b = (MsgInfo*)szMessage;
                   qDebug()<<b->Msg<<endl;
                   qDebug()<<"received"<<endl;
                   switch (b->Msg)
                   {
                       case 'A':
                       {
                            it->color = 'B';
                            it->f = false;
                            it->oppo = false;
                            it->ui->textBrowser->append("�ȴ����ּ��룡");
                            break;
                       }
                       case 'B':
                       {
                            it->color = 'W';
                            it->f = false;
                            it->oppo = false;
                            it->ui->textBrowser->append("�ȴ����ּ��룡");
                            break;
                       }
                       case 'a':
                       {
                            it->color = 'B';
                            it->f = false;
                            it->oppo = true;
                            it->ui->textBrowser->append("�Ѿ�������Ϸ��");
                            break;
                        }
                       case 'b':
                       {
                            it->color = 'W';
                            it->f = false;
                            it->oppo = true;
                            it->ui->textBrowser->append("�Ѿ�������Ϸ��");
                            break;
                       }
                       case 'O':
                       {
                            it->oppo = true;
                            it->ui->textBrowser->append("�����Ѿ����룡");
                            break;
                       }
                       case 'X':
                       {
                            int i,j;
                            for (i=0;i<14;i++)
                                for (j=1;j<14;j++)
                                    it->point[i][j]=b->point[i][j];
                            it->lastx=b->x;
                            it->lasty=b->y;
                            it->ui->textBrowser->append(QString("�Է����ӣ�[%1,%2]").arg(b->x).arg(b->y));
                            it->f=true;
                            break;
                       }
                       case 'W':
                       {
                            int i,j;
                            it->str="Win";
                            for (i=0;i<14;i++)
                                for (j=1;j<14;j++)
                                    it->point[i][j]=b->point[i][j];
                            it->f=false;
                            break;
                       }
                       case 'L':
                       {
                            int i,j;
                            it->str="Lose";
                            for (i=0;i<14;i++)
                                for (j=1;j<14;j++)
                                    it->point[i][j]=b->point[i][j];
                            //it->ui->textBrowser->append(QString("�Է����ӣ�[%1,%1]").arg(b->x).arg(b->y));
                            it->f=false;
                            break;
                       }
                       case 'R':
                       {
                            it->ui->textBrowser->append("�Է��Ѿ�׼��������");
                            break;
                       }
                       case 'r':
                       {
                            it->ready=false;
                            it->start=true;
                            it->ui->textBrowser->append("˫��׼����������Ϸ��ʼ��");
                            if (it->color=='B') it->f=true;
                            it->ui->timeEdit->setTime(QTime(0,10));
                            it->ui->timeEdit_2->setTime(QTime(0,10));
                            for (int i1=0;i1<15;i1++)
                                for (int j1=0;j1<15;j1++)
                                    it->point[i1][j1]=0;
                            it->hui=0;
                            break;
                        }
                       case 'C':
                       {
                            it->str="change";
                            it->change=0;
                            while (it->change==0) Sleep(100);
                            if (it->change==1)
                            {
                                b->Msg='c';
                                ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                            }
                            else
                            {
                                b->Msg='d';
                                ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                            }
                            break;
                       }
                       case 'c':
                       {
                            if (it->color=='B') it->color='W';
                            else it->color='B';
                            it->ui->textBrowser->append("˫���������ӣ�");
                            it->ready=false;
                            it->start=false;
                            break;
                        }
                       case 'd':
                        {
                           it->ui->textBrowser->append("˫����������ʧ�ܡ�");
                           break;
                        }
                       case 'S':
                       {
                           it->str=(QString("�Է�˵��%1").arg(QString::fromLocal8Bit(b->message)));
                           break;
                       }
                       case 'l':
                       {
                            it->str="lose";
                            break;
                       }
                       case 'H':
                       {
                        it->str="he";
                        it->he=0;
                        while (it->he==0) Sleep(100);
                        if (it->he==1)
                        {
                            b->Msg='h';
                            ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                        }
                        else
                        {
                            b->Msg='i';
                            ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                        }
                        break;
                       }
                       case 'i':
                       {
                            it->ui->textBrowser->append("˫������ʧ�ܡ�");
                            break;
                        }
                       case 'h':
                       {
                          it->str="He";
                          break;
                        }
                       case 'T':
                       {
                            it->str="time";
                            break;
                       }
                       case 'U':
                       {
                            it->huiq=0;
                            it->str="hui";
                            while (it->huiq==0) Sleep(100);
                            if (it->huiq==1)
                            {
                                b->Msg='u';
                                ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                            }
                            else
                            {
                                b->Msg='q';
                                ::send(it->ClientSocket,(const char *)b,sizeof(MsgInfo),0);
                            }
                            break;
                        }
                       case 'u':
                       {
                            for (int i1=0;i1<15;i1++)
                                for (int j1=0;j1<15;j1++)
                                    it->point[i1][j1]=b->point[i1][j1];
                            it->ui->textBrowser->append("���壡");
                            it->lastx=0;it->lasty=0;
                            it->hui=2;
                            break;
                        }
                       case 'q':
                       {
                           it->ui->textBrowser->append("����ʧ�ܣ�");
                           break;
                       }
                       case 'o':
                       {
                            it->str="link";
                            break;
                        }
                   }
                }
        }
        return 0;
}
