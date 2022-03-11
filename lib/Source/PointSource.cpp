#include "PointSource.h"

#include <utility>

void PointSource::SetCoordinates(std::vector<double> coordinates) {
    coordinates_ = std::move(coordinates);
    Invalidate();
}

void PointSource::InternalUpdate() {
    output_.clear();
    output_.push_back(new Point(coordinates_));
}

PointSource::PointSource() {
    Invalidate();
}


void PointSource::OnChange(double value, int id) {
    coordinates_[id] = value;
    Invalidate();
}