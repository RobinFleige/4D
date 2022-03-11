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
#include <Renderer/ImageRenderer4D.h>
#include <Filter/CalculateFFField.h>
#include <vtkSimplePointsReader.h>
#include <DataTypeFilter/GetVectorField.h>
#include "Source/VectorFieldSource.h"
#include "Filter/LIC.h"
#include "./Slider/Slider.h"
#include "Filter/Subspace.h"
#include "Filter/CalculateCriticalPoints.h"
#include "Source/PointSource.h"
#include "Filter/DrawPointsOnImage.h"
#include "Filter/CalculateBifurcationPoints.h"

int two_in_one_image(int size, int min, int max,VectorFieldExampleType type){

    int s = size / 2;
    int t = size / 2;

    auto* source = new VectorFieldSource(size,min,max,type);
    auto* vectorfield = new GetVectorField();
    auto* subspace = new Subspace4D2D();
    auto* image = new VectorFieldToImageData();
    auto* lic = new LIC();
    auto* point_subspace = new PointSetSubspace();
    auto* draw_points1 = new DrawPointsOnImage(2,3);
    auto* critical_points = new CalculateCriticalPoints(5);
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
    vectorfield->SetInputConnection(source);
    subspace->SetInputConnection(vectorfield);
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

int render_general(int size, int min, int max,VectorFieldExampleType type,std::vector<int> used_dimensions, int additional_dimension, int subdivision_depth, bool use_transparency, RenderType render_type){
    auto source = new VectorFieldSource(size,min,max,type);
    auto feature_flow_field = new CalculateFFField();
    auto bifurcation = new CalculateBifurcationPoints(subdivision_depth);
    auto renderer = new ImageRenderer4D("Test",render_type,used_dimensions,additional_dimension,false,use_transparency);

    feature_flow_field->SetInputConnection(source);
    feature_flow_field->Update();
    bifurcation->SetInputConnection(feature_flow_field);
    bifurcation->SetCalculateCriticalPoints(true);
    bifurcation->Update();
    renderer->SetInputConnection(bifurcation);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){
    int size = 10;
    int min = -2;
    int max = 2;
    return render_general(size,min,max,VectorFieldExampleType::simple4d,{0,1,2},3,2,false,RenderType::point);
}