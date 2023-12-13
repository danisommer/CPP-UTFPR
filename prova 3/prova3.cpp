#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>

using namespace std;

namespace Essenciais
{
	class Nacao
	{
	private:
		int poderio;

	public:
		Nacao() : poderio(rand() % 100)
		{

		}

		virtual ~Nacao()
		{
		}

		const int getPoderio() const
		{
			return poderio;
		}

		void setPoderio(const int pod)
		{
			poderio = pod;
		}

		void operator++() { poderio++; }

		virtual const int guerrear()
		{
			operator++();
			return getPoderio();
		}
	};
}
using namespace Essenciais;

namespace Principais
{
	class Conjunto
	{
	private:
		list<Nacao*> nacoes_unidas;

	public:
		Conjunto(const int num = 100) :
			nacoes_unidas()
		{
			Nacao* pN = NULL;
			for (int i = 0; i < num; i++)
			{
				pN = new Nacao();

				if (pN)
				{
					nacoes_unidas.push_back(pN);
				}
				else
				{
					cout << "Alocaçao não realizada! " << endl;
				}
			}
		}

		~Conjunto()
		{
			Nacao* pN = NULL;

			list<Nacao*>::iterator it;
			it = nacoes_unidas.begin();

			while (it != nacoes_unidas.end())
			{
				pN = *it;

				if (pN)
				{
					delete pN;
					pN = NULL;
				}
				it++;
			}
			nacoes_unidas.clear();
		}

		const int calc_soma()
		{
			Nacao* pN = NULL;

			list<Nacao*>::iterator it;
			it = nacoes_unidas.begin();

			int soma = 0;

			while (it != nacoes_unidas.end())
			{
				pN = *it;
				if (pN)
				{
					pN->guerrear();
					soma += pN->getPoderio();
				}
				else
				{
					cout << endl << "Hah ponteito nulo na lista!" << endl;
				}
				it++;
			}
			return soma;
		}
	};
}
using namespace Principais;

namespace Essenciais
{
	class Invasora : public Nacao
	{
	private:

		bool  crime_guerra;
		const int RESERVA;

	public:

		Invasora()
			: Nacao(), crime_guerra(true), RESERVA(100)
		{
			int num = rand() % 100;
			crime_guerra = !(1 == num);
		}

		~Invasora()
		{
		}

		const int guerrear()
		{
			return (getPoderio() * RESERVA);
		}

		void operator--()
		{
			int pod = getPoderio();
			pod = crime_guerra ? pod - 10 : pod - 1;
		}
	};

	class Invadida : public Nacao
	{
	private:
		Invasora* pInvas;
		Conjunto* pAliados;

	public:
		Invadida(Invasora* pI = NULL, Conjunto* pC = NULL) :
			Nacao(),
			pInvas(pI),
			pAliados(pC)
		{
		}

		~Invadida()
		{
			pInvas = NULL;
			pAliados = NULL;
		}

		const int guerrear()
		{
			if (pInvas)
			{
				operator++();

				pInvas->operator--();

				if (pAliados)
				{
					return (getPoderio() + pAliados->calc_soma());
				}
				else
				{
					cout << "Nao há aliados!" << endl;
					return getPoderio();
				}
			}
			else
			{
				cout << "Nao há invasao!" << endl;
				return getPoderio();
			}
		}
	};
}
using namespace Essenciais;

namespace Principais
{
	class Mundo
	{
	private:
		Conjunto aliados;
		Invasora invas;
		Invadida invad;  // no modelo o objeto tinha dois is para foi permitido só um i na execuação da prova.

	public:
		Mundo() :
			aliados(),
			invas(),
			invad(&invas, &aliados)
		{
			guerrear();
		}

		~Mundo()
		{
		}

		void guerrear()
		{
			int vInvas = 0;
			int vInvad = 0;

			do
			{
				vInvas = invas.guerrear();
				vInvad = invad.guerrear();
			} while (vInvad < vInvas);

			cout << "Nação invadida libertada!" << endl;
		}
	};
}
using namespace Principais;

int main()
{
	time_t t;
	srand((unsigned)time(&t));
	Mundo m;
	return 0;
}
