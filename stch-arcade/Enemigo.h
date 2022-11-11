#pragma once
#include <iostream>
#include "Entidad.h"

enum SpriteEnemigo
{
	eCaminarAbajo,
	eCaminarIzquierda,
	eCaminarDerecha,
	eCaminarArriba,

	eMorir
};

class Enemigo : public Entidad {
	SpriteEnemigo accion;
	public:
		Enemigo(Bitmap^ img) {
			x = rand() % 200;
			y = rand() % 200;

			if (rand() % 2 == 0)
			{
				//DX
				dx = rand() % 10 - 5;
				if (dx == 0)
					dx = 5;
			}
			else
			{
				//DY
				dy = rand() % 10 - 5;
				if (dy == 0)
					dy = 5;
			}

			ancho = img->Width / 4;
			alto = img->Height / 4;

			accion = eCaminarAbajo;
		}

		SpriteEnemigo GetAccion() { return accion; }

		void SetAccion(SpriteEnemigo value) { accion = value; }
		void Mover(Graphics^ g)
		{
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
		}

		void Mostrar(Graphics^ g, Bitmap^ img)
		{
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

class Enemigos {
	vector<Enemigo*> enemigos;
	public:
		Enemigos(Bitmap^ img, int cant) {
			for (int i = 0; i < cant; i++)
				enemigos.push_back(new Enemigo(img));
		}

		~Enemigos() {
			for each (Enemigo * E in enemigos)
				delete E;
		}

		void Eliminar(int pos) {
			enemigos.erase(enemigos.begin() + pos);
		}

		int Size() { return enemigos.size(); }
		
		Enemigo* Get(int pos) { return enemigos[pos]; }

		void Matar(Rectangle rect) {
			for (int i = 0; i < enemigos.size(); i++)
			{
				Enemigo* E = enemigos[i];
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
			for each (Enemigo * E in enemigos)
				if (E->HitBox().IntersectsWith(obj))
					return true;

			return false;
		}

		void Mover(Graphics^ g) {
			for each (Enemigo * E in enemigos)
				E->Mover(g);
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			for each (Enemigo * E in enemigos)
				E->Mostrar(g, img);
		}
};