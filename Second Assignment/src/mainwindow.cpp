#include <iostream>
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
    rotulo->setStyleSheet("color: rgba(123, 126, 151, 1);");

    quantizationLevel = new QLineEdit(this);
    quantizationLevel->setPlaceholderText("[2-256]");
    quantizationLevel->setFixedWidth(55);

    brightnessLevel = new QLineEdit(this);
    brightnessLevel->setPlaceholderText("[-255,255]");
    brightnessLevel->setFixedWidth(75);

    contrastLevel = new QLineEdit(this);
    contrastLevel->setPlaceholderText("[0,255]");
    contrastLevel->setFixedWidth(55);

    zoomOutSx = new QLineEdit(this);
    zoomOutSx->setPlaceholderText("Sx");
    zoomOutSx->setFixedWidth(20);

    zoomOutSy = new QLineEdit(this);
    zoomOutSy->setPlaceholderText("Sy");
    zoomOutSy->setFixedWidth(20);

    open = new QPushButton("Open", this);
    select_target = new QPushButton("Select Target", this);
    save = new QPushButton("Save", this);
    reset = new QPushButton("Reset", this);

    mirrorX = new QPushButton("mirror in X", this);
    mirrorY = new QPushButton("mirror in Y", this);
    grayScale = new QPushButton("Gray Scale", this);
    quantization = new QPushButton("Quantization", this);
    histogram = new QPushButton("Histogram", this);
    histogram_target = new QPushButton("Histogram Target", this);
    brightness = new QPushButton("Brightness", this);
    contrast = new QPushButton("Contrast", this);
    negative = new QPushButton("Negative", this);
    equalization = new QPushButton("Equalization", this);
    matching = new QPushButton("Matching", this);
    zoomIn = new QPushButton("2x2", this);
    zoomIn->setIcon(QIcon("images/zoom-in.png"));
    zoomOut = new QPushButton("", this);
    zoomOut->setIcon(QIcon("images/zoom-out.png"));
    rotate_left = new QPushButton("", this);
    rotate_left->setIcon(QIcon("images/rotate-ccw.png"));
    rotate_right = new QPushButton("", this);
    rotate_right->setIcon(QIcon("images/rotate-cw.png"));


    image_original = QImage();
    image_src = QImage();
    image_dst = QImage();
    image_target = QImage();

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(QPixmap::fromImage(image_original));

    srcImageLabel = new QLabel(this);
    srcImageLabel->setAlignment(Qt::AlignCenter);
    srcImageLabel->setPixmap(QPixmap::fromImage(image_src));

    dstImageLabel = new QLabel(this);
    dstImageLabel->setAlignment(Qt::AlignCenter);
    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));

    targetImageLabel = new QLabel(this);
    targetImageLabel->setAlignment(Qt::AlignCenter);
    targetImageLabel->setPixmap(QPixmap::fromImage(image_target));

    viewTargetLabel = new QLabel(this);
    viewTargetLabel->setAlignment(Qt::AlignCenter);
    viewTargetLabel->setPixmap(QPixmap::fromImage(image_target));
    targetImageLabel->setMaximumSize(200, 200);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(open);
    topLayout->addWidget(save);
    topLayout->addWidget(rotulo);
    topLayout->addStretch(); 
    topLayout->addWidget(select_target);
    topLayout->addWidget(histogram_target);

    QScrollArea *srcScrollArea = new QScrollArea;
    srcScrollArea->setWidget(srcImageLabel);
    srcScrollArea->setWidgetResizable(true);
    srcScrollArea->setFixedSize(740, 660);

    QScrollArea *dstScrollArea = new QScrollArea;
    dstScrollArea->setWidget(dstImageLabel);
    dstScrollArea->setWidgetResizable(true);
    dstScrollArea->setFixedSize(740, 660);

    QScrollArea *targetArea = new QScrollArea;
    targetArea->setWidget(viewTargetLabel);
    targetArea->setWidgetResizable(true);
    targetArea->setFixedSize(230, 200);

    QHBoxLayout *imagesLayout = new QHBoxLayout;
    imagesLayout->addWidget(srcScrollArea);
    imagesLayout->addWidget(targetArea);
    imagesLayout->addWidget(dstScrollArea);

    QHBoxLayout *OperationsLayout = new QHBoxLayout;
    OperationsLayout->addWidget(mirrorX);
    OperationsLayout->addWidget(mirrorY);
    OperationsLayout->addWidget(grayScale);
    OperationsLayout->addWidget(quantization);
    OperationsLayout->addWidget(quantizationLevel);
    OperationsLayout->addWidget(brightness);
    OperationsLayout->addWidget(brightnessLevel);
    OperationsLayout->addWidget(contrast);
    OperationsLayout->addWidget(contrastLevel);
    OperationsLayout->addWidget(negative);
    OperationsLayout->addWidget(equalization);
    OperationsLayout->addWidget(matching);
    OperationsLayout->addWidget(zoomIn);
    OperationsLayout->addWidget(zoomOut);
    OperationsLayout->addWidget(zoomOutSx);
    OperationsLayout->addWidget(zoomOutSy);
    OperationsLayout->addWidget(rotate_left);
    OperationsLayout->addWidget(rotate_right);
    OperationsLayout->addStretch();
    OperationsLayout->addWidget(histogram);
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
    connect(select_target, &QPushButton::clicked, this, &MainWindow::onSelectTarget);
    connect(save, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(mirrorX, &QPushButton::clicked, this, &MainWindow::mirrorImageX);
    connect(mirrorY, &QPushButton::clicked, this, &MainWindow::mirrorImagey);
    connect(grayScale, &QPushButton::clicked, this, [this]() {
        grayScaleImage(image_src, image_dst, dstImageLabel);
    });
    connect(quantization, &QPushButton::clicked, this, &MainWindow::quantizationImage);
    connect(brightness, &QPushButton::clicked, this, &MainWindow::brightnessImage);
    connect(contrast, &QPushButton::clicked, this, &MainWindow::contrastImage);
    connect(negative, &QPushButton::clicked, this, &MainWindow::negativeImage);
    connect(equalization, &QPushButton::clicked, this, &MainWindow::equalizationImage);
    connect(histogram, &QPushButton::clicked, this, [this]() {
        histogramImage(image_src, image_dst, dstImageLabel);
    });
    connect(histogram_target, &QPushButton::clicked, this, [this]() {
        histogramImage(image_target, image_target, targetImageLabel);
    });
    connect(matching, &QPushButton::clicked, this, &MainWindow::matchingImage);
    connect(reset, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(zoomIn, &QPushButton::clicked, this, &MainWindow::zoomInImage);
    connect(zoomOut, &QPushButton::clicked, this, &MainWindow::zoomOutImage);
    connect(rotate_left, &QPushButton::clicked, this, &MainWindow::rotateLeftImage);
    connect(rotate_right, &QPushButton::clicked, this, &MainWindow::rotateRightImage);
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

void MainWindow::onSelectTarget()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,                                                    
        tr("Select Target Image"),                                      
        QDir::currentPath() + "/images",                        
        tr("Image Files (*.png *.jpg *.jpeg *.bmp)")
    );

    if (!filePath.isEmpty()) {
        if (image_target.load(filePath)) {

            QPixmap pixmap = QPixmap::fromImage(image_target);
            QPixmap scaledPixmap = pixmap.scaled(targetImageLabel->maximumSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            targetImageLabel->setPixmap(QPixmap::fromImage(image_target));
            viewTargetLabel->setPixmap(scaledPixmap);

            rotulo->setText("Target image loaded.");
        } else {
            rotulo->setText("Error: Failed to load target image.");
        }
    }
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

tuple<vector<int>,int,int> MainWindow::grayScaleImage(QImage& img_src, QImage& img_dst, QLabel *image_label)
{
    vector <int> histogram(256, 0);

    if (img_src.isNull()) {
        rotulo->setText("Warning: No image loaded to convert to gray scale!");
        return {histogram,-1,-1};
    }

    unsigned char *p_src, *p_dst;
    int max_gray = 255;
    int min_gray = 0;
    
    p_src = img_src.bits();
    p_dst = img_dst.bits();

    for (int i = 0; i < img_src.height(); i++){
        for (int j = 0; j < img_src.width(); j++){
            int gray = (int)(0.299 * p_src[2] + 0.587 * p_src[1] + 0.114 * p_src[0]);
            p_dst[0] = p_dst[1] = p_dst[2] = gray;

            histogram[gray]++;

            if(gray > max_gray) max_gray = gray;
            if(gray < min_gray) min_gray = gray;

            p_src += 4;
            p_dst += 4;
        }
    }

    image_label->setPixmap(QPixmap::fromImage(img_dst));
    img_src = img_dst;

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

    auto [histogram, min_gray, max_gray] = grayScaleImage(image_src, image_dst, dstImageLabel);

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

void MainWindow::histogramImage(QImage& img_src, QImage& img_dst, QLabel *image_label)
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to generate histogram!");
        return;
    }

    QImage img_before_gray = image_src;
    auto [histogram, min_gray, max_gray] = grayScaleImage(img_src, img_dst, image_label);

    image_label->setPixmap(QPixmap::fromImage(img_before_gray));
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
    dialog->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);


    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->resize(1000, 500);
    dialog->show();

    rotulo->setText("Histogram generated!");
}

