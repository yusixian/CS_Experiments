#include "pch.h"
#include "CTransform.h"

void CTransform::identity() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			T[i][j] = 0;
		}
		T[i][i] = 1;
	}
}

void CTransform::multiMatrix() {
	CP2* Pnew = new CP2[num];
	for (int i = 0; i < num; ++i) {
		Pnew[i] = Polnow[i];
	}
	for (int i = 0; i < num; ++i) {
		Polnow[i].x = Pnew[i].x * T[0][0] + Pnew[i].y * T[1][0] + Pnew[i].w * T[2][0];
		Polnow[i].y = Pnew[i].x * T[0][1] + Pnew[i].y * T[1][1] + Pnew[i].w * T[2][1];
		Polnow[i].w = Pnew[i].x * T[0][2] + Pnew[i].y * T[1][2] + Pnew[i].w * T[2][2];
	}
	delete[]Pnew;
}

void CTransform::translate(double tx, double ty) {
	identity();
	T[2][0] = tx;
	T[2][1] = ty;
	multiMatrix();
}

void CTransform::scale(double sx, double sy) {
	identity();
	T[0][0] = sx;
	T[1][1] = sy;
	multiMatrix();
}

void CTransform::rotate(double beta) {
	identity();
	double rad = beta * PI / 180;
	T[0][0] = T[1][1] = cos(rad);
	T[0][1] = sin(rad);	
	T[1][0] = -sin(rad);
	multiMatrix();
}
