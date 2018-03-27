#include "Projection.h"

Projection::Projection(double _minValue, double _maxValue) {
    minValue = _minValue;
    maxValue = _maxValue;
}

bool Projection::overlaps(Projection p) {
    return !(this->getMin() > p.getMax() || p.getMin() > this->getMax());
}