void MainWindow::brightnessImage(int brightness)
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to adjust brightness!");
        return;
    }

    brightness = brightnessLevel->text().toInt();

    if (brightness < -255 || brightness > 255) {
        rotulo->setText("Error: Brightness must be between -255 and 255.");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            int r = std::clamp(static_cast<int>(p_src[2]) + brightness, 0, 255);
            int g = std::clamp(static_cast<int>(p_src[1]) + brightness, 0, 255);
            int b = std::clamp(static_cast<int>(p_src[0]) + brightness, 0, 255);

            p_dst[2] = static_cast<unsigned char>(r);
            p_dst[1] = static_cast<unsigned char>(g);
            p_dst[0] = static_cast<unsigned char>(b);

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image brightness adjusted!");
}

void MainWindow::contrastImage(double contrast)
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to adjust contrast!");
        return;
    }

    contrast = contrastLevel->text().toFloat();

    if (contrast < 0 || contrast > 255) {
        rotulo->setText("Error: Contrast must be between 0 and 255.");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
            float r = std::clamp(static_cast<int>(p_src[2]) * contrast, 0.0, 255.0);
            float g = std::clamp(static_cast<int>(p_src[1]) * contrast, 0.0, 255.0);
            float b = std::clamp(static_cast<int>(p_src[0]) * contrast, 0.0, 255.0);

            p_dst[2] = static_cast<unsigned char>(int(r));
            p_dst[1] = static_cast<unsigned char>(int(g));
            p_dst[0] = static_cast<unsigned char>(int(b));

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image contrast adjusted!");
}

