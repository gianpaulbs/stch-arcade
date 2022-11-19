#include <time.h>
#include "Info.h"
#include "Jugador.h"
#include "Poblador.h"
#include "Aliado.h"
#include "Enemigo.h"
#include "Rectangulo.h"
#include "Medicina.h"
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
	Medicinas* medicinas;

	Pobladores* pobladores;

	Rectangulo* rectangulo1;
	Rectangulo* rectangulo2;
	Rectangulo* rectangulo3;
	Rectangulo* rectangulo4;
	Fondo* fondo;
	Info^ info;
	Bitmap^ imgEnemigo;
	Bitmap^ imgEnemigo1;
	Bitmap^ imgEnemigo2;
	Bitmap^ imgJugador;
	Bitmap^ imgPoblador;
	Bitmap^ imgAliado;
	Bitmap^ imgMedicina;

	int pobladorAsaciar;
	int cooldownCobardia, cooldownCobardiaManual, cooldownCobardiaAutomatica;
	int cooldownAtaqueEnemigo;
	int tiempo;
	bool resultado;
	int cooldownAparicionPobladores;
	int objetivo;
	int pobladoresSaciados;
	int cooldownCubetaEntregada;
	int cooldownCubetaEntregadaManual;
	int cooldownCubetaEntregadaAutomatica;
	int cooldownAparicionMedicina;
	int cooldownMedicinaRecogida;
	int totalMedicamentos;
	int cooldownInspiracion;
	int cooldownMedicinaRecogidaManual;
	int cooldownMedicinaRecogidaAutomatica;
	int cooldownContagio;
	int cooldownContagioManual;
	int cooldownContagioAutomatico;
	int cooldownRoboHeroe;
	Bitmap^ bmpMap;
	int random0;
	int random1;
	int random2;

	int cooldownRoboManual;

