#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include <DoubleImageRenderer.h>
#include <ImageRenderer3D.h>
#include <PointSetTo3D.h>
#include "Source4D.h"
#include "LIC.h"
#include "ImageRenderer.h"
#include "Slider.h"
#include "Subspace2D.h"
#include "Subspace1D.h"
#include "CriticalPointsSubdivide.h"
#include "CriticalPointsSet.h"
#include "PointSetToScalarField.h"
#include "PointSource.h"
#include "DrawPointsOnImage.h"
#include "PointSetSubspace.h"

void Write(vtkSmartPointer<vtkImageData> image, const std::string& filename) {
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

    auto* source = new Source4D(width,min,max);
    auto* subspace = new Subspace2D();
    auto* lic = new LIC();
    auto* critical_points = new CriticalPointsSubdivide();
    auto* renderer = new ImageRenderer();

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
    renderer->GetInteractor()->Start();
    return EXIT_SUCCESS;
}

int show_parameter_field(){
    int width = 20;
    double min = -2;
    double max = 2;

    auto* source = new Source4D(width,min,max);
    auto* point_set = new CriticalPointsSet();
    auto* scalar_field = new PointSetToScalarField();
    auto* renderer = new ImageRenderer();

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

    auto* source = new Source4D(width,min,max);
    auto* subspace = new Subspace2D();
    auto* lic = new LIC();
    auto* renderer = new ImageRenderer();
    auto* point_set = new CriticalPointsSet();
    auto* scalar_field = new PointSetToScalarField();
    auto* renderer2 = new ImageRenderer();

    subspace->SetInputConnection(source);
    subspace->SetSValue(width/2);
    subspace->SetTValue(width/2);
    lic->SetInputConnection(subspace);
    renderer->SetInputConnection(lic);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer2->SetInputConnection(scalar_field);

    renderer->Update();
    renderer2->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int with_slider() {
    int width = 100;
    double min = -2;
    double max = 2;

    double s = 1. * width / 2;
    double t = 1. * width / 2;

    auto *source = new Source4D(width, min, max);
    auto *subspace = new Subspace2D();
    auto *lic = new LIC();
    auto *renderer = new ImageRenderer();
    auto *point_set = new CriticalPointsSet();
    auto *scalar_field = new PointSetToScalarField();
    auto *renderer2 = new ImageRenderer();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace, 0);
    slider1->Attach(renderer, 0);
    vtkNew<Slider> slider2;
    slider2->Attach(subspace, 1);
    slider2->Attach(renderer, 1);

    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(width - 1);
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
    sliderRep2->SetMaximumValue(width - 1);
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

    renderer->Update();
    renderer2->Update();
    renderer2->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int with_slider_and_points(){
    int width = 100;
    double min = -2;
    double max = 2;

    double s = 1.*width/2;
    double t = 1.*width/2;

    auto* source = new Source4D(width,min,max);
    auto* subspace = new Subspace2D();
    auto* lic = new LIC();
    auto* point_subspace = new PointSetSubspace();
    auto* draw_points1 = new DrawPointsOnImage();
    auto* renderer = new ImageRenderer();
    auto* point_set = new CriticalPointsSet();
    auto* scalar_field = new PointSetToScalarField();
    auto* point_source = new PointSource();
    auto* draw_points2 = new DrawPointsOnImage();
    auto* renderer2 = new ImageRenderer();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace,0);
    slider1->Attach(point_subspace,0);
    slider1->Attach(point_source,0);
    slider1->Attach(renderer,0);
    slider1->Attach(renderer2,0);
    vtkNew<Slider> slider2;
    slider2->Attach(subspace,1);
    slider2->Attach(point_subspace,1);
    slider2->Attach(point_source,1);
    slider2->Attach(renderer,1);
    slider2->Attach(renderer2,1);


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
    point_subspace->SetSValue(s);
    point_subspace->SetTValue(t);
    point_subspace->SetInputConnection(point_set);
    draw_points1->SetInputConnection(lic);
    draw_points1->SetSecondaryInputConnection(point_subspace);
    renderer->SetInputConnection(draw_points1);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    point_source->SetX(s);
    point_source->SetY(t);
    draw_points2->SetInputConnection(scalar_field);
    draw_points2->SetSecondaryInputConnection(point_source);
    renderer2->SetInputConnection(draw_points2);

    renderer->Update();
    renderer2->Update();
    renderer2->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int two_in_one_image(){
    int width = 100;
    double min = -2;
    double max = 2;

    double s = 1.*width/2;
    double t = 1.*width/2;

    auto* source = new Source4D(width,min,max);
    auto* subspace = new Subspace2D();
    auto* lic = new LIC();
    auto* point_subspace = new PointSetSubspace();
    auto* draw_points1 = new DrawPointsOnImage();
    auto* point_set = new CriticalPointsSet();
    auto* scalar_field = new PointSetToScalarField();
    auto* point_source = new PointSource();
    auto* draw_points2 = new DrawPointsOnImage();
    auto* renderer = new DoubleImageRenderer();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace,0);
    slider1->Attach(point_subspace,0);
    slider1->Attach(point_source,0);
    slider1->Attach(renderer,0);
    vtkNew<Slider> slider2;
    slider2->Attach(subspace,1);
    slider2->Attach(point_subspace,1);
    slider2->Attach(point_source,1);
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
    point_subspace->SetSValue(s);
    point_subspace->SetTValue(t);
    point_subspace->SetInputConnection(point_set);
    draw_points1->SetInputConnection(lic);
    draw_points1->SetSecondaryInputConnection(point_subspace);
    renderer->SetInputConnection(draw_points1);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    point_source->SetX(s);
    point_source->SetY(t);
    draw_points2->SetInputConnection(scalar_field);
    draw_points2->SetSecondaryInputConnection(point_source);
    renderer->SetSecondaryInputConnection(draw_points2);

    renderer->Update();
    std::cout<<"Finished"<<std::endl;
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int example_3d(){
    int width = 100;
    double min = -2;
    double max = 2;

    double s = 1.*width/2;

    auto* source = new Source4D(width,min,max);
    auto* point_set = new CriticalPointsSet();
    auto* image_3d = new PointSetTo3D();
    auto* subspace_1d = new Subspace1D();
    auto* renderer = new ImageRenderer3D();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace_1d,0);
    slider1->Attach(renderer,0);


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


    point_set->SetInputConnection(source);
    image_3d->SetInputConnection(point_set);
    image_3d->SetParameterID(0);
    subspace_1d->SetInputConnection(image_3d);
    subspace_1d->SetSValue(s);
    renderer->SetInputConnection(subspace_1d);

    renderer->Update();
    std::cout<<"Finished"<<std::endl;
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    return two_in_one_image();
}


