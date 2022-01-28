#include <vector>
#include "CriticalPointsSet.h"
#include "Subspace.h"
#include "CriticalPointsSubdivide.h"


void CriticalPointsSet::InternalUpdate() {
    output_.clear();
    Subspace* subspace = new Subspace();
    CriticalPointsSubdivide* critical_points = new CriticalPointsSubdivide();
    critical_points->SetInputConnection(subspace);


    subspace->SetInputConnection(input_connection_);
    for(int x = 0; x < input_->size(); x++){
        std::vector<vtkSmartPointer<vtkPoints>> points_1;
        for(int y = 0; y < input_[x].size(); y++){
            subspace->SetSValue(x);
            subspace->SetTValue(y);
            subspace->Update();
            critical_points->Update();
            points_1.push_back(critical_points->GetOutput());
        }
        output_.push_back(points_1);
    }
}
