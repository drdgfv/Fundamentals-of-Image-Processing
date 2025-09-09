#include "mainwindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QDir>       

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("PhotoINF");
    this->showMaximized();

    rotulo = new QLabel("Open an image", this);
    rotulo->setAlignment(Qt::AlignCenter);

    open = new QPushButton("Open", this);
    save = new QPushButton("Save", this);

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

    QWidget *widgetCentral = new QWidget();
    widgetCentral->setLayout(mainLayout);
    this->setCentralWidget(widgetCentral);

    connect(open, &QPushButton::clicked, this, &MainWindow::onOpen);
    connect(save, &QPushButton::clicked, this, &MainWindow::onSave);
}

MainWindow::~MainWindow()
{
}

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
    // 1. Abre uma caixa de diálogo para o usuário selecionar um arquivo
    QString filePath = QFileDialog::getOpenFileName(
        this,                                                    // Janela pai
        tr("Abrir Imagem"),                                      // Título da caixa de diálogo
        QDir::currentPath() + "/images",                        // Diretório inicial
        tr("Arquivos de Imagem (*.png *.jpg *.jpeg *.bmp)")       // Filtro de arquivos
    );

    // 2. Verifica se o usuário selecionou um arquivo (não clicou em "Cancelar")
    if (!filePath.isEmpty()) {
        // 3. Carrega a imagem selecionada
        if (image_src.load(filePath)) {
            // Copia a imagem de origem para a de destino
            image_dst = image_src; 

            // Atualiza os labels para exibir as imagens
            srcImageLabel->setPixmap(QPixmap::fromImage(image_src));
            dstImageLabel->setPixmap(QPixmap::fromImage(image_dst));

            // Extrai e exibe apenas o nome do arquivo no rótulo
            QFileInfo fileInfo(filePath);
            rotulo->setText(fileInfo.fileName());
            fileName = fileInfo.fileName();
        } else {
            rotulo->setText("Error: Failed to load image.");
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}