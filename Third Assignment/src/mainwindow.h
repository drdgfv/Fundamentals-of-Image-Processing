#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <tuple>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    

private slots:

    //Button handlers ==================================
    void onOpen();
    void onSelectTarget();
    void onSave();
    void onReset();

    //Image processing functions handlers =======================
    void mirrorImageX();
    void mirrorImagey();
    tuple<vector<int>,int,int> grayScaleImage(QImage& img_src, QImage& img_dst, QLabel *image_label);
    void quantizationImage(int levels);
    void histogramImage(QImage& img_src, QImage& img_dst, QLabel *image_label);
    void brightnessImage(int brightness);
    void contrastImage(double contrast);
    void negativeImage();
    void equalizationImage();
    void matchingImage();
    void zoomInImage();
    void zoomOutImage();
    void rotateLeftImage();
    void rotateRightImage();
    void convolutionImage();
    void gaussianKernel();
    void laplacianKernel();
    void sobelHxKernel();
    void sobelHyKernel();
    void prewittHxKernel();
    void prewittHyKernel();
    void highPassKernel();

private:

    //GUI components ===============================
    QLabel *rotulo;

    QLineEdit *quantizationLevel;
    QLineEdit *brightnessLevel;
    QLineEdit *contrastLevel;
    QLineEdit *zoomOutSx;
    QLineEdit *zoomOutSy;
    QLineEdit *k00;
    QLineEdit *k01;
    QLineEdit *k02;
    QLineEdit *k10;
    QLineEdit *k11;
    QLineEdit *k12;
    QLineEdit *k20;
    QLineEdit *k21;
    QLineEdit *k22;

    QPushButton *open;
    QPushButton *select_target;
    QPushButton *save;
    QPushButton *reset;
    QPushButton *mirrorX;
    QPushButton *mirrorY;
    QPushButton *grayScale;
    QPushButton *quantization;
    QPushButton *brightness;
    QPushButton *contrast;
    QPushButton *negative;
    QPushButton *equalization;
    QPushButton *matching;
    QPushButton *histogram;
    QPushButton *histogram_target;
    QPushButton *zoomIn;
    QPushButton *zoomOut;
    QPushButton *rotate_left;
    QPushButton *rotate_right;
    QPushButton *convolution;
    QPushButton *gaussian;
    QPushButton *laplacian;
    QPushButton *sobelHx;
    QPushButton *sobelHy;
    QPushButton *prewittHx;
    QPushButton *prewittHy;
    QPushButton *highPass;


    QLabel *imageLabel;
    QLabel *srcImageLabel;
    QLabel *dstImageLabel;
    QLabel *targetImageLabel;
    QLabel *viewTargetLabel;
    QImage image_original;
    QImage image_src;
    QImage image_dst;
    QImage image_target;
    QImage view_target;

    QString fileName;

protected:

    // Key event handlers ================================
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H