void MainWindow::negativeImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to adjust negative!");
        return;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){

            p_dst[2] = 255 - p_src[2];
            p_dst[1] = 255 - p_src[1];
            p_dst[0] = 255 - p_src[0];

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image negative adjusted!");
}

void MainWindow::equalizationImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to equalize!");
        return;
    }

    auto [histogram, min_gray, max_gray] = grayScaleImage(image_src, image_dst, dstImageLabel);

    int total_pixels = image_src.width() * image_src.height();
    vector<int> hist_cum(256, 0);

    double alpha = 255.0 / total_pixels;

    hist_cum[0] = histogram[0];

    for (int i = 1; i < 256; i++) {
        hist_cum[i] = hist_cum[i - 1] + histogram[i];
    }

    for (int i = 1; i < 256; i++) {
        hist_cum[i] = static_cast<int>(hist_cum[i] * alpha);
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){

            int gray = (int)(0.299 * p_src[2] + 0.587 * p_src[1] + 0.114 * p_src[0]);
            p_dst[0] = p_dst[1] = p_dst[2] = static_cast<unsigned char>(hist_cum[gray]);

            p_src += 4;
            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image equalized!");
}

void MainWindow::matchingImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: Two images are required for matching!");
        return;
    }

    if (image_target.isNull()) {
        rotulo->setText("Warning: Two images are required for matching!");
        return;
    }

    auto [hist_src, min_gray_src, max_gray_src] = grayScaleImage(image_src, image_dst, dstImageLabel);
    auto [hist_target, min_gray_target, max_gray_target] = grayScaleImage(image_target, image_target, targetImageLabel);

    vector<double> hist_cum_src(256, 0);
    vector<double> hist_cum_target(256, 0);
    vector<double> hm(256, 0);

    hist_cum_src[0] = hist_src[0];
    hist_cum_target[0] = hist_target[0];

    for (int i = 1; i < 256; i++) {
        hist_cum_src[i] = hist_cum_src[i - 1] + hist_src[i];
        hist_cum_target[i] = hist_cum_target[i - 1] + hist_target[i];
    }

    int total_pixels_src = image_src.width() * image_src.height();
    int total_pixels_target = image_target.width() * image_target.height();

    for (int i = 1; i < 256; i++) {
        hist_cum_src[i] = hist_cum_src[i]/total_pixels_src;
        hist_cum_target[i] = hist_cum_target[i]/total_pixels_target;
    }


    for (int shade_level = 0; shade_level < 256; ++shade_level) {
        double min_diff = abs(hist_cum_src[shade_level] - hist_cum_target[0]);
        double closest = 0;
        for (int target_level = 1; target_level < 256; ++target_level) {
            double diff = abs(hist_cum_src[shade_level] - hist_cum_target[target_level]);
            if (diff < min_diff) {
                min_diff = diff;
                closest = target_level;
            }
        }
        hm[shade_level] = closest;
    }

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < image_src.height(); i++){
        for (int j = 0; j < image_src.width(); j++){
    
            double gray = (int)(0.299 * p_src[2] + 0.587 * p_src[1] + 0.114 * p_src[0]);
            double matched_gray = hm[gray];
            p_dst[0] = p_dst[1] = p_dst[2] = static_cast<unsigned char>(matched_gray);

            p_src += 4;
            p_dst += 4;
        }
    }


    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Images matched!");

}

