#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QPixmap>
#include <QTimer>
#include <QPixmap>
cv::Mat resim;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    tmrTimer = new QTimer(this); //zamanlama
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));//tmrTimer i process.. bağlama.
    tmrTimer->start(20);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFrameAndUpdateGUI()
{

cv::Mat cikis;
    cv::Mat resim=cv::imread("C:/Users/samar/Desktop/image/indir.jpg");
    cv::resize(resim, resim, cv::Size(300, 300), 0, 0, CV_INTER_LINEAR);
  cvtColor(resim, resim, CV_BGR2RGBA);
   // threshold(resim, cikis, 200, 255, CV_THRESH_BINARY);
   Canny(resim, resim, 10, 255);
 QImage imdisplay((uchar*)resim.data, resim.cols, resim.rows, resim.step, QImage::Format_RGB888);
 QImage imdisplay2((uchar*)cikis.data, cikis.cols, cikis.rows, cikis.step, QImage::Format_RGB888);
   ui->label->setPixmap(QPixmap::fromImage(imdisplay));
     ui->label->setPixmap(QPixmap::fromImage(imdisplay2));
}


void MainWindow::on_pushButton_clicked()
{
    if(tmrTimer->isActive()==true)
    {
        tmrTimer->stop();
        ui->pushButton->setText("Resume");
    }else
    {
    tmrTimer->start(20);
    ui->pushButton->setText("Pause");
    }
}

