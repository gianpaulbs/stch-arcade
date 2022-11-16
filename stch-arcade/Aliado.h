#pragma once
#include "Entidad.h"
#include "Poblador.h"

enum SpriteAliado {
	aCaminarArriba,
	aCaminarDerecha,
	aCaminarAbajo,
	aCaminarIzquierda,

	//DefensaPropia
	aAtacarAbajo,
	aAtacarIzquierda,
	aAtacarDerecha,
	aAtacarArriba,

	aMorir
};

class Aliado : public Entidad
{
	private:
		int vidas;
		int puntos;
		int ID;
		bool visible;
		SpriteAliado accion;

	public:
		Aliado(Bitmap^ img, int id) {
			x = 60; y = 60;

			ancho = img->Width / 3;
			alto = img->Height / 4;

			accion = aCaminarAbajo;

			puntos = 0;
			ID = id;
			if (ID == 1) dx = dy = 2;
			else 		 dx = dy = 0;

			visible = false;
		}

		void SetVidas(int value) { vidas += value; }
		void SetPuntos(int value) { puntos += value; }
		void SetVisible(bool value) { visible = value; }
		void SetAccion(SpriteAliado value) {
			if (accion != value)
				IDx = 0;
			accion = value;
		}

		int GetID() { return ID; }
		int GetVidas() { return vidas; }
		int GetPuntos() { return puntos; }
		bool GetVisible() { return visible; }
		SpriteAliado GetAccion() { return accion; }

		void Mover(Graphics^ g, Poblador* poblador) {
			if (!visible) return;

			if (ID == 2) {
				if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
					x += dx;
				if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
					y += dy;
			}
			if (ID == 1) {
				if (x == poblador->GetX())x += 0;
				else if (x > poblador->GetX()) {
					accion = aCaminarIzquierda;
					x -= dx;
				}
				else if ((x < poblador->GetX()) && (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) {
					accion = aCaminarDerecha;
					x += dx;
				}

				if (y == poblador->GetY())y += 0;
				else if (y > poblador->GetY()) {
					//accion = aCaminarArriba;
					y -= dy;
				}
				else if ((y < poblador->GetY()) && (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) {
					//accion = aCaminarAbajo;
					y += dy;
				}

			}
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			if (!visible) return;

			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			//g->DrawRectangle(Pens::Black, Area());
			//g->DrawRectangle(Pens::Blue, HitBox());

			if (accion >= aCaminarArriba && accion <= aCaminarIzquierda && (dx != 0 || dy != 0))
				IDx = (IDx + 1) % 3;
		}
};