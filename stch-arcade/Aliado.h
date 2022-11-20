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

class Aliado : public Entidad {
	private:
		int vidas;
		int puntos;
		int cubetas;
		int medicamentos;
		int ID;
		bool visible;
		SpriteAliado accion;

	public:
		Aliado(Bitmap^ img, int id) {
			x = 65; y = 65;

			ancho = img->Width / 3;
			alto = img->Height / 4;

			accion = aCaminarAbajo;
			cubetas = 0;
			puntos = 0;
			ID = id;
			if (ID == 1) dx = dy = 2;
			else 		 dx = dy = 0;
			medicamentos = 0;
			vidas = 3;

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
		void RecuperarCubeta(int value) { cubetas += value; }

		int GetID() { return ID; }
		int GetVidas() { return vidas; }
		int GetPuntos() { return puntos; }
		bool GetVisible() { return visible; }
		SpriteAliado GetAccion() { return accion; }
		int GetCubetas() { return cubetas; }
		void SetCubetas(int value) { cubetas -= value; }
		void RecargarCubeta() {
			if (GetX() <= 60 && GetY() <= 60 && cubetas < 3)cubetas=3;
		}

		int GetMedicamentos() { return medicamentos; }
		void AgregarMedicamentos(int value) { medicamentos += value; }
		void UsarMedicamento(int value) { medicamentos -= value; }

		void Animacion_Vidas_Agua(Graphics^ g) {
			Bitmap^ bmpBarraAgua = gcnew Bitmap("resources/images/barra" + cubetas + ".png");
			Bitmap^ bmpVidas = gcnew Bitmap("resources/images/corazon" + vidas + ".png");

			g->DrawImage(bmpBarraAgua, x, y + 58, 70, 25);
			g->DrawImage(bmpVidas, x - 2, y + 58, 25, 25);

			delete bmpBarraAgua;
			delete bmpVidas;
		}

		void Mover(Graphics^ g, Poblador* poblador) {
			if (!visible) return;

			if (ID == 2) {
				if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
					x += dx;
				if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
					y += dy;
			}
			if (ID == 1) {
				if (GetCubetas() > 0) {
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
				else if (cubetas==0){
					if (x <= 60) x+= 0;
					else if (x > 60) {
						accion = aCaminarIzquierda;
						x -= dx;
					}
					else if (x < 60 && (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)) {
						accion = aCaminarDerecha;
						x += dx;
					}

					if (y <= 60)y += 0;
					else if (y > 60) {
						//accion = aCaminarArriba;
						y -= dy;
					}
					else if ((y < 60) && (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)) {
						//accion = aCaminarAbajo;
						y += dy;
					}
					RecargarCubeta();
				}

			}
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			if (!visible) return;

			Animacion_Vidas_Agua(g);

			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			//g->DrawRectangle(Pens::Black, Area());
			//g->DrawRectangle(Pens::Blue, HitBox());

			if (accion >= aCaminarArriba && accion <= aCaminarIzquierda && (dx != 0 || dy != 0))
				IDx = (IDx + 1) % 3;
		}
};