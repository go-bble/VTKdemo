#include "vtkengine.h"

vtkEngine::vtkEngine(QWidget *parent)
{
    vtkwidget = new QVTKOpenGLWidget(parent);
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor= vtkSmartPointer<vtkActor>::New();
    render = vtkSmartPointer<vtkRenderer>::New();
    style = vtkSmartPointer<vtkInteractorStyleSwitch>::New();
    axes = vtkSmartPointer<vtkAxesActor>::New();
    axeswidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

    render->SetBackground(1.0, 1.0, 1.0);
    render->SetBackground2(0.829, 0.9578, 0.98157);
    render->SetGradientBackground(true);
    vtkwidget->GetRenderWindow()->AddRenderer(this->render);

    style->SetDefaultRenderer(this->render);
    vtkwidget->GetInteractor()->SetInteractorStyle(this->style);

    axeswidget->SetInteractor(this->vtkwidget->GetInteractor());
    axeswidget->SetOrientationMarker(this->axes);
    axeswidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
    axeswidget->SetViewport(0.0, 0.0, 0.2, 0.3);
    axeswidget->SetEnabled(1);
    axeswidget->InteractiveOn();
}

