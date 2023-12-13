#include <iostream>
#include <set>

using namespace std;

namespace Automoveis
{
class Veiculo
{
protected:
    string nome;
    float x;
    float y;

public:
    Veiculo(const string n = "", const float x1 = 0.0f, const float y1 = 0.0f):
    x(x1),
    y(y1),
    nome(n)
    {
    }

    virtual ~Veiculo()
    {
    }

    const float getX() const { return x; }
    const float getY() const { return y; }
    
    virtual void atualizar() = 0;

    void mostrar()
    {
    atualizar();
    cout << nome << "esta na posicao: (" << x << "," << y << ")." << endl; 
    }
}; //2.0 pontos

class Carro : public Veiculo
{
protected:
    int multas;
    float fator;

public:
    Carro(const string n = "", const float x1 = 0.0f, const float y1 = 0.0f, const int mult = 0, const float fat = 1.0f):
    Veiculo(n,x1,y1),
    multas(mult),
    fator(fat)
    {
    }

    ~Carro()
    {
    }

    virtual void atualizar()
    {
        operator+=(fator);
    }

    void operator+=(const float param)
    {
        x+= param;
        y+= param;
    }
}; //1.7 pontos

class Viatura : public Carro
{
private:
    bool sirene;

public:
    Viatura(const string n = "", const float x1 = 0.0f, const float y1 = 0.0f, const int mult = 0, const float fat = 1.0f, const bool sir = false):
    Carro(n,x1,y1,mult,fat),
    sirene(sir)
    {
    }

    ~Viatura()
    {
    }
    
    void atualizar()
    {
        operator++();
    }
    
    void operator++()
    {
        operator+=(2*fator);
    }
}; //1.6

    
} 

using namespace Automoveis;

namespace Gerenciadores
{
class Frota
{
private:
    set<Veiculo*> conjunto;
    set<Veiculo*>::const_reverse_iterator i;

public:
    Frota()
    {
        excluir();
    }
    
    ~Frota()
    {
        excluir();
    }
    
    void incluir(Veiculo* V)
    {
        if (V)
        {
            conjunto.insert(V);
        }
    }
    
    void excluir()
    {
        conjunto.clear();
    }
    
    void percorrer()
    {
        for(i = conjunto.rbegin(); i < conjunto.rend(); i++)
        {
            (*i)->mostrar();
        }
    }
}; //1.8 pontos

class Simulador
{
private:
    Carro C1;
    Carro C2;
    Viatura V1;
    Frota F;

public:
    Simulador():
    C1("cidadao", 2.0f, 2.0f, 0, 0.5f),
    C2("meliante", 50.0f, 50.0f, 500, 1.0f),
    V1("policial", 0.0f, 0.0f, -1, 3.0f, true),
    F()
    {    
    F.incluir(static_cast<Veiculo*>(&C1));
    F.incluir(static_cast<Veiculo*>(&C2));
    F.incluir(static_cast<Veiculo*>(&V1));

    executar();
    }
    ~Simulador()
    {

    }
    void executar()
    {
        for (int i = 0; i < 100; i++)
            {
                F.percorrer();

                if (
                    (C2.getX() <= V1.getX()) &&
                    (C2.getY() <= V1.getY())
                   )
                {
                    cout << endl << "Meliante esta preso!" << endl;

                    return;
                }
            }

            cout << endl << "Meliante escapou!" << endl;
            cout << endl;
        
    }
};

} // 1.5 ponto

using namespace Gerenciadores;

int main()
{
    Simulador S;
    return 0;
}

//total 8.5