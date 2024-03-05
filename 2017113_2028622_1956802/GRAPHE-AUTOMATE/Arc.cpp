#include "Arc.h"

Arc::Arc(int distance):distance_(distance) {}

Arc::~Arc(){}

void Arc::setDistance(int distance) {
	distance_ = distance;
}
int Arc::getDistance() {
	return distance_;
}