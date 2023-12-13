#include <iostream>

using namespace std;

class Nave
{
protected:
    string numero;

public:
    Nave():
    numero(" ")
    {
    }
    ~Nave()
    {
        numero.clear();
    }

    void setNumero(const string n)
    {
        numero = n;
    }
    const string getNumero() const
    {
        return numero;
    }

    virtual void informar() const = 0;
}; // 1.8 pontos

class Aviao : public Nave
{
private:
    bool supersonico;

public:
    Aviao():
    Nave(),
    supersonico(false)
    {}
    ~Aviao() = default;

    void setSup(const bool sps)
    {
        supersonico = sps;
    }
    const bool getSup() const
    {
        return supersonico;
    }
    void informar() const override
    {
        cout << "Transporte Aéreo." << endl;
        cout << "Número: " << numero << endl;
        cout << "Supersonico: " << supersonico << endl;
    }
    bool operator==(Aviao &A) const
    {
        return (A.getSup() == getSup() && A.getNumero() == getNumero());
    }
}; // 2.0 pontos

class Lista_Naves
{
public:

    template<class T>
    class Elemento
    {
    private:
        Elemento<T>* pAnterior;
        T* pDatum;

    public:
        Elemento()
        {
            pAnterior = NULL;
            pDatum = NULL;
        }
        ~Elemento()
        {
            pAnterior = NULL;
            pDatum = NULL;
        }

        void setAnterior( Elemento<T>* pAnte) { pAnterior = pAnte; }
        Elemento<T>* getAnterior() const { return pAnterior; }

        void setDatum( T* pDt) { pDatum = pDt; }
        T* getDatum() const { return pDatum; }
    };


private:
    Elemento<Nave>* pUltimo;
    Elemento<Nave>* pAtual;

public:
    Lista_Naves()
    {
        pUltimo     = NULL;
        pAtual      = NULL;
    }

    ~Lista_Naves()
    {
        Elemento<Nave>* aux = NULL;
        aux = pUltimo;

        while (aux != NULL)
        {
            pUltimo = pUltimo->getAnterior();
            aux->setAnterior(NULL);
            aux->setDatum(NULL);
            delete (aux);
            aux = pUltimo;
        }

        aux = NULL;
        pUltimo = NULL;
        pAtual = NULL;
    }

    void incluir(Nave* pNave)     // Método para incluir uma Nave.
    {
        if (NULL != pNave)
        {
            Elemento<Nave>* aux = NULL;

            aux = new Elemento<Nave>();

            aux->setDatum(pNave);

            if (NULL == pUltimo)
            {
                pUltimo = aux;
                pAtual  = aux;
            }
            else //if(NULL != pprime)
            {
                pAtual->setAnterior(aux);
                pAtual = aux;
            }
        }
    }


    void listar() const
    {
        if (pUltimo != NULL)
        {
            Elemento<Nave>* aux;
            aux = pUltimo;

            while (aux != NULL)
            {
                (aux->getDatum())->informar();
                cout<<endl;
                aux = aux->getAnterior();
            }
        }
        else
        {
            cout << "Lista Vazia!" << endl << endl;
        }
    }
}; //0.5 pontos

class Navio : public Nave
{
private:
    Lista_Naves lista_avioes;

public:
    Navio():
    Nave(),
    lista_avioes()
    {
    }
    ~Navio() = default;
    void incluir_aviao(Aviao* pAviao)
    {
        if(pAviao)
            lista_avioes.incluir(pAviao);
    }
    void informar() const override
    {
        cout << "Porta-aviões." << endl;
        cout << "Número: " << numero << endl;
        cout << "Está transportando: " << endl;
        lista_avioes.listar();
    }

}; // 2.0

class Sistema
{
private:
    Aviao A1, A2;
    Navio N1;

public:
    Sistema():
    A1(),
    A2(),
    N1()
    {
        A1.setNumero("F16");
        A1.setSup( true );

        A2.setNumero("F15");
        A2.setSup( true );

        N1.setNumero("Porta-avioes");
        N1.incluir_aviao(&A1);
        N1.incluir_aviao(&A2);

        executar();
    }

    ~Sistema() = default;

    void executar()
    {
        if (A1 == A2)
        {
            cout << "O avião " << A1.getNumero() << " é igual ao avião "    << A2.getNumero() << endl ;
        }
        else
        {
            cout << "O avião " << A1.getNumero() << " é diferente do avião " << A2.getNumero() << endl ;
        }

        N1.informar();
    }
}; // 1 ponto

int main()
{
    Sistema sistema;
    return 0;
}

//Nota final: 7,3