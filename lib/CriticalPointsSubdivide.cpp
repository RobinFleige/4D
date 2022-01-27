#include "CriticalPointsSubdivide.h"

vtkSmartPointer<vtkPoints> CriticalPointsSubdivide::GetInternalOutput() {
    return critical_points_;
}

void CriticalPointsSubdivide::InternalUpdate() {
    critical_points_ = vtkSmartPointer<vtkPoints>::New();
    input_connection_->Update();
    vtkSmartPointer<vtkImageData> input = input_connection_->GetOutput();
    for (int x = 0; x < input->GetDimensions()[0]-1; x++) {
        for (int y = 0; y < input->GetDimensions()[1]-1; y++) {
            std::vector<double*> pixel;
            pixel.push_back(static_cast<double*>(input->GetScalarPointer(x,y,0)));
            pixel.push_back(static_cast<double*>(input->GetScalarPointer(x+1,y,0)));
            pixel.push_back(static_cast<double*>(input->GetScalarPointer(x,y+1,0)));
            pixel.push_back(static_cast<double*>(input->GetScalarPointer(x+1,y+1,0)));
            int positive_x = 0;
            int positive_y = 0;
            for(int i = 0; i < 4; i++){
                if(pixel[i][0] > 0){
                    positive_x++;
                }
                if(pixel[i][1] > 0){
                    positive_y++;
                }
            }
            if(positive_x != 0 && positive_x != 4 && positive_y != 0 && positive_y != 4){
                critical_points_->InsertNextPoint(x,y,0);
            }
        }
    }

    //TODO Check für kritische Punkte genau auf Grenze
    //TODO Filter for duplicates
    //TODO Subdivide to find exact Points -> https://stackoverflow.com/questions/808441/inverse-bilinear-interpolation
}