//TODO Improve CriticalPoint Calculation
//TODO FFF Paper erneut lesen und formeln aufschreiben
//TODO FFF (3D Vektorfeld für jede Parameterrichtung)
//TODO Ableitungsfilter + Kreuzprodukt
//TODO ValueFilter (FFF_3 = 0)
//TODO Bifurcation Points
//TODO Bifurcation Line/Bifurcation FFF
    //Bei Subdivision den genauen Punkt berechnen
    //FFF für den genauen Punkt berechnen
    //Für Punkt an dem gelandet wird wieder Subdivision berechnen um leichte Fehler auszugleichen
    //Wiederholen und kritische Punkte damit zu Polyline machen
    //Bei zwei Parametern -> 100 Polylines in jede Parameterdimension
    //Pro Parameterdimension bei drittem Wert von FFF nach Vorzeichenwechsel suchen
    //Bei angrenzenden Parameterwerten nach Bifurcation suchen und die zur Polyline zusammenfügen
    // Kritische Punkte-Polyplanes und Bifurcation-Polylines visualisieren

//TODO 3D Point Set Visualization
//TODO Add Axes -> https://kitware.github.io/vtk-examples/site/Cxx/GeometricObjects/Axes/
//TODO Render Iso-Surface with increasing Transparency



//TODO Store Calculations for faster Example
//TODO PointSetSubSpace und Subspace kombinieren (unabhängig vom Type machen)
//TODO Change Image To StructuredGrid
//TODO Implement StructuredGridnD
//TODO Implement StructuredGridToImage
//TODO Implement nDImageToVtkImageData