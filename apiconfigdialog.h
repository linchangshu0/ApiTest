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

private slots:
    void on_ok_clicked();

    void on_cancle_clicked();

    void on_requestMethod_currentIndexChanged(int index);

private:
    Ui::ApiConfigDialog *ui;
    int     m_eRequestType;
    int     m_eParamsType;
};

#endif // APICONFIGDIALOG_H
