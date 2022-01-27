#include <Source4D.h>

float Source4D::x_function(int x, int y, int s, int t){
    double xd = normalize(x);
    double yd = normalize(y);
    double sd = normalize(s);
    double td = normalize(t);

    return xd*xd+td;
}

float Source4D::y_function(int x, int y, int s, int t){
    double xd = normalize(x);
    double yd = normalize(y);
    double sd = normalize(s);
    double td = normalize(t);

    return -yd+sd;
}

void Source4D::InternalUpdate(){
    std::vector<std::vector<vtkSmartPointer<vtkImageData>>> st_images;
    for(int t = 0; t < param_width_; t++){
        std::vector<vtkSmartPointer<vtkImageData>> t_images;
        for(int s = 0; s < param_width_; s++){
            vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
            image->SetDimensions(width_,width_,1);
            image->AllocateScalars(VTK_FLOAT, 3);
            for(int y = 0; y < width_; y++){
                for(int x = 0; x < width_; x++){
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
    vector_field =  st_images;
}

std::vector<std::vector<vtkSmartPointer<vtkImageData>>> Source4D::GetInternalOutput(){
    return vector_field;
}

double Source4D::normalize(int i) {
    return i*step_+min_;
}

Source4D::Source4D(int width, double min, double max){
    width_ = width;
    param_width_ = width;
    min_ = min;
    max_ = max;
    step_ = (max_-min_)/width;
}