#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QStatusBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadImage(QString const&);
    void box(QString const&);
    void renderImage();

    int reflect(int M, int x);

private slots:
    void on_LoadFileButton_clicked();

    void on_TestButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat m_image;

    QString fileName = "";
};

#endif // MAINWINDOW_H
