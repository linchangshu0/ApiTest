#ifndef SERVERCONFIGDIALOG_H
#define SERVERCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ServerConfigDialog;
}

class ServerConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConfigDialog(QWidget *parent = nullptr);
    ~ServerConfigDialog();
    QString GetServerName();
    QString GetServerDesc();

private slots:
    void on_ok_clicked();

    void on_cancle_clicked();

private:
    Ui::ServerConfigDialog *ui;
};

#endif // SERVERCONFIGDIALOG_H
