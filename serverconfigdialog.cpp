#include "serverconfigdialog.h"
#include "ui_serverconfigdialog.h"

#include <QMessageBox>

ServerConfigDialog::ServerConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfigDialog)
{
    ui->setupUi(this);
}

ServerConfigDialog::~ServerConfigDialog()
{
    delete ui;
}

QString ServerConfigDialog::GetServerName() {
    return ui->serverName->text();
}

void ServerConfigDialog::on_ok_clicked()
{
    if (ui->serverName->text().isEmpty()) {
        QMessageBox msg;
        msg.setWindowTitle("提示");
        msg.setText("请输入服务名");
        msg.addButton("确定", QMessageBox::AcceptRole);
        msg.exec();
        return;
    }
    accept();
}

void ServerConfigDialog::on_cancle_clicked()
{
    reject();
}
