#include <vector>
#include <iostream>
using namespace std;

#include <windows.h>

// Esta funcao não precisaria escrever na prova, bastaria usar: gotoxy ( x, y );
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();

	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


class Forma
{
protected:
	bool agregado;

public:

	Forma(const bool ag = false):
	agregado(ag)
	{
	}

	virtual ~Forma()
	{
	}

	void setAgregado(const bool ag) { agregado = ag; }

	virtual void desenhar() const = 0;		// método virtual puro, portanto, classe abstrata;
};

class Ponto : public Forma
{
private:
    int x, y;

public:
	Ponto(const bool ag = false, const int px = -1, const int py = -1) :
    Forma(ag),
    x(px),
    y(py)
	{
	}

	~Ponto()
	{
	}

	void setX(const int px)	{	x = px;		}
	void setY(const int py)	{	y = py;		}

	void  desenhar() const
	{
		gotoxy(x, y);
        cout << ".";
	}
};

// classe Reta, derivada de Forma;
class Reta : public Forma
{
private:
	const int comprimento;
	const int y;		// Atributo constante;
	static int x;		// Atributo estático;
	Ponto *pontos;		// Vetor de objetos de Ponto por meio de alocação dinâmica;

public:
	Reta(const int comp = 10) :
    Forma(),
    comprimento(comp),
    y(5),
    pontos(NULL)
	{
        if ( comprimento > 0 )
        {
			pontos = new Ponto [ comprimento ];
		    for (int i = 0; i < comprimento; i++)
		    {
			    pontos[ i ].setX( x + i );
			    pontos[ i ].setY( y + (2 * i) );
			    pontos[ i ].setAgregado( true );
	        }
	        x += 2;
         }
         else
         {
            cout << "Comprimento não pode ser menor ou igual a zero."  << endl;
         }
	}

	~Reta()
	{
        if ( NULL != pontos )
        {
		   delete [] pontos;
		   pontos = NULL;
        }
	}

	void desenhar() const
	{
		for (int i = 0; i < comprimento; i++)
		{
			pontos[ i ].desenhar();
		}
	}
};

int Reta::x = 0;	// inicialização do atributo estático x da classe Reta;
// int Reta::x(0);


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

	void incluir(const Forma* pforma)
	{
        if (pforma)
        {
		   v.push_back( pforma );
        }
        else
        {
           cout << "Ponteiro nulo." << endl;
        }
	}

    const int getTamanho() const
	{
	    return (int)v.size();
	}

	const Forma* operator[](const int indice) const
	{
	    if ( ( indice >= 0 ) && ( indice < getTamanho() ) )
        {
            return v[indice];
            //return v.at(indice);
        }
        else
        {
            return NULL;
        }
	}

};


class Editor
{
private:
	Vetor vetor;
    Ponto p1, p2;
	Reta r1, r2, r3, r4, r5;

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
	    vetor.incluir(static_cast<Forma*>(&p1));
	    vetor.incluir(static_cast<Forma*>(&p2));
	    vetor.incluir(static_cast<Forma*>(&r1));
	    vetor.incluir(static_cast<Forma*>(&r2));
	    vetor.incluir(static_cast<Forma*>(&r3));
	    vetor.incluir(static_cast<Forma*>(&r4));
	    vetor.incluir(static_cast<Forma*>(&r5));
	}

	~Editor()
	{

	}

	void percorrer() const
	{
		int tam = vetor.getTamanho();

		int i = 0;

		while ( i < tam )
		{
            if (vetor[i])
            {
                (vetor[i])->desenhar();   // vetor.operator[](i)->desenhar();

            }
            else
            {
                cout << "Posição nula no vetor!" << endl;
            }

			i++;
		}
	}

};

int main()
{
    Editor editor;

    editor.percorrer();

    cout << endl << endl ;

    return 0;
}

