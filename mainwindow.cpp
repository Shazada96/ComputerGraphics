/// @author Shazada
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



void MainWindow::loadImage(QString const& path)
{
    std::string file = path.toStdString(); //Convert QString to stdstring
    m_image = cv::imread(file);            // Open existing image

    if(m_image.empty())
    {
        box("File Not Found!");
        return;                            //Go back without opening empty image!
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadFileButton_clicked()
{
    //Load user file from dialog
    QString path = QFileDialog::getOpenFileName(this, "Open File", "C:/Users/tedad/OneDrive/Dokumente/ocv1", tr("Image (*.jpg *.png)"));

    //Make sure the path has a value (no value if user exits dialog)
    if(path != "")
    {
        //Load file info and save file name
        QFileInfo info(path);
        fileName = info.fileName();

        //Load image from path and render image
        loadImage(path);
        renderImage();
    }
}

void MainWindow::renderImage()
{
     //Convert cv image -> QImage -> QPixmap
    QImage img((uchar*)m_image.data, m_image.cols, m_image.rows, m_image.step, QImage::Format_RGB888);
    QPixmap pic = QPixmap::fromImage(img);

    //Store dimensions
    int width  = pic.width();
    int height = pic.height();

    int labelWidth = ui->Image->width();
    int labelHeight = ui->Image->height();

    //Scale pic and apply to our Image label
    ui->Image->setPixmap(pic.scaled(labelWidth, labelHeight));

    //Modify file information text
    ui->fileName->setText(fileName + "(" + QString::number(width) + "x" + QString::number(height) + ")");
}

/*int MainWindow::render(int M, int x)
{
    if(x < 0)
        return - x - 1;
    if(x>=M)
        return 2*M - x - 1;
    return x;
}*/

void MainWindow::on_TestButton_clicked()
{
    loadImage("C:/Users/tedad/OneDrive/Dokumente/ocv1/eye.png");
    renderImage();
}

void MainWindow::box(QString const& text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();  //Execute box
}

/*
 *
    cv::namedWindow("Image");              // Create a new window...

    cv::imshow( "Image", image );          // ... and show image in it

    // Wait for keystroke
  //  cv::waitKey(0);
  */
