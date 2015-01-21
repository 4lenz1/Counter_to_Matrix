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
int border ;
string arr[81306] ;
string buffer;
fstream fp;
int row = 0 ;
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


void load(){
    qDebug() << " Load :: Row : " << row ;
    buffer.pop_back();
    fp <<buffer << endl;
    qDebug() << "write line  :" << QString::fromStdString( buffer) ;
    buffer.erase(buffer.begin() , buffer.end());
    row ++;
    for(int index = 0  ; index < border ; index ++)
        arr[index] = '0';
    qDebug() <<"Row Clean !" ;
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
             << "\tcol :" << detailList.at(1)
             << "\tquantity :" << detailList.at(2);

    border = detailList.at(0).toInt();
    qDebug() << "border : " << border ;

    QStringList lineList;
    string filePath = QFileDialog::getSaveFileName(this, tr("Save File to"),
                                                   "",
                                                   tr("csv (*csv*)")).toStdString();

    fp.open(filePath , ios::out | ios::app);
    if( !fp){
        qDebug () << "fail to open file"   ;
        exit(1);
    }

    lineList = in.readLine().split(" ");
    while(! in.atEnd()){
        while(row == lineList.at(0).toInt() ){
            qDebug() << "Row : " << lineList.at(0)
                     <<"\nCol :" << lineList.at(1)
                    <<"\nVal :" << lineList.at(2);
            arr[lineList.at(1).toInt()] = lineList.at(2).toStdString();
            lineList = in.readLine().split(" ");
        }
        qDebug() << " row not match : " << row << " " << lineList.at(0);

        for(int i = 0 ; i  < border ; i ++){
            buffer +=(arr[i]=="") ? "0," : arr[i] + ",";
            //qDebug() << QString::fromStdString( buffer);
        }
        load();
    }// end while atEnd()

    while(row == lineList.at(0).toInt() ){
        qDebug() << "Row : " << lineList.at(0)
                 <<"\nCol :" << lineList.at(1)
                <<"\nVal :" << lineList.at(2);
        arr[lineList.at(1).toInt()] = lineList.at(2).toStdString();
        lineList = in.readLine().split(" ");
    }
    qDebug() << " row not match : " << row << " " << lineList.at(0);

    for(int i = 0 ; i  < border ; i ++){
        buffer +=(arr[i]=="") ? "0," : arr[i] + ",";
       // qDebug() << QString::fromStdString( buffer);
    }
    load();

    if (row <= border){
        for(int i = 0 ; i  < border ; i ++){
            buffer +="0,";
           // qDebug() << QString::fromStdString( buffer);
        }
        load();
    }



    fp.close();
    qDebug() << "Done !!" ;
}
