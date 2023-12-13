#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Sensor
{
protected:
    static vector<Sensor*> colecao_sensores;
    static int cont;
    bool ativo;

public:
    Sensor() : ativo(true)
    {
        ativo = !((rand() % 10) == 1);
        cont++;
    }

    virtual ~Sensor()
    {
        ativo = false;

        for (int i = 0; i < colecao_sensores.size(); i++)
        {
            if (colecao_sensores[i])
            {
                delete colecao_sensores[i];
                colecao_sensores[i] = NULL;
            }
        }
    }

    const bool getAtivo() const
    {
        return ativo;
    }

    static const bool TodosInativos()
    {
        bool at = true;

        for (int i = 0; i < (int)colecao_sensores.size(); i++)
        {
            if (colecao_sensores[i]->getAtivo())
            {
                at = false;
                break;
            }

        }
        return false;
    }

    static void incluirSensor(Sensor* pS)
    {
        if (pS)
        {
            colecao_sensores.push_back(pS);
        }
    }

    static void percorrer()
    {
        for (int i = 0; i < (int)colecao_sensores.size(); i++)
        {
            (colecao_sensores[i])->operator++();
        }
    }

    virtual void operator++() = 0;
};

vector<Sensor*> Sensor::colecao_sensores;
int Sensor::cont = 0;

class Temper : public Sensor
{
private:
    int temperatura;

public:
    Temper() : Sensor(), temperatura(cont)
    {
        cout << "O valor da temperatura eh:" << temperatura << endl;

        incluirSensor(static_cast<Sensor*>(this));
    }

    ~Temper()
    {
        temperatura = 0;
    }

    void operator++()
    {
        temperatura++;
        cout << "Novo valor da temperatura é: " << temperatura << endl;
    }

    const int getTemperatura() const
    {
        return temperatura;
    }
};

class Presen : public Sensor
{
private:
    Temper* pTemper;
    bool alguem;

public:
    Presen() : alguem(false), pTemper(NULL)
    {
        alguem = ((cont % 2) == 0);
        pTemper = new Temper();

    }

    ~Presen()
    {
        alguem = false;

        if (pTemper)
        {
            delete pTemper;
        }
        pTemper = NULL;
    }

    void setTemper(Temper* pT)
    {
        pTemper = pT;
    }

    const bool getAlguem() const
    {
        return alguem;
    }

    const int getTemperatura() const
    {
        return pTemper->getTemperatura();
    }

    const bool getAmbosAtivos() const
    {
        if (ativo && pTemper->getAtivo())
        {
            return true;
        }
        return false;
    }

    void operator++()
    {
        cout << endl << "Troquei!" << endl;
        alguem = !alguem;
    }
};

class Controle_Predio;

class Controle_Andar
{
private:
    Presen sens_pres;
    Controle_Predio* pCtrlPred;
    float oxigenio;
    bool incendio;

public:
    Controle_Andar(float O = 100.0) : oxigenio(O), sens_pres(), pCtrlPred(NULL), incendio(false)
    {
    }

    ~Controle_Andar()
    {
        pCtrlPred = NULL;

    }

    void setControlePredio(Controle_Predio* pCP)
    {
        pCtrlPred = pCP;
    }

    const float getOxigenio() const
    {
        return oxigenio;
    }

    const bool getIncendio() const
    {
        return incendio;
    }

    void controlar();
};


class Controle_Predio
{
private:
    int temperatura;
    Controle_Andar andares[5];

public:
    Controle_Predio(int T = 0) : temperatura(T), andares()
    {
        for (int i = 0; i < 5; i++)
        {
            andares[i].setControlePredio(this);
        }
        executar();
    }

    ~Controle_Predio()
    {
    }

    const int getTemperatura()
    {
        return temperatura;
    }

    void informar_Colapso() const
    {
        cout << endl;
        if (Sensor::TodosInativos())
        {
            cout << "Colapso total, nenhum sensor ativo!" << endl;
        }
        else
        {
            cout << "Ainda não há colapso total pois há ao menos um sensor funcionando." << endl;
            informar_Incendio();
        }
    }

    void informar_Incendio() const
    {
        cout << endl;

        int cont_incendios = 0;

        for (int i = 0; i < 5; i++)
        {
            if (andares[i].getIncendio())
            {
                cont_incendios++;
                cout << "O andar " << i + 1 << " está em incêndio!" << endl;
            }
        }
        cout << endl;
        cout << "Há " << cont_incendios << " andares em incêndio!" << endl;

    }

    void executar()
    {
        for (int i = 0; i < temperatura; i++)
        {
            cout << endl;
            cout << "Percorrimento de número " << i << endl;

            Sensor::percorrer();

            for (int j = 0; j < 5; j++)
            {
                andares[j].controlar();
            }
        }
        informar_Colapso();
    }

};

void Controle_Andar::controlar()
{
    if (NULL == pCtrlPred)
    {
        cout << "Erro - pCtrlPred Nulo" << endl;
        exit(1);
    }

    if ( sens_pres.getAmbosAtivos() &&    //cout << "Ambos os sensore ativos!" << endl;
            ( sens_pres.getTemperatura() > 55 )
       )
    {

        if ( sens_pres.getAlguem() == false  )
        {
            oxigenio = 0.0;
            incendio = false;
            cout << endl << "Desoxigenação !" << endl;
        }
        else
        {
            if ( sens_pres.getTemperatura() >= pCtrlPred->getTemperatura() )
            {
                incendio = true;
                cout << endl << "Incendio !" << endl;
            }
        }
    }
}

int main()
{
    time_t t;

    srand(3 * (unsigned)time(&t));

    Controle_Predio CP1(1);
    Controle_Predio CP2(30);
    Controle_Predio CP3(60);

    return 0;
}
