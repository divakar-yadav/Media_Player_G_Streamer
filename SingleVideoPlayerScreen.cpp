#include "SingleVideoPlayerScreen.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>

SingleVideoPlayerScreen::SingleVideoPlayerScreen(QWidget *parent)
    : QWidget(parent)
{
    videoPlayer = new VideoPlayer(this);

    pathInput = new QLineEdit(this);
    pathInput->setPlaceholderText("Enter video file path...");

    playButton = new QPushButton("Play Video", this);
    uploadButton = new QPushButton("Upload Video", this);
    saveButton = new QPushButton("Save Modified Video", this);

    connect(playButton, &QPushButton::clicked, this, &SingleVideoPlayerScreen::onLoadAndPlayVideo);
    connect(uploadButton, &QPushButton::clicked, this, &SingleVideoPlayerScreen::onUploadVideo);
    connect(saveButton, &QPushButton::clicked, this, &SingleVideoPlayerScreen::onSaveModifiedVideo);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pathInput);
    layout->addWidget(uploadButton);
    layout->addWidget(playButton);
    layout->addWidget(saveButton);
    layout->addWidget(videoPlayer);

    setLayout(layout);
}

void SingleVideoPlayerScreen::onUploadVideo()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Video", "", "Video Files (*.mp4 *.avi *.mkv);;All Files (*)");
    if (!filePath.isEmpty()) {
        pathInput->setText(filePath);
    }
}

void SingleVideoPlayerScreen::onLoadAndPlayVideo()
{
    QString currentVideoPath = pathInput->text();
    if (!currentVideoPath.isEmpty()) {
        videoPlayer->playVideo(currentVideoPath);
    } else {
        qDebug() << "Error: No file path provided.";
    }
}

void SingleVideoPlayerScreen::onSaveModifiedVideo()
{
    QString currentVideoPath = pathInput->text();
    if (!currentVideoPath.isEmpty()) {
        QString modifiedPath = currentVideoPath.left(currentVideoPath.lastIndexOf(".")) + "_modified.mp4";
        videoPlayer->saveModifiedVideo(currentVideoPath, modifiedPath, 1280, 720, 30);  // Save as 720p at 30fps
        qDebug() << "Saved modified video to: " << modifiedPath;
    } else {
        qDebug() << "Error: No file path provided.";
    }
}
