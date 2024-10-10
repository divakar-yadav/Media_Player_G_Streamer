#ifndef SINGLEVIDEOPLAYERSCREEN_H
#define SINGLEVIDEOPLAYERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "VideoPlayer.h"

class SingleVideoPlayerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SingleVideoPlayerScreen(QWidget *parent = nullptr);

private slots:
    void onUploadVideo();
    void onLoadAndPlayVideo();
    void onSaveModifiedVideo();

private:
    QLineEdit *pathInput;
    QPushButton *playButton;
    QPushButton *uploadButton;
    QPushButton *saveButton;
    VideoPlayer *videoPlayer;
};

#endif // SINGLEVIDEOPLAYERSCREEN_H
