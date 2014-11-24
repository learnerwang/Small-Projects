#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ip="127.0.0.1";
    ui->lineEdit->setText(ip);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Button0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"0");
}

void Dialog::on_Button1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"1");
}

void Dialog::on_Button2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"2");
}

void Dialog::on_Button3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"3");
}

void Dialog::on_Button4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"4");
}

void Dialog::on_Button5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"5");
}

void Dialog::on_Button6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"6");
}

void Dialog::on_Button7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"7");
}

void Dialog::on_Button8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"8");
}

void Dialog::on_Button9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"9");
}

void Dialog::on_ButtonClr_clicked()
{
    ui->lineEdit->clear();
}

void Dialog::on_ButtonDel_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().remove(ui->lineEdit->text().length()-1,1));
}

void Dialog::on_ButtonOK_clicked()
{
   ip=ui->lineEdit->text();
   this->accept();
}

void Dialog::on_Button__clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+".");
}
