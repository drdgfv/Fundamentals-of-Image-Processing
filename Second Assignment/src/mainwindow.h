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
    void onSave();
    void onReset();

    //Image processing functions handlers =======================
    void mirrorImageX();
    void mirrorImagey();
    tuple<vector<int>,int,int> grayScaleImage();
    void quantizationImage(int levels);
    void histogramImage();
    void brightnessImage(int brightness);
    void contrastImage(double contrast);
    void negativeImage();


private:

    //GUI components ===============================
    QLabel *rotulo;
    QLineEdit *quantizationLevel;
    QLineEdit *brightnessLevel;
    QLineEdit *contrastLevel;
    QPushButton *open;
    QPushButton *save;
    QPushButton *reset;
    QPushButton *mirrorX;
    QPushButton *mirrorY;
    QPushButton *grayScale;
    QPushButton *quantization;
    QPushButton *brightness;
    QPushButton *contrast;
    QPushButton *negative;
    QPushButton *histogram;
    QLabel *imageLabel;
    QLabel *srcImageLabel;
    QLabel *dstImageLabel;
    QImage image_original;
    QImage image_src;
    QImage image_dst;
    QString fileName;

protected:

    // Key event handlers ================================
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H