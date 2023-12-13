#include <iostream>

using namespace std;

class Transporte
{
private:
    long int id_geral;

public:
    Transporte(const long int ig = -1) : id_geral(ig) { }

    ~Transporte()
    {
        id_geral = -1;
    }

    const int getIdT() const { return id_geral; }

    virtual void informarIDs() const = 0;
}; //2.0 pontos

class Barco : public Transporte
{
private:
    long int id_barco;

public:
    Barco(const long int ig = -1, const long int ib = -1):
    Transporte(ig),
    id_barco(ib)
    {

    }

    ~Barco()
    {
        id_barco = -1;
    }

    const long int getIdB() const { return id_barco; }

    virtual void informarIDs() const
    {
        cout << "ID Barco: " << id_barco << endl;
        cout << "ID Geral: " << getIdT() << endl;
    }

}; // 2.0 pontos

class CarroAnfibio : public Barco
{
private:
    short int id_carroanf;

public:
    CarroAnfibio(const long int ig = -1, const int ib = -1, const short int ica = -1):
    Barco(ig, ib),
    id_carroanf(ica)
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

    void informarIDs() const
    {
        cout << "ID Barco: " << getIdB() << endl;
        cout << "ID Geral: " << getIdT() << endl;
        cout << "ID Carro Anfibio: " << getIdCA() << endl;
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
        };

private:
    ElemTransp* pPrim;

public:
    ListaTransps():
    pPrim(nullptr)
    {

    }
    ~ListaTransps()
    {
        ElemTransp* current = pPrim;

        while (current != nullptr)
        {
            ElemTransp* next = current->getProx();
            delete current;
            current = next;
        }
    }
    void inserir(Transporte* p)
    {
        if (!pPrim && p)
        {
            pPrim = new ElemTransp;
            pPrim->setTransp(p);
            return;
        }

        ElemTransp *elemAtual = pPrim;

        while (elemAtual->getProx() != nullptr)
        {
            elemAtual = elemAtual->getProx();
        }

        ElemTransp* novoElem = new ElemTransp;
        novoElem->setTransp(p);
        elemAtual->setProx(novoElem);
    }
    void listar() const
    {
        ElemTransp* current = pPrim;

        while (current != nullptr)
        {
            current->getTransp()->informarIDs();
        }
    }
}; // 1.5 pontos

class Sistema
{
private:
    ListaTransps listaTransps;
    static long int contTransps;
    static int contBarcos;
    static short int contCarsAnfs;
    const int maxBarcos;
    const int maxCarsAnfs;
public:
    Sistema(const int maxBs = 100, const short int maxCAs = 10):
    listaTransps( ),
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
        Transporte*     pT  =   NULL;
        Barco*          pB  =   NULL;

        for (int i = 0; i < maxBarcos; i++)
        {
            pB  = new Barco         (contTransps++, contBarcos++);

            pT  = static_cast<Transporte*>(pB);

            listaTransps.inserir( pT );
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

            listaTransps.inserir( pT );
        }
    }
    void executar() const
    {
        listaTransps.listar();

        cout << endl;

        cout << "Quantidade de transportes:     "   << contTransps  << endl;
        cout << "Quantidade de barcos:          "   << contBarcos   << endl;
        cout << "Quantidade de carros anfibios: "   << contCarsAnfs << endl;

        cout << endl;

        cout << "Quantidade m�xima de barcos:          "   << maxBarcos   << endl;
        cout << "Quantidade m�xima de carros anfibios: "   << maxCarsAnfs << endl;

        cout << endl;
    }
}; //1.5

long int Sistema::contTransps(0);
int Sistema::contBarcos(0);
short int Sistema::contCarsAnfs(0);


int main()
{
    int         x   = 100;
    short int   y   = 10;

    Sistema sistema(x, y);

    return 0;
}

// notal final 8.5