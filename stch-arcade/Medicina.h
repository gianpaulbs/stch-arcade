#pragma once
#include "Entidad.h"

class Medicina : public Entidad
{
private:
	bool visible;
public:
	Medicina(Bitmap^ img)
	{
		x = rand() % 1200;
		y = rand() % 700;

		ancho = 15;
		alto = 20;
	}
	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		g->DrawImage(img, Area());
		//g->DrawRectangle(Pens::Black, Area());
	}
	void SetVisible(bool value) { visible = value; }
	bool GetVisible() { return visible; }
};

class Medicinas
{
private:
	vector<Medicina*> medicinas;

public:
	Medicinas(Bitmap^ img, int cant, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for (int i = 0; i < cant; i++) {
			Medicina* obs = new Medicina(img);
			if (obs->Area().IntersectsWith(r1) == false &&
				obs->Area().IntersectsWith(r2) == false &&
				obs->Area().IntersectsWith(r3) == false &&
				obs->Area().IntersectsWith(r4) == false)
				medicinas.push_back(obs);
			else {
				delete obs;
				i--;
			}
		}
	}



	~Medicinas()
	{
		for (int i = 0; i < medicinas.size(); i++)
			delete medicinas.at(i);
	}
	Medicina* Get(int pos) { return medicinas[pos]; }
	void Eliminar() {
		for (int i = 0; i < medicinas.size(); i++)
			if (medicinas[i]->GetVisible() == false)
				medicinas.erase(medicinas.begin() + i);
	}
	int Size() { return medicinas.size(); }
	void AgregarMedicina(Bitmap^ img, Rectangle r1, Rectangle r2, Rectangle r3, Rectangle r4) {
		for (int i = 0; i < 5; i++) {
			Medicina* medicina = new Medicina(img);
			if (medicina->Area().IntersectsWith(r1) == false &&
				medicina->Area().IntersectsWith(r2) == false &&
				medicina->Area().IntersectsWith(r3) == false &&
				medicina->Area().IntersectsWith(r4) == false)
				medicinas.push_back(medicina);
			else {
				delete medicina;
				i--;
			}
		}
	}
	bool Colision(Rectangle obj)
	{
		for each (Medicina * obs in medicinas)
		{
			if (obs->NextArea().IntersectsWith(obj))
				return true;
		}
		return false;
	}

	void Mover(Graphics^ g)
	{
		for each (Medicina * obs in medicinas)
		{
			obs->Mover(g);
		}
	}
	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		for (Medicina* obs : medicinas)
		{
			obs->Mostrar(g, img);
		}
	}
};