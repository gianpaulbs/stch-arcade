#pragma once
#include <time.h>
#include "Entidad.h"

enum SpritePoblador {
	eCaminarAbajo,
	eCaminarIzquierda,
	eCaminarDerecha,
	eCaminarArriba,

	eMorir
};

class Poblador : public Entidad {
private:
	bool enfermo;
	int time;
	SpritePoblador accion;
public:
	Poblador(Bitmap^ img) {
		enfermo = false;
		x = rand() % 1200;
		y = rand() % 680;
		time = clock();
		if (rand() % 2 == 0) {
			dx = rand() % 2;
			if (dx == 0) dx = -1;
		}

		else {
			dy = rand() % 2;
			if (dy == 0) dy = -1;
		}

		ancho = img->Width / 4;
		alto = img->Height / 4;
		accion = eCaminarAbajo;
	}
	int GetTime() { return time; }
	
	SpritePoblador GetAccion() { return accion; }

	void SetAccion(SpritePoblador value) { accion = value; }
	void SetEnfermo(bool value) { enfermo = value; }
	bool GetEnfermo() { return enfermo; }

	void Mover(Graphics^ g, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		if (time >= 3000)enfermo = true;
		if (!enfermo) {
			if (NextArea().IntersectsWith(r1) ||
				NextArea().IntersectsWith(r2) ||
				NextArea().IntersectsWith(r3) ||
				NextArea().IntersectsWith(r4)) {
				dx *= -1;
				dy *= -1;
			}
			if (!(x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) dx *= -1;
			if (!(y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) dy *= -1;
			if (dx < 0) accion = eCaminarIzquierda;
			else if (dx > 0) accion = eCaminarDerecha;
			else if (dy < 0) accion = eCaminarArriba;
			else if (dy > 0) accion = eCaminarAbajo;
			x += dx;
			y += dy;
		}
		else {
			dy = dx = 0;
			accion = eCaminarAbajo;
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img) {
		Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		if (accion >= eCaminarAbajo && accion <= eCaminarArriba) IDx = (IDx + 1) % 4;
	}
};

class Pobladores {
private:
	vector<Poblador*> pobladores;
public:
	Pobladores(Bitmap^ img, int cant, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for (int i = 0; i < cant; i++) {
			Poblador* poblador = new Poblador(img);
			if (poblador->Area().IntersectsWith(r1) == false &&
				poblador->Area().IntersectsWith(r2) == false &&
				poblador->Area().IntersectsWith(r3) == false &&
				poblador->Area().IntersectsWith(r4) == false)
			pobladores.push_back(poblador);

			else {
				delete poblador;
				i--;
			}
		}
	}

	~Pobladores() { for each (Poblador * E in pobladores) delete E; }

	void Eliminar(int pos) { pobladores.erase(pobladores.begin() + pos); }

	int Size() { return pobladores.size(); }

	Poblador* Get(int pos) { return pobladores[pos]; }

	bool Colision(Rectangle obj) {
		for each (Poblador * E in pobladores)
			if (E->HitBox().IntersectsWith(obj)) return true;
			return false;
	}

	void Mover(Graphics^ g,Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for each (Poblador * E in pobladores) {
			if (E->GetTime() >= 3000) {
				E->SetEnfermo(true);
				E->SetDX(0);
				E->SetDY(0);
			}
			E->Mover(g, r1, r2, r3, r4);
		}
	}
	void Mostrar(Graphics^ g, Bitmap^ img) { for each (Poblador * E in pobladores) E->Mostrar(g, img); }
};