#pragma once
#include <time.h>
#include "Entidad.h"

enum SpritePoblador {
	eCaminarAbajo,
	eCaminarIzquierda,
	eCaminarDerecha,
	eCaminarArriba,

	ehCaminarAbajo,
	ehCaminarIzquierda,
	ehCaminarDerecha,
	ehCaminarArriba,

	eMorir
};

//poblacion al conjunto

class Poblador : public Entidad {
private:
	int cooldown;
	bool enfermo;
	bool saciado;
	bool visible;
	bool movimiento;
	int timew;
	int ID;
	int otrocooldown;
	int tieempo;
	SpritePoblador accion;
public:
	Poblador(Bitmap^ img) {
		Random^rand3 = gcnew Random();
		cooldown = 0;
		otrocooldown = 0;
		tieempo = rand3->Next(2000,7000);
		enfermo = false;
		movimiento = true;
		saciado = false;
		x = rand3->Next(1230);
		y = rand3->Next(126,365);
		timew = clock();
		
		if (rand() % 2 == 0) {
			dx = rand() % 2;
			if (dx == 0) dx = -5;
			if (dx == 1)dx = 5;
		}

		else {
			dy = rand() % 2;
			if (dy == 0) dy = -5;
			else dy == 5;
		}
		ancho = img->Width / 12;
		alto = img->Height / 8;

		switch (rand() % 7) {
		case 0:
			ID = 0;
			IDx = 1;
			accion = eCaminarAbajo;
			break;
		case 1:
			ID = 1;
			IDx = 7;
			accion = eCaminarAbajo;
			break;
		case 2:
			ID = 2;
			IDx = 10;
			accion = eCaminarAbajo;
			break;
		case 3:
			ID = 3;
			IDx = 1;
			accion = ehCaminarAbajo;
			break;
		case 4:
			ID = 4;
			IDx = 4;
			accion = ehCaminarAbajo;
			break;
		case 5:
			ID = 5;
			IDx = 7;
			accion = ehCaminarAbajo;
			break;
		case 6:
			ID = 6;
			IDx = 10;
			accion = ehCaminarAbajo;
			break;
		}
	}
	int GetTime() { return timew; }
	
