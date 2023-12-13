#include <iostream>
#include <vector>

using namespace std;

class Forma
{
protected:
    bool agregado;

public:
    explicit Forma(const bool ag = false):
    agregado(ag)
    {
    }
    virtual ~Forma() = default;

    void setAgregado(const bool ag)
    {
        agregado = ag;
    }
    virtual void desenhar() const = 0;
}; // 2 pontos

class Ponto : public Forma
{
private:
    int x;
    int y;

public:
    Ponto(const bool ag = false, const int px = -1, const int py = -1):
    x(px),
    y(py),
    Forma(ag)
    {
    }
    ~Ponto() override = default;

    void setX(const int px)
    {
        x = px;
    }
    void setY(const int py)
    {
        y = py;
    }
    void desenhar() const override
    {
        //gotoxy(x,y);
    }
}; // 2 pontos

class Reta : public Forma
{
private:
    const int comprimento;
    const int y;
    static int x;
    Ponto* pontos;

public:

    Reta(const int comp = 10):
    comprimento(comp),
    y(5),
    pontos(nullptr)
    {
        if ( comprimento > 0 ) {
            pontos = new Ponto[comprimento];

            for (int i = 0; i < comprimento; i++) {
                pontos[i].setX(x + 1);
                pontos[i].setY(y + (2 * i));
                pontos[i].setAgregado(true);
            }
            x += 2;
        }
    }
    ~Reta() override
    {
        if ( nullptr != pontos )
        {
            delete [] pontos;
            pontos = nullptr;
        }
    }


    void desenhar() const override
    {
        for(int i = 0; i < comprimento; i++)
        {
            pontos[i].desenhar();
        }
    }
}; // 1 ponto

int Reta::x = 0;

class Vetor
{
private:
    vector<const Forma*> v;

public:
    Vetor():
    v()
    {

    }
    ~Vetor()
    {
        v.clear();
    }
    void incluir (const Forma* pForma)
    {
        if (pForma) {
            v.push_back(pForma);
        }
    }
    const Forma* operator[](const int indice) const
    {
        if(indice >= 0 && indice < getTamanho())
            return v.at(indice);
        else
            return nullptr;
    }
    const int getTamanho() const
    {
        return (int)v.size();
    }
}; // 1.5

class Editor
{
private:
    Vetor vetor;
    Ponto p1;
    Ponto p2;
    Reta r1;
    Reta r2;
    Reta r3;
    Reta r4;
    Reta r5;

public:
    Editor():
    vetor(),
    p1(1,1),
    p2(2,2),
    r1(),
    r2(),
    r3(),
    r4(),
    r5()
    {
        vetor.incluir(static_cast<Forma*>(&r1));
        vetor.incluir(static_cast<Forma*>(&r2));
        vetor.incluir(static_cast<Forma*>(&r3));
        vetor.incluir(static_cast<Forma*>(&r4));
        vetor.incluir(static_cast<Forma*>(&r5));
        vetor.incluir(static_cast<Forma*>(&p1));
        vetor.incluir(static_cast<Forma*>(&p2));
    }

    ~Editor() = default;

    void percorrer() const
    {
        for(int i = 0; i < vetor.getTamanho(); i++)
        {
            if(vetor[i])
                vetor[i]->desenhar();
        }

    }

}; //1,5

int main()
{
    Editor editor;

    editor.percorrer();

    return 0;
}

//nota final: 8.0