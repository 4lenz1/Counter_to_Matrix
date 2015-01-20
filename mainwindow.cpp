#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>
#include <QStringList>

using namespace std;
string arr[81306][81306] ;

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
    qDebug() << "opening file" ;
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

    int border = detailList.at(0).toInt();
    vector<vector<string> > vec( border, vector<string>(border));


    //    //    while (!in.atEnd()) {
    //    //
    //    //        QStringList lineList = in.readLine().split(" ");
    //    //        int row = lineList.at(0).toInt();
    //    //        int col = lineList.at(1).toInt();
    //    //        string val = lineList.at(2).toStdString();
    //    //        vec[row][col] = val;
    //    //    }

    //   // ifstream myfile(ui->lineout->text().toStdString());
    string str;



    //    //    char *chr = "hwllo ";
    //    //    qDebug() << chr;

    qDebug() << "make a array" ;
    int index=  0 ;
    QStringList lineList;
    while(! in.atEnd()){
        //qDebug() << QString::fromStdString(str);
        lineList = QString::fromStdString(in.readLine().toStdString()).split(" ");
        arr[lineList.at(0).toInt()][lineList.at(1).toInt()] = lineList.at(2).toStdString();
        qDebug() << "index : " << index++ ;
        //vec[lineList.at(0).toInt()][lineList.at(1).toInt()] = lineList.at(2).toStdString();
        lineList.clear();
    }
    qDebug() << "read completed" ;

    string filePath = QFileDialog::getSaveFileName(this, tr("Save File to"),
                                                   "",
                                                   tr("csv (*csv*)")).toStdString();
    fstream fp;
    string buffer;


    fp.open(filePath , ios::out | ios::app);
    if( !fp){
        qDebug () << "fail to open file"   ;
        exit(1);
    }
    for (int i = 0 ; i < border ; i++){
        for (int j = 0 ; j < border ; j++){
            buffer += (arr[i][j]=="") ? "0," : arr[i][j] + ",";
        }
        buffer.pop_back();
        fp <<buffer << endl;
        buffer.erase(buffer.begin() , buffer.end());
    }
    fp.close();

    qDebug() << "Done !!" ;
}
