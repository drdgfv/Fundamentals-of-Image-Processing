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
    void onOpen();
    void onSave();
    void onMirrorX();
    void onMirrorY();
    void mirrorImageX();
    void mirrorImagey();

private:
    QLabel *rotulo;
    QPushButton *open;
    QPushButton *save;
    QPushButton *mirrorX;
    QPushButton *mirrorY;
    QLabel *srcImageLabel;
    QLabel *dstImageLabel;
    QImage image_src;
    QImage image_dst;
    QString fileName;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H