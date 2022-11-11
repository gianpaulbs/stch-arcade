#pragma once
#include "Entidad.h"

enum SpriteJugador
{
	CaminarAbajo,
	CaminarIzquierda,
	CaminarDerecha,
	CaminarArriba,

	Morir
};

class Jugador : public Entidad
{
	private:
		int vidas;
		int puntos;
		SpriteJugador accion;
		
	public:
		Jugador(Bitmap^ img)
		{
			x = 60; y = 60;
			dx = dy = 0;

			ancho = img->Width / 4;
			alto = img->Height / 4;

			accion = CaminarArriba;

			puntos = 0;
			vidas = 3;
		}

		void SetVidas(int value) {
			vidas += value;
		}

		int GetVidas() {
			return vidas;
		}

		void SetAccion(SpriteJugador value) {
			if (accion != value)
				IDx = 0;
			accion = value;
		}

		SpriteJugador GetAccion() {
			return accion;
		}

		int GetPuntos() {
			return puntos;
		}

		void SetPuntos(int value) {
			puntos += value;
		}

		void Mover(Graphics^ g) {
			if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
				x += dx;
			if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
				y += dy;
		}

		void Mostrar(Graphics^ g, Bitmap^ img) {
			g->DrawString("Vidas: " + vidas, gcnew Font("Arial", 12), Brushes::Black, 0, 0);
			g->DrawString("Puntos: " + puntos, gcnew Font("Arial", 12), Brushes::Black, 0, 40);

			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			g->DrawRectangle(Pens::Black, Area());
			g->DrawRectangle(Pens::Blue, HitBox());


			if (accion >= CaminarAbajo && accion <= CaminarArriba && (dx != 0 || dy != 0))
				IDx = (IDx + 1) % 4;
			else if (accion == Morir)
				IDx = (IDx + 1) % 6;
		}
};