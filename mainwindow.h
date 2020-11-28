#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apilisttreeview.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ApiListTreeView *m_pApiListTreeView;
};

#endif // MAINWINDOW_H
