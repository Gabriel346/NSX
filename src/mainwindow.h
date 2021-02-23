#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Viewport *viewport;

    void openSceneExplorer();

private:
    Ui::MainWindow *ui;

    QDockWidget *sceneExplorerWidget = nullptr;

private slots:
    void registerCommand();
    void testCommand();
    void openUVEditor();
    void loadModel();
    void saveModel();

};
#endif // MAINWINDOW_H
