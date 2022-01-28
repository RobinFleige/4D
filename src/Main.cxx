#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include "Source4D.h"
#include "LIC.h"
#include "ImageRenderer.h"
#include "Slider.h"
#include "Subspace.h"
#include "CriticalPointsSubdivide.h"
#include "CriticalPointsSet.h"
#include "PointSetToScalarField.h"

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
int show_lic() {
    int width = 100;
    double min = -2;
    double max = 2;

    Source4D* source = new Source4D(width,min,max);
    Subspace* subspace = new Subspace();
    LIC* lic = new LIC();
    CriticalPointsSubdivide* critical_points = new CriticalPointsSubdivide();
    ImageRenderer* renderer = new ImageRenderer();

    source->Update();
    Write(source->GetOutput()[0][0], "Source");
    subspace->SetInputConnection(source);
    subspace->SetSValue(width/2);
    subspace->SetTValue(width/2);
    subspace->Update();
    Write(subspace->GetOutput(),"Subspace");
    lic->SetInputConnection(subspace);
    lic->Update();
    Write(lic->GetOutput(),"LIC");
    critical_points->SetInputConnection(subspace);
    critical_points->Update();
    Write(critical_points->GetOutput(),"CriticalPoints");
    renderer->SetInputConnection(lic);
    renderer->Update();
    return EXIT_SUCCESS;
}

int show_parameter_field(){
    int width = 20;
    double min = -2;
    double max = 2;

    Source4D* source = new Source4D(width,min,max);
    CriticalPointsSet* point_set = new CriticalPointsSet();
    PointSetToScalarField* scalar_field = new PointSetToScalarField();
    ImageRenderer* renderer = new ImageRenderer();

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer->SetInputConnection(scalar_field);
    source->Update();
    point_set->Update();
    scalar_field->Update();
    renderer->Update();

    return EXIT_SUCCESS;
}

int show_both(){
    int width = 20;
    double min = -2;
    double max = 2;

    Source4D* source = new Source4D(width,min,max);
    Subspace* subspace = new Subspace();
    LIC* lic = new LIC();
    ImageRenderer* renderer = new ImageRenderer();
    CriticalPointsSet* point_set = new CriticalPointsSet();
    PointSetToScalarField* scalar_field = new PointSetToScalarField();
    ImageRenderer* renderer2 = new ImageRenderer();

    subspace->SetInputConnection(source);
    subspace->SetSValue(width/2);
    subspace->SetTValue(width/2);
    lic->SetInputConnection(subspace);
    renderer->SetInputConnection(lic);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer2->SetInputConnection(scalar_field);
    point_set->Update();
    scalar_field->Update();


    renderer->Update();
    renderer2->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int with_slider(){
    int width = 60;
    double min = -2;
    double max = 2;

    double s = width/2;
    double t = width/2;

    Source4D* source = new Source4D(width,min,max);
    Subspace* subspace = new Subspace();
    LIC* lic = new LIC();
    ImageRenderer* renderer = new ImageRenderer();
    CriticalPointsSet* point_set = new CriticalPointsSet();
    PointSetToScalarField* scalar_field = new PointSetToScalarField();
    ImageRenderer* renderer2 = new ImageRenderer();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace,0);
    slider1->Attach(renderer,0);
    vtkNew<Slider> slider2;
    slider2->Attach(subspace,1);
    slider2->Attach(renderer,1);

    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(width-1);
    sliderRep1->SetValue(s);
    sliderRep1->SetTitleText("S");
    sliderRep1->SetPoint1InWorldCoordinates(-10, -10, 0);
    sliderRep1->SetPoint2InWorldCoordinates(10, -10, 0);
    sliderRep1->SetSliderWidth(.2);
    sliderRep1->SetLabelHeight(.1);
    vtkNew<vtkSliderWidget> sliderWidget1;
    sliderWidget1->SetInteractor(renderer->GetInteractor());
    sliderWidget1->SetRepresentation(sliderRep1);
    sliderWidget1->SetAnimationModeToAnimate();
    sliderWidget1->EnabledOn();
    sliderWidget1->AddObserver(vtkCommand::InteractionEvent, slider1);

    vtkNew<vtkSliderRepresentation3D> sliderRep2;
    sliderRep2->SetMinimumValue(0);
    sliderRep2->SetMaximumValue(width-1);
    sliderRep2->SetValue(t);
    sliderRep2->SetTitleText("T");
    sliderRep2->SetPoint1InWorldCoordinates(10, -10, 0);
    sliderRep2->SetPoint2InWorldCoordinates(30, -10, 0);
    sliderRep2->SetSliderWidth(.2);
    sliderRep2->SetLabelHeight(.1);
    vtkNew<vtkSliderWidget> sliderWidget2;
    sliderWidget2->SetInteractor(renderer->GetInteractor());
    sliderWidget2->SetRepresentation(sliderRep2);
    sliderWidget2->SetAnimationModeToAnimate();
    sliderWidget2->EnabledOn();
    sliderWidget2->AddObserver(vtkCommand::InteractionEvent, slider2);


    subspace->SetInputConnection(source);
    subspace->SetSValue(s);
    subspace->SetTValue(t);
    lic->SetInputConnection(subspace);
    renderer->SetInputConnection(lic);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer2->SetInputConnection(scalar_field);
    point_set->Update();
    scalar_field->Update();


    renderer->Update();
    renderer2->Update();
    renderer2->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    return with_slider();
}



//TODO Filter um PointSet auf Bild zu malen (InputConnection=HasOutput(vtkImageData);SecondaryInputConnection=HasOutput(vtkPoints)->Update überschreiben um SecondaryInput zu Updaten)
//TODO Kritische Punkte in Raum-Feld anzeigen
//TODO Aktuelle Parameter-Kombi in Parameterbild zeigen

//TODO FFF
//TODO Bifurcation Points
//TODO Isoline Anzahl Bifurcation Point
//TODO Bifurcation Line/Bifurcation FFF


//TODO ScalarFieldToImage
//TODO PointSetSubSpace (Oder Subspace unmabhängig vom Typ machen)
//TODO Change Image To StructuredGrid
//TODO Implement StructuredGridnD
//TODO Implement StructuredGridToImage
//TODO Implement nDImageToVtkImageData


//vtkNew<vtkSliderRepresentation3D> sliderRep;
//sliderRep->SetMinimumValue(0.0);
//sliderRep->SetMaximumValue(30.0);
//sliderRep->SetValue(10.0);
//sliderRep->SetTitleText("Contour value");
//sliderRep->SetPoint1InWorldCoordinates(-20, -40, 0);
//sliderRep->SetPoint2InWorldCoordinates(0, -40, 0);
//sliderRep->SetSliderWidth(.2);
//sliderRep->SetLabelHeight(.1);
//
//vtkNew<vtkSliderWidget> sliderWidget;
//sliderWidget->SetInteractor(interactor);
//sliderWidget->SetRepresentation(sliderRep);
//sliderWidget->SetAnimationModeToAnimate();
//sliderWidget->EnabledOn();
//
//vtkNew<vtkSliderCallback> callback;
//sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);


