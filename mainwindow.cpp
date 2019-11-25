#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
}
void MainWindow::initUi()
{
    QWidget *p = takeCentralWidget();
    if(p)
        delete p;
    setDockNestingEnabled(true);
    rootDoc = new QDockWidget(QString("root"),this);
    rootDoc->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rootEngine = new vtkEngine(rootDoc);
    rootDoc->setWidget(rootEngine->vtkwidget);
    addDockWidget(Qt::LeftDockWidgetArea,rootDoc);
    fromFileAction();
    loadModelAction();

}

void MainWindow::fromFileAction()
{
    ui->toolBar->addAction("Fromfile", this, [=]()mutable{

        vtkSmartPointer<vtkPoints> points0 = vtkSmartPointer<vtkPoints>::New();

        QString qfilepath = QFileDialog::getOpenFileName(this,"数据文件","./data","*.txt");
        QByteArray byte = qfilepath.toLatin1();    //??????
        char *cfilepath = byte.data();
        std::string m_file = cfilepath;
        std::ifstream ifs(m_file.c_str());
        std::string singleLine;
        double x,y,z,low_z,high_z;
        low_z = high_z =0;
        int cun = 0;

        while (std::getline(ifs,singleLine))
            {
                std::stringstream linestream;
                size_t pos = singleLine.find(",");
                if(pos != std::string::npos)
                {
                    singleLine = singleLine.replace(pos,1," ");
                }
                pos = singleLine.find(",");
                if(pos != std::string::npos)
                {
                    singleLine = singleLine.replace(pos,1," ");
                }
                linestream << singleLine;
                linestream >> x >> y >> z;
                if (z < low_z)
                    low_z = z;
                else if (z > high_z)
                    high_z = z;
                std::cout<<x<<","<<y<<","<<z<<endl;
                points0->InsertNextPoint(x, y, z);
                cun++;
                if(cun%100== 0)
                {
                    buildModel(points0,low_z,high_z);
                    points0->Reset();
                    points0->InsertNextPoint(x, y, z);
                }

                QApplication::processEvents();
            }

            ifs.close();


    });
}

void MainWindow::loadModelAction()
{
    ui->toolBar->addAction("loadModel",this,[=]()mutable{
        vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();


        QString filepath = QFileDialog::getOpenFileName(this, "Open File", "./", "*.obj");

        if(filepath.length() == 0) return ;

        reader->SetFileName(filepath.toUtf8());
        reader->Update();

        mapper->SetInputConnection(reader->GetOutputPort());
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1.0, 0.5, 0.1);

        rootEngine->render->AddActor(actor);
        rootEngine->render->ResetCamera();
        rootEngine->vtkwidget->GetRenderWindow()->Render();
    });
}

void MainWindow::buildModel(const vtkSmartPointer<vtkPoints> &pos1,double low_z,double high_z)
{
    vtkSmartPointer<vtkLineSource> linesource0 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter0 = vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vtkSmartPointer<vtkTubeFilter> tube0 = vtkSmartPointer<vtkTubeFilter>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper0 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> actor0 = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkElevationFilter> elevationFilter = vtkSmartPointer<vtkElevationFilter>::New();
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();




    linesource0->SetPoints(pos1);
    glyphFilter0->SetInputData(polydata);
    glyphFilter0->Update();
    elevationFilter->SetInputConnection(glyphFilter0->GetOutputPort());
    elevationFilter->SetLowPoint(0, 0, low_z);
    elevationFilter->SetHighPoint(0, 0, high_z);

    tube0->SetInputConnection(linesource0->GetOutputPort());
    tube0->SetRadius(.3); //default is .5
    tube0->SetNumberOfSides(50);
    tube0->Update();


    mapper0->SetInputConnection(tube0->GetOutputPort());

    actor0->SetMapper(mapper0);
    actor0->GetProperty()->SetColor(0.8, 0.3, 0.6);
    rootEngine->render->AddActor(actor0);

    rootEngine->render->SetDebug(0);
    rootEngine->render->SetGlobalWarningDisplay(0);
    rootEngine->render->ResetCamera();
    rootEngine->render->SetBackground(.1, .2, .3);

    rootEngine->vtkwidget->GetRenderWindow()->Render();
}

MainWindow::~MainWindow()
{
    delete ui;
}


