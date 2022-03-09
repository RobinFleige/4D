#include <vtkNew.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include <Renderer/DoubleImageRenderer2D.h>
#include <Renderer/ImageRenderer3D.h>
#include <Filter/PointSetTo3D.h>
#include <Filter/PointSetToScalarField.h>
#include <Filter/VectorFieldToImageData.h>
#include <Source/TestSource.h>
#include <Filter/PointSetSubspace.h>
#include <Filter/Subspace4D2D.h>
#include <DataTypeFilter/GetPointsSet.h>
#include <Filter/CalculateFFPoints.h>
#include <Renderer/CriticalPointRenderer3D.h>
#include <Renderer/ImageRenderer4D.h>
#include <Filter/CalculateFFField.h>
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
    auto* renderer = new DoubleImageRenderer2D();


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
    auto fff = new CalculateFFPoints();
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
    auto fff = new CalculateFFPoints();
    auto renderer = new CriticalPointRenderer3D();

    source->Update();
    fff->SetInputConnection(source);
    fff->Update();
    renderer->SetInputConnection(fff);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;

}

int example_3d_with_lines(int size, int min, int max)
{
    auto source = new VectorFieldSource(size,min,max);
    auto critical_points = new CalculateCriticalPoints();
    auto fff = new CalculateFFPoints();
    auto renderer = new CriticalPointRenderer3D();

    source->Update();
    critical_points->SetInputConnection(source);
    critical_points->Update();
    std::cout<<critical_points->GetOutput()->GetCriticalPoints().size()<<std::endl;
    fff->SetInputConnection(critical_points);
    fff->Update();
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

int example_3d_bifurcation(int size, int min, int max){
    auto source = new VectorFieldSource(size,-2,2);
    auto critical_points = new CalculateCriticalPoints();
    auto feature_flow = new CalculateFFField();
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
    critical_points->Update();
    feature_flow->SetInputConnection(critical_points);
    feature_flow->Update();

    points_set->SetInputConnection(feature_flow);
    image->SetParameterID(3);
    image->SetInputConnection(points_set);
    subspace->SetId(size/2);
    subspace->SetInputConnection(image);
    renderer->SetInputConnection(subspace);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int example_4d(int size, int min, int max){
    auto source = new VectorFieldSource(size,min,max);
    auto critical_points = new CalculateCriticalPoints();
    auto fff = new CalculateFFPoints();
    auto renderer = new ImageRenderer4D();

    source->Update();
    critical_points->SetInputConnection(source);
    critical_points->Update();
    std::cout<<critical_points->GetOutput()->GetCriticalPoints().size()<<std::endl;
    fff->SetInputConnection(critical_points);
    fff->Update();
    renderer->SetInputConnection(fff);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    int size = 40;
    int min = -2;
    int max = 2;
    return example_3d(size,min,max);
}