#include "apiconfigdialog.h"
#include "ui_apiconfigdialog.h"
#include "common.h"

#include <QMessageBox>

ApiConfigDialog::ApiConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApiConfigDialog)
{
    ui->setupUi(this);

    ui->requestMethod->addItem("GET");
    ui->requestMethod->addItem("POST");
    ui->requestMethod->setCurrentIndex(0);

    ui->jsonEdit->hide();
}

ApiConfigDialog::~ApiConfigDialog()
{
    delete ui;
}

QString ApiConfigDialog::GetApiName() {
     return ui->describe->text();
}

QString ApiConfigDialog::GetUrl() {
    return ui->url->text();
}

int ApiConfigDialog::GetRequestType() {
    return m_eRequestType;
}

int ApiConfigDialog::GetParamsType() {
    return m_eParamsType;
}

void ApiConfigDialog::SetApiName(QString &s) {
    ui->apiName->setText(s);
}

void ApiConfigDialog::SetUrl(QString &s) {
    ui->url->setText(s);
}

void ApiConfigDialog::SetRequestType(int t) {
    ui->requestMethod->setCurrentIndex(t);
}

void ApiConfigDialog::SetParamsType(int t) {
    if (t == PARAM_NONE) {
        ui->paramNone->setChecked(true);
    } else if (t == PARAM_JSON) {
        ui->paramJson->setChecked(true);
    } else if (t == PARAM_FORMDATA) {
        ui->paramFormData->setChecked(true);
    }
}

void ApiConfigDialog::SetParams(QJsonObject &obj) {

}

void ApiConfigDialog::on_ok_clicked()
{
    if (ui->describe->text().isEmpty()) {
        QMessageBox msg;
        msg.setWindowTitle("提示");
        msg.setText("请输入描述");
        msg.addButton("确定", QMessageBox::AcceptRole);
        msg.exec();
        return;
    }
    accept();
}

void ApiConfigDialog::on_cancle_clicked()
{
    reject();
}

void ApiConfigDialog::on_requestMethod_currentIndexChanged(int index)
{
    if (index == 0) {
        m_eRequestType = REQUEST_GET;
    } else if (1 == index) {
        m_eRequestType = REQUEST_POST;
    } else if (2 == index) {
        m_eRequestType = REQUEST_OPTIONS;
    } else if (3 == index) {
        m_eRequestType = REQUEST_DELETE;
    } else if (4 == index) {
        m_eRequestType = REQUEST_UPDATE;
    }
}

void ApiConfigDialog::on_paramJson_toggled(bool checked)
{
    if (checked) {
        ui->jsonEdit->show();
    } else {
        ui->jsonEdit->hide();
    }
}
