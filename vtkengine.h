#ifndef VTKENGINE_H
#define VTKENGINE_H
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

#include <vtkActor.h>
#include <vtkInteractionStyleModule.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkTubeFilter.h>
#include <vtkProperty.h>
#include <vtkPointPicker.h>
#include <vtkObjectFactory.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkClipPolyData.h>
#include <vtkOBJReader.h>
#include <vtkTextWidget.h>
#include <vtkTextActor.h>
#include <vtkTextRepresentation.h>
#include <vtkBalloonWidget.h>
#include <vtkBalloonRepresentation.h>

#include <vtkEarthSource.h>
#include <vtkArrowSource.h>
#include <vtkSphereSource.h>
#include <vtkLineSource.h>

#include <QVTKOpenGLWidget.h>
#include <QDebug>

//image
#include <vtkImageCanvasSource2D.h>
#include <vtkImageBlend.h>
#include <vtkPNGReader.h>
#include <vtkImageReader.h>
#include <vtkMetaImageReader.h>
#include <vtkBMPReader.h>
#include <vtkImageViewer.h>
#include <vtkImageViewer2.h>
#include <vtkImageActor.h>
#include <vtkImageMapper.h>
#include <vtkInteractorStyleImage.h>

// example header
#include <vtkActor.h>

#include <vtkBooleanOperationPolyDataFilter.h>

#include <vtkPolyDataMapper.h>

#include <vtkRenderer.h>

#include <vtkRenderWindow.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkSmartPointer.h>

#include <vtkSphereSource.h>



#include <vtkSTLReader.h>

class vtkEngine
{
public:
    vtkEngine(QWidget *parent = nullptr);

    QVTKOpenGLWidget *vtkwidget;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer>  render;
    vtkSmartPointer<vtkInteractorStyleSwitch> style;
    vtkSmartPointer<vtkAxesActor> axes;
    vtkSmartPointer<vtkOrientationMarkerWidget> axeswidget;

    ~vtkEngine(){
        delete vtkwidget;
    }
private:

};

#endif // VTKENGINE_H
