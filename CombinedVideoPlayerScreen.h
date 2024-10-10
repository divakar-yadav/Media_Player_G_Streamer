#ifndef COMBINEDVIDEOPLAYERSCREEN_H
#define COMBINEDVIDEOPLAYERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "VideoPlayer.h"

class CombinedVideoPlayerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CombinedVideoPlayerScreen(QWidget *parent = nullptr);

private slots:
    void onUploadFirstVideo();
    void onUploadSecondVideo();
    void onCombineAndPlayVideos();

private:
    QLineEdit *pathInput1;
    QLineEdit *pathInput2;
    QPushButton *combineButton;
    QPushButton *uploadButton1;
    QPushButton *uploadButton2;
    VideoPlayer *videoPlayer;
    QString videoPath1;
    QString videoPath2;
};

#endif // COMBINEDVIDEOPLAYERSCREEN_H
