#pragma once
#include <time.h>
#include "Entidad.h"

enum SpritePoblador
{
	eCaminarAbajo,
	eCaminarIzquierda,
	eCaminarDerecha,
	eCaminarArriba,

	eMorir
};

class Poblador : public Entidad
{
	SpritePoblador accion;
	public:
		int tiempo;
		bool movido;

		Poblador(Bitmap^ img) {
			movido = false;
			tiempo = clock() + 10 * 1000;
			x = rand() % 800;
			y = rand() % 350;

			if (rand() % 2 == 0)
			{
				//DX
				dx = rand() % 2;
				if (dx == 0)
					dx = -1;
			}
			else
			{
				//DY
				dy = rand() % 2;
				if (dy == 0)
					dy = -1;
			}

			ancho = img->Width / 4;
			alto = img->Height / 4;

			accion = eCaminarAbajo;
		}

		SpritePoblador GetAccion() {
			return accion;
		}

		void SetAccion(SpritePoblador value) {
			accion = value;
		}

		void Mover(Graphics^ g) {
			if (clock() >= tiempo) {
				if (!(x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width))
					dx *= -1;
				if (!(y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height))
					dy *= -1;

				if (dx < 0)
					accion = eCaminarIzquierda;
				else if (dx > 0)
					accion = eCaminarDerecha;
				else if (dy < 0)
					accion = eCaminarArriba;
				else if (dy > 0)
					accion = eCaminarAbajo;
				x += dx;
				y += dy;

				movido = true;
				tiempo += 5000;
			}
			movido = false;
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			g->DrawRectangle(Pens::Black, Area());
			g->DrawRectangle(Pens::Blue, HitBox());

			if (accion >= eCaminarAbajo && accion <= eCaminarArriba)
				IDx = (IDx + 1) % 4;
			else if (accion == eMorir)
				IDx = (IDx + 1) % 6;
		}
};

class Pobladores
{
	vector<Poblador*> pobladores;
	public:
		Pobladores(Bitmap^ img, int cant) {
			for (int i = 0; i < cant; i++)
				pobladores.push_back(new Poblador(img));
		}

		~Pobladores() {
			for each (Poblador * E in pobladores)
				delete E;
		}

		void Eliminar(int pos) {
			pobladores.erase(pobladores.begin() + pos);
		}

		int Size() {
			return pobladores.size();
		}

		Poblador* Get(int pos) {
			return pobladores[pos];
		}

		void Matar(Rectangle rect) {
			for (int i = 0; i < pobladores.size(); i++)
			{
				Poblador* E = pobladores[i];
				if (E->HitBox().IntersectsWith(rect))
				{
					//enemigos.erase(enemigos.begin() + i--);
					//cant++;
					E->SetDX(0);
					E->SetDY(0);
					E->SetAccion(eMorir);
				}
			}
		}

		bool Colision(Rectangle obj) {
			for each (Poblador * E in pobladores)
				if (E->HitBox().IntersectsWith(obj))
					return true;

			return false;
		}

		void Mover(Graphics^ g) {
			for each (Poblador * E in pobladores)
				E->Mover(g);
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			for each (Poblador * E in pobladores)
				E->Mostrar(g, img);
		}
};