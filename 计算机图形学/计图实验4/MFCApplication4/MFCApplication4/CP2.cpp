#include "pch.h"
#include "CP2.h"

CP2::CP2() {
	x = y = 0;
	w = 1;
}

CP2::~CP2() {}

CP2::CP2(double x, double y) {
	this->x = x; this->y = y, this->w = 1;
}
