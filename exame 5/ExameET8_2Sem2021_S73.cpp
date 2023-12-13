
#include <map>
#include <iostream>
using namespace std;

class Inseto
{
    private:
        int energia;

    public:

        Inseto():
            energia (0)
        {
        }

        virtual ~Inseto()
        {
        }

        void setEnergia(const int e)
        {
            energia = e;
        }

        const int getEnergia() const
        {
            return energia;
        }

        void informar_energia() const
        {
            cout << "O valor da energia eh: " << energia << endl;
        }

        virtual void executar() = 0;

        virtual void locomover() const = 0;
};

class Abelha : public Inseto
{
    protected:
        bool ferrao;

    public:

        Abelha():
            Inseto(),
            ferrao(false)
        {
        }

        ~Abelha()
        {
        }

        void setFerrao(const bool f)
        {
            ferrao = f;
        }

        const int getFerrao() const
        {
            return ferrao;
        }

        void locomover() const
        {
            cout << " Abelha voa. " << endl;
            informar_energia();
        }

        void executar()
        {
            locomover();
        }

};

class Formiga : public Inseto
{
    protected:
        Abelha* pAbelha;

    public:

        Formiga():
        Inseto(),
        pAbelha(NULL)
        {
        }

        virtual ~Formiga()
        {
            pAbelha = NULL;
        }

        void setAbelha(Abelha* pAb)
        {
            pAbelha = pAb;
        }

        Abelha* getAbelha() const
        {
            return pAbelha;
        }

        virtual void interagir()
        {
            if ( pAbelha ) {
                if ( ! pAbelha->getFerrao()  )
                {
                    pAbelha->setEnergia(pAbelha->getEnergia() - 1);
                    cout << "Ataquei!" << endl;
                }
                else
                {
                    cout << "Não ataquei!" << endl;
                }
            }
        }


        void locomover() const
        {
            cout << "A formiga anda." << endl;
            informar_energia();
        }

        void executar()
        {
            interagir();
            locomover();
        }
};

class ForAmiga :  public Formiga
{
private:

    float amigavel;

    static const float MIN;

public:
    ForAmiga():
        Formiga(),
        amigavel(false)
    {
    }

    ~ForAmiga()
    {
    }

    void setAmigavel(const float a) { amigavel = a; }
    const float getAmigavel() { return amigavel; }

    void interagir()
    {
        if (pAbelha != NULL)
        {
            if (amigavel > MIN)
            {
                pAbelha->setEnergia(pAbelha->getEnergia()+1);
                cout << "Ajudei!" << endl;
            }
            else
            {
                 cout << "Não ajudei!" << endl;
            }
        }
    }


    const bool operator>(ForAmiga& F) const
    {
        if (amigavel > F.getAmigavel())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

const float ForAmiga::MIN = 3.1;

//typedef map< int, Inseto*> mapa;

class Colonia
{
    private:
        map< int, Inseto*> VIs;
        map< int, Inseto*>::const_iterator iterador;
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

        void incluir(Inseto* pi)
        {
            if (pi != NULL)
            {
                VIs.insert( map< int, Inseto*>::value_type(cont, pi) );
                //VIs.insert( pair< int, Inseto*>(cont, pi) );
                //VIs[cont] = pi;
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

            cout << endl;
        }

        /*void percorrer2()
        {
            int TAM = 0;
            TAM = (int)VIs.size();

            Inseto* pt = NULL;

            for (int i = 0; i < TAM; i++)
            {
                cout << endl;
                pt = VIs[i];
                pt->executar();
            }
            cout << endl;
        } */

};

int Colonia::cont(0);

class Habitat
{
    private:

        Abelha ab1;
        Abelha ab2;
        Formiga fo1;
        Formiga fo2;
        ForAmiga fa1;
        ForAmiga fa2;

        Colonia C;

    public:

        Habitat():
        ab1(),
        ab2(),
        fo1(),
        fo2(),
        fa1(),
        fa2(),
        C()
        {

            ab1.setEnergia(1);
            ab2.setEnergia(1);
            fo1.setEnergia(1);
            fo2.setEnergia(1);
            fa1.setEnergia(1);
            fa2.setEnergia(1);

            ab1.setFerrao(true);
            ab2.setFerrao(false);

            fo1.setAbelha(&ab1);
            fo2.setAbelha(&ab2);

            fa1.setAmigavel(1.0);
            fa2.setAmigavel(4.0);

            fa1.setAbelha(&ab2);
            fa2.setAbelha(&ab1);

            C.incluir(static_cast<Inseto*>(&fo1));
            C.incluir(static_cast<Inseto*>(&fo2));
            C.incluir(static_cast<Inseto*>(&fa1));
            C.incluir(static_cast<Inseto*>(&fa2));
            C.incluir(static_cast<Inseto*>(&ab1));
            C.incluir(static_cast<Inseto*>(&ab2));

            executar();

        }

        ~Habitat()
        {

        }

        void verificarMaisAmigavel()
        {    cout << endl;
             ( fa1 > fa2 ) ? ( cout << "Fa1 maior que fa2" << endl ) : ( cout << "Fa2 maior ou igual a fa1" << endl );
             cout << endl;
        }

        void executar()
        {
            C.percorrer();

            verificarMaisAmigavel();
        }

};

int main()
{
    Habitat habitat;

    cout << endl;

    cout << "FIM" << endl;

    return 0;
}

