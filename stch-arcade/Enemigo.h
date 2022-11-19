#pragma once

#include <iostream>
#include "Entidad.h"
#include "Jugador.h"

enum SpriteEnemigo
{
	enCaminarAbajo,
	enCaminarIzquierda,
	enCaminarDerecha,
	enCaminarArriba,

	enMorir
};

class Enemigo : public Entidad {
private:
	SpriteEnemigo accion;
	bool visible;
	bool avergonzado;
	bool picardia;
	public:
		Enemigo(Bitmap^ img) {
			x = 600;
			y = 300;
			picardia = false;
			dx = dy = 2;

			ancho = img->Width / 4;
			alto = img->Height / 4;

			accion = enCaminarAbajo;
			visible = true;
			avergonzado = false;
		}

		SpriteEnemigo GetAccion() { return accion; }

		void SetVisible(bool value) { visible = value; }
		void SetAccion(SpriteEnemigo value) {
			if (accion != value)
				IDx = 0;
			accion = value;
		}
		bool GetAvergonzado() { return avergonzado; }
		void SetAvergonzado(bool value) { avergonzado = value; }
		bool GetPicardia() { return picardia; }
		void SetPicardia(bool value) { picardia = value; }
		bool GetVisible() { return visible; }

		void Mover(Graphics^ g, Jugador* jugador, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
			if (!visible) return;
			if (avergonzado == false && picardia == false) {
				SetDX(2);
				if (x == jugador->GetX())x += 0;
				else if (x > jugador->GetX()) {
					accion = enCaminarIzquierda;
					x -= dx;
				}
				else if ((x < jugador->GetX()) && (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) {
					accion = enCaminarDerecha;
					x += dx;
				}

				if (y == jugador->GetY())y += 0;
				else if (y > jugador->GetY()) {
					//accion = aCaminarArriba;
					y -= dy;
				}
				else if ((y < jugador->GetY()) && (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) {
					//accion = aCaminarAbajo;
					y += dy;
								}
			}
			else if (avergonzado == false && picardia == true) {
				
						SetDX(1);	
				
				if (NextArea().IntersectsWith(r1) ||
					NextArea().IntersectsWith(r2) ||
					NextArea().IntersectsWith(r3) ||
					NextArea().IntersectsWith(r4)) {
					dx *= -1;
				}
				if (!(x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) dx *= -1;
				if (!(y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) dy *= -1;
				if (dx < 0) accion = enCaminarIzquierda;
				else if (dx > 0) accion = enCaminarDerecha;
				else if (dy < 0) accion = enCaminarArriba;
				else if (dy > 0) accion = enCaminarAbajo;
				x += dx;
				y += dy;
			}
			else if(avergonzado==true) {
				accion = enCaminarIzquierda;
				SetDX(20);
				x-=dx;
				if (x - 1 == 0)visible = false;
			}
		}


		void nMover(Graphics^ g, Aliado* aliado) {
			if (!visible) return;
			if (avergonzado == false) {
				SetDX(2);
				if (x == aliado->GetX())x += 0;
				else if (x > aliado->GetX()) {
					accion = enCaminarIzquierda;
					x -= dx;
				}
				else if ((x < aliado->GetX()) && (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) {
					accion = enCaminarDerecha;
					x += dx;
				}

				if (y == aliado->GetY())y += 0;
				else if (y > aliado->GetY()) {
					//accion = aCaminarArriba;
					y -= dy;
				}
				else if ((y < aliado->GetY()) && (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) {
					//accion = aCaminarAbajo;
					y += dy;
				}
			}
			else {
				accion = enCaminarIzquierda;
				SetDX(20);
				x -= dx;
				if (x - 1 == 0)visible = false;
			}
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			if (!visible) return;

			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			g->DrawRectangle(Pens::Black, Area());
			g->DrawRectangle(Pens::Blue, HitBox());

			if (accion >= enCaminarAbajo && accion <= enCaminarArriba && (dx != 0 || dy != 0))
				IDx = (IDx + 1) % 3;
			else if (accion == Morir)
				IDx = (IDx + 1) % 6;
		}


		bool Colision(Rectangle obj)
		{
				if (HitBox().IntersectsWith(obj))
					return true;

			return false;
		}

};