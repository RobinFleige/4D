#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkImageData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageDataLIC2D.h>
#include <vtkPointData.h>
#include <vtkImageMapper.h>

std::vector<std::vector<vtkSmartPointer<vtkImageData>>> create_vector_field(){
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> st_images;
    for(int t = 0; t < 10; t++){
        std::vector<vtkSmartPointer<vtkImageData>> t_images;
        for(int s = 0; s < 10; s++){
            vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
            image->SetDimensions(10,10,1);
            image->AllocateScalars(VTK_DOUBLE, 2);
            for(int y = 0; y < 10; y++){
                for(int x = 0; x < 10; x++){
                }
            }
            image->Modified();
            t_images.push_back(image);
        }
        st_images.push_back(t_images);
    }
    return st_images;
}

void visualize_lic(vtkSmartPointer<vtkImageData> vector_field){

    vtkSmartPointer<vtkImageDataLIC2D> lic = vtkSmartPointer<vtkImageDataLIC2D>::New();
    lic->SetInputData(vector_field);
    lic->Update();
    std::cout<<lic->GetOutput()<<std::endl;
    vtkSmartPointer<vtkImageActor> actor;
    actor->GetMapper()->SetInputData(lic->GetOutput());


    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    window->AddRenderer(renderer);
    window->SetWindowName("Prototype");
    interactor->SetRenderWindow(window);
    renderer->AddActor(actor);
    window->Render();
}

vtkSmartPointer<vtkImageData> space_subset(std::vector<std::vector<vtkSmartPointer<vtkImageData>>> vector_field, int s_slider_value, int t_slider_value){
    return vector_field[s_slider_value][t_slider_value];
}

int main(int argc, char* argv[])
{
    //s,t,image
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> vector_field;
    vector_field = create_vector_field();
    int s_slider_value = 5;
    int t_slider_value = 5;

    visualize_lic(space_subset(vector_field,s_slider_value,t_slider_value));

    return EXIT_SUCCESS;
}

//TODO LIC Visualization
//TODO 2D mit Slider
//TODO Kritische Punkte in 2D Feld anzeigen
//TODO Kritische Punkte in Parameterfeld zeichnen
//TODO Isolines Anzahl kritische Punkte in Parameterfeld
//TODO FFF
//TODO Bifurcation Points
//TODO Isoline Anzahl Bifurcation Point
//TODO Bifurcation Line/Bifurcation FFF
//TODO Read and Write

//void write_vector_field(){
//
//}

//std::vector<std::vector<vtkSmartPointer<vtkImageData>>> read_vector_field(){
//
//}