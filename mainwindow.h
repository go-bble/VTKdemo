#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vtkengine.h"
#include <QDockWidget>
#include <QToolBar>
#include <fstream>
#include <sstream>
#include <string>
#include <QFileDialog>
#include <vtkVertexGlyphFilter.h>
#include <vtkElevationFilter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUi();
    vtkEngine *rootEngine;
    QDockWidget *rootDoc;

    void fromFileAction();
    void loadModelAction();
    void buildModel(const vtkSmartPointer<vtkPoints> &pos1, double low_z, double high_z);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
