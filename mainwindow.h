#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSingleVideoPlayer();
    void showDualVideoPlayer();
    void showCombinedVideoPlayer();

private:
    QWidget *contentWidget;  // Holds the currently active screen
    void clearContentWidget();  // Clears the content widget when switching screens
};

#endif // MAINWINDOW_H
