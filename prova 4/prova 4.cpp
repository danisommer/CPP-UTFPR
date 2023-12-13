#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace Bombas
{
	class Atomica
	{
	protected:
		static int potencial_atomico;
		int megatons;
	public:
		Atomica(const int mgtns = 5) : megatons(mgtns)
		{
			potencial_atomico += megatons;
		}

		virtual ~Atomica()
		{
			potencial_atomico -= megatons;
		}

		const int getMegatons() const
		{
			return megatons;
		}

		static int getPotencialAtomico()
		{
			return potencial_atomico;
		}

		virtual bool explodir() = 0;
	};

	int Atomica::potencial_atomico = 0;

	class Fusao;

	class Fissao : public Atomica
	{
	private:
		int potencial;
		Fusao* pFusao;
	public:
		Fissao(Fusao* pFs = NULL, const int mgtns = 15) : Atomica(mgtns), potencial(rand() % 100), pFusao(pFs)
		{
		}

		~Fissao()
		{
		}

		bool explodir();

	};

	class Fusao : public Atomica
	{
	private:
		Fissao detonadora;
		bool duplicador;
	public:
		Fusao(const int mgtns = 100) : detonadora(this), duplicador(false)
		{
		}

		~Fusao()
		{
		}

		void setDuplicador(const bool dp)
		{
			duplicador = dp;
		}

		const int getMegatons() const
		{
			return (duplicador ? megatons * 2 : megatons);
		}

		bool explodir()
		{
			return detonadora.explodir();
		}
	};

	bool Fissao::explodir()
	{
		potencial > 77 ? pFusao->setDuplicador(true) : pFusao->setDuplicador(false);

		return (potencial > 33 ? true : false);
	}
}

using namespace Bombas;

class Arsenal
{
private:
	vector <Fusao*> colecao;
public:
	Arsenal(const int nBombas = 100)
	{
		Fusao* BombaNova = NULL;

		for (int i = 0; i < nBombas; i++)
		{
			BombaNova = new Fusao();

			if (BombaNova)
			{
				colecao.push_back(BombaNova);
			}
			else
			{
				cout << "Nao foi possivel alocar!" << endl;
			}
			BombaNova = NULL;
		}
	}

	~Arsenal()
	{
		Fusao* pN = NULL;

		vector<Fusao*>::iterator it;
		it = colecao.begin();

		while (it != colecao.end())
		{
			pN = *it;

			if (pN)
			{
				delete pN;
				pN = NULL;
			}
			it++;
		}
		colecao.clear();

		/*Fusao* pFusao = NULL;
		int nBombas = (int) colecao.size();
		for (int i = 0; i < nBombas; i++)
		{
			pFusao = colecao[i];

			if (pFusao)
			{
				delete(pFusao);
			}
			pFusao = NULL;
		}
		colecao.clear();*/
	}

	const int getTotalMegatons()
	{
		int soma = 0;
		Fusao* pFusao = NULL;

		for (int i = 0; i < (int)colecao.size(); i++)
		{
			pFusao = colecao[i];
			if (pFusao)
			{
				if (pFusao->explodir())
				{
					soma += pFusao->getMegatons();
				}
			}
			pFusao = NULL;
		}
		return soma;
	}
};

class Nacao
{
private:
	static const int MAX;
	bool atacar;
	Nacao* pBeligerante;

public:
	Arsenal arsenal;

public:
	Nacao() : atacar(false), pBeligerante(NULL), arsenal()
	{
		atacar = ((rand() % 100) == 1);
	}

	~Nacao()
	{
		pBeligerante = NULL;
	}

	const bool getAtacar() const
	{
		return atacar;
	}

	void informar_dano()
	{
		cout << endl;

		if (pBeligerante)
		{
			int total = arsenal.getTotalMegatons();

			total += pBeligerante->arsenal.getTotalMegatons();
			if (total > MAX)
			{
				cout << "Fim do Mundo!" << endl;
				exit(0);
			}
			else
			{
				if (total > (MAX / 2))
				{
					cout << "Inverno Nuclear!" << endl;
				}
				else
				{
					cout << "Planeta Danificado!" << endl;
				}
			}
		}
		else
		{
			cout << "Nao ha danos!" << endl;
		}
	}

	void defender()
	{
		cout << endl;

		if (pBeligerante)
		{
			if (pBeligerante->getAtacar())
			{
				informar_dano();
			}
			else
			{
				cout << "Ha paz e o planeta esta a salvo!" << endl;
			}
		}
		else
		{
			cout << "Nao ha beligerante!" << endl;
		}
		cout << endl;
	}

	void operator= (Nacao* pBelg)
	{
		pBeligerante = pBelg;
	}
};

const int Nacao::MAX(1000);

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	Nacao A;
	Nacao B;

	cout << "O pontecial atomico eh pelo menos: " << Atomica::getPotencialAtomico() << " megatons!" << endl << endl;

	A = &B;
	A.defender();
	B.defender();

	return 0;
}
