/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Sat Sep 1 13:52:13 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *Button0;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *Button4;
    QPushButton *Button_;
    QPushButton *ButtonClr;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Button5;
    QPushButton *Button6;
    QPushButton *Button7;
    QPushButton *Button8;
    QPushButton *Button9;
    QPushButton *ButtonOK;
    QPushButton *ButtonDel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(234, 94);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 61, 16));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 10, 113, 20));
        widget = new QWidget(Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 30, 211, 51));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Button0 = new QPushButton(widget);
        Button0->setObjectName(QString::fromUtf8("Button0"));

        horizontalLayout->addWidget(Button0);

        Button1 = new QPushButton(widget);
        Button1->setObjectName(QString::fromUtf8("Button1"));

        horizontalLayout->addWidget(Button1);

        Button2 = new QPushButton(widget);
        Button2->setObjectName(QString::fromUtf8("Button2"));

        horizontalLayout->addWidget(Button2);

        Button3 = new QPushButton(widget);
        Button3->setObjectName(QString::fromUtf8("Button3"));

        horizontalLayout->addWidget(Button3);

        Button4 = new QPushButton(widget);
        Button4->setObjectName(QString::fromUtf8("Button4"));

        horizontalLayout->addWidget(Button4);

        Button_ = new QPushButton(widget);
        Button_->setObjectName(QString::fromUtf8("Button_"));

        horizontalLayout->addWidget(Button_);

        ButtonClr = new QPushButton(widget);
        ButtonClr->setObjectName(QString::fromUtf8("ButtonClr"));

        horizontalLayout->addWidget(ButtonClr);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Button5 = new QPushButton(widget);
        Button5->setObjectName(QString::fromUtf8("Button5"));

        horizontalLayout_2->addWidget(Button5);

        Button6 = new QPushButton(widget);
        Button6->setObjectName(QString::fromUtf8("Button6"));

        horizontalLayout_2->addWidget(Button6);

        Button7 = new QPushButton(widget);
        Button7->setObjectName(QString::fromUtf8("Button7"));

        horizontalLayout_2->addWidget(Button7);

        Button8 = new QPushButton(widget);
        Button8->setObjectName(QString::fromUtf8("Button8"));

        horizontalLayout_2->addWidget(Button8);

        Button9 = new QPushButton(widget);
        Button9->setObjectName(QString::fromUtf8("Button9"));

        horizontalLayout_2->addWidget(Button9);

        ButtonOK = new QPushButton(widget);
        ButtonOK->setObjectName(QString::fromUtf8("ButtonOK"));

        horizontalLayout_2->addWidget(ButtonOK);

        ButtonDel = new QPushButton(widget);
        ButtonDel->setObjectName(QString::fromUtf8("ButtonDel"));

        horizontalLayout_2->addWidget(ButtonDel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "\350\276\223\345\205\245IP\357\274\232", 0, QApplication::UnicodeUTF8));
        Button0->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        Button1->setText(QApplication::translate("Dialog", "1", 0, QApplication::UnicodeUTF8));
        Button2->setText(QApplication::translate("Dialog", "2", 0, QApplication::UnicodeUTF8));
        Button3->setText(QApplication::translate("Dialog", "3", 0, QApplication::UnicodeUTF8));
        Button4->setText(QApplication::translate("Dialog", "4", 0, QApplication::UnicodeUTF8));
        Button_->setText(QApplication::translate("Dialog", ".", 0, QApplication::UnicodeUTF8));
        ButtonClr->setText(QApplication::translate("Dialog", "clr", 0, QApplication::UnicodeUTF8));
        Button5->setText(QApplication::translate("Dialog", "5", 0, QApplication::UnicodeUTF8));
        Button6->setText(QApplication::translate("Dialog", "6", 0, QApplication::UnicodeUTF8));
        Button7->setText(QApplication::translate("Dialog", "7", 0, QApplication::UnicodeUTF8));
        Button8->setText(QApplication::translate("Dialog", "8", 0, QApplication::UnicodeUTF8));
        Button9->setText(QApplication::translate("Dialog", "9", 0, QApplication::UnicodeUTF8));
        ButtonOK->setText(QApplication::translate("Dialog", "ok", 0, QApplication::UnicodeUTF8));
        ButtonDel->setText(QApplication::translate("Dialog", "del", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
