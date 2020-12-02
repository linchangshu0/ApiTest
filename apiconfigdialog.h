#ifndef APICONFIGDIALOG_H
#define APICONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ApiConfigDialog;
}

class ApiConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApiConfigDialog(QWidget *parent = nullptr);
    ~ApiConfigDialog();

    QString GetApiName();
    QString GetUrl();
    int GetRequestType();
    int GetParamsType();

    void SetApiName(QString &s);
    void SetUrl(QString &s);
    void SetRequestType(int t);
    void SetParamsType(int t);
    void SetParams(QJsonObject &obj);

private slots:
    void on_ok_clicked();

    void on_cancle_clicked();

    void on_requestMethod_currentIndexChanged(int index);

    void on_paramJson_toggled(bool checked);

private:
    Ui::ApiConfigDialog *ui;
    int     m_eRequestType;
    int     m_eParamsType;
};

#endif // APICONFIGDIALOG_H
