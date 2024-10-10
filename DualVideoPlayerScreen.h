#ifndef DUALVIDEOPLAYERSCREEN_H
#define DUALVIDEOPLAYERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include "VideoPlayer.h"

class DualVideoPlayerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DualVideoPlayerScreen(QWidget *parent = nullptr);

private slots:
    void onUploadFirstVideo();
    void onUploadSecondVideo();
    void onLoadAndPlayVideos();

    // Slot functions for handling slider changes
    void onBrightnessChanged(int value);
    void onContrastChanged(int value);
    void onHueChanged(int value);
    void onSaturationChanged(int value);
    void onGammaChanged(int value);

private:
    QLineEdit *pathInput1;
    QLineEdit *pathInput2;
    QPushButton *playButton;
    QPushButton *uploadButton1;
    QPushButton *uploadButton2;
    VideoPlayer *videoPlayer1;
    VideoPlayer *videoPlayer2;

    // Sliders for the first video
    QSlider *brightnessSlider;
    QSlider *contrastSlider;
    QSlider *hueSlider;
    QSlider *saturationSlider;

    // Slider for the second video (gamma)
    QSlider *gammaSlider;

    // Paths for both videos
    QString videoPath1;
    QString videoPath2;

    // Values for video adjustments
    float brightness = 0.5f;
    float contrast = 1.2f;
    float hue = 0.1f;
    float saturation = 1.5f;
    float gamma = 1.2f;
};

#endif // DUALVIDEOPLAYERSCREEN_H
