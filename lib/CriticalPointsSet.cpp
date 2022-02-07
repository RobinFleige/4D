#include <vector>
#include "CriticalPointsSet.h"
#include "Subspace2D.h"
#include "CriticalPointsSubdivide.h"


void CriticalPointsSet::InternalUpdate() {
    std::cout<<"CriticalPointSet"<<std::endl;
    output_.clear();
    input_ = input_connection_->GetOutput();

    Subspace2D* subspace = new Subspace2D();
    CriticalPointsSubdivide* critical_points = new CriticalPointsSubdivide();

    subspace->SetInputConnection(input_connection_);
    critical_points->SetInputConnection(subspace);

    for(int x = 0; x < input_.size(); x++){
        std::vector<vtkSmartPointer<vtkPoints>> points_1;
        for(int y = 0; y < input_[x].size(); y++){
            subspace->SetSValue(x);
            subspace->SetTValue(y);
            critical_points->Update();
            points_1.push_back(critical_points->GetOutput());
        }
        output_.push_back(points_1);
    }
}
