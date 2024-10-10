#include "VideoPlayer.h"
#include <QDebug>
#include <cstdlib>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent), pipeline(nullptr)
{
    gst_init(nullptr, nullptr);  // Initialize GStreamer
}

GstElement* VideoPlayer::getPipeline() const
{
    return pipeline;
}

void VideoPlayer::initializePipeline(const QString &pipelineDesc)
{
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);  // Reset the pipeline if it's already running
        gst_object_unref(pipeline);
    }

    // Print the pipeline description for debugging
    qDebug() << "Creating GStreamer pipeline with: " << pipelineDesc;

    pipeline = gst_parse_launch(pipelineDesc.toUtf8().constData(), nullptr);
    if (!pipeline) {
        qDebug() << "Error: Failed to create GStreamer pipeline.";
        return;
    }

    GstBus *bus = gst_element_get_bus(pipeline);
    gst_bus_add_watch(bus, [](GstBus *, GstMessage *message, gpointer data) -> gboolean {
        if (message->type == GST_MESSAGE_EOS) {
            qDebug() << "Video playback finished.";
        }
        if (message->type == GST_MESSAGE_ERROR) {
            GError *err;
            gchar *debug_info;
            gst_message_parse_error(message, &err, &debug_info);
            qDebug() << "GStreamer Error: " << err->message << " Debug info: " << debug_info;
            g_clear_error(&err);
            g_free(debug_info);
        }
        return TRUE;
    }, this);

    qDebug() << "Setting pipeline state to playing...";
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        qDebug() << "Error: Failed to start playback.";
        return;
    }

    qDebug() << "Pipeline is playing.";
}


void VideoPlayer::playVideo(const QString &filePath)
{
    QString gstreamerUri = QString("file:///%1").arg(filePath);
    QString pipelineDesc = QString("playbin uri=%1").arg(gstreamerUri);
    qDebug() << "Playing video: " << filePath;
    initializePipeline(pipelineDesc);
}

void VideoPlayer::playVideoWithAdjustments(const QString &filePath, float brightness, float contrast, float hue, float saturation)
{
    QString gstreamerUri = QString("file:///%1").arg(filePath);
    QString pipelineDesc = QString(
                               "playbin uri=%1 ! videobalance brightness=%2 contrast=%3 hue=%4 saturation=%5 ! videoconvert ! autovideosink")
                               .arg(gstreamerUri)
                               .arg(brightness)
                               .arg(contrast)
                               .arg(hue)
                               .arg(saturation);

    qDebug() << "Playing video with adjustments: " << filePath;
    initializePipeline(pipelineDesc);
}

void VideoPlayer::playVideoWithGamma(const QString &filePath, float gamma)
{
    QString gstreamerUri = QString("file:///%1").arg(filePath);
    QString pipelineDesc = QString(
                               "playbin uri=%1 ! videobalance gamma=%2 ! videoconvert ! autovideosink")
                               .arg(gstreamerUri)
                               .arg(gamma);

    qDebug() << "Playing video with gamma correction: " << filePath;
    initializePipeline(pipelineDesc);
}

void VideoPlayer::combineVideos(const QString &filePath1, const QString &filePath2)
{
    QString pipelineDesc = QString(
                               "videomixer name=mix ! videoconvert ! autovideosink "
                               "filesrc location=%1 ! decodebin ! videoconvert ! mix. "
                               "filesrc location=%2 ! decodebin ! videoconvert ! mix.")
                               .arg(filePath1)
                               .arg(filePath2);

    qDebug() << "Combining and playing videos: " << filePath1 << " and " << filePath2;
    initializePipeline(pipelineDesc);
}

void VideoPlayer::saveModifiedVideo(const QString &inputPath, const QString &outputPath, int width, int height, int framerate)
{
    QString pipeline = QString(
                           "gst-launch-1.0 filesrc location=%1 ! decodebin ! videoconvert ! videoscale ! video/x-raw,width=%2,height=%3,framerate=%4/1 ! x264enc ! mp4mux ! filesink location=%5")
                           .arg(inputPath)
                           .arg(width)
                           .arg(height)
                           .arg(framerate)
                           .arg(outputPath);

    qDebug() << "Executing GStreamer pipeline to save modified video: " << pipeline;
    system(pipeline.toUtf8().constData());
}
