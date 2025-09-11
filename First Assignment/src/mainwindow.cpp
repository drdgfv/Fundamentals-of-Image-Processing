#include "mainwindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QDir>       


// Constructor =====================================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("PhotoINF");
    this->showMaximized();

    rotulo = new QLabel("Open an image", this);
    rotulo->setAlignment(Qt::AlignCenter);

    open = new QPushButton("Open", this);
    save = new QPushButton("Save", this);
    mirrorX = new QPushButton("mirror in X", this);
    mirrorY = new QPushButton("mirror in Y", this);
    grayScale = new QPushButton("Gray Scale", this);
    quantization = new QPushButton("Quantization", this);

    image_src = QImage();
    image_dst = QImage();

    srcImageLabel = new QLabel(this);
    srcImageLabel->setAlignment(Qt::AlignCenter);
    srcImageLabel->setPixmap(QPixmap::fromImage(image_src));

    dstImageLabel = new QLabel(this);
    dstImageLabel->setAlignment(Qt::AlignCenter);
    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(open);
    topLayout->addWidget(save);
    topLayout->addWidget(rotulo);
    topLayout->addStretch(); 

    QHBoxLayout *imagesLayout = new QHBoxLayout;
    imagesLayout->addWidget(srcImageLabel);
    imagesLayout->addWidget(dstImageLabel);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout); 
    mainLayout->addStretch();
    mainLayout->addLayout(imagesLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(mirrorX);
    mainLayout->addWidget(mirrorY);
    mainLayout->addWidget(grayScale);
    mainLayout->addWidget(quantization);

    QWidget *widgetCentral = new QWidget();
    widgetCentral->setLayout(mainLayout);
    this->setCentralWidget(widgetCentral);

    connect(open, &QPushButton::clicked, this, &MainWindow::onOpen);
    connect(save, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(mirrorX, &QPushButton::clicked, this, &MainWindow::mirrorImageX);
    connect(mirrorY, &QPushButton::clicked, this, &MainWindow::mirrorImagey);
    connect(grayScale, &QPushButton::clicked, this, &MainWindow::grayScaleImage);
    connect(quantization, &QPushButton::clicked, this, &MainWindow::quantizationImage);
}

// Destructor ======================================================================================
MainWindow::~MainWindow()
{
}

// Button handlers =================================================================================
void MainWindow::onSave()
{
    if (fileName.isEmpty()) {
        rotulo->setText("Warning: No image loaded to save!");
        return;
    }

    
    QString savePath = QString("images/dst_%1").arg(fileName);

    if (image_dst.save(savePath)) {
        rotulo->setText("Image save as " + QFileInfo(savePath).fileName());
    } else {
        rotulo->setText("Error: Failed to save image.");
    }
}

void MainWindow::onOpen()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,                                                    
        tr("Abrir Imagem"),                                      
        QDir::currentPath() + "/images",                        
        tr("Arquivos de Imagem (*.png *.jpg *.jpeg *.bmp)")       
    );

    if (!filePath.isEmpty()) {
        if (image_src.load(filePath)) {
            image_dst = image_src; 

            srcImageLabel->setPixmap(QPixmap::fromImage(image_src));
            dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));

            QFileInfo fileInfo(filePath);
            rotulo->setText(fileInfo.fileName());
            fileName = fileInfo.fileName();
        } else {
            rotulo->setText("Error: Failed to load image.");
        }
    }
}

void MainWindow::onMirrorX(){
    mirrorImageX();
}

void MainWindow::onMirrorY(){
    mirrorImagey();
}

void MainWindow::onGrayScale(){
    grayScaleImage();
}

void MainWindow::onQuantization(){
    quantizationImage(4);
}

// Image processing functions =====================================================================
void MainWindow::mirrorImageX()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to mirror!");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits() + image_dst.width() * 4 * (image_dst.height()-1);

    for (int i = 0; i < image_src.height(); i++){
        memcpy(p_dst, p_src, image_dst.width() * 4);
        p_src +=  image_dst.width() * 4;
        p_dst -=  image_dst.width() * 4;
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image mirrored!");
}

void MainWindow::mirrorImagey()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to mirror!");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits() + image_dst.width() * 4 - 4;

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            memcpy(p_dst, p_src, 4);
            p_src += 4;
            p_dst -= 4;
        }
        p_dst += 2 * image_dst.width() * 4;
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image mirrored!");
}

void MainWindow::grayScaleImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to convert to gray scale!");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            int gray = (int)(0.299 * p_src[2] + 0.587 * p_src[1] + 0.114 * p_src[0]);
            p_dst[0] = p_dst[1] = p_dst[2] = gray;
            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));

    rotulo->setText("Image converted to gray scale!");
}

void MainWindow::quantizationImage(int levels)
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to quantize!");
        return;
    }

    rotulo->setText("Image quantized!");
}

// Key event handlers ===============================================================================
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}