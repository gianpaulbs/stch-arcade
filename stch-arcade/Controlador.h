#include <time.h>
#include "Info.h"
#include "Jugador.h"
#include "Poblador.h"
#include "Aliado.h"
#include "Enemigo.h"
#include "Rectangulo.h"
#include <vector>
using namespace std;

using namespace System::Windows::Forms;

ref class ControladorJuego {
private:
	Jugador* jugador;
	Aliado* aliadoManual;
	Aliado* aliadoAutomatico;
	Enemigo* enemigoHeroe;
	Enemigo* enemigoAliadoAutomatico;
	Enemigo* enemigoAliadoManual;


	Pobladores* pobladores;
	Rectangulo* rectangulo1;
	Rectangulo* rectangulo2;
	Rectangulo* rectangulo3;
	Rectangulo* rectangulo4;
	Info^ info;
	Bitmap^ imgEnemigo;
	Bitmap^ imgJugador;
	Bitmap^ imgPoblador;
	Bitmap^ imgAliado;

	int pobladorAsaciar;
	int cooldownCobardia;
	int cooldownAtaqueEnemigo;
	int tiempo;
	bool resultado;
	int objetivo;
	int pobladoresSaciados;

public:
	ControladorJuego() {
		imgJugador = gcnew Bitmap("resources/images/bruno.png");
		imgPoblador = gcnew Bitmap("resources/images/rojo.png");
		imgAliado = gcnew Bitmap("resources/images/zombies1.png");
		imgEnemigo = gcnew Bitmap("resources/images/proton.png");
		rectangulo1 = new Rectangulo(780, 550, 510,100);
		rectangulo2 = new Rectangulo(800, 480, 510, 100);
		rectangulo3 = new Rectangulo(900, 290, 200, 150);
		rectangulo4 = new Rectangulo(1130, 250, 200, 150);


		jugador = new Jugador(imgJugador);
		pobladores = new Pobladores(imgPoblador, 30,rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
		aliadoAutomatico = new Aliado(imgAliado, 1);
		aliadoManual = new Aliado(imgAliado, 2);
		enemigoHeroe = new Enemigo(imgEnemigo);
		enemigoAliadoAutomatico = new Enemigo(imgEnemigo);
		enemigoAliadoManual = new Enemigo(imgEnemigo);

		pobladorAsaciar = 0;
		cooldownCobardia = 0;
		cooldownAtaqueEnemigo = 0;
		objetivo = 30;
		tiempo = 90 * 1000 + clock();
		info = gcnew Info();
		pobladoresSaciados = 0;
	}

	~ControladorJuego() {
		delete jugador, pobladores, aliadoManual, aliadoAutomatico;
		delete enemigoHeroe, enemigoAliadoManual,enemigoAliadoAutomatico;
	}

	bool GetResultado() { return resultado; }

	void MovimientoManual(bool accion, Keys tecla) {
		int v = 3;

		if (accion) {
			if (tecla == Keys::I) {
				aliadoManual->SetDY(-v);
				aliadoManual->SetAccion(aCaminarArriba);
			}
			else if (tecla == Keys::J) {
				aliadoManual->SetDX(-v);
				aliadoManual->SetAccion(aCaminarIzquierda);
			}
			else if (tecla == Keys::K) {
				aliadoManual->SetDY(v);
				aliadoManual->SetAccion(aCaminarAbajo);
			}
			else if (tecla == Keys::L) {
				aliadoManual->SetDX(v);
				aliadoManual->SetAccion(aCaminarDerecha);
			}
			else if (tecla == Keys::P) {
				if (aliadoManual->GetAccion() == aCaminarArriba)
					aliadoManual->SetAccion(aAtacarArriba);
				else if (aliadoManual->GetAccion() == aCaminarAbajo)
					aliadoManual->SetAccion(aAtacarAbajo);
				else if (aliadoManual->GetAccion() == aCaminarIzquierda)
					aliadoManual->SetAccion(aAtacarIzquierda);
				else if (aliadoManual->GetAccion() == aCaminarDerecha)
					aliadoManual->SetAccion(aAtacarDerecha);
			}
			if (tecla == Keys::W) {
				jugador->SetDY(-v);
				jugador->SetAccion(CaminarArriba);
			}
			else if (tecla == Keys::A) {
				jugador->SetDX(-v);
				jugador->SetAccion(CaminarIzquierda);
			}
			else if (tecla == Keys::S) {
				jugador->SetDY(v);
				jugador->SetAccion(CaminarAbajo);
			}
			else if (tecla == Keys::D) {
				jugador->SetDX(v);
				jugador->SetAccion(CaminarDerecha);
			}
			else if (tecla == Keys::Q) {
				if (jugador->GetAccion() == CaminarArriba)
					jugador->SetAccion(AtacarArriba);
				else if (jugador->GetAccion() == CaminarAbajo)
					jugador->SetAccion(AtacarAbajo);
				else if (jugador->GetAccion() == CaminarIzquierda)
					jugador->SetAccion(AtacarIzquierda);
				else if (jugador->GetAccion() == CaminarDerecha)
					jugador->SetAccion(AtacarDerecha);
			}
		}
		else {
			if (tecla == Keys::W) jugador->SetDY(0);
			else if (tecla == Keys::A) jugador->SetDX(0);
			else if (tecla == Keys::S) jugador->SetDY(0);
			else if (tecla == Keys::D) jugador->SetDX(0);
			if (tecla == Keys::I) aliadoManual->SetDY(0);
			else if (tecla == Keys::J) aliadoManual->SetDX(0);
			else if (tecla == Keys::K) aliadoManual->SetDY(0);
			else if (tecla == Keys::L) aliadoManual->SetDX(0);
		}

	}

	void Mostrar(Graphics^ g, Graphics^ i) {
		int t = (tiempo - clock()) / 1000;
		rectangulo1->Mostrar(g);
		rectangulo2->Mostrar(g);
		rectangulo3->Mostrar(g);
		rectangulo4->Mostrar(g);


		//g->DrawString("Tiempo: " + a, gcnew Font("Arial", 12), Brushes::Black, 0, 90);
		pobladores->Mostrar(g, imgPoblador);
		jugador->Mostrar(g, imgJugador);
		aliadoManual->Mostrar(g, imgAliado);
		aliadoAutomatico->Mostrar(g, imgAliado);
		enemigoHeroe->Mostrar(g, imgEnemigo);
		if (aliadoManual->GetVisible())enemigoAliadoManual->Mostrar(g, imgEnemigo);
		if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->Mostrar(g, imgEnemigo);

		info->Mostrar(i, t, jugador->GetPuntos(), aliadoManual->GetVisible(), aliadoAutomatico->GetVisible());
	}

	bool Mover(Graphics^ g)	{
		if (rectangulo1->Colision(jugador->NextArea()) == false &&
			rectangulo2->Colision(jugador->NextArea()) == false &&
			rectangulo3->Colision(jugador->NextArea()) == false &&
			rectangulo4->Colision(jugador->NextArea()) == false &&
			jugador->GetAccion() != Morir) {
			jugador->Mover(g);
		}
		if (rectangulo1->Colision(aliadoManual->NextArea()) == false &&
			rectangulo2->Colision(aliadoManual->NextArea()) == false &&
			rectangulo3->Colision(aliadoManual->NextArea()) == false &&
			rectangulo4->Colision(aliadoManual->NextArea()) == false &&
			aliadoManual->GetAccion() != aMorir) {
			aliadoManual->Mover(g, pobladores->Get(pobladorAsaciar));
		}
		pobladores->Mover(g, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
		aliadoAutomatico->Mover(g, pobladores->Get(pobladorAsaciar));
		if (aliadoManual->GetVisible())enemigoAliadoManual->nMover(g, aliadoManual);
		if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->nMover(g, aliadoAutomatico);
		enemigoHeroe->Mover(g, jugador);
		if (jugador->GetAccion() >= AtacarAbajo && jugador->GetAccion() <= AtacarArriba) {
			if (enemigoHeroe->Colision(jugador->HitBox())) {
				enemigoHeroe->SetAvergonzado(true);
				cooldownCobardia = clock();
			}
		}

		if (enemigoHeroe->GetAvergonzado()==true && clock() - cooldownCobardia >= 4000) {
			enemigoHeroe->SetAvergonzado(false);
			enemigoHeroe->SetX(600);
			enemigoHeroe->SetY(300);
			enemigoHeroe->SetVisible(true);
			enemigoHeroe->Mostrar(g, imgEnemigo);
		}
		
		if (clock() >= tiempo) {
			jugador->SetAccion(Morir);
		}

		if (objetivo == jugador->GetPuntos()) {
			resultado = true;
			return false;
		}
		return true;
	}

	

	void Habilitar_Aliados() {
		if (!aliadoManual->GetVisible()) aliadoManual->SetVisible(true);
		else if (!aliadoAutomatico->GetVisible()) aliadoAutomatico->SetVisible(true);
	}
};