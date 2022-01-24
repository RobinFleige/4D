#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkImageData.h>
#include <vtkPolyLine.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkIntArray.h>
#include <vtkPolyData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkImageDataLIC2D.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkNamedColors.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageShiftScale.h>

int width = 100;
int param_width = 10;

float x_function(int x, int y, int s, int t){
    return -10;
}

float y_function(int x, int y, int s, int t){
    return 10;
}

std::vector<std::vector<vtkSmartPointer<vtkImageData>>> create_vector_field(){
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> st_images;
    for(int t = 0; t < param_width; t++){
        std::vector<vtkSmartPointer<vtkImageData>> t_images;
        for(int s = 0; s < param_width; s++){
            vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
            image->SetDimensions(width,width,1);
            image->AllocateScalars(VTK_FLOAT, 3);
            for(int y = 0; y < width; y++){
                for(int x = 0; x < width; x++){
                    float* pixel = static_cast<float*>(image->GetScalarPointer(x, y, 0));
                    pixel[0] = x_function(x,y,s,t);
                    pixel[1] = y_function(x,y,s,t);
                    pixel[2] = 0.0;
                }
            }
            image->GetPointData()->SetActiveVectors("ImageScalars");
            image->Modified();
            t_images.push_back(image);
        }
        st_images.push_back(t_images);
    }
    return st_images;
}

void save(vtkSmartPointer<vtkImageData> vector_field){
    vtkNew<vtkImageDataLIC2D> lic;
    lic->SetInputData(vector_field);
    lic->Update();

    vtkNew<vtkImageShiftScale> scale;
    scale->SetInputData(lic->GetOutput());
    scale->SetScale(128);

    vtkNew<vtkImageActor> actor;
    actor->GetMapper()->SetInputConnection(scale->GetOutputPort());


    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

    vtkNew<vtkRenderWindow> window;
    window->SetSize(1000, 1000);
    window->AddRenderer(renderer);
    window->SetWindowName("Test");

    vtkNew<vtkRenderWindowInteractor> interactor;

    interactor->SetRenderWindow(window);
    window->Render();
    interactor->Start();




    //vtkNew<vtkXMLImageDataWriter> writer;
    //writer->SetFileName("test.xml");
    //writer->SetCompressorTypeToNone();
    //writer->SetDataModeToAscii();
    //writer->SetInputData(lic->GetOutput());
    //writer->Write();
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

    save(space_subset(vector_field,s_slider_value,t_slider_value));

    return EXIT_SUCCESS;
}

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