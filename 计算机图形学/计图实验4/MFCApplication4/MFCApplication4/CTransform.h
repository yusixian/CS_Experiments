#pragma once
#include "CP2.h"
#include <cmath>
class CTransform {
public:
	int num;			// 点的个数
	CP2* Polnow;
	double PI;
	double T[3][3];		// 变换矩阵
	CTransform() {
		num = 0; 
		Polnow = nullptr;
		identity();
		PI = acos(-1);
	}
	CTransform(int num, CP2* Pnow) {
		this->Polnow = Pnow;
		this->num = num;
		PI = acos(-1);
	}
	void identity();
	void multiMatrix();
	void translate(double tx, double ty);
	void scale(double sx, double sy);
	void rotate(double beta);
};

