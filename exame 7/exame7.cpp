#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Hormonio
{
protected:
    string nivel;
    bool estresse;

private:
    static int soma;

public:
    Hormonio():
    nivel("indeterminado"),
    estresse(false)
    {
        estresse = !((bool)(soma % 2));
        soma++;
    }
    virtual ~Hormonio()
    {
    }

    const string getNivel() const { return nivel; }

    virtual void calcular_nivel() = 0;
}; // 2.0 pontos

int Hormonio::soma = 0;

class Serotonina;

class Endorfina : public Hormonio
{
private:
    float real;
    Serotonina* pSero;

public:
    Endorfina():
     Hormonio(), 
     real(0.0), 
     pSero(nullptr)
    {
        real = rand() % 11;
    }
    ~Endorfina()
    {
        
    }
    const float getReal() const { return real; }
  
    void setSero(Serotonina* pS) { if(pS) pSero = pS; }

    void calcular_nivel();
}; //1.5

class Serotonina : public Hormonio
{
private:
    int inteiro;
    Endorfina* pEndo;

public:
    Serotonina():
    Hormonio(), 
    inteiro(0), 
    pEndo(nullptr)
    {
        inteiro = rand() % 11;

        if(estresse && (inteiro > 0))
        {
            inteiro--;
        }
    }
    ~Serotonina()
    {
        pEndo = nullptr;
    }
    const int getInteiro() const { return inteiro; }
  
    void setEndo(Endorfina* pE) { if(pE) pEndo = pE; }

    void calcular_nivel()
    {
        if(pEndo)
        {
            if((inteiro <= 10) && (inteiro >= 7) && (pEndo->getReal() > 5.0f))
            {
                nivel = "normal";
            }
            else if ((inteiro < 7) && (inteiro > 4) && (pEndo->getReal() > 3.0f))
            {
                nivel = "medio";
            }
            else if ((inteiro <= 4) && (inteiro >= 0) && (pEndo->getReal() > 0.0f))
            {
                nivel = "baixo";
            }
        }
    }
}; // 1.8 pontos

 void Endorfina::calcular_nivel()
    {
        if(pSero)
        {
            if((real <= 10.0f) && (real >= 6.0f) && (pSero->getInteiro() > 7))
            {
                nivel = "normal";
            }
            else if ((real < 6.0f) && (real > 3.0f) && (pSero->getInteiro() > 5))
            {
                nivel = "medio";
            }
            else if ((real <= 3.0f) && (real >= 0.0f) && (pSero->getInteiro() > 0))
            {
                nivel = "baixo";
            }
        }
    }

class Reg_Paciente
{
private:
    Endorfina nivel_endo;
    Serotonina nivel_sero;
    bool ok;

public:
    Reg_Paciente()
    {
        nivel_endo.setSero(&nivel_sero);
        nivel_sero.setEndo(&nivel_endo);

        nivel_endo.calcular_nivel();
        nivel_sero.calcular_nivel();
    }
    ~Reg_Paciente()
    {

    }
    const int getOk() const
    {
        return (int)ok;
    }
    void auto_avaliar()
    {
        if((nivel_endo.getNivel() == "medio" || nivel_endo.getNivel() == "normal") && 
           (nivel_sero.getNivel() == "medio" || nivel_sero.getNivel() == "normal")) 
        {
             ok = true;
        }
        else
        {
            ok = false;
        }
          
    }
}; // 1.9 pontos

class Diagnosticador
{
private:
   list<Reg_Paciente*> listap;
   ostringstream saida;

public:
    Diagnosticador(const int num = 10):
    listap(),
    saida()
    {
        listap.clear();

        Reg_Paciente* novoRegistro = nullptr;

        for(int i = 0; i < num; i++)
        {
            novoRegistro = new Reg_Paciente;

            if(novoRegistro)
            {
                listap.push_back(novoRegistro);
            }
            
            novoRegistro = nullptr;
        }
    }
    ~Diagnosticador()
    {
        listap.clear();
    }

    ostringstream& getSaida()
    {
        return saida;
    }


    void diagnosticar()
    {
        Reg_Paciente* pR = NULL;

        list<Reg_Paciente*>::iterator it;

        it = listap.begin();

        int cont = 0;

        while (it != listap.end())
        {
            pR = *it;

            if (pR)
            {
                pR->auto_avaliar();

                if (pR->getOk() != 0)
                {
                    cont++;
                }
            }
            it++;
        }

        int tam = (int)listap.size();

        float calc = static_cast<float>((cont*100)/tam);

        saida << endl << "A porcentagem de pacientes OK eh de " << calc << endl;

    }

}; // 0.5 pontos

ostream& operator<<( ostream& s, Diagnosticador& d)
{
    cout << (d.getSaida()).str();
    return s ;
}

int main ()
{
    Diagnosticador diag1(100);

    cout << diag1 << endl;

    return 0;
}

//7.7 pontos