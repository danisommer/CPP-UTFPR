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
    ~Transporte()
    {
        id_geral = -1;
    }
    const int getID() const{ return id_geral; }

    virtual void informarIDs() const = 0;

}; // 2.0 pontos

class Barco : public Transporte
{
private:
    int id_barco;

public:
    Barco(const long int ig = -1, const int ib = -1):
    Transporte(ig),
    id_barco(ib)
    {

    }
    ~Barco()
    {
        id_barco = -1;
    }
    const int getIDT() const{ return id_barco; }

    virtual void informarIDs() const
    {
        cout << "Barco: " << endl;
        cout << getID() << endl;
        cout << getIDT() << endl;
    }
    
}; // 2.0 pontos

class CarroAnfibio : public Barco
{
private:
    short int id_carro_anf;

public:
    CarroAnfibio(const long int ig = -1, const int ib = -1, const short int ica = -1):
    Barco(ig, ib),
    id_carro_anf(ica)
    {

    }
    ~CarroAnfibio()
    {
        id_carro_anf = -1;
    }
    const short int getIDCA() const { return id_carro_anf; }

    void informarIDs() const
    {
        cout << "Carro anfibio: " << endl;
        cout << getID() << endl;
        cout << getIDT() << endl;
        cout << getIDCA() << endl;
    }
}; // 2.0 pontos

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
        pProx(nullptr),
        pTransp(nullptr)
        {

        }
        ~ElemTransp()
        {
            pProx = nullptr;
            pTransp = nullptr;
        }

        void setProx(ElemTransp* p) { pProx = p; }
        ElemTransp* getProx() const { return pProx; }
        void setTransp(Transporte* p) { pTransp = p; }
        Transporte* getTransp() const { return pTransp; }
    }; // 1 ponto

private:
    ElemTransp* pPrim;

public:
    ListaTransps():
    pPrim(nullptr)
    {

    }
    ~ListaTransps()
    {
        ElemTransp* pAux = nullptr;
		pAux = pPrim;

		while ( nullptr != pAux )
		{
		    pPrim = pPrim->getProx();

            if (pAux->getTransp())
            {
                delete pAux->getTransp();
                pAux->setTransp(nullptr);
            }

            delete pAux;
            pAux = nullptr;

			pAux = pPrim;
		}

		pPrim = nullptr;
    }
    void inserir(Transporte* const p)
    {
        if(!pPrim && p)
        {
            pPrim->setTransp(p);
            return;
        }

        ElemTransp* elemAtual = pPrim;

        while(elemAtual != nullptr)
        {
            elemAtual = elemAtual->getProx();
        }

        elemAtual->setTransp(p);


    }
    void listar() const
    {
        ElemTransp* elemAtual = pPrim;

        while(elemAtual != nullptr)
        {
            elemAtual->getTransp()->informarIDs();
            elemAtual = elemAtual->getProx();
        }
    }
}; //0.5 pontos

class Sistema
{
private:
    ListaTransps lista_transps;
    static long int contTransps;
    static int contBarcos;
    static short int contCarsAnfs;
    const int maxBarcos;
    const int maxCarsAnfs;

public:
    Sistema(const int maxBs = 100, const short int maxCAs = 10):
    maxBarcos(maxBs),
    maxCarsAnfs(maxCAs)
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
        Barco* novoBarco = nullptr;

        for(int i = 0; i < maxCarsAnfs; i++)
        {
            novoBarco = new Barco(contTransps++, contBarcos++);

            lista_transps.inserir(static_cast<CarroAnfibio*>(novoBarco));

            novoBarco = nullptr;
        }
    }
    void criarCarrosAnfs()
    {
        CarroAnfibio* novoCA = nullptr;

        for(int i = 0; i < maxCarsAnfs; i++)
        {
            novoCA = new CarroAnfibio(contTransps++, contBarcos++, contCarsAnfs++);

            lista_transps.inserir(static_cast<CarroAnfibio*>(novoCA));

            novoCA = nullptr;
        }
    }
    void executar()
    {
        lista_transps.listar();
        
        cout << "Numero de transportes: "<< contTransps << endl;
        cout << "Numero de barcos: " << contBarcos << endl;
        cout << "Numero de carros anfibios: "<< contCarsAnfs << endl;
    }
}; // 2.0 pontos

long int Sistema::contTransps(0);
int Sistema::contBarcos(0);
short int Sistema::contCarsAnfs(0);


int main()
{
    int x, y;

    cin >> x >> y;

    Sistema s(x, y);

    return 0;
}

//total 9.5 pontos