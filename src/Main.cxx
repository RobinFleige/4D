#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include <Renderer/DoubleImageRenderer.h>
#include <Renderer/ImageRenderer3D.h>
#include <Filter/PointSetTo3D.h>
#include <Filter/VectorFieldToImageData.h>
#include "Source/VectorFieldSource.h"
#include "Filter/LIC.h"
#include "Renderer/ImageRenderer.h"
#include "Source/Slider/Slider.h"
#include "Filter/Subspace.h"
#include "CriticalPointsSubdivide.h"
#include "Filter/CriticalPointsSet.h"
#include "Filter/PointSetToScalarField.h"
#include "Filter/PointSource.h"
#include "Filter/DrawPointsOnImage.h"
#include "Filter/PointSetSubspace.h"

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
int show_lic(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto* subspace = new Subspace();
    auto* image = new VectorFieldToImageData();
    auto* lic = new LIC();
    auto* critical_points = new CriticalPointsSubdivide();
    auto* renderer = new ImageRenderer();

    int s = widths[0] / 2;
    int t = widths[1] / 2;

    source->Update();
    subspace->SetInputConnection(source);
    subspace->SetParameters({s,t});
    subspace->Update();
    image->SetInputConnection(subspace);
    image->Update();
    lic->SetInputConnection(image);
    lic->Update();
    Write(lic->GetOutput(),"LIC");
    renderer->SetInputConnection(lic);
    renderer->Update();
    renderer->GetInteractor()->Start();
    return EXIT_SUCCESS;
}