void MainWindow::zoomOutImage(){

    auto [sx,sy] = make_pair(zoomOutSx->text().toInt(), zoomOutSy->text().toInt());

    int srcWidth = image_src.width();
    int srcHeight = image_src.height();

    if(sx == 0 || sy == 0) {
        rotulo->setText("Error: Sx and Sy are undefiened.");
        return;
    }

    int dstWidth = (srcWidth + sx - 1) / sx;
    int dstHeight = (srcHeight + sy - 1) / sy;

    image_dst = QImage(dstWidth, dstHeight, image_src.format()); 

    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to zoom out!");
        return;
    }

    unsigned char *p_src, *p_dst;

    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < dstHeight; i++){
        for (int j = 0; j < dstWidth; j++ ){

            int r=0, g=0, b=0, pixels=0, av_r=0, av_g=0, av_b=0;
            int srcStartX = j * sx;
            int srcStartY = i * sy;

            for (int y = srcStartY; y<srcStartY+sy && y<srcHeight; y++){
                for (int x = srcStartX; x<srcStartX+sx && x<srcWidth; x++){

                    const unsigned char *p_current_src = p_src + (y * image_src.width() * 4) + (x * 4);

                    r += p_current_src[2];
                    g += p_current_src[1];
                    b += p_current_src[0];
                    pixels++;
                }
            }


            if(pixels!=0){
                av_r = r/pixels;
                av_g = g/pixels;
                av_b = b/pixels;
            }

            p_dst[2] = static_cast<unsigned char>(av_r);
            p_dst[1] = static_cast<unsigned char>(av_g);
            p_dst[0] = static_cast<unsigned char>(av_b);

            p_dst += 4;
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image zoomed out!");
}

void MainWindow::zoomInImage(){
    
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to zoom in!");
        return;
    }
    
    int srcWidth = image_src.width();
    int srcHeight = image_src.height();

    image_dst = QImage(srcWidth+srcWidth-1, srcHeight+srcHeight-1, image_src.format());
    
    int dstWidth = image_dst.width();
    int dstHeight = image_dst.height();

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < srcHeight; i++){
        for (int j = 0; j < srcWidth; j++){

            unsigned char *p_dst_row = p_dst + (i * 2) * dstWidth * 4 + (j * 2) * 4;

            p_dst_row[2] = p_src[2];
            p_dst_row[1] = p_src[1];
            p_dst_row[0] = p_src[0];

            p_src+=4;
        }
    }

    p_dst = image_dst.bits();

    for (int i = 0; i < dstHeight; i+=2){
        for (int j = 1; j<dstWidth; j+=2){

            unsigned char *p_current_dst = p_dst + i * dstWidth * 4 + j * 4;
            unsigned char *p_left_dst = p_current_dst - 4;
            unsigned char *p_right_dst = p_current_dst + 4;

            p_current_dst[2] = (p_left_dst[2] + p_right_dst[2]) * 0.5;
            p_current_dst[1] = (p_left_dst[1] + p_right_dst[1]) * 0.5;
            p_current_dst[0] = (p_left_dst[0] + p_right_dst[0]) * 0.5;
        }
    }

    p_dst = image_dst.bits();

    for (int i = 1; i < dstHeight-1; i+=2){
        for (int j = 0; j < dstWidth; j++){

            unsigned char *p_current_dst = p_dst + i * dstWidth * 4 + j * 4;
            unsigned char *p_above_dst = p_current_dst - dstWidth * 4;
            unsigned char *p_below_dst = p_current_dst + dstWidth * 4;

            p_current_dst[2] = (p_above_dst[2] + p_below_dst[2]) * 0.5;
            p_current_dst[1] = (p_above_dst[1] + p_below_dst[1]) * 0.5;
            p_current_dst[0] = (p_above_dst[0] + p_below_dst[0]) * 0.5;
        }
    }


    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image zoomed in!");
}

