#pragma once
#include "Entidad.h"
class Fondo : public Entidad{
public:
	Fondo(Bitmap^img){
		x = y = 0;
		dx = dy = 0;
		ancho = 1281;
		alto = 595;
	}
	~Fondo(){}
	void SumarX() { x++; }
	void RestarX() { x--; }
	void SumarY() { y++; }
	void RestarY() { y--; }
};