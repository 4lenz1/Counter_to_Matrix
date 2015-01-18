#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
using namespace std;
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

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this , "About Qt");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this , "About 4lenz1" , "For BIG data final homework !!!!!\npingfallenzone@gmail.com\n4lenz1");
}

void MainWindow::on_btnOpen_clicked()
{
    string filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   "",
                                                   tr("txt (*txt*)")).toStdString();
    ui->lineout->setText(QString::fromStdString(filePath));

}

void MainWindow::on_btnClick_clicked()
{
    if(ui->lineout->text() == ""){
        on_btnOpen_clicked();
    }

    QFile file(ui->lineout->text());
    QTextStream in(&file);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "get error when oping file : " << ui->lineout->text();
        exit(1);
    }

    string martixDetail = in.readLine().toStdString();
    QStringList detailList =  QString::fromStdString( martixDetail ).split(" ");
    qDebug() << "row :" << detailList.at(0)
             << "\ncol :" << detailList.at(1)
             << "\nquantity :" << detailList.at(2);
//    while (!in.atEnd()) {

//    }
}
