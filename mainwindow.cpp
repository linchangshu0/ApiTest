#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pApiListTreeView(nullptr)
{
    ui->setupUi(this);

    m_pApiListTreeView = new ApiTreeView();

    setCentralWidget(m_pApiListTreeView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