	SpritePoblador GetAccion() { return accion; }
	void SetVisible(int value) { visible = value; }
	bool GetVisible() { return visible; }
	void SetAccion(SpritePoblador value) { accion = value; }
	void SetEnfermo(bool value) { enfermo = value; }
	bool GetEnfermo() { return enfermo; }
	void SetSaciado(bool value) { saciado = value; }
	bool GetSaciado() { return saciado; }
	void Mover(Graphics^ g, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		if (clock() - timew >= 20000) {
			SetEnfermo(true);
			timew = INT_MAX;
		}
		if (!enfermo && !saciado) {
			if (NextArea().IntersectsWith(r1) ||
				NextArea().IntersectsWith(r2) ||
				NextArea().IntersectsWith(r3) ||
				NextArea().IntersectsWith(r4)) {
				dx *= -1;
				dy *= -1;
			}

			if (movimiento) {

				if (ID >= 0 && ID <= 2) {
					if (!(x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) dx *= -1;
					if (!(y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) dy *= -1;
					if (dx < 0) accion = eCaminarIzquierda;
					else if (dx > 0) accion = eCaminarDerecha;
					else if (dy < 0) accion = eCaminarArriba;
					else if (dy > 0) accion = eCaminarAbajo;
					x += dx;
					y += dy;

				}
				if (ID >= 3 && ID <= 6) {
					if (!(x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) dx *= -1;
					if (!(y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) dy *= -1;
					if (dx < 0) accion = ehCaminarIzquierda;
					else if (dx > 0) accion = ehCaminarDerecha;
					else if (dy < 0) accion = ehCaminarArriba;
					else if (dy > 0) accion = ehCaminarAbajo;
					x += dx;
					y += dy;
				}
				if ((tieempo - clock()) <= 0) {
					movimiento = false;
					tieempo += clock();
					cooldown = clock();
					IDx = 1;
					dx *= -1;
					dy *= -1;
				}
			}
			if (clock() - cooldown >= (rand() % 3400 + 2000)) {
				movimiento = true;
			}


			if (!movimiento) {
				if (ID == 0)IDx = 1;
				else if (ID == 1)IDx = 7;
				else if (ID == 2)IDx = 10;
				else if (ID == 3)IDx = 1;
				else if (ID == 4)IDx = 4;
				else if (ID == 5)IDx = 7;
				else if (ID == 6)IDx = 10;
			}
		}
		else if (enfermo) {
			SetDY(0);
			SetDX(0);
			if (ID >= 0 && ID <= 2)accion = eCaminarAbajo;
			else accion = ehCaminarAbajo;
			if (ID == 0)IDx = 1;
			else if (ID == 1)IDx = 7;
			else if (ID == 2)IDx = 10;
			else if (ID == 3)IDx = 1;
			else if (ID == 4)IDx = 4;
			else if (ID == 5)IDx = 7;
			else if (ID == 6)IDx = 10;
		}
		if (saciado) {
			if (ID >= 0 && ID <= 2)accion = eCaminarIzquierda;
			else accion = ehCaminarIzquierda;
			SetDX(5);
			if (ID == 0) {
				IDx = (IDx + 1) % 3;
			}
			if (ID == 1) {
				if (IDx <= 7)IDx++;
				else IDx = 6;
			}
			if (ID == 2) {
				if (IDx <= 10)IDx++;
				else IDx = 9;
			}
			if (ID == 3) {
				IDx = (IDx + 1) % 3;
			}
			if (ID == 4) {
				if (IDx <= 4)IDx++;
				else IDx = 3;
			}
			if (ID == 5) {
				if (IDx <= 7)
					IDx++;
				else IDx = 6;
			}
			if (ID == 6) {
				if (IDx <= 10)
					IDx++;
				else IDx = 9;
			}
			x -= dx;
			if (x <= 0)SetVisible(false);
		}
	}
	

	void Mostrar(Graphics^ g, Bitmap^ img) {
		Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		if (ID>=0&&ID<=2&&accion >= eCaminarAbajo && accion <= eCaminarArriba) {
			if (ID == 0) {
				IDx = (IDx + 1) % 3;
			}
			if (ID == 1) {
				if (IDx <= 7)IDx++;
				else IDx = 6;
			}
			if (ID == 2) {
				if (IDx <= 10)IDx++;
				else IDx = 9;
			}
		}

		if (ID >=3 && ID<=6 && accion >= ehCaminarAbajo && accion <= ehCaminarArriba) {
			if (ID == 3) {
				IDx = (IDx + 1) % 3;
			}
			if (ID == 4) {
				if (IDx <= 4)IDx++;
				else IDx = 3;
			}
			if (ID == 5) {
				if (IDx <= 7)
					IDx++;
				else IDx = 6;
			}
			if (ID == 6) {
				if (IDx <= 10)
					IDx++;
				else IDx = 9;
			}
		}
		if (GetEnfermo() == true && GetSaciado() == false) {
			if (ID == 0)IDx = 1;
			else if (ID == 1)IDx = 7;
			else if (ID == 2)IDx = 10;
			else if (ID == 3)IDx = 1;
			else if (ID == 4)IDx = 4;
			else if (ID == 5)IDx = 7;
			else if (ID == 6)IDx = 10;
		}
		if (saciado) {
			if (ID >= 0 && ID <= 2)accion = eCaminarIzquierda;
			else accion = ehCaminarIzquierda;
			SetDX(5);
			x -= dx;
			if (x <= 0)SetVisible(false);
		}
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
				poblador->Area().IntersectsWith(r4) == false){
				pobladores.push_back(poblador);
			_sleep(10);
		}
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
				poblador->Area().IntersectsWith(r4) == false) {
				pobladores.push_back(poblador);
				_sleep(10);
			}
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