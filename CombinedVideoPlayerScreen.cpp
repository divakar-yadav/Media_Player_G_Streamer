#include "CombinedVideoPlayerScreen.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>

CombinedVideoPlayerScreen::CombinedVideoPlayerScreen(QWidget *parent)
    : QWidget(parent), videoPath1(""), videoPath2("")
{
    videoPlayer = new VideoPlayer(this);

    pathInput1 = new QLineEdit(this);
    pathInput1->setPlaceholderText("Enter first video file path...");

    pathInput2 = new QLineEdit(this);
    pathInput2->setPlaceholderText("Enter second video file path...");

    combineButton = new QPushButton("Combine and Play Videos", this);
    uploadButton1 = new QPushButton("Upload First Video", this);
    uploadButton2 = new QPushButton("Upload Second Video", this);

    connect(combineButton, &QPushButton::clicked, this, &CombinedVideoPlayerScreen::onCombineAndPlayVideos);
    connect(uploadButton1, &QPushButton::clicked, this, &CombinedVideoPlayerScreen::onUploadFirstVideo);
    connect(uploadButton2, &QPushButton::clicked, this, &CombinedVideoPlayerScreen::onUploadSecondVideo);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pathInput1);
    layout->addWidget(uploadButton1);
    layout->addWidget(pathInput2);
    layout->addWidget(uploadButton2);
    layout->addWidget(combineButton);
    layout->addWidget(videoPlayer);

    setLayout(layout);
}

void CombinedVideoPlayerScreen::onUploadFirstVideo()
{
    videoPath1 = QFileDialog::getOpenFileName(this, "Select First Video", "", "Video Files (*.mp4 *.avi *.mkv);;All Files (*)");
    if (!videoPath1.isEmpty()) {
        pathInput1->setText(videoPath1);
    } else {
        qDebug() << "Error: No file selected for the first video.";
    }
}

void CombinedVideoPlayerScreen::onUploadSecondVideo()
{
    videoPath2 = QFileDialog::getOpenFileName(this, "Select Second Video", "", "Video Files (*.mp4 *.avi *.mkv);;All Files (*)");
    if (!videoPath2.isEmpty()) {
        pathInput2->setText(videoPath2);
    } else {
        qDebug() << "Error: No file selected for the second video.";
    }
}

void CombinedVideoPlayerScreen::onCombineAndPlayVideos()
{
    if (!videoPath1.isEmpty() && !videoPath2.isEmpty()) {
        videoPlayer->combineVideos(videoPath1, videoPath2);
    } else {
        qDebug() << "Error: Both video paths must be selected.";
    }
}
