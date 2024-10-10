#include "DualVideoPlayerScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>

DualVideoPlayerScreen::DualVideoPlayerScreen(QWidget *parent)
    : QWidget(parent), videoPath1(""), videoPath2("")
{
    videoPlayer1 = new VideoPlayer(this);
    videoPlayer2 = new VideoPlayer(this);

    pathInput1 = new QLineEdit(this);
    pathInput1->setPlaceholderText("Enter first video file path...");

    pathInput2 = new QLineEdit(this);
    pathInput2->setPlaceholderText("Enter second video file path...");

    playButton = new QPushButton("Play Both Videos", this);
    uploadButton1 = new QPushButton("Upload First Video", this);
    uploadButton2 = new QPushButton("Upload Second Video", this);

    connect(playButton, &QPushButton::clicked, this, &DualVideoPlayerScreen::onLoadAndPlayVideos);
    connect(uploadButton1, &QPushButton::clicked, this, &DualVideoPlayerScreen::onUploadFirstVideo);
    connect(uploadButton2, &QPushButton::clicked, this, &DualVideoPlayerScreen::onUploadSecondVideo);

    // Create sliders for the first video (brightness, contrast, hue, saturation)
    brightnessSlider = new QSlider(Qt::Horizontal, this);
    brightnessSlider->setRange(-100, 100);
    brightnessSlider->setValue(50);  // Default brightness = 0.5
    connect(brightnessSlider, &QSlider::valueChanged, this, &DualVideoPlayerScreen::onBrightnessChanged);

    contrastSlider = new QSlider(Qt::Horizontal, this);
    contrastSlider->setRange(0, 200);
    contrastSlider->setValue(120);  // Default contrast = 1.2
    connect(contrastSlider, &QSlider::valueChanged, this, &DualVideoPlayerScreen::onContrastChanged);

    hueSlider = new QSlider(Qt::Horizontal, this);
    hueSlider->setRange(-100, 100);
    hueSlider->setValue(10);  // Default hue = 0.1
    connect(hueSlider, &QSlider::valueChanged, this, &DualVideoPlayerScreen::onHueChanged);

    saturationSlider = new QSlider(Qt::Horizontal, this);
    saturationSlider->setRange(0, 200);
    saturationSlider->setValue(150);  // Default saturation = 1.5
    connect(saturationSlider, &QSlider::valueChanged, this, &DualVideoPlayerScreen::onSaturationChanged);

    // Create a slider for the second video (gamma)
    gammaSlider = new QSlider(Qt::Horizontal, this);
    gammaSlider->setRange(100, 300);
    gammaSlider->setValue(120);  // Default gamma = 1.2
    connect(gammaSlider, &QSlider::valueChanged, this, &DualVideoPlayerScreen::onGammaChanged);

    // Layout for the first video player and its controls
    QVBoxLayout *controlsLayout1 = new QVBoxLayout;
    controlsLayout1->addWidget(pathInput1);
    controlsLayout1->addWidget(uploadButton1);
    controlsLayout1->addWidget(new QLabel("Brightness"));
    controlsLayout1->addWidget(brightnessSlider);
    controlsLayout1->addWidget(new QLabel("Contrast"));
    controlsLayout1->addWidget(contrastSlider);
    controlsLayout1->addWidget(new QLabel("Hue"));
    controlsLayout1->addWidget(hueSlider);
    controlsLayout1->addWidget(new QLabel("Saturation"));
    controlsLayout1->addWidget(saturationSlider);

    // Layout for the second video player and its controls
    QVBoxLayout *controlsLayout2 = new QVBoxLayout;
    controlsLayout2->addWidget(pathInput2);
    controlsLayout2->addWidget(uploadButton2);
    controlsLayout2->addWidget(new QLabel("Gamma"));
    controlsLayout2->addWidget(gammaSlider);

    // Layout to display both videos side by side
    QHBoxLayout *videoLayout = new QHBoxLayout;
    videoLayout->addWidget(videoPlayer1);
    videoLayout->addWidget(videoPlayer2);

    // Final layout for the entire screen
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(controlsLayout1);
    mainLayout->addLayout(controlsLayout2);
    mainLayout->addWidget(playButton);
    mainLayout->addLayout(videoLayout);
    setLayout(mainLayout);
}

void DualVideoPlayerScreen::onUploadFirstVideo()
{
    videoPath1 = QFileDialog::getOpenFileName(this, "Select First Video", "", "Video Files (*.mp4 *.avi *.mkv);;All Files (*)");
    if (!videoPath1.isEmpty()) {
        pathInput1->setText(videoPath1);
        qDebug() << "Selected first video: " << videoPath1;
    }
}

void DualVideoPlayerScreen::onUploadSecondVideo()
{
    videoPath2 = QFileDialog::getOpenFileName(this, "Select Second Video", "", "Video Files (*.mp4 *.avi *.mkv);;All Files (*)");
    if (!videoPath2.isEmpty()) {
        pathInput2->setText(videoPath2);
        qDebug() << "Selected second video: " << videoPath2;
    }
}

void DualVideoPlayerScreen::onLoadAndPlayVideos()
{
    if (!videoPath1.isEmpty() && !videoPath2.isEmpty()) {
        // Pass the current slider values for the first video
        qDebug() << "Playing first video with adjustments:";
        qDebug() << "Brightness:" << brightness;
        qDebug() << "Contrast:" << contrast;
        qDebug() << "Hue:" << hue;
        qDebug() << "Saturation:" << saturation;

        videoPlayer1->playVideoWithAdjustments(videoPath1, brightness, contrast, hue, saturation);

        // Pass the gamma correction value for the second video
        qDebug() << "Playing second video with gamma correction:";
        qDebug() << "Gamma:" << gamma;

        videoPlayer2->playVideoWithGamma(videoPath2, gamma);

        // Check if pipelines were initialized correctly using the getter method
        if (videoPlayer1->getPipeline() == nullptr) {
            qDebug() << "Error: Failed to initialize GStreamer pipeline for first video.";
        }

        if (videoPlayer2->getPipeline() == nullptr) {
            qDebug() << "Error: Failed to initialize GStreamer pipeline for second video.";
        }
    } else {
        qDebug() << "Error: Both video paths must be selected.";
    }
}

// Slots to handle slider changes for the first video
void DualVideoPlayerScreen::onBrightnessChanged(int value)
{
    brightness = value / 100.0f;
    qDebug() << "Brightness changed: " << brightness;
}

void DualVideoPlayerScreen::onContrastChanged(int value)
{
    contrast = value / 100.0f;
    qDebug() << "Contrast changed: " << contrast;
}

void DualVideoPlayerScreen::onHueChanged(int value)
{
    hue = value / 100.0f;
    qDebug() << "Hue changed: " << hue;
}

void DualVideoPlayerScreen::onSaturationChanged(int value)
{
    saturation = value / 100.0f;
    qDebug() << "Saturation changed: " << saturation;
}

// Slot to handle slider change for the second video (gamma)
void DualVideoPlayerScreen::onGammaChanged(int value)
{
    gamma = value / 100.0f;
    qDebug() << "Gamma changed: " << gamma;
}
