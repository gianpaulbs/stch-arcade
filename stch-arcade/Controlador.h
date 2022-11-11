#pragma once
#include "Jugador.h"
#include "Poblador.h"
#include "Aliado.h"

using namespace System::Windows::Forms;

ref class ControladorJuego {
	private:
		Jugador* jugador;
		Pobladores* pobladores;
		Aliado* aliadoManual;
		Aliado* aliadoAutomatico;
		Bitmap^ imgTrol;
		Bitmap^ imgJugador;
		Bitmap^ imgPoblador;
		Bitmap^ imgAliado;

		int pobladorAsaciar;
		int cooldownAtaqueEnemigo;
		int tiempo;
		bool resultado;
		int objetivo;

	public:
		ControladorJuego()
		{
			imgJugador = gcnew Bitmap("resources/images/bruno.png");
			imgPoblador = gcnew Bitmap("resources/images/rojo.png");
			imgAliado = gcnew Bitmap("resources/images/zombies1.png");

			jugador = new Jugador(imgJugador);
			pobladores = new Pobladores(imgPoblador, 30);
			aliadoAutomatico = new Aliado(imgAliado, 1);
			aliadoManual = new Aliado(imgAliado, 2);
			pobladorAsaciar = 0;

			cooldownAtaqueEnemigo = 0;
			objetivo = 5 + 3;
			tiempo = 90 * 1000 + clock();
		}

		~ControladorJuego() {
			delete jugador, pobladores, aliadoManual, aliadoAutomatico;
		}

		bool GetResultado() {
			return resultado;
		}

		void MovimientoJugador(bool accion, Keys tecla) {
			int v = 3;

			if (accion == true)
			{
				if (tecla == Keys::W)
				{
					jugador->SetDY(-v);
					jugador->SetAccion(CaminarArriba);
				}
				else if (tecla == Keys::S)
				{
					jugador->SetDY(v);
					jugador->SetAccion(CaminarAbajo);
				}
				else if (tecla == Keys::A)
				{
					jugador->SetDX(-v);
					jugador->SetAccion(CaminarIzquierda);
				}
				else if (tecla == Keys::D)
				{
					jugador->SetDX(v);
					jugador->SetAccion(CaminarDerecha);
				}

			}
			else
			{
				if (tecla == Keys::W)
					jugador->SetDY(0);
				else if (tecla == Keys::S)
					jugador->SetDY(0);
				else if (tecla == Keys::A)
					jugador->SetDX(0);
				else if (tecla == Keys::D)
					jugador->SetDX(0);
			}


			if (accion == true)
			{
				if (tecla == Keys::I)
				{
					aliadoManual->SetDY(-v);
					aliadoManual->SetAccion(aCaminarArriba);
				}
				else if (tecla == Keys::K)
				{
					aliadoManual->SetDY(v);
					aliadoManual->SetAccion(aCaminarAbajo);
				}
				else if (tecla == Keys::J)
				{
					aliadoManual->SetDX(-v);
					aliadoManual->SetAccion(aCaminarIzquierda);
				}
				else if (tecla == Keys::L)
				{
					aliadoManual->SetDX(v);
					aliadoManual->SetAccion(aCaminarDerecha);
				}

			}
			else
			{
				if (tecla == Keys::I)
					aliadoManual->SetDY(0);
				else if (tecla == Keys::K)
					aliadoManual->SetDY(0);
				else if (tecla == Keys::J)
					aliadoManual->SetDX(0);
				else if (tecla == Keys::L)
					aliadoManual->SetDX(0);
			}
		}

		bool Mover(Graphics^ g)
		{
			/*if (enemigos->Colision(jugador->HitBox()) && clock() - cooldownAtaqueEnemigo >= 2000)
			{
				jugador->SetVidas(-1);
				cooldownAtaqueEnemigo = clock();

				if (jugador->GetVidas() == 0)
				{
					jugador->SetAccion(Morir);
				}
			}*/

			if (clock() >= tiempo) {
				jugador->SetAccion(Morir);
			}

			if (objetivo == jugador->GetPuntos()) {
				resultado = true;
				return false;
			}

			if (jugador->GetAccion() != Morir)
				jugador->Mover(g);

			pobladores->Mover(g);
			aliadoManual->Mover(g, pobladores->Get(pobladorAsaciar));
			aliadoAutomatico->Mover(g, pobladores->Get(pobladorAsaciar));

			return true;
		}

		void Mostrar(Graphics^ g)
		{
			g->DrawString("Tiempo: " + ((tiempo - clock()) / 1000), gcnew Font("Arial", 12), Brushes::Black, 0, 20);
			pobladores->Mostrar(g, imgPoblador);
			jugador->Mostrar(g, imgJugador);
			aliadoManual->Mostrar(g, imgAliado);
			aliadoAutomatico->Mostrar(g, imgAliado);
		}
};