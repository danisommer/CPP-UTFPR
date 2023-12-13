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
    Robo(const float i = 0.0f):
    id(i),
    pTime(nullptr)
    {

    }

    virtual ~Robo()
    {
        pTime = nullptr;
    }

    const int getId() const { return id; }
    void setTime(Time* pT) { pTime = pT; }
    Time* getTime() const { return pTime; }
    virtual void executar() = 0;
    virtual void operator++() = 0;
}; //2.0 pontos

class Goleiro;

class Atacante : public Robo
{
private:
    int num_gols;

public:
    Atacante(const float i = 0.0f, const int n = 0):
    Robo(i),
    num_gols(n)
    {

    }
    ~Atacante()
    {

    }

    void executar();

    void operator++()
    {
        num_gols++;
    }


}; //1.5

class Goleiro : public Robo
{
private:
    const bool titular;
    int num_defs;

public:
    Goleiro(const int i = 0.0f):
    Robo(i),
    titular(rand() % 2),
    num_defs(0)
    {

    }
    ~Goleiro()
    {

    }
    const bool getTitular() const { return titular; }

    void executar();

    void operator++()
    {
        num_defs++;
    }


}; //1.5 pontos

class Fila
{
public:
    class Elemento
    {
    private:
        Robo* pRobo;
        Elemento* pProx;
    
    public:
        Elemento(Robo* R = nullptr):
        pRobo(R),
        pProx(nullptr)
        {

        }
        ~Elemento()
        {
            pRobo = nullptr;
            pProx = nullptr;    
        }
        Robo* getRobo() const { return pRobo; }
        void setProx(Elemento* p) { pProx = p; }
        Elemento* getProx() const { return pProx; }
    };

private:
    Elemento* pPrim;
    Elemento* pUltimo;

public:
    Fila():
    pPrim(nullptr),
    pUltimo(nullptr)
    {

    }
    ~Fila()
    {
Elemento* pAux = NULL;
	    pAux = pPrim;

	    while (pAux != NULL)
        {

            Robo* pR = NULL;

            pR = pAux->getRobo();

            if (pR != NULL)
            {
                delete (pR);
                
            }

            pPrim = pPrim->getProx();
            delete pAux;
            pAux = NULL;
            pAux = pPrim;
        }

        pAux        = NULL;
        pPrim   = NULL;
        pUltimo     = NULL;
    }
    void incluir(Robo* p) 
    { 
	    if (p)
        {
            Elemento* pAux = NULL;
            pAux = new Elemento(p);

            if (pPrim == NULL)
            {
                pPrim = pAux;
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

        pAux = pPrim;

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
    
}; //1 ponto

class Time
{
private:
    string nome;
    Atacante* pA;
    Goleiro* pG;
    Goleiro* pGAdv;
    Fila f1;
    int num_gols;  

public:
    Time(const string n = "", const int i = 0):
     nome(n),
	pA(NULL),
	pG(NULL),
	pGAdv(NULL),
	f1(),
	num_gols(i)
    {
        pG = new Goleiro((int)1.0);
        pG->setTime(this);
        f1.incluir(static_cast<Robo*>(pG));

        pA = new Atacante(2.0);
        pA->setTime(this);
        f1.incluir(static_cast<Robo*>(pA));
        pA = NULL;

        pA = new Atacante(3.0);
        pA->setTime(this);
        f1.incluir(static_cast<Robo*>(pA));
        pA = NULL;

    }
    ~Time()
    {
        
    }
    void jogar()
    {
        if (pGAdv)
        { 
            f1.percorrer(); 
        }
    }
    const string getNome() const { return nome; }
    void setGoleiroAdversario(Goleiro* pGA) { pGAdv = pGA; }
    Goleiro* getGoleiroAdversario() const { return pGAdv; }
    Goleiro* getGoleiro() const { return pG; }
    const int getNumGols() const { return num_gols; }
    void operator++()
    {
        num_gols++;
    } 
}; //1.5 pontos

void Goleiro::executar()
{
    if (pTime)
    {
        cout    << "A quantidade de gois feitos pelo time " << pTime->getNome()
                <<  " �: " << pTime->getNumGols() << endl;

        cout    << "A quantidade de defesas feitas pelo goleiro " << getId()
                <<  " �: " << num_defs << endl;
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
            cout << "Goleiro Advers�rio Inexistente!" << endl;
        }
    }
    else
    {
        cout << "Atacante sem time!" << endl;
    }
}


int main ()
{
    Time TA("Time A"), TB("Time B");

    TA.setGoleiroAdversario(TB.getGoleiro());
    TB.setGoleiroAdversario(TA.getGoleiro());

    for(int i = 0; i < 10; i++)
    {
        (i % 2) ? TB.jogar() : TA.jogar();
    }

    return 0;
}


// nota final: 7.5