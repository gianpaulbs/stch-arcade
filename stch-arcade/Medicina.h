#pragma once
#include "Entidad.h"

#pragma once
#include "Entidad.h"

class Medicina : public Entidad
{
public:
	Medicina(Bitmap^ img)
	{
		x = rand() % 200;
		y = rand() % 200;

		ancho = img->Width;
		alto = img->Height;
	}
	void Mostrar(Graphics^ g, Bitmap^ img)
	{
		g->DrawImage(img, Area());
		//g->DrawRectangle(Pens::Black, Area());
	}
};

class Medicinas
{
private:
	vector<Medicina*> medicinas;

public:
	Medicinas(int n, Rectangle obj, Bitmap^ img)
	{
		for (int i = 0; i < n; i++)
		{
			Medicina* obs = new Medicina(img);
			if (obs->Area().IntersectsWith(obj) == false && Colision(obs->Area()) == false)
				medicinas.push_back(obs);
			else
			{
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