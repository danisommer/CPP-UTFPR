#include <iostream>
#include <vector>
#include <list>

using namespace std;

namespace Controlados
{

	class Ente
	{
	protected:
		int x;
		int y;
		static int cont;

	public:
		Ente(const int xx = 0, const int yy = 0) : x(xx), y(yy)
		{
		}

		virtual ~Ente() {}

		virtual const int getX()
		{
			return x;
		}
		virtual const int getY()
		{
			return y;
		}
		virtual const bool mover(Ente* pE) = 0;
	};
	int Ente::cont(35); //quando for static, declarar o valor fora da classe

	class Carro : public Ente
	{
	private:
		const int y;
		static const int MAXVEL;
		int velocidade;
		int multas;
	public:
		Carro(const int xx = 0) : y(5), velocidade(0), multas(0)
		{
			cont++;
		}
		~Carro() {}
		const bool mover(Ente* pE) override
		{
			x += velocidade;

			if (pE->getX() == getX() && pE->getY() == getY())
			{
				cout << "O carro " << this << " e o pedestre " << pE << " estao na mesma posição!" << endl;

				if (velocidade > MAXVEL)
				{
					cout << "Acidente grave com do carro " << this << " para com o pedestre " << pE << endl;
					return true;
				}
			}
			else
			{
				return false;
			}
			return false;
		}
		const bool frenar()
		{
			if (velocidade <= MAXVEL)
			{
				velocidade = 0;
				return true;
			}
			else
			{
				velocidade = (int)velocidade / 2;
				return false;
			}
		}
		const int getY()
		{
			return y;
		}
		void operator++()
		{
			multas++;
		}
		const int getMultas()
		{
			return multas;
		}
	};

	const int  Carro::MAXVEL = 40;

	class Pedestre : public Ente
	{
	private:
		const int x;
		bool guarda;
	public:
		Pedestre(const int yy = 0) : Ente(5, yy), x(5), guarda(false)
		{

			if ((int)rand() % 100 == 0)
				guarda = true;
		}
		~Pedestre() {}
		const bool mover(Ente* pE) override
		{
			y++;

			cout << "Movi o pedestre: " << pE << endl;

			Carro* pC = static_cast<Carro*> (pE);

			bool moverCarro = pC->mover((Ente*)this);

			if (pE->getX() == getX() && pE->getY() == getY())
			{
				if (guarda && moverCarro)
				{
					pC->operator++();
				}

				if (pC->frenar())
				{
					cout << "Frenou a tempo! Acidente menor!" << endl;
					return false;
				}
				else
				{
					cout << "Acidente grave!" << endl;
					return true;
				}
			}
			return false;
		}
		const int getX()
		{
			return x;
		}
	};
}

using namespace Controlados;

namespace Controle
{
	class Conjunto {
	private:
		list<Ente*> coletivo;
		list<Ente*>::iterator it;
	public:
		Conjunto() : coletivo(), it() {
			coletivo.clear();
		}
		~Conjunto() {
			Ente* pE = NULL;

			it = coletivo.begin();

			while (it != coletivo.end())
			{
				pE = *it;

				if (pE)
				{
					delete pE;
					pE = NULL;
				}
				it++;
			}
			coletivo.clear();
		}
		void incluir(Ente* pe) {
			if (pe)
			{
				coletivo.push_back(pe);
			}
			else
			{
				cout << "Nao se pode incluir ponteiro nulo!" << endl;
			}
		}
		void irParaInicio() {
			it = coletivo.begin();
		}
		void operator++ () {
			it++;
		}
		const bool fim() const {
			if (it == coletivo.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		Ente* getAtual() {
			return *it;
		}
	};

	class Transito {
	private:
		Conjunto pedestres;
		Conjunto carros;
	public:
		Transito() {
			Pedestre* pP = NULL;
			for (int i = 0; i < 50; i++)
			{
				int y = (int)(rand() % 10);
				pP = new Pedestre(y);

				if (pP)
				{
					pedestres.incluir(pP);
					cout << " Inclui o Pedestre: " << pP << endl;

				}
				else
				{
					cout << " Pedestre não instaciando - ponteiro nulo! " << endl;
				}
			}

			Carro* pC = NULL;
			for (int i = 0; i < 10; i++)
			{
				int x = (int)(rand() % 10);

				pC = new Carro(x);

				if (pC)
				{
					carros.incluir(pC);
					// cout << " Inclui o Carro: " << pC << endl;

				}
				else
				{
					cout << " Pedestre não instaciando - ponteiro nulo! " << endl;
				}
			}

			transitar();
		}
		~Transito() {

		}
		void transitar() {

			bool flag = false;

			for (int i = 0; i < 10; i++)
			{
				Pedestre* pP = NULL;

				pedestres.irParaInicio();

				while (pedestres.fim() == false)
				{

					pP = (Pedestre*)pedestres.getAtual();

					carros.irParaInicio();

					while (carros.fim() == false)
					{
						Ente*  pE  = NULL;
						Carro* pC = NULL;
						pE = carros.getAtual();
						pC = (Carro*)carros.getAtual();

						bool rP = pP->mover((Ente*)pC);

						cout << "Movendo o ente " << pE << " que eh o pedestre " << pP << " em funcao do carro " << pC << endl;

						if (rP == true)
						{
							flag = true;
						}

						carros.operator++();
					}
					pedestres.operator++();
				}

				if (flag)
				{
					carros.irParaInicio();

					int cont = 0;

					while (carros.fim() == false)
					{
						Carro* pC = NULL;
						pC = (Carro*)carros.getAtual();
						cout << "A quantidade de multa do carro " << cont << " eh: " << pC->getMultas();
						carros.operator++();
					}

					break;
				}
			}


		}



	};
}
using namespace Controle;


int main()
{
	time_t tempo;
	srand((unsigned)time(&tempo));
	Transito t;
	return 0;
}