void MainWindow::rotateLeftImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to rotate!");
        return;
    }

    int srcWidth = image_src.width();
    int srcHeight = image_src.height();

    image_dst = QImage(srcHeight, srcWidth, image_src.format()); 

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < srcHeight; i++){
        for (int j = 0; j < srcWidth; j++ ){

            unsigned char *p_current_src = p_src + (i * srcWidth * 4) + (j * 4);
            unsigned char *p_current_dst = p_dst + ((srcWidth - 1 - j) * srcHeight * 4) + (i * 4);

            p_current_dst[2] = p_current_src[2];
            p_current_dst[1] = p_current_src[1];
            p_current_dst[0] = p_current_src[0];
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image rotated left!");
}

void MainWindow::rotateRightImage()
{
    if (image_src.isNull()) {
        rotulo->setText("Warning: No image loaded to rotate!");
        return;
    }

    int srcWidth = image_src.width();
    int srcHeight = image_src.height();

    image_dst = QImage(srcHeight, srcWidth, image_src.format()); 

    unsigned char *p_src, *p_dst;
    
    p_src = image_src.bits();
    p_dst = image_dst.bits();

    for (int i = 0; i < srcHeight; i++){
        for (int j = 0; j < srcWidth; j++ ){

            unsigned char *p_current_src = p_src + (i * srcWidth * 4) + (j * 4);
            unsigned char *p_current_dst = p_dst + (j * srcHeight * 4) + ((srcHeight - 1 - i) * 4);

            p_current_dst[2] = p_current_src[2];
            p_current_dst[1] = p_current_src[1];
            p_current_dst[0] = p_current_src[0];
        }
    }

    dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));
    image_src = image_dst;

    rotulo->setText("Image rotated right!");
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