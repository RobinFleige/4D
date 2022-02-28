#include "PolyDataRenderer.h"
void PolyDataRenderer::InternalUpdate() {
    int factor1 = 40;
    int factor2 = 40;
    std::vector<CriticalPoint*> critical_points = input_->GetCriticalPoints();

    vtkNew<vtkPoints> points;
    vtkNew<vtkCellArray> lines;
    vtkNew<vtkPolyData> linesPolyData;

    for(int i = 0; i < critical_points.size(); i++){
        double p0[3] = {critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2]};
        double p1[3] = {critical_points[i]->GetCoordinates()[0]+critical_points[i]->GetFFF()[0].GetValue()[2]*factor2,critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2]+critical_points[i]->GetFFF()[0].GetValue()[0]*factor1};
        double p2[3] = {critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1]+critical_points[i]->GetFFF()[1].GetValue()[2]*factor2,critical_points[i]->GetCoordinates()[2]+critical_points[i]->GetFFF()[1].GetValue()[0]*factor1};
        points->InsertNextPoint(p0);
        points->InsertNextPoint(p1);
        points->InsertNextPoint(p2);
        vtkNew<vtkLine> line1;
        vtkNew<vtkLine> line2;
        line1->GetPointIds()->SetId(0, 3*i);
        line1->GetPointIds()->SetId(1, 3*i+1);;
        line2->GetPointIds()->SetId(0, 3*i);
        line2->GetPointIds()->SetId(1, 3*i+2);
        lines->InsertNextCell(line1);
        lines->InsertNextCell(line2);
    }
    linesPolyData->SetPoints(points);
    linesPolyData->SetLines(lines);

    mapper_->SetInputData(linesPolyData);

    window_->SetWindowName(name_.c_str());
    window_->Render();
}

PolyDataRenderer::PolyDataRenderer(){
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor_ = vtkSmartPointer<vtkActor>::New();
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();

    actor_->SetMapper(mapper_);
    actor_->GetProperty()->SetLineWidth(4);

    renderer_->AddActor(actor_);
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());


    vtkNew<vtkAxesActor> axes;
    axes->SetNormalizedShaftLength(80,80,80);
    axes->SetXAxisLabelText("S");
    axes->SetYAxisLabelText("T");
    axes->SetZAxisLabelText("X");
    axes->AxisLabelsOff();
    renderer_->AddActor(axes);

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor_->SetInteractorStyle(style);
    //vtkNew<vtkInteractorStyleImage> style;
    //interactor_->SetInteractorStyle(style);
    Invalidate();
}

void PolyDataRenderer::OnChange(double value, int id) {
    Update();
}

void PolyDataRenderer::SetName(std::string name) {
    name_ = name;
    Invalidate();
}