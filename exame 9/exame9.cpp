#include <iostream>
#include <Windows.h>
#include <vector>
#include <math.h>

using namespace std;

void draw(int x, int y, string c)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();

	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);

	cout << ".";
}


class Ponto
{
protected:
    int x;
    int y;
    bool ok;

public:
    Ponto(const int x1 = 0, const int y1 = 0):
    x(x1),
    y(y1),
    ok(true)  
    {

    }
    virtual ~Ponto()
    {

    }
    virtual void imprimir() const 
    {
        draw(x, y, ".");
    }
    const bool operator==(const Ponto& p) 
    {
        return ((p.getX() == x) && (p.getY() == y));
    }

    const bool getOk() const { return ok; }

    const int getX() const { return x; }

    const int getY() const { return y; }
}; // 1.5 pontos

class VetPontos
{
private:
    vector<Ponto*> pontos;

public:
    VetPontos():
    pontos()
    {
        pontos.clear();
    }
    ~VetPontos()
    {
        for(int i = 0; i< (int)pontos.size(); i++)
        {
            if (pontos[i])
            {
			  delete pontos[i];
			  pontos[i] = nullptr;
            }
		}
        pontos.clear();
    }
    const int getTamanho() const
    {
        return (int)pontos.size();
    }
    void incluir(Ponto* p)
    {
        if (p)
        {
            pontos.push_back(p);
        }
    }
    void percorrer() const
    {
        for(int i = 0; i < getTamanho(); i++)
        {
            pontos[i]->imprimir();
        }
    }

}; //1.9 pontos

class LinhaOrtogonal : public Ponto
{
private:
   int xf;
   int yf;
   VetPontos vPontos;

public:
    LinhaOrtogonal(const int x1 = 0, const int y1 = 0, const int xf1 = 0, const int yf1 = 0):
    Ponto(x1, y1),
    xf(xf1),
    yf(yf1),
    vPontos()
    {
        if(x1 == xf1)
        {
            Ponto* p = nullptr;

            int fator = ((y1 - yf1) > 0) ? 1 : -1;
             
            int tamanho = fabs(y1 - yf1);

            for(int i = 0; i < tamanho; i++)
            {
                p = new Ponto(x1, y1 + (i * fator));

                vPontos.incluir(p);
            
                p = nullptr;
            }

            ok = true;
        }
        else if (y1 == yf1)
        {
            Ponto* p = nullptr;

            int fator = ((x1 - xf1) > 0) ? 1 : -1;
             
            int tamanho = fabs(x1 - xf1);

            for(int i = 0; i < tamanho; i++)
            {
                p = new Ponto(x1 + (i * fator), y1);

                vPontos.incluir(p);
            
                p = nullptr;
            }
            ok = true;
        }
        else
        {
            ok = false;
        }
        
    }
    ~LinhaOrtogonal()
    {

    }
    void imprimir() const
    {
        if(ok && (vPontos.getTamanho() > 0))
        {
            vPontos.percorrer();
        }    
    }
}; //2.0 pontos

class Retangulo : public Ponto
{
private:
    VetPontos vet;
    int A;
    int L;

public:
    Retangulo(const int x1 = 0, const int y1 = 0, const int alt = 0, const int lar = 0):
    Ponto(x1, y1),
    A(alt),
    L(lar)
    {
 		   LinhaOrtogonal* p = NULL;

		   p = new LinhaOrtogonal(x, y, x, y+A);
		   if ( false == p->getOk() ) { ok = false; return; }
		   vet.incluir(p);

		   p = new LinhaOrtogonal(x, y, x+L, y);
           if ( false == p->getOk() ) { ok = false; return; }
           vet.incluir(p);

		   p = new LinhaOrtogonal(x+L, y, x+L, y+A);
           if ( false == p->getOk() ) { ok = false; return; }
           vet.incluir(p);

		   p = new LinhaOrtogonal(x, y+A, x+L, y+A);
           if ( false == p->getOk() ) { ok = false; return; }
           vet.incluir(p);


    }
    virtual ~Retangulo()
    {

    }
    void imprimir() const
    {
        if(ok)
        {
            vet.percorrer();
        }
    }
}; // 1.6 pontos

class Principal
{
private:
    LinhaOrtogonal* linha_nao_ortogonal;
    Retangulo* R1;
	Ponto* p_ponto1;
	Ponto* p_ponto2;

    VetPontos conjunto;

    static Principal* principal;

    Principal():
    conjunto(),
    p_ponto1(new Ponto(9,9)),
    p_ponto2(new Ponto(12,12)),
    linha_nao_ortogonal( new LinhaOrtogonal(17,18,19,20)),
    R1(new Retangulo(0, 0, 4, 4))
    {
        if (p_ponto1->getOk())
        {
            conjunto.incluir(static_cast<Ponto*>(p_ponto1));
        }
        else
        {
            delete p_ponto1;
        }

        if (p_ponto2->getOk())
        {
            conjunto.incluir(static_cast<Ponto*>(p_ponto2));
        }
        else
        {
            delete p_ponto2;
        }

        if (linha_nao_ortogonal->getOk())
        {
            conjunto.incluir(static_cast<Ponto*>(linha_nao_ortogonal));
        }
        else
        {
            delete linha_nao_ortogonal;
        }

        if (R1->getOk())
        {
            conjunto.incluir(static_cast<Ponto*>(R1));
        }
        else
        {
            delete R1;
        }

		executar();
    }

public:
    
    static Principal* getPrincipal();

    ~Principal()
    {

    }
    void executar()
    {
        conjunto.percorrer();

        if ( (p_ponto1->operator==(*p_ponto2)) && p_ponto2->operator==(*p_ponto1) )
        {
            cout << "Pontos coincidentes!" << endl;
        }
    }

}; //1.5 pontos

Principal* Principal::principal(nullptr);

Principal* Principal::getPrincipal()
    {
        if(principal == nullptr)
        {
            return new Principal;
        }
        else
        {
            return principal;
        }
    }

int main ()
{
    Principal* novaPrincipal = nullptr;
    novaPrincipal = Principal::getPrincipal();

    if (novaPrincipal) { delete novaPrincipal; }

    return 0;
}

// nota final: 8.5