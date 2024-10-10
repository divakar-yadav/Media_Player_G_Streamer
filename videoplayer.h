#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <gst/gst.h>

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);

    // Public method to access the pipeline state
    GstElement* getPipeline() const;

    // Play video without any adjustments
    void playVideo(const QString &filePath);

    // Play video with brightness, contrast, hue, and saturation adjustments
    void playVideoWithAdjustments(const QString &filePath, float brightness, float contrast, float hue, float saturation);

    // Play video with gamma correction
    void playVideoWithGamma(const QString &filePath, float gamma);

    // Combine two video files and play them
    void combineVideos(const QString &filePath1, const QString &filePath2);

    // Save a modified video with specified resolution and frame rate
    void saveModifiedVideo(const QString &inputPath, const QString &outputPath, int width, int height, int framerate);

private:
    GstElement *pipeline;
    void initializePipeline(const QString &pipelineDesc);
};

#endif // VIDEOPLAYER_H