public:
	ControladorJuego() {
		imgJugador = gcnew Bitmap("resources/images/bruno.png");
		imgPoblador = gcnew Bitmap("resources/images/sheet2.png");
		imgAliado = gcnew Bitmap("resources/images/zombies1.png");
		imgEnemigo = gcnew Bitmap("resources/images/Enemigos.png");
		imgEnemigo1 = gcnew Bitmap("resources/images/Enemigos1.png");
		imgEnemigo2 = gcnew Bitmap("resources/images/Enemigos2.png");
		imgMedicina = gcnew Bitmap("resources/images/medicina.png");
		rectangulo1 = new Rectangulo(750, 500, 510,100);
		rectangulo2 = new Rectangulo(800, 430, 510, 100);
		rectangulo3 = new Rectangulo(900, 290, 200, 150);
		rectangulo4 = new Rectangulo(1130, 280, 200, 150);
		bmpMap = gcnew Bitmap("resources/images/background.png");
		fondo = new Fondo(bmpMap);
		jugador = new Jugador(imgJugador);
		pobladores = new Pobladores(imgPoblador,rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
		aliadoAutomatico = new Aliado(imgAliado, 1);
		aliadoManual = new Aliado(imgAliado, 2);
		enemigoHeroe = new Enemigo(imgEnemigo);
		enemigoAliadoAutomatico = new Enemigo(imgEnemigo);
		enemigoAliadoManual = new Enemigo(imgEnemigo);
		medicinas = new Medicinas(imgMedicina, 3, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
		pobladorAsaciar = 0;
		cooldownCobardia = 0;
		cooldownCobardiaManual = 0;
		cooldownCobardiaAutomatica = 0;
		cooldownCubetaEntregadaManual=0;
		cooldownCubetaEntregadaAutomatica=0;
		cooldownAtaqueEnemigo = 0;
		objetivo = 20;
		tiempo = 90 * 1000 + clock();
		info = gcnew Info();
		pobladoresSaciados = 0;
		cooldownCubetaEntregada = 0;
		cooldownInspiracion = 0;
		cooldownAparicionPobladores = 0;
		cooldownAparicionMedicina = 0;
		cooldownMedicinaRecogida = 0;
		totalMedicamentos = 0;
		cooldownMedicinaRecogidaManual = 0;
		cooldownMedicinaRecogidaAutomatica = 0;
		cooldownContagio = 0;
		cooldownContagioManual = 0;
		cooldownContagioAutomatico = 0;
		cooldownRoboHeroe = 0;
		cooldownRoboManual = 0;
		random0 = rand() % 3;
		random1 = rand() % 3;
		random2 = rand() % 3;
	}

	~ControladorJuego() {
		delete jugador, pobladores, aliadoManual, aliadoAutomatico;
		delete enemigoHeroe, enemigoAliadoManual,enemigoAliadoAutomatico;
		delete medicinas;
	}

	bool GetResultado() { return resultado; }

	void MovimientoManual(bool accion, Keys tecla) {
		int v = 3;
		int vel = 3;
		if (jugador->GetInspirado()) v = 5;
		else v = 3;
		if (accion) {
			if (tecla == Keys::I) {
				aliadoManual->SetDY(-vel);
				aliadoManual->SetAccion(aCaminarArriba);
			}
			else if (tecla == Keys::J) {
				aliadoManual->SetDX(-vel);
				aliadoManual->SetAccion(aCaminarIzquierda);
			}
			else if (tecla == Keys::K) {
				aliadoManual->SetDY(vel);
				aliadoManual->SetAccion(aCaminarAbajo);
			}
			else if (tecla == Keys::L) {
				aliadoManual->SetDX(vel);
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
				if(fondo->GetY() > 125)fondo->SumarY();
			}
			else if (tecla == Keys::A) {
				jugador->SetDX(-v);
				jugador->SetAccion(CaminarIzquierda);
				if(fondo->GetX()<0)fondo->SumarX();

			}
			else if (tecla == Keys::S) {
				jugador->SetDY(v);
				jugador->SetAccion(CaminarAbajo);
				fondo->RestarY();

			}
			else if (tecla == Keys::D) {
				jugador->SetDX(v);
				jugador->SetAccion(CaminarDerecha);
				fondo->RestarX();

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
		srand((unsigned)time(NULL));
		
		
		Rectangle sectionShown = Rectangle(0, 0, fondo->GetAncho(), fondo->GetAlto());
		Rectangle zoom = Rectangle(fondo->GetX(), fondo->GetY(), fondo->GetAncho() * 1.5, fondo->GetAlto() * 1.5);
		g->DrawImage(bmpMap, zoom, sectionShown, GraphicsUnit::Pixel);
		//g->DrawImage(bmpMap, fondo->GetX(), fondo->GetY(), 1280, 125);
		//g->DrawString("Tiempo: " + a, gcnew Font("Arial", 12), Brushes::Black, 0, 90);
		rectangulo1->Mostrar(g);
		rectangulo2->Mostrar(g);
		rectangulo3->Mostrar(g);
		rectangulo4->Mostrar(g);
		medicinas->Mostrar(g, imgMedicina);
		pobladores->Mostrar(g, imgPoblador);
		jugador->Mostrar(g, imgJugador);
		aliadoManual->Mostrar(g, imgAliado);
		aliadoAutomatico->Mostrar(g, imgAliado);
		switch (random0) {
		case 0:
			enemigoHeroe->Mostrar(g, imgEnemigo);
			break;
		case 1:
			enemigoHeroe->Mostrar(g, imgEnemigo1);
			break;
		case 2:
			enemigoHeroe->Mostrar(g, imgEnemigo2);
			break;
		}

		switch (random1) {
		case 0:
			if (aliadoManual->GetVisible())enemigoAliadoManual->Mostrar(g, imgEnemigo);
			break;
		case 1:
			if (aliadoManual->GetVisible())enemigoAliadoManual->Mostrar(g, imgEnemigo1);
			break;
		case 2:
			if (aliadoManual->GetVisible())enemigoAliadoManual->Mostrar(g, imgEnemigo2);
			break;
		}
		switch (random2) {
		case 0:
			if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->Mostrar(g, imgEnemigo);
			break;
		case 1:
			if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->Mostrar(g, imgEnemigo1);
			break;
		case 2:
			if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->Mostrar(g, imgEnemigo2);
			break;
		}

		totalMedicamentos = jugador->GetMedicamentos() + aliadoManual->GetMedicamentos() + aliadoAutomatico->GetMedicamentos();
		info->Mostrar(i, t, totalMedicamentos, aliadoManual->GetVisible(), aliadoAutomatico->GetVisible(), pobladoresSaciados);
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
		aliadoAutomatico->Mover(g, pobladores->Get(pobladorAsaciar));
		if (aliadoManual->GetVisible())enemigoAliadoManual->nMover(g, aliadoManual);
		if (aliadoAutomatico->GetVisible())enemigoAliadoAutomatico->nMover(g, aliadoAutomatico);
		enemigoHeroe->Mover(g, jugador, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
		if (jugador->GetAccion() >= AtacarAbajo && jugador->GetAccion() <= AtacarArriba) {
			if (enemigoHeroe->Colision(jugador->HitBox())) {
				enemigoHeroe->SetAvergonzado(true);
				enemigoHeroe->SetPicardia(false);
				cooldownCobardia = clock();
				jugador->RecuperarCubeta(1);
			}
		}

		if (pobladores->Get(pobladorAsaciar)->GetSaciado() == true||
			pobladores->Get(pobladorAsaciar)->GetVisible() == false
			)pobladorAsaciar++;

		if (aliadoManual->GetAccion() >= aAtacarAbajo && aliadoManual->GetAccion() <= aAtacarArriba) {
			if (enemigoAliadoManual->Colision(aliadoManual->HitBox())) {
				enemigoAliadoManual->SetAvergonzado(true);
				enemigoAliadoManual->SetPicardia(false);
				cooldownCobardiaManual = clock();
				aliadoManual->RecuperarCubeta(1);

			}
		}

		if (aliadoAutomatico->GetAccion() >= aCaminarArriba && aliadoAutomatico->GetAccion() <= aCaminarIzquierda) {
			if (enemigoAliadoAutomatico->Colision(aliadoAutomatico->HitBox())) {
				enemigoAliadoAutomatico->SetAvergonzado(true);
				cooldownCobardiaAutomatica = clock();
			}
		}


		if (enemigoHeroe->GetAvergonzado()==true && clock() - cooldownCobardia >= 10000) {
			enemigoHeroe->SetAvergonzado(false);
			enemigoHeroe->SetX(600);
			enemigoHeroe->SetY(300);
			enemigoHeroe->SetVisible(true);

		}
		if (enemigoAliadoManual->GetAvergonzado() == true && clock() - cooldownCobardiaManual >= 10000) {
			enemigoAliadoManual->SetAvergonzado(false);
			enemigoAliadoManual->SetX(600);
			enemigoAliadoManual->SetY(300);
			enemigoAliadoManual->SetVisible(true);

		}
		if (clock() >= tiempo) {
			jugador->SetAccion(Morir);
		}

		if (jugador->NextHitBox().IntersectsWith(enemigoHeroe->HitBox()) &&
			clock() - cooldownRoboHeroe >= 1000) {
			enemigoHeroe->SetPicardia(true);
			cooldownRoboHeroe = clock();
			if(jugador->GetCubetas()>0)jugador->SetCubetas(1);

		}
		if (aliadoManual->NextHitBox().IntersectsWith(enemigoAliadoManual->HitBox()) &&
			clock() - cooldownRoboManual >= 1000) {
			enemigoAliadoManual->SetPicardia(true);
			cooldownRoboManual = clock();
			if (aliadoManual->GetCubetas() > 0)aliadoManual->SetCubetas(1);
		}

		for (int i = 0; i < medicinas->Size(); i++) {
			if (jugador->NextHitBox().IntersectsWith(medicinas->Get(i)->HitBox()) &&
				clock() - cooldownMedicinaRecogida >= 1000) {
				cooldownMedicinaRecogida = clock();
				jugador->AgregarMedicamentos(1);
				medicinas->Get(i)->SetVisible(false);
			}
			if (aliadoManual->NextHitBox().IntersectsWith(medicinas->Get(i)->HitBox()) &&
				clock() - cooldownMedicinaRecogidaManual >= 1000) {
				cooldownMedicinaRecogidaManual = clock();
				aliadoManual->AgregarMedicamentos(1);
				medicinas->Get(i)->SetVisible(false);
			}
			if (aliadoAutomatico->NextHitBox().IntersectsWith(medicinas->Get(i)->HitBox()) &&
				clock() - cooldownMedicinaRecogidaAutomatica >= 1000) {
				cooldownMedicinaRecogidaAutomatica = clock();
				aliadoAutomatico->AgregarMedicamentos(1);
				medicinas->Get(i)->SetVisible(false);
			}
		}
		//here
		for (int i = 0;i<pobladores->Size();i++) {
			pobladores->Get(i)->Mover(g, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
			if (jugador->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
				if (pobladores->Get(i)->GetEnfermo() == false &&
					clock() - cooldownCubetaEntregada >= 1000) {
					if (jugador->GetCubetas() > 0) {
						pobladores->Get(i)->SetSaciado(true);
						cooldownCubetaEntregada = clock();
						jugador->SetCubetas(1);
						pobladoresSaciados++;
						jugador->SetPuntos(1);
					}
				}
			}
			if (pobladores->Get(i)->GetEnfermo() == true &&
				jugador->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
					if (jugador->GetMedicamentos() >= 1) {
						pobladores->Get(i)->SetEnfermo(false);
						jugador->UsarMedicamento(1);
						if (jugador->GetCubetas() > 0) {
							pobladores->Get(i)->SetSaciado(true);
							cooldownCubetaEntregada = clock();
							jugador->SetCubetas(1);
							pobladoresSaciados++;
							jugador->SetPuntos(1);
						}
					}//here
					else if (clock() - cooldownContagio >= 2000) {
						jugador->SetVidas(-1);
						cooldownContagio = clock();
					}
				}
			
			if (aliadoManual->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
				if (pobladores->Get(i)->GetEnfermo() == false &&
					clock() - cooldownCubetaEntregadaManual >= 1000) {
					if (aliadoManual->GetCubetas() > 0) {
						pobladores->Get(i)->SetSaciado(true);
						cooldownCubetaEntregadaManual = clock();
						aliadoManual->SetCubetas(1);
						pobladoresSaciados++;
						aliadoManual->SetPuntos(1);
					}
				}
				else if (pobladores->Get(i)->GetEnfermo() == true &&
					aliadoManual->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
					if (aliadoManual->GetMedicamentos() > 0) {
						pobladores->Get(i)->SetEnfermo(false);
						aliadoManual->UsarMedicamento(1);
						if (aliadoManual->GetCubetas() > 0) {
							pobladores->Get(i)->SetSaciado(true);
							cooldownCubetaEntregadaManual = clock();
							aliadoManual->SetCubetas(1);
							pobladoresSaciados++;
							jugador->SetPuntos(1);
						}
					}//here
					else if (clock() - cooldownContagioManual >= 2000) {
						aliadoManual->SetVidas(-1);
						cooldownContagioManual = clock();
					}
				}
			}
			if (aliadoAutomatico->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
				if (pobladores->Get(i)->GetEnfermo() == false &&
					clock() - cooldownCubetaEntregadaAutomatica >= 1000) {
					if (aliadoAutomatico->GetCubetas() > 0) {
						pobladores->Get(i)->SetSaciado(true);
						cooldownCubetaEntregadaAutomatica = clock();
						aliadoAutomatico->SetCubetas(1);
						pobladoresSaciados++;
						aliadoAutomatico->SetPuntos(1);
					}
				}
				else if (pobladores->Get(i)->GetEnfermo() == true &&
					aliadoAutomatico->NextHitBox().IntersectsWith(pobladores->Get(i)->HitBox())) {
					if (aliadoAutomatico->GetMedicamentos() > 0) {
						pobladores->Get(i)->SetEnfermo(false);
						aliadoAutomatico->UsarMedicamento(1);
						if (aliadoAutomatico->GetCubetas() > 0) {
							pobladores->Get(i)->SetSaciado(true);
							cooldownCubetaEntregadaAutomatica = clock();
							aliadoAutomatico->SetCubetas(1);
							pobladoresSaciados++;
							jugador->SetPuntos(1);
						}
					}//here
					else if (clock() - cooldownContagioAutomatico >= 2000) {
						aliadoAutomatico->SetVidas(-1);
						cooldownContagioAutomatico = clock();
					}
				}
			}
		}


		
		if (jugador->GetCubetas() < 3)jugador->RecargarCubeta();
		if (aliadoManual->GetCubetas() < 3)aliadoManual->RecargarCubeta();


		if (jugador->GetPuntos() >= 10  && clock()-cooldownInspiracion>=10000) {
			jugador->SetInspirado(true);
			cooldownInspiracion = clock();
			jugador->ResetPuntos(0);
			if (clock() - cooldownInspiracion >= 10000)jugador->SetInspirado(false);
		}

		if (pobladores->Size() < 20 && clock() - cooldownAparicionPobladores >= 10000) {
			pobladores->AgregarPobladores(imgPoblador, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
			cooldownAparicionPobladores = clock();
		}

		pobladores->Eliminar();
		medicinas->Eliminar();
		if (medicinas->Size() < 15 && clock() - cooldownAparicionMedicina >= 15000) {
			medicinas->AgregarMedicina(imgMedicina, rectangulo1->Area(), rectangulo2->Area(), rectangulo3->Area(), rectangulo4->Area());
			cooldownAparicionMedicina = clock();
		}

		if (jugador->GetVidas() == 0||aliadoManual->GetVidas()==0||aliadoAutomatico->GetVidas()==0){
			jugador->SetAccion(Morir);
			aliadoManual->SetAccion(aMorir);
			aliadoAutomatico->SetAccion(aMorir);
		}

		if (jugador->GetAccion() == Morir|| aliadoManual->GetAccion()==aMorir||
			aliadoAutomatico->GetAccion() == aMorir){
			resultado = false;
			return false;
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