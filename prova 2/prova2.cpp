#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Inseto
{
private:
    int energia;
public:
    Inseto(const int energ = 0) : energia(energ)
    {

    }
    virtual ~Inseto()
    {
        energia = -1;
    }
    const int getEnergia()
    {
        return energia;
    }
    virtual void sobreviver() = 0;

    void operator-- ()
    {
        energia--;
    }
};

class Formigueiro;

class Gafanhoto : public Inseto
{
private:
    const bool invasor;
    static Formigueiro* pGueiro;
public:
    Gafanhoto(const int energ = 10) : Inseto(energ), invasor((bool)(rand() % 2))
    {

    }
    ~Gafanhoto()
    {


    }
    const bool getInvasor()
    {
        return invasor;
    }
    void static setFormigueiro(Formigueiro* p)
    {
        pGueiro = p;

    }
    void sobreviver() override
    {

    }
};
Formigueiro* Gafanhoto::pGueiro(NULL);

class Formiga : public Inseto
{
private:
    static Gafanhoto* pGafa;
    static int cont;
    int ferrao;
public:
    Formiga(const int energ = 1) : Inseto(energ), ferrao(cont++)
    {

    }

    ~Formiga()
    {
        cont--;
    }

    void sobreviver() override
    {

        int n_ataques = ferrao;

        if (pGafa->getInvasor())
            n_ataques *= 2;

        for (int i = 0; i < n_ataques; i++)
        {
            pGafa->operator--();
        }

        operator--();
    }

    void static setGafa(Gafanhoto* pG)
    {
        pGafa = pG;
    }
};

class Formigueiro
{
private:
    vector<Formiga*> colecao;
public:
    Formigueiro(const int nFormigas = 100) : colecao()
    {
        colecao.clear();

        Formiga* pF = NULL;

        for (int i = 0; i < nFormigas; i++)
        {
            pF = new Formiga(100);
            if (pF)
            {
                colecao.push_back(pF);
            }
            else
            {
                continue;
            }

        }

    }
    ~Formigueiro()
    {
        int tam = (int)colecao.size();
        for (int i = 0; i < tam; i++)
        {
            if (colecao[i])
            {
                delete colecao[i];
                colecao[i] = NULL;
            }
        }
        colecao.clear();
    }
    void eliminar_ultima()
    {
        if (!colecao.empty())
        {
            Formiga* pF = NULL;
            pF = colecao.back();
            colecao.pop_back();
            if (pF)
            {
                delete pF;
                pF = NULL;
            }
            else
            {
                cout << "A última formiga estava nula!" << endl;
            }
        }
        else
        {
            cout << "Colecao de formigas vazia!" << endl;
        }
    }
    void eliminar_sem_energia()
    {
        bool flag = true;
        while (flag)
        {
            int tam = (int)colecao.size();

            for (int i = 0; i < tam; i++)
            {
                if (colecao[i]->getEnergia() <= 0)
                {
                    delete colecao[i];
                    colecao[i] = NULL;
                }

                if (NULL == colecao[i])
                {
                    vector<Formiga*>::iterator it;
                    it = colecao.begin() + i;
                    colecao.erase(it);
                    break;
                }
            }
            flag = false;
        }

    }
    void defender(Gafanhoto* pGafa)
    {
        bool    luta = true;
        Formiga::setGafa(pGafa);
        while (luta)
        {
            int tam = (int)colecao.size();

            if (pGafa->getEnergia() <= 0)
            {
                cout << "Gafanhoto derrotado" << endl;
                luta = false;
            }

            if (tam <= 0)
            {
                cout << "Formigueiro derrotado" << endl;
                luta = false;
            }

            if (false == luta)
            {
                return;
            }

            for (int i = 0; i < tam; i++)
            {
                if (colecao[i])
                {
                    colecao[i]->sobreviver();
                }
            }

            eliminar_sem_energia();
        }
    }
};

class Habitat
{
private:
    const int num_gafs;
    Formigueiro formigueiro;
    list<Gafanhoto*> colecao;
public:
    Habitat() : num_gafs(10), formigueiro((int)(rand() % 1000)), colecao()
    {
        colecao.clear();
        Gafanhoto::setFormigueiro(&formigueiro);
        criarGafanhotos();
        executar();
    }

    ~Habitat()
    {
        list<Gafanhoto*>::iterator it;
        it = colecao.begin();
        while (it != colecao.end())
        {
            if (*it)
            {
                delete (*it);
            }
            it++;
        }
        colecao.clear();
    }
    void criarGafanhotos()
    {
        Gafanhoto* pG = NULL;

        for (int i = 0; i < num_gafs; i++)
        {
            pG = new Gafanhoto(1);
            if (pG)
            {
                colecao.push_back(pG);
                pG = NULL;
            }
            else
            {
                cout << "Gafanhoto não alocado" << endl;
            }
        }
    }
    void executar()
    {
        list<Gafanhoto*>::iterator it;
        it = colecao.begin();
        while (it != colecao.end())
        {
            if (*it)
            {
                (*it)->sobreviver();
            }
            it++;
        }
    }
};

int main()
{
    time_t t;

    srand((unsigned)time(&t));

    Habitat habitat;
    return 0;
}
