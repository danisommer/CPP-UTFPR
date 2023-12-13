#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

class Personagem
{
protected:
	int x;
	const static int MAX;

public:
	Personagem(const int xx = 1) : x(xx)
	{

	}

	virtual ~Personagem()
	{

	}

	const int getX() const
	{
		return x;
	}

	static const int getMAX()
	{
		return MAX;
	}

	virtual void movimentar() = 0;
};

const int Personagem::MAX = 20;

class Curupira : public Personagem
{
private:
	bool empoderado;
	bool avancar;
	int nvidas;

public:
	Curupira(const bool av = true, const bool emp = false, const int xx = 1) : avancar(av), empoderado(emp), Personagem(xx)
	{
		nvidas = MAX;
	}

	~Curupira()
	{
	}

	const bool getEmpoderado() const
	{
		return empoderado;
	}

	const int getNVidas() const
	{
		return nvidas;
	}

	void setNvidas(const int nv)
	{
		nvidas = nv;
	}

	void movimentar()
	{
		if (avancar)
		{
			if (x < MAX)
			{
				x++;
			}
			else
			{
				avancar = false;
				x--;
			}
		}
		else
		{
			if (x > 0)
			{
				x--;
			}
			else
			{
				avancar = true;
				x++;
			}
		}
	}
};


class BoiTata : public Personagem
{
private:
	int energia;
	Curupira* pCurupira;

public:
	BoiTata(Curupira* pCur = NULL, const int energ = 0, const int xx = 0) : Personagem(xx), pCurupira(pCur), energia(energ)
	{
	}

	~BoiTata()
	{
	}

	const int getEnergia() const
	{
		return energia;
	}

	void atacar()
	{
		if (pCurupira->getX() == x)
		{
			if (pCurupira->getEmpoderado())
			{
				energia--;
			}
			else
			{
				energia++;
				int decrementa = pCurupira->getNVidas() - 1;
				pCurupira->setNvidas(decrementa);
			}
		}
	}

	void movimentar()
	{

		if (x > pCurupira->getX())
		{
			x--;
		}
		else
		{
			x++;
		}
		atacar();

	}
};

class VetorPersonagens
{
private:
	list<Personagem*> personagens;
	list<Personagem*>::const_iterator itPersonagens;

public:
	VetorPersonagens()
	{
		personagens.clear();
	}

	~VetorPersonagens()
	{
		personagens.clear();
	}

	void inserir(Personagem* p)
	{
		personagens.push_back(p);
	}

	Personagem* operator[](const int idx)
	{
		int tam = 0;
		tam = (int)personagens.size();

		if ((idx >= 0) && (idx < tam))
		{
			itPersonagens = personagens.begin();
			for (int i = 0; i < idx; i++)
			{
				itPersonagens++;
			}
			return *itPersonagens;
		}
		else
		{
			cout << "Operador de colchetes operando foram dos limites." << endl;
			return NULL;
		}
	}

	Personagem* excluir(int idx)
	{
		int tam = 0;
		tam = (int)personagens.size();

		if ((idx >= 0) && (idx < tam))
		{
			itPersonagens = personagens.begin();

			for (int i = 0; i < idx; i++)
			{
				itPersonagens++;
			}


			Personagem* p = NULL;
			p = *itPersonagens;

			if (p)
			{
				personagens.remove(p);
			}
			else
			{
				cout << "Ponteiro nulo na remoção." << endl;
			}


			return p;
		}
		else
		{
			cout << "Exclusão operando fora dos limites." << endl;
			return NULL;
		}

	}
};

class Jogo
{
private:

	int quant_bt;

	VetorPersonagens vetPers;

public:

	Jogo(int qbt = 1) : quant_bt(qbt), vetPers()
	{
		time_t t;
		srand((unsigned)time(&t));

		int valor = rand() % 2;
		cout << "Numero aleatotio: " << valor << endl;

		int pos = rand() % (Personagem::getMAX());
		cout << "Numero aleatotio: " << pos << endl;

		Curupira* pCur = NULL;
		pCur = new Curupira((bool)valor, pos);
		vetPers.inserir(static_cast<Personagem*>(pCur));

		BoiTata* pBT = NULL;

		for (int i = 0; i < quant_bt; i++)
		{
			pBT = new BoiTata(pCur, i, i);
			vetPers.inserir(static_cast<Personagem*>(pBT));
		}

		executar();
	}

	~Jogo()
	{
		int total = quant_bt + 1;

		Personagem* pP = NULL;

		for (int i = 0; i < total; i++)
		{
			pP = vetPers.excluir(0);

			if (pP)
			{
				delete pP;
			}
			else
			{
				cout << "Nao se pode deletar ponteiro nulo." << endl;
			}
		}
	}

	void executar()
	{
		int total = quant_bt + 1;
		Personagem* pP = NULL;

		cout << "Entrou." << endl;

		for (int j = 0; j < Personagem::getMAX(); j++)
		{
			for (int i = 0; i < total; i++)
			{
				pP = vetPers[i];
				pP->movimentar();
			}
		}

		Curupira* pCur = NULL;
		pP = vetPers[0];
		pCur = static_cast<Curupira*>(pP);
		cout << "O valor de vidas do Curupira eh: " << pCur->getNVidas() << endl;
		cout << endl;

		BoiTata* pBT = NULL;
		for (int i = 1; i < total; i++)
		{
			pP = vetPers[i];
			pBT = static_cast<BoiTata*>(pP);

			cout << " O " << i << ". Boi Tata tem o seguinte valor de energia: " << pBT->getEnergia() << endl;
		}
	}
};

int main() 
{
	time_t t;

	srand(3*(unsigned)time(&t));

	Jogo jogo(3);

	return 0;
}