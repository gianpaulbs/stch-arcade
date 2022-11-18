#pragma once
using namespace System::Drawing;
ref class Info {
	private:
		Bitmap^ bmpReloj;
		Bitmap^ bmpMedicina;
		Bitmap^ bmpRostroPoblador;
		Bitmap^ bmpPressEnter;
		Bitmap^ bmpEnter;
		Bitmap^ bmpPoints;
		Bitmap^ bmpDescription;

		void Animacion_Cabezas(Graphics^ g, int ps) {
			Bitmap^ bmpD;
			Bitmap^ bmpU;
			bmpD = nullptr;
			bmpU = nullptr;

			int d = ps / 10 % 10;
			int u = ps % 10;

			bmpD = gcnew Bitmap("resources/images/" + d + ".png");
			bmpU = gcnew Bitmap("resources/images/" + u + ".png");
			g->DrawImage(bmpD, 658, 10, 80, 70);
			g->DrawImage(bmpU, 692, 10, 80, 70);

			delete bmpD;
			delete bmpU;
		}

		void Animacion_Medicamentos(Graphics^ g, int m) {
			Bitmap^ bmpD;
			Bitmap^ bmpU;
			bmpD = nullptr;
			bmpU = nullptr;

			int d = m / 10 % 10;
			int u = m % 10;

			bmpD = gcnew Bitmap("resources/images/" + d + ".png");
			bmpU = gcnew Bitmap("resources/images/" + u + ".png");
			g->DrawImage(bmpD, 373, 10, 80, 70);
			g->DrawImage(bmpU, 407, 10, 80, 70);

			delete bmpD;
			delete bmpU;
		}

		void Animacion_Temporizador(Graphics^ g, int t) {
			if (t < 0) return;

			Bitmap^ bmpMin;
			Bitmap^ bmpSecD;
			Bitmap^ bmpSecU;
			bmpMin = nullptr;
			bmpSecD = nullptr;
			bmpSecU = nullptr;

			int d = 0;
			int u = 0;
			int seconds = 0;
			
			if (t < 60) {
				bmpMin = gcnew Bitmap("resources/images/0.png");
				seconds = t;
			}
			else {
				bmpMin = gcnew Bitmap("resources/images/1.png");
				seconds = t - 60;
			}

			d = seconds / 10 % 10;
			u = seconds % 10;
			bmpSecD = gcnew Bitmap("resources/images/" + d + ".png");
			bmpSecU = gcnew Bitmap("resources/images/" + u + ".png");

			g->DrawImage(bmpMin, 80, 10, 80, 70);
			g->DrawImage(bmpSecD, 141, 10, 80, 70);
			g->DrawImage(bmpSecU, 175, 10, 80, 70);

			delete bmpMin;
			delete bmpSecD;
			delete bmpSecU;
		}

		void Animacion_PressEnter(Graphics^ g, int t, bool vAliadoM, bool vAliadoA) {
			if (vAliadoM && vAliadoA) {
				// Imprimimos otra cosa
				return;
			}

			if (t % 2 == 0) {
				g->DrawImage(bmpPressEnter, 1500, 27, 250, 48);
				g->DrawImage(bmpEnter, 1500, 12, 62, 73);
			}
			else {
				g->DrawImage(bmpPressEnter, 895, 27, 250, 48);
				g->DrawImage(bmpEnter, 1157, 12, 62, 73);
			}
		}
	
	public:
		~Info() {}
		Info() {
			bmpPoints = gcnew Bitmap("resources/images/dospuntos.png");
			bmpMedicina = gcnew Bitmap("resources/images/medicina.png");
			bmpRostroPoblador = gcnew Bitmap("resources/images/rostro.png");
			bmpPressEnter = gcnew Bitmap("resources/images/presiona-enter.png");
			bmpEnter = gcnew Bitmap("resources/images/enter.png");
			bmpDescription = gcnew Bitmap("resources/images/description.png");
		}

		void Mostrar(Graphics^ g, int t, int m, bool visibleAliadoM, bool visibleAliadoA, int pobladoresSaciados) {
			g->DrawImage(bmpPoints, 121, 28, 55, 45);
			g->DrawImage(bmpMedicina, 345, 23, 40, 55);
			g->DrawImage(bmpRostroPoblador, 590, 20, 85, 57);

			if (visibleAliadoM) g->DrawImage(bmpDescription, 138, 90, 750, 16);

			Animacion_Temporizador(g, t);
			Animacion_Medicamentos(g, m);
			Animacion_Cabezas(g, pobladoresSaciados);
			Animacion_PressEnter(g, t, visibleAliadoM, visibleAliadoA);
		}
};