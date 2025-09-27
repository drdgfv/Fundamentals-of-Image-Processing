#include "mainwindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QDir>     
#include <QLineEdit>
#include <tuple>
#include <QScrollArea>
#include <QtCharts>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

using namespace std;


// Constructor =====================================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("PhotoINF");
    this->showMaximized();

    rotulo = new QLabel("Open an image", this);
    rotulo->setAlignment(Qt::AlignCenter);

    quantizationLevel = new QLineEdit(this);
    quantizationLevel->setPlaceholderText("Q-Levels (2-256)");
    quantizationLevel->setFixedWidth(150);

    open = new QPushButton("Open", this);
    save = new QPushButton("Save", this);
    reset = new QPushButton("Reset", this);

    mirrorX = new QPushButton("mirror in X", this);
    mirrorY = new QPushButton("mirror in Y", this);
    grayScale = new QPushButton("Gray Scale", this);
    quantization = new QPushButton("Quantization", this);
    histogram = new QPushButton("Histogram", this);

    image_original = QImage();
    image_src = QImage();
    image_dst = QImage();

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(QPixmap::fromImage(image_original));

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

    QScrollArea *srcScrollArea = new QScrollArea;
    srcScrollArea->setWidget(srcImageLabel);
    srcScrollArea->setWidgetResizable(true);
    srcScrollArea->setFixedSize(740, 660);

    QScrollArea *dstScrollArea = new QScrollArea;
    dstScrollArea->setWidget(dstImageLabel);
    dstScrollArea->setWidgetResizable(true);
    dstScrollArea->setFixedSize(740, 660);


    QHBoxLayout *imagesLayout = new QHBoxLayout;
    imagesLayout->addWidget(srcScrollArea);
    imagesLayout->addWidget(dstScrollArea);


    QHBoxLayout *OperationsLayout = new QHBoxLayout;
    OperationsLayout->addWidget(mirrorX);
    OperationsLayout->addWidget(mirrorY);
    OperationsLayout->addWidget(grayScale);
    OperationsLayout->addWidget(quantization);
    OperationsLayout->addWidget(quantizationLevel);
    OperationsLayout->addWidget(histogram);
    OperationsLayout->addStretch();
    OperationsLayout->addWidget(reset);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout); 
    mainLayout->addStretch();
    mainLayout->addLayout(imagesLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(OperationsLayout);
    

    QWidget *widgetCentral = new QWidget();
    widgetCentral->setLayout(mainLayout);
    this->setCentralWidget(widgetCentral);

    connect(open, &QPushButton::clicked, this, &MainWindow::onOpen);
    connect(save, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(mirrorX, &QPushButton::clicked, this, &MainWindow::mirrorImageX);
    connect(mirrorY, &QPushButton::clicked, this, &MainWindow::mirrorImagey);
    connect(grayScale, &QPushButton::clicked, this, &MainWindow::grayScaleImage);
    connect(quantization, &QPushButton::clicked, this, &MainWindow::quantizationImage);
    connect(histogram, &QPushButton::clicked, this, &MainWindow::histogramImage);
    connect(reset, &QPushButton::clicked, this, &MainWindow::onReset);
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

    if (image_dst.save(savePath, "JPEG")) {
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
            image_original = image_src;

            srcImageLabel->setPixmap(QPixmap::fromImage(image_src));
            dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
            imageLabel->setPixmap(QPixmap::fromImage(image_original));

            QFileInfo fileInfo(filePath);
            rotulo->setText(fileInfo.fileName());
            fileName = fileInfo.fileName();
        } else {
            rotulo->setText("Error: Failed to load image.");
        }
    }
}

void MainWindow::onReset()
{
    if (image_original.isNull()) {
        rotulo->setText("Warning: No image loaded to reset!");
        return;
    }

    image_src = image_dst = image_original;

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    dstImageLabel->setPixmap(QPixmap::fromImage(image_src));

    rotulo->setText("Image reset to original!");
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

tuple<vector<int>,int,int> MainWindow::grayScaleImage()
{
    vector <int> histogram(256, 0);

    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to convert to gray scale!");
        return {histogram,-1,-1};
    }

    unsigned char *p_src, *p_dst;
    int max_gray = 255;
    int min_gray = 0;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            int gray = (int)(0.299 * p_src[2] + 0.587 * p_src[1] + 0.114 * p_src[0]);
            p_dst[0] = p_dst[1] = p_dst[2] = gray;

            histogram[gray]++;

            if(gray > max_gray) max_gray = gray;
            if(gray < min_gray) min_gray = gray;

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image converted to gray scale!");

    return {histogram, min_gray, max_gray};
}

void MainWindow::quantizationImage(int levels)
{

    levels = quantizationLevel->text().toInt();

    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to quantize!");
        return;
    }

    if (levels < 2 || levels > 256) {
        rotulo->setText("Error: Levels must be between 2 and 256.");
        return;
    }

    auto [histogram, min_gray, max_gray] = grayScaleImage();

    int range_grays = max_gray - min_gray + 1;

    if (range_grays < levels) {
        rotulo->setText("Warning: The image already has fewer gray levels than requested.");
        return; 
    }

    unsigned char *p_src, *p_dst;

    p_src = image_src.bits();
    p_dst = image_dst.bits();

    float tam_int = (float)range_grays/levels;

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            
            int bin = (int)((p_src[0] - min_gray) / tam_int);
            auto head_bin = min_gray + bin*tam_int;
            auto tail_bin = head_bin + tam_int;

            int gray = (int)((head_bin + tail_bin)/2);
            
            p_dst[0] = p_dst[1] = p_dst[2] = gray;

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image quantized!");
}

void MainWindow::histogramImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to generate histogram!");
        return;
    }

    QImage img_before_gray = image_src;
    auto [histogram, min_gray, max_gray] = grayScaleImage();

    dstImageLabel->setPixmap(QPixmap::fromImage(img_before_gray));
    image_src = img_before_gray;

    int max_value = *std::max_element(histogram.begin(), histogram.end());

    QBarSet *set = new QBarSet("Gray Levels");
    set->setColor(Qt::darkBlue);
    for (int i = 0; i < 256; ++i){
        double normalized = max_value > 0 ? static_cast<double>(histogram[i]) / max_value : 0.0;
        *set << normalized;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Histogram");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i = 0; i < 256; i++)
        categories << QString::number(i);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Histogram");

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->resize(1000, 500);
    dialog->show();

    rotulo->setText("Histogram generated!");
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