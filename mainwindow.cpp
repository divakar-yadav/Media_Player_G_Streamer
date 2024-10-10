#include "MainWindow.h"
#include "SingleVideoPlayerScreen.h"
#include "DualVideoPlayerScreen.h"
#include "CombinedVideoPlayerScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;

    QVBoxLayout *navLayout = new QVBoxLayout;
    QPushButton *singlePlayerButton = new QPushButton("Single Video Player", this);
    QPushButton *dualPlayerButton = new QPushButton("Dual Video Player", this);
    QPushButton *combinedPlayerButton = new QPushButton("Combined Video Player", this);

    navLayout->addWidget(singlePlayerButton);
    navLayout->addWidget(dualPlayerButton);
    navLayout->addWidget(combinedPlayerButton);
    navLayout->addStretch();

    contentWidget = new QWidget(this);
    mainLayout->addLayout(navLayout, 1);
    mainLayout->addWidget(contentWidget, 3);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    resize(screenWidth * 0.7, screenHeight * 0.7);

    connect(singlePlayerButton, &QPushButton::clicked, this, &MainWindow::showSingleVideoPlayer);
    connect(dualPlayerButton, &QPushButton::clicked, this, &MainWindow::showDualVideoPlayer);
    connect(combinedPlayerButton, &QPushButton::clicked, this, &MainWindow::showCombinedVideoPlayer);

    showSingleVideoPlayer();  // Show Single Video Player by default
}

MainWindow::~MainWindow() {}

void MainWindow::clearContentWidget()
{
    QLayout *oldLayout = contentWidget->layout();
    if (oldLayout != nullptr) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }
}

void MainWindow::showSingleVideoPlayer()
{
    clearContentWidget();
    SingleVideoPlayerScreen *screen = new SingleVideoPlayerScreen(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(screen);
    contentWidget->setLayout(layout);
}

void MainWindow::showDualVideoPlayer()
{
    clearContentWidget();
    DualVideoPlayerScreen *screen = new DualVideoPlayerScreen(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(screen);
    contentWidget->setLayout(layout);
}

void MainWindow::showCombinedVideoPlayer()
{
    clearContentWidget();
    CombinedVideoPlayerScreen *screen = new CombinedVideoPlayerScreen(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(screen);
    contentWidget->setLayout(layout);
}
