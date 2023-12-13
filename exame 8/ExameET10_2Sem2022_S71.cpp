// Exame de Substituição - 2 Sem 2022 - TecProg S71 DAINF/UTFPR - Ctba - Prof. Simão. 13/12/2022

//#include <stdlib.h>
//#include <time.h

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
using namespace std;

class Time;

class Robo
{
protected:
	float id;
    Time* pTime;

public:

	Robo(const float i = 0.0):
	    id(i),
	    pTime(NULL)
	{
	}

	virtual ~Robo()
	{
	    pTime = NULL;
	}

	//void setId(const float cid) { id = cid; }
	const float getId() const { return id; }

    void setTime (Time* pT) { pTime = pT; }

    Time* getTime()const { return pTime; }

	virtual void executar() = 0;

	virtual void operator++() = 0;
};

class Fila
{

public:

    class Elemento
    {
        private:
            Robo* pRobo;
            Elemento* pProx;

        public:
            Elemento( Robo* pR = NULL ) : pRobo (pR), pProx (NULL)
            {
            }

            ~Elemento()
            {
                pRobo = NULL;
                pProx = NULL;
            }

            //void setRobo(Robo* pR) { pRobo = pR; }
            Robo* getRobo() const { return pRobo; }

            void setProx(Elemento* p) { pProx = p; }
            Elemento* getProx() const { return pProx; }
    };

private:
    Elemento* pPrimeiro;
    Elemento* pUltimo;

public:

	Fila()
	{
	    pPrimeiro = NULL;
	    pUltimo   = NULL;
	}

	~Fila()
	{
	    Elemento* pAux = NULL;
	    pAux = pPrimeiro;

	    while (pAux != NULL)
        {

            Robo* pR = NULL;

            pR = pAux->getRobo();

            if (pR != NULL)
            {
                delete (pR);
                //pPrimeiro->setRobo(NULL);
            }

            pPrimeiro = pPrimeiro->getProx();
            delete pAux;
            pAux = NULL;
            pAux = pPrimeiro;
        }

        pAux        = NULL;
        pPrimeiro   = NULL;
        pUltimo     = NULL;
	}

	void incluir(Robo* pRobo)
	{
	    if (pRobo)
        {
            Elemento* pAux = NULL;
            pAux = new Elemento(pRobo);

            if (pPrimeiro == NULL)
            {
                pPrimeiro = pAux;
                pUltimo   = pAux;
            }
            else
            {
                pUltimo->setProx(pAux);
                pUltimo = pAux;
            }
        }
        else
        {
            cout << "Ponteiro de robo nulo!" << endl;
        }
	}

	void percorrer()
	{
        Elemento* pAux = NULL;

        pAux = pPrimeiro;

        while (pAux != NULL)
        {
            Robo* pR = NULL;
            pR = pAux->getRobo();
            if (pR != NULL)
            {
                pR->executar();
            }
            else
            {
                cout << "Ponteiro nulo de robo no percorrimento1" << endl;
            }
            pAux = pAux->getProx();
        }
	}
};

class Goleiro : public Robo
{
private:
	const bool titular;
	int num_defs;

public:


	Goleiro(const int i = 0.0):
	    Robo((float) i),
	    titular((bool)(rand()%2)),
	    num_defs(0)
    {
    }

	~Goleiro()
	{
	}

    const int getTitular() const
    {
        return titular;
    }

	void executar();

	void operator++() { num_defs++; }
};


class Atacante : public Robo
{
private:
	int num_gois;

public:
	Atacante(const float i = 0.0, const int n  = 0):
	    Robo(i),
	    num_gois(n)
	{
    }

	~Atacante()
	{
	}

	void executar();

	void operator++() { num_gois++; }
};




// Questao 3: classe time
class Time
{
private:
	string nome;
	Atacante*   pA;
	Goleiro*    pG;
	Goleiro*    pGAdv;
	Fila f;
    int num_gois;

public:
	Time(const string n = "", const int i = 0) : // por ajuste/dedução do modelo, o segundo parâmetro é inteiro.
	    nome(n),
	    pA(NULL),
	    pG(NULL),
	    pGAdv(NULL),
	    f(),
	    num_gois(i)
	{
        pG = new Goleiro((int)1.0);
        pG->setTime(this);
        f.incluir(static_cast<Robo*>(pG));

        pA = new Atacante(2.0);
        pA->setTime(this);
        f.incluir(static_cast<Robo*>(pA));
        pA = NULL;

        pA = new Atacante(3.0);
        pA->setTime(this);
        f.incluir(static_cast<Robo*>(pA));
        pA = NULL;
	}
	~Time()
	{
        pA  =   NULL;
	    pG  =   NULL;
	    pGAdv = NULL;
	}

	void jogar()
	{
	    if (pGAdv){ f.percorrer(); }
	    else { cout << "Sem time adversário!" << endl; }
    }

	const string getNome() const { return nome; }

	void setGoleiroAdversario(Goleiro* pGA)
	{
	    pGAdv = pGA;
	}

	Goleiro* getGoleiroAdversario() const
	{
	    return pGAdv;
	}

	Goleiro* getGoleiro() const { return pG; }

	const int getNumGois() { return num_gois; }

	void operator++() { num_gois++; }
};


void Goleiro::executar()
{
    if (pTime)
    {
        cout    << "A quantidade de gois feitos pelo time " << pTime->getNome()
                <<  " é: " << pTime->getNumGois() << endl;

        cout    << "A quantidade de defesas feitas pelo goleiro " << getId()
                <<  " é: " << num_defs << endl;
    }
    else
    {
        cout << "Goleiro sem time!" << endl;
    }
}

void Atacante::executar()
{
    if (pTime)
    {
        Goleiro* pAdv = NULL;
        pAdv = pTime->getGoleiroAdversario();

        if (pAdv)
        {
            time_t t;
            srand((unsigned) time(&t));
            int result = rand()%10;

            if (pAdv->getTitular())
            {
                if ( (result>=0) && (result<7) )
                {
                    operator++();
                    pTime->operator++();
                }
                else
                {
                    pAdv->operator++();
                }
            }
            else
            {
                if ( (result>0) && (result<=3) )
                {
                    operator++();
                    pTime->operator++();
                }
                else
                {
                    pAdv->operator++();
                }
            }
        }
        else
        {
            cout << "Goleiro Adversário Inexistente!" << endl;
        }
    }
    else
    {
        cout << "Atacante sem time!" << endl;
    }
}



int main()
{
    time_t t;     // https://pt.wikipedia.org/wiki/Time_t
                  // Para função srand e rand vide: https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
    srand((unsigned) time(&t));

    Time TA("Time A", 0 );
    Time TB("Time B", 0 );

    TA.setGoleiroAdversario(TB.getGoleiro());
    TB.setGoleiroAdversario(TA.getGoleiro());

    //TA.jogar();
    //TB.jogar();

    for (int i = 0; i < 10; i++)
    {
        (i % 2) ? TB.jogar() : TA.jogar();
        cout << endl;
    }
}
