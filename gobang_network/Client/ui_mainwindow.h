/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Sep 1 22:09:52 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QGroupBox *groupBox;
    QLabel *myPic;
    QLabel *mylabel;
    QLabel *label;
    QLabel *label_2;
    QTimeEdit *timeEdit;
    QGroupBox *groupBox_2;
    QLabel *yourPic;
    QLabel *label_3;
    QTimeEdit *timeEdit_2;
    QTextBrowser *textBrowser;
    QPushButton *linkButton;
    QPushButton *startButton;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *changeButton;
    QPushButton *huiButton;
    QPushButton *loseButton;
    QPushButton *heButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 420);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMouseTracking(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/Five.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 370, 370));
        frame->setMouseTracking(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(390, 10, 240, 80));
        myPic = new QLabel(groupBox);
        myPic->setObjectName(QString::fromUtf8("myPic"));
        myPic->setGeometry(QRect(180, 10, 50, 50));
        mylabel = new QLabel(groupBox);
        mylabel->setObjectName(QString::fromUtf8("mylabel"));
        mylabel->setGeometry(QRect(160, 60, 61, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 60, 61, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 54, 12));
        timeEdit = new QTimeEdit(groupBox);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setEnabled(false);
        timeEdit->setGeometry(QRect(20, 40, 71, 22));
        timeEdit->setAutoFillBackground(true);
        timeEdit->setKeyboardTracking(false);
        timeEdit->setTime(QTime(0, 10, 0));
        timeEdit->setCurrentSection(QDateTimeEdit::SecondSection);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(390, 100, 240, 80));
        yourPic = new QLabel(groupBox_2);
        yourPic->setObjectName(QString::fromUtf8("yourPic"));
        yourPic->setGeometry(QRect(180, 10, 50, 50));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 54, 12));
        timeEdit_2 = new QTimeEdit(groupBox_2);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));
        timeEdit_2->setEnabled(false);
        timeEdit_2->setGeometry(QRect(20, 40, 71, 22));
        timeEdit_2->setAutoFillBackground(true);
        timeEdit_2->setKeyboardTracking(false);
        timeEdit_2->setTime(QTime(0, 10, 0));
        timeEdit_2->setCurrentSection(QDateTimeEdit::MinuteSection);
        yourPic->raise();
        label_2->raise();
        label_3->raise();
        timeEdit_2->raise();
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(390, 190, 241, 191));
        linkButton = new QPushButton(centralWidget);
        linkButton->setObjectName(QString::fromUtf8("linkButton"));
        linkButton->setGeometry(QRect(10, 390, 75, 23));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(90, 390, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(390, 390, 191, 20));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(584, 390, 51, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 390, 141, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        changeButton = new QPushButton(layoutWidget);
        changeButton->setObjectName(QString::fromUtf8("changeButton"));

        horizontalLayout->addWidget(changeButton);

        huiButton = new QPushButton(layoutWidget);
        huiButton->setObjectName(QString::fromUtf8("huiButton"));

        horizontalLayout->addWidget(huiButton);

        loseButton = new QPushButton(layoutWidget);
        loseButton->setObjectName(QString::fromUtf8("loseButton"));

        horizontalLayout->addWidget(loseButton);

        heButton = new QPushButton(layoutWidget);
        heButton->setObjectName(QString::fromUtf8("heButton"));

        horizontalLayout->addWidget(heButton);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\224\345\255\220\346\243\213", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\210\221\347\232\204\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        myPic->setText(QString());
        mylabel->setText(QApplication::translate("MainWindow", "0\350\203\2340\350\264\2370\345\271\263", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\347\264\257\347\247\257\350\203\234\350\264\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\345\200\222\350\256\241\346\227\266\357\274\232", 0, QApplication::UnicodeUTF8));
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "mm:ss", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\257\271\346\211\213\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        yourPic->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\345\200\222\350\256\241\346\227\266\357\274\232", 0, QApplication::UnicodeUTF8));
        timeEdit_2->setDisplayFormat(QApplication::translate("MainWindow", "mm:ss", 0, QApplication::UnicodeUTF8));
        linkButton->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213/\345\207\206\345\244\207", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        changeButton->setText(QApplication::translate("MainWindow", "\344\272\244\346\215\242", 0, QApplication::UnicodeUTF8));
        huiButton->setText(QApplication::translate("MainWindow", "\346\202\224\346\243\213", 0, QApplication::UnicodeUTF8));
        loseButton->setText(QApplication::translate("MainWindow", "\350\256\244\350\276\223", 0, QApplication::UnicodeUTF8));
        heButton->setText(QApplication::translate("MainWindow", "\345\222\214\346\243\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
