// Exame recuperacao TecProg S73 2 Sem 2022 - 14 de dezembro de 2022 - DAINF / UTFFPR - Campus Curitiba - Prof J. M. Simão.

#include <iostream>
using namespace std;


class Transporte
{
private:
	long int id_geral;

public:
	Transporte(const long int ig = -1):
    id_geral(ig)
	{
	}

	virtual ~Transporte()
	{
	    id_geral = -1;
    }

	const long int getIdT() const
	{
	    return id_geral;
    }
	// retorno com long int por refino do modelo que estava com retorno int.

	virtual void informarIDs() const = 0;
};


class Barco	: public Transporte
{
private:
	int id_barco;

public:
	Barco(const long int ig = -1, const int ib = -1) :
	Transporte( ig ),
	id_barco( ib )
    {
    }

	virtual ~Barco()
	{
        id_barco = -1;
	}

	const int getIdB() const
	{
	    return id_barco;
    }
    // retorno com int por refino do modelo que estava com retorno long int.


	virtual void informarIDs() const
	{
		cout << "Id geral: "         << getIdT() << endl;
		cout << "Id barco: "         << getIdB() << endl;
		cout << endl;
	}
};


class CarroAnfibio	: public Barco
{
private:
	short int id_carroanf;

public:
	CarroAnfibio(const long int ig = -1, const int ib = -1, const short int ica = -1) :
	Barco( ig, ib ),
	id_carroanf( ica )
	{
	}

	~CarroAnfibio()
	{
	    id_carroanf = -1;
    }

	const short int getIdCA() const
	{
	    return id_carroanf;
    }

	// redefinição do método virtual da classe base;
	void informarIDs() const
	{
	    //Barco::informarIDs();

		cout << "Id geral: "            << getIdT()     << endl;
		cout << "Id barco: "            << getIdB()     << endl;
		cout << "Id carro anfibio: "    << getIdCA()    << endl;
		cout << endl;
	}
};


class ListaTransps
{
public:

    class ElemTransp
    {
        private:
            ElemTransp* pProx;
            Transporte* pTransp;

        public:

        ElemTransp():
            pProx (NULL),
            pTransp (NULL)
        {
        }

        ~ElemTransp()
        {
            pProx = NULL;
            pTransp = NULL;
        }

        void setProx(ElemTransp* p) { pProx = p;}
        ElemTransp* const getProx()  { return pProx; }

        void setTransp(Transporte* p) { pTransp = p;	}
        Transporte* getTransp() const { return pTransp; }
    };

private:
	ElemTransp *pPrim;

public:
	ListaTransps():
	    pPrim (NULL)
    { }

	~ListaTransps()
	{
		ElemTransp* pAux = NULL;
		pAux = pPrim;

		while ( NULL != pAux )
		{
		    pPrim = pPrim->getProx();

            if (pAux->getTransp())
            {
                delete pAux->getTransp();
                pAux->setTransp(NULL);
            }

            delete pAux;
            pAux = NULL;

			pAux = pPrim;
		}

		pPrim = NULL;
	}

	void inserir(Transporte* const pt)
	{
		if ( NULL == pt)
        {
            cout << " Tentativa de inserir ponteiro nulo na lista! " << endl;
        }
		else
        {
            ElemTransp* pAux    = NULL;
            ElemTransp* pUlt    = NULL;

            pUlt = pPrim;

            pAux = new ElemTransp();

            if (NULL == pAux) // Quase um exagero de precaucao.
            {
                cout << "Erro de alocação!" << endl;
            }
            else
            {
                pAux->setTransp(pt);

                if (NULL == pUlt)
                {
                    pPrim  = pAux;
                }
                else
                {
                    while ( NULL != pUlt->getProx() )
                    {
                        pUlt = pUlt->getProx();
                    }

                    pUlt->setProx( pAux );
                    //pUlt = pUlt->getProx();
                }
            }
		}
	}

	void listar() const
	{
		ElemTransp* pAux = NULL;
		Transporte* pt   = NULL;

		pAux = pPrim;

		while ( NULL != pAux )
		{
		    pt = pAux->getTransp();

		    if (pt != NULL)
            {
                pt->informarIDs();
            }
            else
            {
                cout << "Ponteiro nulo em transporte na listagem." << endl;
            }

			pAux = pAux->getProx();
		}
	}
};


class Sistema
{
private:
	ListaTransps            listatransps;

	static  long    int     contTransps;
	static          int     contBarcos;
	static  short   int     contCarsAnfs;

	const           int     maxBarcos;
	const   short   int     maxCarsAnfs;
	// short por refino do modelo.

public:

	Sistema(const int maxBs = 100, const short int maxCAs = 10) :
	    listatransps( ),
	    maxBarcos   ( maxBs  ),
	    maxCarsAnfs ( maxCAs )
	{
	    criarBarcos();
	    criarCarrosAnfs();
	    executar();
	}

	~Sistema()
	{
	    contTransps     = -1;
	    contBarcos      = -1;
	    contCarsAnfs    = -1;
	}

	void criarBarcos()
	{
	    Transporte*     pT  =   NULL;
	    Barco*          pB  =   NULL;

	    for (int i = 0; i < maxBarcos; i++)
        {
            pB  = new Barco         (contTransps++, contBarcos++);

            pT  = static_cast<Transporte*>(pB);

            listatransps.inserir( pT );
        }
	}


    void criarCarrosAnfs()
	{
	    Transporte*     pT  =   NULL;
	    CarroAnfibio*   pCA =   NULL;

	    for (int i = 0; i < maxCarsAnfs; i++)
        {
            pCA = new CarroAnfibio  (contTransps++, contBarcos++, contCarsAnfs++);

            pT  = static_cast<Transporte*>(pCA);

            listatransps.inserir( pT );
        }
	}

	void executar() const
	{
        listatransps.listar();

        cout << endl;

		cout << "Quantidade de transportes:     "   << contTransps  << endl;
		cout << "Quantidade de barcos:          "   << contBarcos   << endl;
		cout << "Quantidade de carros anfibios: "   << contCarsAnfs << endl;

		cout << endl;

		cout << "Quantidade máxima de barcos:          "   << maxBarcos   << endl;
		cout << "Quantidade máxima de carros anfibios: "   << maxCarsAnfs << endl;

		cout << endl;
	}
};

long    int     Sistema::contTransps(0);
        int     Sistema::contBarcos(0);
short   int     Sistema::contCarsAnfs(0);


int main()
{
    int         x   = 0;
    short int   y   = 0;

    cout << "Informar quantidade maxima de barcos e carros anfibios: " << endl;
    cin >> x >> y;

    cout << endl;

	Sistema sistema (x, y);

	return 0;
}

