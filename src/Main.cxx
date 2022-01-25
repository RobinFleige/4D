#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkPolyDataWriter.h>
#include <vtkSimplePointsWriter.h>
#include <vtkPolyData.h>
#include "Source4D.h"
#include "LIC.h"
#include "ImageRenderer.h"
#include "Slider.h"
#include "Subspace.h"
#include "CriticalPointsTrivial.h"

void Write(vtkSmartPointer<vtkImageData> image, const std::string filename) {
    //if(typeof<T>vtkImageData))
    vtkNew <vtkXMLImageDataWriter> writer;
    writer->SetFileName(filename.c_str());
    writer->SetCompressorTypeToNone();
    writer->SetDataModeToAscii();
    writer->SetInputData(image);
    writer->Write();
}

void Write(vtkSmartPointer<vtkPoints> points, const std::string filename) {
    vtkNew<vtkPolyData> polydata;
    polydata->SetPoints(points);
    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName(filename.c_str());
    writer->SetInputData(polydata);
    writer->Write();
}

int main(int argc, char* argv[])
{
    Source4D* source = new Source4D();
    Subspace* subspace = new Subspace();
    LIC* lic = new LIC();
    CriticalPointsTrivial* critical_points = new CriticalPointsTrivial();
    ImageRenderer* renderer = new ImageRenderer();


    int s = 3;
    int t = 3;
    subspace->SetSValue(s);
    subspace->SetTValue(t);
    //Slider* slider1 = new Slider();
    //slider1->Attach(renderer,s);
    //Slider* slider2 = new Slider();
    //slider2->Attach(renderer,t);

    source->Update();
    Write(source->GetOutput()[0][0], "Source");
    //subspace->SetInputConnection(source);
    //subspace->Update();
    //Write(subspace->GetOutput(),"Subspace");
    //lic->SetInputConnection(subspace);
    //lic->Update();
    //Write(lic->GetOutput(),"LIC");
    //critical_points->SetInputConnection(subspace);
    //critical_points->Update();
    //Write(critical_points->GetOutput(),"CriticalPoints");

    vtkSmartPointer<vtkImageData> critical_points_image = vtkSmartPointer<vtkImageData>::New();
    critical_points_image->SetDimensions(100,100,1);
    critical_points_image->AllocateScalars(VTK_FLOAT, 3);
    subspace->SetInputConnection(source);
    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            float* pixel = static_cast<float*>(critical_points_image->GetScalarPointer(x,y,0));
            subspace->SetSValue(x);
            subspace->SetTValue(y);
            subspace->Update();
            critical_points->SetInputConnection(subspace);
            critical_points->Update();
            pixel[0] = critical_points->GetOutput()->GetNumberOfPoints()*64;
        }
    }
    renderer->SetInput(critical_points_image);

    //renderer->SetInputConnection(lic);
    renderer->Update();
    //source->Write("Source");
    //lic->Write("LIC");
    return EXIT_SUCCESS;
}

//TODO 2D mit Slider
//TODO Kritische Punkte in 2D Feld anzeigen (Subdivision; Newton Verfahren)
//TODO Kritische Punkte in Parameterfeld zeichnen
//TODO Isolines Anzahl kritische Punkte in Parameterfeld
//TODO FFF
//TODO Bifurcation Points
//TODO Isoline Anzahl Bifurcation Point
//TODO Bifurcation Line/Bifurcation FFF
//TODO Read and Write



