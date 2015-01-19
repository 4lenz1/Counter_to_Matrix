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

    int border = detailList.at(0).toInt();
    vector<vector<string> > vec( border, vector<string>(border));



    // the stupidest way to initial vector with 0
    for (int i = 0 ; i < border ; i++)
        for (int j = 0 ; j < border ; j++)
            vec[i][j] = "0";


    // testing vector output

    //    for (int i = 0 ; i < border ; i++)
    //        {
    //            for (int j = 0 ; j < border ; j++)
    //                cout << setw(3) << vec[i][j];
    //            cout << endl;
    //        }




    while (!in.atEnd()) {
        //
        QStringList lineList = in.readLine().split(" ");
        int row = lineList.at(0).toInt();
        int col = lineList.at(1).toInt();
        string val = lineList.at(2).toStdString();
        vec[row][col] = val;
    }

    string filePath = QFileDialog::getSaveFileName(this, tr("Save File to"),
                                                   "",
                                                   tr("csv (*csv*)")).toStdString();

//    std::ofstream outputFile(filePath);
//    std::ostream_iterator<string > output_iterator(outputFile, "\n");
//    std::copy(vec.begin() , vec.end(), output_iterator);


//    QFile saveFile(QString::fromStdString(filePath));
//    saveFile.open(QIODevice::WriteOnly);
//    QDataStream out(&saveFile);

    fstream fp;
      string bufferLine[border];
     string buffer ;
    fp.open(filePath , ios::out | ios::app);
    if( !fp){
        qDebug () << "fail to open file"   ;
    }
    for (int i = 0 ; i < border ; i++)
    {
        for (int j = 0 ; j < border ; j++){

//            fp << (vec[i][j] == 0) ? "0"  : vec[i][j]  ;
//            fp  << " ";



//            if (vec[i][j] =="")
//               fp<< vec[i][j] = "0";
//            else
//                fp << vec[i][j] + " ";
           buffer += vec[i][j] + ",";



            //string out = vec[i][j] + ",";
            //fp << out;
        }

        buffer.resize(buffer.size() - 1 );
        //bufferLine[i] = buffer ;
        fp <<buffer;
        fp << endl;
      //  qDebug()  << QString::fromStdString( bufferLine[i]) << "\n" ;
        buffer.erase(buffer.begin() , buffer.end());
    }


    fp.close();

//        ofstream output_file("example.txt");
//        ostream_iterator<string > output_iterator(output_file, "\n");
//    for(int i = 0 ; i < border ; i++)
//         copy(  vec.begin() , vec.end(), output_iterator);

        //    for(const auto& vt : vec) {
    //         std::copy(vt.cbegin(), vt.cend(),
    //               std::ostream_iterator<int>(std::cout, " "));
    //         std::cout << '\n';
    //    }

    //ofstream outputFile("text.csv");

}
