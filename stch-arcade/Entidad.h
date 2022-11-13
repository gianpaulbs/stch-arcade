#pragma once
#include <vector>

using namespace std;
using namespace System;
using namespace System::Drawing;

class Entidad
{
	protected:
		int x, y;
		int dx, dy;
		int ancho, alto;
		int IDx;

	public:
		Entidad() {
			x = y = 0;
			dx = dy = 0;
			ancho = alto = 0;
			IDx = 0;
		}

		void SetDX(int value) { dx = value; }
		void SetDY(int value) { dy = value; }
		void SetX(int value) { x = value; }
		void SetY(int value) { y = value; }

		int GetX() { return x; }
		int GetY() { return y; }
		int GetAncho() { return ancho; }
		int GetAlto() { return alto; }
		int GetIDx() { return IDx; }

		Rectangle Area() { 
			return Rectangle(x, y, ancho, alto);
		}

		Rectangle NextArea() { 
			return Rectangle(x + dx, y + dy, ancho, alto);
		}

		Rectangle HitBox() {
			return Rectangle(x + ancho / 4, y + alto / 3 - 5, ancho / 2, alto * 2 / 3);
		}

		Rectangle NextHitBox() { 
			return Rectangle(x + ancho / 4 + dx, y + alto / 3 - 5 + dy, ancho / 2, alto * 2 / 3);
		}

		virtual void Mover(Graphics^ g) {
			x += dx;
			y += dy;
		}

		virtual void Mostrar(Graphics^ g, Bitmap^ img) {
			g->FillRectangle(Brushes::Black, Area());
		}
};