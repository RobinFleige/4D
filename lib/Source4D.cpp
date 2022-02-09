#include <Source4D.h>
#include <valarray>

float Source4D::x_function(int x, int y, int s, int t){
    double xd = normalize(x);
    double yd = normalize(y);
    double sd = normalize(s);
    double td = normalize(t);

    //1. xd*xd+td; -> vertical zweigeteilt
    //2. xd*xd+td+sd -> schräg zweigeteilt
    //3. xd*xd+td*td+sd*sd-1 -> durch Kreis geteilt
    //4. xd*xd+td -> 2 bifurcationen (linien liegen aufeinander)
    //5. (xd*xd+td)*(xd*xd+sd) -> 2 kreuzende Bifurcation Lines (Mit fragmenten im weißen Bereich)
    //6. (xd-td)*(xd+td)*(xd-1-sd)*(xd-1+sd) -> seltsame Box
    //7. (xd*xd+td)*(yd-1)-(xd*xd+sd)*(yd+1) -> 2 kreuzende Bifurcation Lines (kritische Punkte werden nicht korrekt berechnet)
    //8. (xd*xd+td-1)*(yd-1)+(xd*xd+td+1)*(yd+1) -> doppelt parallel vertical zweigeteilt (kritische Punkte werden nicht korrekt berechnet)
    return (xd*xd+td-1)*(yd-1)+(xd*xd+td+1)*(yd+1);
}

float Source4D::y_function(int x, int y, int s, int t){
    double xd = normalize(x);
    double yd = normalize(y);
    double sd = normalize(s);
    double td = normalize(t);

    //1. -yd+sd
    //2. -yd
    //3. -yd
    //4. -yd*yd+sd
    //5. -yd
    //6. -yd
    //7. (yd+1)*(yd-1)
    //8. (yd+1)*(yd-1)
    return (yd+1)*(yd-1);
}

void Source4D::InternalUpdate(){
    output_.clear();
    for(int t = 0; t < param_width_; t++){
        std::vector<vtkSmartPointer<vtkImageData>> t_images;
        for(int s = 0; s < param_width_; s++){
            vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
            image->SetDimensions(width_,width_,1);
            image->AllocateScalars(VTK_FLOAT, 3);
            for(int y = 0; y < width_; y++){
                for(int x = 0; x < width_; x++){
                    auto* pixel = static_cast<float*>(image->GetScalarPointer(x, y, 0));
                    pixel[0] = x_function(x,y,s,t);
                    pixel[1] = y_function(x,y,s,t);
                    pixel[2] = 0.0;
                }
            }
            image->GetPointData()->SetActiveVectors("ImageScalars");
            image->Modified();
            t_images.push_back(image);
        }
        output_.push_back(t_images);
    }
}

double Source4D::normalize(int i) const {
    return i*step_+min_;
}

Source4D::Source4D(int width, double min, double max){
    width_ = width;
    param_width_ = width;
    min_ = min;
    max_ = max;
    step_ = (max_-min_)/width;
    Invalidate();
}