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

//poblacion al conjunto

class Poblador : public Entidad {
private:
	bool enfermo;
	bool saciado;
	bool visible;
	int time;
	SpritePoblador accion;
public:
	Poblador(Bitmap^ img) {
		enfermo = false;
		saciado = false;
		x = rand() % 1170;
		y = rand() % 550;
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
	void SetVisible(int value) { visible = value; }
	bool GetVisible() { return visible; }
	void SetAccion(SpritePoblador value) { accion = value; }
	void SetEnfermo(bool value) { enfermo = value; }
	bool GetEnfermo() { return enfermo; }
	void SetSaciado(bool value) { saciado = value; }
	bool GetSaciado() { return saciado; }
	void Mover(Graphics^ g, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		if (clock() - time >= 20000) {
			SetEnfermo(true);
			time = INT_MAX;
		}
		if (!enfermo&&!saciado) {
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
		else if(enfermo){
			SetDY(0);
			SetDX(0);
			accion = eCaminarAbajo;
			IDx = 0;
		}
		if (saciado && !enfermo) {
			accion = eCaminarIzquierda;
			IDx = (IDx + 1) % 4;
			SetDX(5);
			x -= dx;
			if (x <= 0)SetVisible(false);
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img) {
		Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		if (accion >= eCaminarAbajo && accion <= eCaminarArriba) IDx = (IDx + 1) % 4;
		if (GetEnfermo() == true&& GetSaciado()==false)IDx = 0;
		if(saciado) IDx = (IDx + 1) % 4;
	}
};

class Pobladores {
private:
	vector<Poblador*> pobladores;
public:
	Pobladores(Bitmap^ img, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for (int i = 0; i < 5; i++) {
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

	void AgregarPobladores(Bitmap^ img, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for (int i = 0; i < 5; i++) {
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

	

	int Size() { return pobladores.size(); }

	Poblador* Get(int pos) { return pobladores[pos]; }

	void Eliminar() {
		for(int i=0;i<pobladores.size();i++)
		if (pobladores[i]->GetVisible()==false)
			pobladores.erase(pobladores.begin() + i);
	}

	bool Colision(Rectangle obj) {
		for each (Poblador * E in pobladores)
			if (E->HitBox().IntersectsWith(obj)) return true;
			return false;
	}

	void Mover(Graphics^ g,Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for each (Poblador * E in pobladores) {
			E->Mover(g, r1, r2, r3, r4);
		}
	}
	void Mostrar(Graphics^ g, Bitmap^ img) { for each (Poblador * E in pobladores) E->Mostrar(g, img); }
};