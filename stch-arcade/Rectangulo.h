#pragma once
#include "Entidad.h"

class Rectangulo : public Entidad {
public:
	Rectangulo(int x, int y,int ancho, int alto) {
		this->x = x;
		this->y = y;

		this->ancho = ancho;
		this->alto = alto;
		dx = dy = 0;
	}
	~Rectangulo(){}
	void Mostrar(Graphics^ g)
	{
		g->FillRectangle(Brushes::Transparent, Area());
	}
	bool Colision(Rectangle obj)
	{
		if (NextArea().IntersectsWith(obj)) return true;
		return false;
	}
};