#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <string.h>
#include <sstream>

using namespace std;

class Hormonio
{
protected:
	string nivel;
	bool estresse;

private:
	static int soma;

public:
	Hormonio() : nivel("indeterminado")
	{
		estresse = ((soma % 2) == 0);
		soma++;
	}

	~Hormonio()
	{
		soma--;
	}

	const string getNivel() const
	{
		return nivel;
	}

	virtual void calcular_nivel() = 0;
};

int Hormonio::soma = 0;

class Serotonina;

class Endorfina : public Hormonio
{
private:
	float real;
	Serotonina* pSero;

public:
	Endorfina() : real(0.0), pSero(NULL)
	{
		real = static_cast<float>(rand() % 11);
	}

	~Endorfina()
	{
		pSero = NULL;
	}

	const float getReal() const
	{
		return real;
	}

	void setSero(Serotonina* pS)
	{
		pSero = pS;
	}

	void calcular_nivel();
};

class Serotonina : public Hormonio
{
private:
	int inteiro;
	Endorfina* pEndo;

public:
	Serotonina() : inteiro(rand() % 11), pEndo(NULL)
	{
		if (estresse && (inteiro > 0))
			inteiro--;
	}

	~Serotonina()
	{
		pEndo = NULL;
	}

	const int getInteiro() const
	{
		return inteiro;
	}

	void setEndo(Endorfina* pE)
	{
		pEndo = pE;
	}

	void calcular_nivel()
	{
		if (pEndo == NULL)
		{
			cout << endl << "Erro - pEndo nulo" << endl;
			return;
		}

		if ((inteiro >= 7) &&
			(inteiro <= 10) &&
			(pEndo->getReal() > 5.0)
			)
		{
			nivel = "normal";
			cout << endl << "Serotonina: " << nivel << endl;
		}
		else
		{
			if ((inteiro > 4) &&
				(inteiro < 7) &&
				(pEndo->getReal() > 3.0)
				)
			{
				nivel = "medio";
				cout << endl << "Serotonina: " << nivel << endl;
			}
			else
			{
				if ((inteiro <= 4) &&
					(inteiro >= 0) &&
					(pEndo->getReal() > 0.0)
					)
				{
					nivel = "baixo";
					cout << endl << "Serotonina: " << nivel << endl;
				}
				else
				{
					cout << endl << "Serotonina: " << nivel << endl;
				}
			}
		}
	}
};

void Endorfina::calcular_nivel()
{
	if (pSero == NULL)
	{
		cout << endl << "Erro - pSero nulo" << endl;
		return;
	}

	if ((real >= 6.0) &&
		(real <= 10.0) &&
		(pSero->getInteiro() > 7)
		)
	{
		nivel = "normal";
		cout << endl << "Endorfina: " << nivel << endl;
	}
	else
	{
		if ((real > 6.0) &&
			(real < 3.0) &&
			(pSero->getInteiro() > 5)
			)
		{
			nivel = "medio";
			cout << endl << "Endorfina: " << nivel << endl;
		}
		else
		{
			if ((real <= 3.0) &&
				(real >= 0.0) &&
				(pSero->getInteiro() > 0)
				)
			{
				nivel = "baixo";
				cout << endl << "Endorfina: " << nivel << endl;
			}
			else
			{
				cout << endl << "Endorfina: " << nivel << endl;
			}
		}
	}
}

class Reg_Paciente
{
private:
	Endorfina nivel_endo;
	Serotonina nivel_sero;
	bool ok;

public:
	Reg_Paciente() : ok(true), nivel_endo(), nivel_sero()
	{
		nivel_endo.setSero(&nivel_sero);
		nivel_sero.setEndo(&nivel_endo);

		nivel_endo.calcular_nivel();
		nivel_sero.calcular_nivel();
	}

	~Reg_Paciente()
	{

	}

	const int getOk() const
	{
		return (int)ok;
	}

	void auto_avaliar()
	{
		if ((nivel_endo.getNivel() == "baixo") || (nivel_sero.getNivel() == "baixo")) {
			ok = false;
			cout << "nao esta OK!" << endl;
		}
		else
		{
			cout << "tudo OK!" << endl;
		}
	}

};

class Diagnosticador
{
private:
	list<Reg_Paciente*> listap;
	ostringstream saida;

public:
	Diagnosticador(const int num = 10) : listap(), saida()
	{
		Reg_Paciente* pR = NULL;

		for (int i = 0; i < num; i++)
		{
			pR = new Reg_Paciente();

			listap.push_back(pR);

			pR = NULL;
		}
		diagnosticar();
	}

	~Diagnosticador()
	{
		Reg_Paciente* pR = NULL;

		list<Reg_Paciente*>::iterator it;

		it = listap.begin();

		while (it != listap.end())
		{
			pR = *it;

			if (pR)
			{
				delete pR;
				pR = NULL;
			}
			it++;
		}
		listap.clear();
	}

	ostringstream& getSaida()
	{
		return saida;
	}

	void diagnosticar()
	{
		Reg_Paciente* pR = NULL;

		list<Reg_Paciente*>::iterator it;

		it = listap.begin();

		int cont = 0;

		while (it != listap.end())
		{
			pR = *it;

			if (pR)
			{
				pR->auto_avaliar();

				if (pR->getOk() != 0)
				{
					cont++;
				}
			}
			it++;
		}

		int tam = (int)listap.size();

		float calc = static_cast<float>((cont * 100) / tam);

		saida << endl << "A porcentagem de pacientes OK eh de " << calc << endl;
	}
};

ostream& operator<< (ostream& s, Diagnosticador& d)
{
	cout << (d.getSaida()).str();
	return s;
}

int main()
{
	time_t t;
	srand((unsigned)time(&t));

	Diagnosticador diag1(100);

	cout << diag1 << endl;

	return 0;
}