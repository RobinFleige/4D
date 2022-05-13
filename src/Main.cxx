#include <vtkNew.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkSliderWidget.h>
#include <Renderer/DoubleImageRenderer2D.h>
#include <Filter/PointSetToScalarField.h>
#include <Filter/VectorFieldToImageData.h>
#include <Filter/PointSetSubspace.h>
#include <DataTypeFilter/GetVectorField.h>
#include <DataTypeFilter/GetPointsSet.h>
#include <Renderer/ImageRenderer4D.h>
#include <Filter/CalculateFFField.h>
#include <Filter/ReformDimension.h>
#include "Source/VectorFieldSource.h"
#include "Filter/LIC.h"
#include "./Slider/Slider.h"
#include "Source/PointSource.h"
#include "Filter/DrawPointsOnImage.h"
#include "Filter/CalculateBifurcationPoints.h"
#include "Filter/CalculateCriticalPoints.h"

int two_in_one_image(int size, double min, double max,VectorFieldExampleType type){

    int s = size / 2;
    int t = size / 2;

    auto* source = new VectorFieldSource(size,min,max,type);
    auto* subspace = new GetVectorField(2);
    auto* image = new VectorFieldToImageData();
    auto* lic = new LIC();
    auto* point_subspace = new PointSetSubspace();
    auto* draw_points1 = new DrawPointsOnImage(2,3);
    auto* critical_points = new CalculateBifurcationPoints(5);
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
    point_source->SetCoordinates({(double)s,(double)t});
    draw_points2->SetInputConnection(scalar_field);
    draw_points2->SetSecondaryInputConnection(point_source);
    renderer->SetSecondaryInputConnection(draw_points2);

    renderer->Update();
    std::cout<<"Finished"<<std::endl;
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int render_general(int size, double min, double max,VectorFieldExampleType type,std::vector<int> used_dimensions, int additional_dimension, int subdivision_depth, bool use_transparency, RenderType render_type){
    auto source = new VectorFieldSource(size,min,max,type);
    auto feature_flow_field = new CalculateFFField();
    auto bifurcation = new CalculateBifurcationPoints(subdivision_depth);
    auto critical = new CalculateCriticalPoints(subdivision_depth);
    auto renderer = new ImageRenderer4D(render_type,used_dimensions,additional_dimension,false,use_transparency);

    feature_flow_field->SetInputConnection(source);
    feature_flow_field->Update();
    bifurcation->SetInputConnection(feature_flow_field);
    bifurcation->Update();
    critical->SetInputConnection(bifurcation);
    critical->Update();
    renderer->SetInputConnection(critical);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int reduced_dimensions(int size, double min, double max,VectorFieldExampleType type,std::vector<int> used_dimensions, int additional_dimension, int subdivision_depth, bool use_transparency, RenderType render_type){
    auto source = new VectorFieldSource(size,min,max,type);
    auto feature_flow_field = new CalculateFFField();
    auto reform_dimension = new ReformDimension();
    auto feature_flow_field_2 = new CalculateFFField();
    auto bifurcation = new CalculateBifurcationPoints(subdivision_depth);
    auto critical = new CalculateCriticalPoints(subdivision_depth);
    auto renderer = new ImageRenderer4D(render_type, used_dimensions,additional_dimension,true,use_transparency);

    feature_flow_field->SetInputConnection(source);
    feature_flow_field->Update();
    reform_dimension->SetInputConnection(feature_flow_field);
    reform_dimension->Update();
    feature_flow_field_2->SetInputConnection(reform_dimension);
    feature_flow_field_2->Update();
    bifurcation->SetInputConnection(feature_flow_field_2);
    bifurcation->Update();
    critical->SetInputConnection(bifurcation);
    critical->Update();
    renderer->SetInputConnection(critical);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int double_reduced(int size, double min, double max,VectorFieldExampleType type,std::vector<int> used_dimensions, int additional_dimension, int subdivision_depth, bool use_transparency, RenderType render_type){
    auto source = new VectorFieldSource(size,min,max,type);
    auto feature_flow_field = new CalculateFFField();
    auto reform_dimension = new ReformDimension();
    auto feature_flow_field_2 = new CalculateFFField();
    auto reform_dimension_2 = new ReformDimension();
    auto feature_flow_field_3 = new CalculateFFField();
    auto bifurcation = new CalculateBifurcationPoints(subdivision_depth);
    auto critical = new CalculateCriticalPoints(subdivision_depth);
    auto renderer = new ImageRenderer4D(render_type, used_dimensions,additional_dimension,true,use_transparency);

    feature_flow_field->SetInputConnection(source);
    feature_flow_field->Update();
    reform_dimension->SetInputConnection(feature_flow_field);
    reform_dimension->Update();
    feature_flow_field_2->SetInputConnection(reform_dimension);
    feature_flow_field_2->Update();
    reform_dimension_2->SetInputConnection(feature_flow_field_2);
    reform_dimension_2->Update();
    feature_flow_field_3->SetInputConnection(reform_dimension_2);
    feature_flow_field_3->Update();
    bifurcation->SetInputConnection(feature_flow_field_3);
    bifurcation->Update();
    critical->SetInputConnection(bifurcation);
    critical->Update();
    renderer->SetInputConnection(critical);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int triple_reduced(int size, double min, double max,VectorFieldExampleType type,std::vector<int> used_dimensions, int additional_dimension, int subdivision_depth, bool use_transparency, RenderType render_type){
    auto source = new VectorFieldSource(size,min,max,type);
    auto feature_flow_field = new CalculateFFField();
    auto reform_dimension = new ReformDimension();
    auto feature_flow_field_2 = new CalculateFFField();
    auto reform_dimension_2 = new ReformDimension();
    auto feature_flow_field_3 = new CalculateFFField();
    auto reform_dimension_3 = new ReformDimension();
    auto critical = new CalculateCriticalPoints(subdivision_depth);
    auto renderer = new ImageRenderer4D(render_type, used_dimensions,additional_dimension,true,use_transparency);

    feature_flow_field->SetInputConnection(source);
    feature_flow_field->Update();
    reform_dimension->SetInputConnection(feature_flow_field);
    reform_dimension->Update();
    feature_flow_field_2->SetInputConnection(reform_dimension);
    feature_flow_field_2->Update();
    reform_dimension_2->SetInputConnection(feature_flow_field_2);
    reform_dimension_2->Update();
    feature_flow_field_3->SetInputConnection(reform_dimension_2);
    feature_flow_field_3->Update();
    reform_dimension_3->SetInputConnection(feature_flow_field_3);
    reform_dimension_3->Update();
    critical->SetInputConnection(reform_dimension_3);
    critical->Update();
    renderer->SetInputConnection(critical);
    renderer->Update();
    renderer->GetInteractor()->Start();

    return EXIT_SUCCESS;
}

int test(){
    int length = 5;
    auto source1 = new VectorFieldSource(length,-2,2,VectorFieldExampleType::simple2d2d);
    auto feature_flow_field = new CalculateFFField();
    auto reform_dimension = new ReformDimension();
    auto source2 = new VectorFieldSource(length,-2,2,VectorFieldExampleType::simple2d2dr);

    source1->Update();
    feature_flow_field->SetInputConnection(source1);
    feature_flow_field->Update();
    reform_dimension->SetInputConnection(feature_flow_field);
    reform_dimension->Update();
    source2->Update();

    for(int s = 0; s < length; s++){
        for(int t = 0; t < length; t++){
            for(int x = 0; x < length; x++){
                for(int y = 0; y < length; y++){
                    std::cout<<s<<" "<<t<<" "<<x<<" "<<y<<std::endl;
                    for(int i = 0; i < 3; i++){
                        double a = reform_dimension->GetOutput()->GetData({s,t,x,y}).values_[i];
                        double b = source2->GetOutput()->GetData({s,t,x,y}).values_[i];
                        double c = a-b;
                        std::cout<<a<<" "<<b<<" "<<c<<std::endl;
                    }
                    std::cout<<std::endl;
                }
            }
        }
    }


    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){
    //test();
    //return 0;
    int size = 11;
    double min = -2;
    double max = 2;
    return render_general(size, min, max, VectorFieldExampleType::circle2d2d, {0, 1, 2}, 3, 2, false, RenderType::point);
}