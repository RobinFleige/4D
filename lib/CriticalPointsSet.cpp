#include <vector>
#include "CriticalPointsSet.h"
#include "Subspace.h"
#include "CriticalPointsSubdivide.h"

std::vector<std::vector<vtkSmartPointer<vtkPoints>>> CriticalPointsSet::GetInternalOutput() {
    return points_;
}

void CriticalPointsSet::InternalUpdate() {
    points_.clear();
    Subspace* subspace = new Subspace();
    CriticalPointsSubdivide* critical_points = new CriticalPointsSubdivide();
    critical_points->SetInputConnection(subspace);


    subspace->SetInputConnection(input_connection_);
    for(int x = 0; x < input_connection_->GetOutput().size(); x++){
        std::vector<vtkSmartPointer<vtkPoints>> points_1;
        for(int y = 0; y < input_connection_->GetOutput()[x].size(); y++){
            subspace->SetSValue(x);
            subspace->SetTValue(y);
            subspace->Update();
            critical_points->Update();
            points_1.push_back(critical_points->GetOutput());
        }
        points_.push_back(points_1);
    }
}
