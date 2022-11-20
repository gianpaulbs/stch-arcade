#pragma once

#include "Fondo.h"
#include "Entidad.h"
#include "File.h"

enum SpriteJugador
{
	CaminarAbajo,
	CaminarIzquierda,
	CaminarDerecha,
	CaminarArriba,

	//DefensaPropia
	AtacarAbajo,
	AtacarIzquierda,
	AtacarDerecha,
	AtacarArriba,

	Morir
};

class Jugador : public Entidad
{
	private:
		int vidas;
		int puntos;
		int cubetas;
		int medicamentos;
		int puntosInspiracion;
		bool inspirado;
		SpriteJugador accion;
		File* file;

	public:
		Jugador(Bitmap^ img) {
			file = new File();
			file->readData();
			x=file->getX();
			y = file->getY();
			dx = dy = 0;
			cubetas = 0;
			ancho = img->Width / 4;
			alto = img->Height / 4;

			accion = CaminarAbajo;

			puntos = 0;
			vidas = 3;
			puntosInspiracion = 0;
			medicamentos = 0;
			inspirado = false;
		}

		void SetVidas(int value) {
			vidas += value;
		}

		void SetInspirado(bool value) { 
			inspirado = value; 
		}
		
		void SetCubetas(int value) { 
			cubetas -= value; 
		}
		
		int GetCubetas() {
			return cubetas;
		}
		
		void RecuperarCubeta(int value) { 
			cubetas += value; 
		}
		
		void RecargarCubeta() {
			if (GetX() <= 120 && GetY() <= 60 && cubetas < 3) cubetas++;
		}

		int GetVidas() {
			return vidas;
		}

		int GetMedicamentos() { return medicamentos; }
		void AgregarMedicamentos(int value) { medicamentos += value; }
		void UsarMedicamento(int value) { medicamentos -= value; }

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

		bool GetInspirado() { return inspirado; }

		void SetPuntos(int value) {
			puntos += value;
		}

		void ResetPuntos(int value) {
			puntos = value;
		}

		void SetPuntosInspiracion(int value) { 
			puntosInspiracion = value;
		}

		int GetPuntosInspiracion() { 
			return puntosInspiracion; 
		}

		void Animacion_Vidas_Agua(Graphics^ g) {
			Bitmap^ bmpBarraAgua = gcnew Bitmap("resources/images/barra" + cubetas + ".png");
			Bitmap^ bmpVidas = gcnew Bitmap("resources/images/corazon" + vidas + ".png");

			g->DrawImage(bmpBarraAgua, x, y + 58, 70, 25);
			g->DrawImage(bmpVidas, x - 2, y + 58, 25, 25);

			delete bmpBarraAgua;
			delete bmpVidas;
		}

		void Mover(Graphics^ g) {
			if (puntosInspiracion >= 10)dx = dy *= 7;
			if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
				x += dx;
			if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
				y += dy;
		}


		void Mostrar(Graphics^ g, Bitmap^ img) {
			//g->DrawString("Vidas: " + vidas, gcnew Font("Arial", 12), Brushes::Black, 150, 0);
			//g->DrawString("Puntos: " + puntos, gcnew Font("Arial", 12), Brushes::Black, 0, 40);
			//g->DrawString("Cubetas: " + cubetas, gcnew Font("Arial", 12), Brushes::Black, 0, 80);

			Animacion_Vidas_Agua(g);

			Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
			g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
			/*g->DrawRectangle(Pens::Black, Area());
			g->DrawRectangle(Pens::Blue, HitBox());*/

			if (accion >= CaminarAbajo && accion <= CaminarArriba && (dx != 0 || dy != 0))
				IDx = (IDx + 1) % 4;
			else if (accion == Morir)
				IDx = (IDx + 1) % 6;
		}
};