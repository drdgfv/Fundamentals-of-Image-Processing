#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

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
    void onMirrorX();
    void onMirrorY();
    void onGrayScale();
    void onQuantization();

    //Image processing functions =======================
    void mirrorImageX();
    void mirrorImagey();
    void grayScaleImage();
    void quantizationImage(int levels);


private:

    //GUI components ===============================
    QLabel *rotulo;
    QPushButton *open;
    QPushButton *save;
    QPushButton *mirrorX;
    QPushButton *mirrorY;
    QPushButton *grayScale;
    QPushButton *quantization;
    QLabel *srcImageLabel;
    QLabel *dstImageLabel;
    QImage image_src;
    QImage image_dst;
    QString fileName;

protected:

    // Key event handlers ================================
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H