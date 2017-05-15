#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>

#include <iostream>

cv::Mat normalize(cv::Mat img) {
    // normalize image
    double minVal, maxVal;
    cv::minMaxLoc(img, &minVal, &maxVal);
    cv::Mat out;
    img.convertTo(out, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    return out;
}

cv::Mat diffImg(cv::Mat img, int x, int y) {
    // convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // compute derivative
    cv::Mat imgDiff;
    cv::Sobel(gray, imgDiff, CV_16S, x, y);

    return imgDiff;
}

cv::Mat diffx(cv::Mat img) {
    // compute x derivative
    return diffImg(img, 1, 0);
}

cv::Mat diffy(cv::Mat img) {
    // compute y derivative
    return diffImg(img, 0, 1);
}

cv::Mat magnitude(cv::Mat img) {
    cv::Mat gradX = diffx(img);
    cv::Mat gradY = diffy(img);
    cv::Mat absGradX, absGradY, grad;
    cv::convertScaleAbs(gradX, absGradX);
    cv::convertScaleAbs(gradY, absGradY);
    cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);
    return grad;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // read an image
    cv::Mat image = cv::imread("C:/Users/tedad/OneDrive/Dokumente/ocv1/woman.png" , 1 );
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", normalize(diffx(image)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
