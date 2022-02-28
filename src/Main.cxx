#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include <Renderer/DoubleImageRenderer.h>
#include <Renderer/ImageRenderer3D.h>
#include <Filter/PointSetTo3D.h>
#include <Filter/PointSetToScalarField.h>
#include <Filter/VectorFieldToImageData.h>
#include <Source/TestSource.h>
#include <Filter/PointSetSubspace.h>
#include <Filter/Subspace4D2D.h>
#include <DataTypeFilter/GetPointsSet.h>
#include <Filter/CalculateFFF.h>
#include <Renderer/PolyDataRenderer.h>
#include "Source/VectorFieldSource.h"
#include "Filter/LIC.h"
#include "./Slider/Slider.h"
#include "Filter/Subspace.h"
#include "Filter/CalculateCriticalPoints.h"
#include "Source/PointSource.h"
#include "Filter/DrawPointsOnImage.h"

int two_in_one_image(int size, int min, int max){

    int s = size / 2;
    int t = size / 2;

    auto* source = new VectorFieldSource(size,min,max);
    auto* subspace = new Subspace4D2D();
    auto* image = new VectorFieldToImageData();
    auto* lic = new LIC();
    auto* point_subspace = new PointSetSubspace();
    auto* draw_points1 = new DrawPointsOnImage(2,3);
    auto* critical_points = new CalculateCriticalPoints();
    auto* point_set = new GetPointsSet();
    auto* scalar_field = new PointSetToScalarField(size);
    auto* point_source = new PointSource();
    auto* draw_points2 = new DrawPointsOnImage(0,1);
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
    sliderRep1->SetMaximumValue(size-1);
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
    sliderRep2->SetMaximumValue(size-1);
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

    source->Update();
    subspace->SetInputConnection(source);
    subspace->SetId(s,0);
    subspace->SetId(t,0);
    subspace->Update();
    image->SetInputConnection(subspace);
    image->Update();
    lic->SetInputConnection(image);
    lic->Update();
    point_subspace->SetSValue(s);
    point_subspace->SetTValue(t);
    critical_points->SetInputConnection(source);
    critical_points->Update();
    point_subspace->SetInputConnection(critical_points);
    point_subspace->Update();
    draw_points1->SetInputConnection(lic);
    draw_points1->SetSecondaryInputConnection(point_subspace);
    draw_points1->Update();
    renderer->SetInputConnection(draw_points1);
    point_set->SetInputConnection(critical_points);
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

int fake_3d(int size, int min, int max)
{
    auto source = new TestSource(size);
    auto points_set = new GetPointsSet();
    auto fff = new CalculateFFF();
    auto image = new PointSetTo3D(size);
    auto subspace = new Subspace<vtkSmartPointer<vtkImageData>>();
    auto renderer = new ImageRenderer3D();

    vtkNew<Slider> slider1;
    slider1->Attach(subspace, 0);
    slider1->Attach(renderer, 0);

    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(size - 1);
    sliderRep1->SetValue(size/2);
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


    source->Update();
    fff->SetInputConnection(source);
    fff->Update();
    points_set->SetInputConnection(source);
    image->SetParameterID(3);
    image->SetInputConnection(points_set);
    image->Update();
    subspace->SetId(size/2);
    subspace->SetInputConnection(image);
    subspace->Update();
    renderer->SetInputConnection(subspace);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;

}

int fake_3d_with_lines(int size, int min, int max)
{
    auto source = new TestSource(size);
    auto points_set = new GetPointsSet();
    auto fff = new CalculateFFF();
    auto image = new PointSetTo3D(size);
    auto subspace = new Subspace<vtkSmartPointer<vtkImageData>>();
    //auto renderer = new ImageRenderer3D();
    auto renderer = new PolyDataRenderer();

    vtkNew<Slider> slider1;
    slider1->Attach(subspace, 0);
    slider1->Attach(renderer, 0);

    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(size - 1);
    sliderRep1->SetValue(size/2);
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


    source->Update();
    fff->SetInputConnection(source);
    fff->Update();
    points_set->SetInputConnection(source);
    image->SetParameterID(3);
    image->SetInputConnection(points_set);
    image->Update();
    subspace->SetId(size/2);
    subspace->SetInputConnection(image);
    subspace->Update();
    //renderer->SetInputConnection(subspace);
    renderer->SetInputConnection(fff);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;

}

int real_3d_with_lines(int size, int min, int max)
{
    auto source = new VectorFieldSource(size,min,max);
    auto critical_points = new CalculateCriticalPoints();
    auto points_set = new GetPointsSet();
    auto fff = new CalculateFFF();
    auto image = new PointSetTo3D(size);
    auto subspace = new Subspace<vtkSmartPointer<vtkImageData>>();
    //auto renderer = new ImageRenderer3D();
    auto renderer = new PolyDataRenderer();

    source->Update();
    fff->SetInputConnection(critical_points);
    fff->Update();
    points_set->SetInputConnection(critical_points);
    image->SetParameterID(3);
    image->SetInputConnection(points_set);
    image->Update();
    subspace->SetId(size/2);
    subspace->SetInputConnection(image);
    subspace->Update();
    //renderer->SetInputConnection(subspace);
    renderer->SetInputConnection(fff);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;

}

int example_3d(int size, int min, int max){
    auto source = new VectorFieldSource(size,-2,2);
    auto critical_points = new CalculateCriticalPoints();
    auto points_set = new GetPointsSet();
    auto subspace = new Subspace<vtkSmartPointer<vtkImageData>>();
    auto image = new PointSetTo3D(size);
    auto renderer = new ImageRenderer3D();

    vtkNew<Slider> slider1;
    slider1->Attach(subspace, 0);
    slider1->Attach(renderer, 0);

    vtkNew<vtkSliderRepresentation3D> sliderRep1;
    sliderRep1->SetMinimumValue(0);
    sliderRep1->SetMaximumValue(size - 1);
    sliderRep1->SetValue(size/2);
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


    critical_points->SetInputConnection(source);
    points_set->SetInputConnection(critical_points);
    image->SetParameterID(3);
    image->SetInputConnection(points_set);
    subspace->SetId(size/2);
    subspace->SetInputConnection(image);
    renderer->SetInputConnection(subspace);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    int size = 40;
    int min = -2;
    int max = 2;
    return fake_3d_with_lines(size,min,max);
}

//MEETING TODO
//3D Visualisierung mit Slider für 4. Komponente
//2D Side-by-Side Visualisierung für besseres Verständnis
//Bifurcation Curve extrahieren
//FFF von FFF
//Nabla/Gradient von Vektor
//Trackball Code ins Wiki










//Vorzeichenwechsel im FFF
//Bifurcation Lines per ParameterDimension-1



//TODO Filter zum Erstellen der Linien zwischen den kritischen Punkten erstellen (Vielleicht über FFF, dann FFF anwenden und mögliche Abweichungen verhindern)
//TODO Filter zum Berechnen von FFF auf kritischen Punkten von ProcessObject erstellen (Ableitung in x und y Richtung des x und y Wertes (oder höherer Raumdimensionen) pro Parameterdimension)
//TODO Filter zum Berechnen der Bifurkationen erstellen (multilineare Interpolation der FFF der Nachbarn des kritischen Punktes)
//TODO Filter zum Berechnen der Linien der Bifurkationen erstellen


//TODO Container für Vektorfelder
//TODO Container für ParameterDependentVektorfelder
//TODO Filter um Teile aus ProcessObject wieder rauszuziehen (kritische Punkte, Bifurkationen, Vektorfeld?)


//Backlog Render Iso-Surface with increasing Transparency
//Backlog Store Calculations for faster Example
//Backlog Optimization: Start with reduced resolution and use subdivision to ignore big parts of the vectorfield
//Backlog Höhere Dimensionen


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