#include <vtkUnsignedIntArray.h>
#include <vtkSimplePointsReader.h>
#include "ImageRenderer4D.h"
void ImageRenderer4D::InternalUpdate() {
    std::vector<CriticalPoint*> critical_points = input_->GetCriticalPoints();

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    vtkNew<vtkUnsignedCharArray> cellData;
    cellData->SetNumberOfComponents(4);

    if(type_ == RenderType::line || type_ == RenderType::triangle) {
        cellData->SetNumberOfTuples(2 * critical_points.size());
    }else{
        cellData->SetNumberOfTuples(critical_points.size());
    }

    for(int i = 0; i < critical_points.size(); i++){
        int transparency = (int)abs(((int)critical_points[i]->GetCoordinates()[0])-((int)input_->GetVectorField()->GetSize()/2));
        if(transparency < 0){
            transparency = 0;
        }else if(transparency > input_->GetVectorField()->GetSize()-1){
            transparency = input_->GetVectorField()->GetSize()-1;
        }

        double rgba[4];
        if(critical_points[i]->GetCriticalPointType() == CriticalPointType::saddle){
            rgba[0] = 255;
            rgba[1] = 0;
            rgba[2] = 0;
        }else if (critical_points[i]->GetCriticalPointType() == CriticalPointType::source){
            rgba[0] = 0;
            rgba[1] = 255;
            rgba[2] = 0;
        }else if(critical_points[i]->GetCriticalPointType() == CriticalPointType::sink){
            rgba[0] = 0;
            rgba[1] = 0;
            rgba[2] = 255;
        }else if(critical_points[i]->GetCriticalPointType() == CriticalPointType::bifurcation){
            rgba[0] = 255;
            rgba[1] = 255;
            rgba[2] = 255;
        }
        rgba[3] = 255-20*transparency;
        if(rgba[3] < 0){
            rgba[3] = 0;
        }
        if(type_ == RenderType::line || type_ == RenderType::triangle) {
            cellData->InsertTuple(2*i,rgba);
            cellData->InsertTuple(2*i+1,rgba);
        }else{
            cellData->InsertTuple(i,rgba);
        }


        if(type_ == RenderType::point){
            double p0[3] = {critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2]};
            vtkIdType pid[1];
            pid[0] = points->InsertNextPoint(p0);
            vertices->InsertNextCell(1,pid);
        }

        if(type_ == RenderType::line) {
            Vector fff1 = input_->GetVectorField()->GetInterpolatedFFF({critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]},0);
            Vector fff2 = input_->GetVectorField()->GetInterpolatedFFF({critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]},1);
            double p0[3] = {critical_points[i]->GetCoordinates()[0]-fff1.values_[0]  ,critical_points[i]->GetCoordinates()[1]                                                ,critical_points[i]->GetCoordinates()[2]-fff1.values_[2]};
            double p1[3] = {critical_points[i]->GetCoordinates()[0]+fff1.values_[0]   ,critical_points[i]->GetCoordinates()[1]                                                ,critical_points[i]->GetCoordinates()[2]+fff1.values_[2]};
            double p2[3] = {critical_points[i]->GetCoordinates()[0]                                                 ,critical_points[i]->GetCoordinates()[1]-fff2.values_[1]  ,critical_points[i]->GetCoordinates()[2]-fff2.values_[2]};
            double p3[3] = {critical_points[i]->GetCoordinates()[0]                                                 ,critical_points[i]->GetCoordinates()[1]+fff2.values_[1]  ,critical_points[i]->GetCoordinates()[2]+fff2.values_[2]};
            points->InsertNextPoint(p0);
            points->InsertNextPoint(p1);
            points->InsertNextPoint(p2);
            points->InsertNextPoint(p3);
            vtkNew<vtkLine> line1;
            line1->GetPointIds()->SetId(0, 4*i);
            line1->GetPointIds()->SetId(1, 4*i+1);
            lines->InsertNextCell(line1);
            vtkNew<vtkLine> line2;
            line2->GetPointIds()->SetId(0, 4*i+2);
            line2->GetPointIds()->SetId(1, 4*i+3);
            lines->InsertNextCell(line2);
        }

        if(type_ == RenderType::triangle) {
            Vector fff1 = input_->GetVectorField()->GetInterpolatedFFF({critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]},0);
            Vector fff2 = input_->GetVectorField()->GetInterpolatedFFF({critical_points[i]->GetCoordinates()[0],critical_points[i]->GetCoordinates()[1],critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3]},1);
            double p0[3] = {critical_points[i]->GetCoordinates()[2],critical_points[i]->GetCoordinates()[3],critical_points[i]->GetCoordinates()[1]};
            double p1[3] = {critical_points[i]->GetCoordinates()[2]+fff1.values_[2],critical_points[i]->GetCoordinates()[3]+fff1.values_[3],critical_points[i]->GetCoordinates()[1]};
            double p2[3] = {critical_points[i]->GetCoordinates()[2]+fff2.values_[2],critical_points[i]->GetCoordinates()[3]+fff2.values_[3],critical_points[i]->GetCoordinates()[1]+fff2.values_[1]};
            double p3[3] = {critical_points[i]->GetCoordinates()[2]+fff2.values_[2]+fff1.values_[2],critical_points[i]->GetCoordinates()[3]+fff2.values_[3]+fff1.values_[3],critical_points[i]->GetCoordinates()[1]+fff2.values_[1]};
            points->InsertNextPoint(p0);
            points->InsertNextPoint(p1);
            points->InsertNextPoint(p2);
            points->InsertNextPoint(p3);

            vtkNew<vtkTriangle> triangle1;
            triangle1->GetPointIds()->SetId(0,4*i);
            triangle1->GetPointIds()->SetId(1,4*i+1);
            triangle1->GetPointIds()->SetId(2,4*i+2);
            cells->InsertNextCell(triangle1);
            vtkNew<vtkTriangle> triangle2;
            triangle2->GetPointIds()->SetId(0,4*i+3);
            triangle2->GetPointIds()->SetId(1,4*i+1);
            triangle2->GetPointIds()->SetId(2,4*i+2);
            cells->InsertNextCell(triangle2);
        }
    }

    polyData->SetPoints(points);
    polyData->SetPolys(cells);
    polyData->SetLines(lines);
    polyData->SetVerts(vertices);
    polyData->GetCellData()->SetScalars(cellData);
    mapper_->SetInputData(polyData);
    window_->Render();
}

