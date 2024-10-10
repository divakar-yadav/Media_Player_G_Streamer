#include <QApplication>
#include "MainWindow.h"
#include <gst/gst.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv); // Initialize GStreamer
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
