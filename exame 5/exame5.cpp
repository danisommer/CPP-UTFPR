#include <iostream>
#include <map>

using namespace std;

class Inseto
{
protected:
    int energia;

public:
    Inseto():
    energia(0)
    {

    }
    virtual ~Inseto()
    {
        
    }

    void setEnergia(const int e) { energia = e; } 
    const int getEnergia() const { return energia; }
    void informa_energia() const
    {
        cout << "a energia eh: " << energia << endl;
    }

    virtual void locomover() const = 0;
    virtual void executar() = 0;
}; // 1.0 ponto

class Colonia
{
private:
    std::map<int, Inseto*> VIs;
    std::map<int, Inseto*>::const_iterator iterador;
    static int cont;

public:
    Colonia():
    VIs(),
    iterador()
    {
        VIs.clear();
    }
    ~Colonia()
    {
        VIs.clear();
    }

    void incluir(Inseto* P)
    {
        if(P)
        {
            //VIs.insert( map< int, Inseto*>::value_type(cont, pi) );

            VIs.insert(pair(cont, P));
            cont++;
        }

    }

    void percorrer()
    {
        for ( iterador = VIs.begin(); iterador != VIs.end(); ++iterador)
        {
            cout << endl;
            (iterador->second)->executar();
        }
    }
}; // 0.5 pontos

int Colonia::cont(0);

class Abelha : public Inseto
{
protected:
    bool ferrao;

public:
    Abelha():
    ferrao(false),
    Inseto()
    {

    }
    ~Abelha()
    {
        ferrao = false;
    }
    void setFerrao(const bool f) { ferrao = f; }
    const bool getFerrao() const { return ferrao; }

    void locomover() const
    {
        cout << "abelha voa" << endl;
        informa_energia();
    }
    void executar()
    {  
        locomover();
    }

}; // 1.0 ponto

class Formiga : public Inseto
{
protected:
    Abelha* pAbelha;

public:
    Formiga():
    pAbelha(nullptr),
    Inseto()
    {
    }
    virtual ~Formiga()
    {  
        pAbelha = nullptr;
    }
    
    void setAbelha(Abelha* pA)
    {
        if(pA)
        {
            pAbelha = pA;
        }
    }

    Abelha* getAbelha() const
    {
        if(pAbelha)
        {
           return pAbelha;
        }
        
    }

    void locomover() const
    {
        cout << "Formiga anda" << endl;
        informa_energia();
    }

    virtual void interagir()
    {
        if(pAbelha)
        {
            if(!pAbelha->getFerrao())
            {
                pAbelha->setEnergia(pAbelha->getEnergia() - 1);
                cout << "Formiga atacou abelha" << endl;
            }
            else
            {
                cout << "Formiga não atacou abelha" << endl;

            }
        }
    }

        void executar()
    {
        interagir();
        locomover();
    }
}; // 2.0 pontos

class ForAmiga : public Formiga
{
private:
    float amigavel;
    static const float MIN;

public:
    ForAmiga():
    amigavel(0.0f),
    Formiga()
    {

    }
    ~ForAmiga()
    {
    }

    void setAmigavel(const float a) { amigavel = a; }  
    const float getAmigavel() const { return amigavel; }

    void interagir()
    {
        if(pAbelha)
        {
            if(amigavel > MIN)
            {
                pAbelha->setEnergia(pAbelha->getEnergia() + 1);
                cout << "Formiga ajudou abelha" << endl;

            }
            else
            {
                cout << "Formiga não ajudou abelha" << endl;
            }
        }
    }

    const bool operator>(ForAmiga& f) const
    {
        return (amigavel > f.getAmigavel());
    } 
}; //2.0 pontos

const float ForAmiga::MIN(3.1);

class Habitat
{
private:
    Abelha A1;
    Abelha A2;
    Formiga F1;
    Formiga F2;
    ForAmiga FA1;
    ForAmiga FA2;
    Colonia C;

public:
    Habitat():
    A1(),
    A2(),
    F1(),
    F2(),
    FA1(),
    FA2()
    {
        A1.setEnergia(1);
        A2.setEnergia(1);
        F1.setEnergia(1);
        F2.setEnergia(1);
        FA1.setEnergia(1);
        FA2.setEnergia(1);

        A1.setFerrao(true);
        A2.setEnergia(false);

        F1.setAbelha(&A1);
        F2.setAbelha(&A2);
        FA1.setAbelha(&A1);
        FA2.setAbelha(&A2);

        FA1.setAmigavel(1.0f);
        FA2.setAmigavel(4.0f);

        C.incluir(static_cast<Inseto*>(&F1));
        C.incluir(static_cast<Inseto*>(&F2));
        C.incluir(static_cast<Inseto*>(&A1));
        C.incluir(static_cast<Inseto*>(&A2));
        C.incluir(static_cast<Inseto*>(&FA1));
        C.incluir(static_cast<Inseto*>(&FA2));

        executar();
    }
    ~Habitat()
    {

    }
    void verificarMaisAmigavel()
    {
    ( F1 > F2 ) ? ( cout << "Fa1 maior que fa2" << endl ) : ( cout << "Fa2 maior ou igual a fa1" << endl );
    }
    void executar()
    {
        C.percorrer();
        verificarMaisAmigavel();

    }

}; //1.5 pontos

int main ()
{
    Habitat H;
    return 0;
}

//total 8.0 pontos