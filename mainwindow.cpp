#include "mainwindow.h"
#include "resource.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadResource_clicked()
{
    QString ModName     = ui->InputLoadName->toPlainText();
    //QString ModName     = "China_1933";
    QString GameResPath = "/"+ModName;
    Resource RS(ModName);
    RS.GetSelfResNames();
    RS.LoadSelf(GameResPath);
}

void MainWindow::on_SignResource_clicked()
{
    QString ModName = ui->InputSignName->toPlainText();
    QString GameResPath = "/"+ModName;
    Resource RS(ModName);
    RS.GetSelfResNames();
    RS.CleanSelf(GameResPath);
}
