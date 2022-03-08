#include <vtkUnsignedIntArray.h>
#include "ImageRenderer4D.h"
void ImageRenderer4D::InternalUpdate() {
    std::vector<CriticalPoint*> critical_points = input_->GetCriticalPoints();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    vtkNew<vtkUnsignedCharArray> cellData;
    cellData->SetNumberOfComponents(4);
    cellData->SetNumberOfTuples(2*critical_points.size());

    for(int i = 0; i < critical_points.size(); i++){
        int transparency = ((int)input_->GetVectorField()->GetSize()/2)-((int)abs(((int)critical_points[i]->GetCoordinates()[0])-((int)input_->GetVectorField()->GetSize()/2)));
        if(transparency < 0){
            transparency = 0;
        }else if(transparency >= 20){
            transparency = 19;
        }
        double p0[3] = {critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3],critical_points[i]->GetCoordinates()[1]};
        double p1[3] = {critical_points[i]->GetCoordinates()[2]+critical_points[i]->GetFFF()[0][0],critical_points[i]->GetCoordinates()[3]+critical_points[i]->GetFFF()[0][1],critical_points[i]->GetCoordinates()[1]};
        double p2[3] = {critical_points[i]->GetCoordinates()[2]+critical_points[i]->GetFFF()[1][0],critical_points[i]->GetCoordinates()[3]+critical_points[i]->GetFFF()[1][1],critical_points[i]->GetCoordinates()[1]+critical_points[i]->GetFFF()[1][2]};
        double p3[3] = {critical_points[i]->GetCoordinates()[2]+critical_points[i]->GetFFF()[1][0]+critical_points[i]->GetFFF()[0][0],critical_points[i]->GetCoordinates()[3]+critical_points[i]->GetFFF()[1][1]+critical_points[i]->GetFFF()[0][1],critical_points[i]->GetCoordinates()[1]+critical_points[i]->GetFFF()[1][2]};
        points->InsertNextPoint(p0);
        points->InsertNextPoint(p1);
        points->InsertNextPoint(p2);
        points->InsertNextPoint(p3);
        vtkNew<vtkTriangle> cell1;
        vtkNew<vtkTriangle> cell2;
        double rgb[4];
        rgb[0] = 255;
        rgb[1] = 0;
        rgb[2] = 0;
        if(transparency < 7){
            rgb[3] = 0;
        }else{
            rgb[3] = 20*(double)transparency-130;
        }
        cell1->GetPointIds()->SetId(0,4*i);
        cell1->GetPointIds()->SetId(1,4*i+1);
        cell1->GetPointIds()->SetId(2,4*i+2);
        cells->InsertNextCell(cell1);
        cellData->InsertTuple(2*i,rgb);
        cell2->GetPointIds()->SetId(0,4*i+3);
        cell2->GetPointIds()->SetId(1,4*i+1);
        cell2->GetPointIds()->SetId(2,4*i+2);
        cells->InsertNextCell(cell2);
        cellData->InsertTuple(2*i+1,rgb);
    }

    polyData->SetPoints(points);
    polyData->SetPolys(cells);
    polyData->GetCellData()->SetScalars(cellData);
    mapper_->SetInputData(polyData);

    window_->SetWindowName(name_.c_str());
    window_->Render();
}

ImageRenderer4D::ImageRenderer4D(){
    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor_ = vtkSmartPointer<vtkActor>::New();
    actor_->SetMapper(mapper_);
    actor_->GetProperty()->SetLineWidth(4);
    renderer_->AddActor(actor_);
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());


    vtkNew<vtkAxesActor> axes;
    axes->SetNormalizedShaftLength(80,80,80);
    axes->SetXAxisLabelText("X");
    axes->SetYAxisLabelText("Y");
    axes->SetZAxisLabelText("T");
    //axes->AxisLabelsOff();
    renderer_->AddActor(axes);

    window_->SetSize(1000, 1000);
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor_->SetInteractorStyle(style);
    Invalidate();
}

void ImageRenderer4D::SetName(std::string name) {
    name_ = name;
    Invalidate();
}