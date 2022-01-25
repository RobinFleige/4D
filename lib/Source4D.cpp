#include <Source4D.h>

float Source4D::x_function(int x, int y, int s, int t){
    double xd = x;
    double yd = y;
    double sd = s;
    double td = t;

    return (xd/25-2)*(xd/25-2)+(td/25-2);
}

float Source4D::y_function(int x, int y, int s, int t){
    double xd = x;
    double yd = y;
    double sd = s;
    double td = t;

    return -(yd/25-2);
}
void Source4D::SetWidth(int width){
    width_ = width;
}
void Source4D::SetParamWidth(int param_width){
    param_width_ = param_width;
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

Source4D::Source4D(){
    width_ = 100;
    param_width_ = 100;
}