ImageRenderer4D::ImageRenderer4D(std::string name, RenderType type, std::vector<int> used_dimensions, int supportive_dimension, bool show_axes, bool use_transparency){
    name_ = name;
    type_ = type;
    supportive_dimension_ = supportive_dimension;
    use_transparency_ = use_transparency;
    used_dimensions_ = used_dimensions;

    renderer_ = vtkSmartPointer<vtkRenderer>::New();
    window_ = vtkSmartPointer<vtkRenderWindow>::New();
    mapper_ = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor_ = vtkSmartPointer<vtkActor>::New();
    actor_->SetMapper(mapper_);
    actor_->GetProperty()->SetLineWidth(4);
    actor_->GetProperty()->SetPointSize(10);
    renderer_->AddActor(actor_);
    interactor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    colors_ = vtkSmartPointer<vtkNamedColors>::New();
    renderer_->SetBackground(colors_->GetColor3d("SteelBlue").GetData());

    if(show_axes){
        vtkNew<vtkAxesActor> axes;
        axes->SetNormalizedShaftLength(80,80,80);
        axes->SetXAxisLabelText("X");
        axes->SetYAxisLabelText("Y");
        axes->SetZAxisLabelText("T");
        //axes->AxisLabelsOff();
        renderer_->AddActor(axes);
    }

    window_->SetSize(1000, 1000);
    window_->SetWindowName(name_.c_str());
    window_->AddRenderer(renderer_);

    interactor_->SetRenderWindow(window_);
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor_->SetInteractorStyle(style);
    Invalidate();
}