int show_parameter_field(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
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

int show_both(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto* subspace = new Subspace();
    auto* image = new VectorFieldToImageData();
    auto* lic = new LIC();
    auto* renderer = new ImageRenderer();
    auto* point_set = new CriticalPointsSet();
    auto* scalar_field = new PointSetToScalarField();
    auto* renderer2 = new ImageRenderer();

    int s = widths[0] / 2;
    int t = widths[1] / 2;

    subspace->SetInputConnection(source);
    subspace->SetParameters({s,t});
    image->SetInputConnection(subspace);
    image->Update();
    lic->SetInputConnection(image);
    renderer->SetInputConnection(lic);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer2->SetInputConnection(scalar_field);

    renderer->Update();
    renderer2->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int with_slider(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    int s = widths[0] / 2;
    int t = widths[1] / 2;

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto *subspace = new Subspace();
    auto* image = new VectorFieldToImageData();
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
    sliderRep1->SetMaximumValue(widths[3] - 1);
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
    sliderRep2->SetMaximumValue(widths[4] - 1);
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
    subspace->SetParameters({s,t});
    image->SetInputConnection(subspace);
    lic->SetInputConnection(image);
    renderer->SetInputConnection(lic);

    point_set->SetInputConnection(source);
    scalar_field->SetInputConnection(point_set);
    renderer2->SetInputConnection(scalar_field);

    renderer->Update();
    renderer2->Update();
    renderer2->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int with_slider_and_points(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    int s = widths[0] / 2;
    int t = widths[1] / 2;

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto* subspace = new Subspace();
    auto* image = new VectorFieldToImageData();
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
    sliderRep1->SetMaximumValue(widths[3]-1);
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
    sliderRep2->SetMaximumValue(widths[4]-1);
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
    subspace->SetParameters({s,t});
    image->SetInputConnection(subspace);
    image->Update();
    lic->SetInputConnection(image);
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

int two_in_one_image(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    int s = widths[0] / 2;
    int t = widths[1] / 2;

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto* subspace = new Subspace();
    auto* image = new VectorFieldToImageData();
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
    sliderRep1->SetMaximumValue(widths[3]-1);
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
    sliderRep2->SetMaximumValue(widths[4]-1);
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
    subspace->SetParameters({s,t});
    image->SetInputConnection(subspace);
    image->Update();
    lic->SetInputConnection(image);
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

int example_3d(std::vector<int> widths, std::vector<double> mins, std::vector<double> maxs){

    int s = widths[0] / 2;

    auto* source = new VectorFieldSource(2,2,widths,mins,maxs);
    auto* point_set = new CriticalPointsSet();
    auto* image_3d = new PointSetTo3D();
    auto* subspace = new Subspace();
    auto* renderer = new ImageRenderer3D();


    vtkNew<Slider> slider1;
    slider1->Attach(subspace,0);
    slider1->Attach(renderer,0);


    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(widths[3]-1);
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


    //point_set->SetInputConnection(source);
    //image_3d->SetInputConnection(point_set);
    //image_3d->SetParameterID(0);
    //subspace->SetInputConnection(image_3d);
    //subspace->SetParameters({s});
    //renderer->SetInputConnection(subspace);

    //renderer->Update();
    //std::cout<<"Finished"<<std::endl;
    //renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    std::vector<int> widths = {64,64,128,128};
    std::vector<double> mins = {-1,-1,-1,-1};
    std::vector<double> maxs = {1,1,1,1};
    return two_in_one_image(widths,mins,maxs);
}


//TODO CriticalPointSet
//TODO Filter zum Erstellen der Linien zwischen den kritischen Punkten erstellen (Vielleicht über FFF, dann FFF anwenden und mögliche Abweichungen verhindern)
//TODO Filter zum Berechnen von FFF auf kritischen Punkten von ProcessObject erstellen (Ableitung in x und y Richtung des x und y Wertes (oder höherer Raumdimensionen) pro Parameterdimension)
//TODO Filter zum Berechnen der Bifurkationen erstellen (multilineare Interpolation der FFF der Nachbarn des kritischen Punktes)
//TODO Filter zum Berechnen der Linien der Bifurkationen erstellen
//TODO Filter um Teile aus ProcessObject wieder rauszuziehen (kritische Punkte, Bifurkationen, Vektorfeld?)
//TODO Parameter-Subspace der (kritischen Punkte und ) Bifurkationspunkte
//TODO Main ans laufen bringen (Slider Namen switchen,++)
//TODO Axen in Renderer packen (https://kitware.github.io/vtk-examples/site/Cxx/GeometricObjects/Axes/))
//TODO 3D Ansicht der Linien erstellen (teiltransparente Flächen sollten dann recht einfach werden)

//https://www.lernhelfer.de/schuelerlexikon/mathematik-abitur/artikel/zwei-und-dreireihige-determinanten
//https://de.serlo.org/mathe/1761/vektor-oder-kreuzprodukt

//TODO Render Iso-Surface with increasing Transparency
//TODO Optimization: Start with reduced resolution and use subdivision to ignore big parts of the vectorfield
//TODO Move classes away from vtk one by one
//TODO Store Calculations for faster Example
//TODO PointSetSubSpace und Subspace kombinieren (unabhängig vom Type machen)



//1. xd*xd+td; -> vertical zweigeteilt
//2. xd*xd+td+sd -> schräg zweigeteilt
//3. xd*xd+td*td+sd*sd-1 -> durch Kreis geteilt
//4. xd*xd+td -> 2 bifurcationen (linien liegen aufeinander)
//5. (xd*xd+td)*(xd*xd+sd) -> 2 kreuzende Bifurcation Lines (Mit fragmenten im weißen Bereich)
//6. (xd-td)*(xd+td)*(xd-1-sd)*(xd-1+sd) -> seltsame Box
//7. (xd*xd+td)*(yd-1)-(xd*xd+sd)*(yd+1) -> 2 kreuzende Bifurcation Lines (kritische Punkte werden nicht korrekt berechnet)
//8. (xd*xd+td-1)*(yd-1)+(xd*xd+td+1)*(yd+1) -> doppelt parallel vertical zweigeteilt (kritische Punkte werden nicht korrekt berechnet)

//1. -yd+sd
//2. -yd
//3. -yd
//4. -yd*yd+sd
//5. -yd
//6. -yd
//7. (yd+1)*(yd-1)
//8. (yd+1)*(yd-1)