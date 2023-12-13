// Data: 27/06/2023 - 1º Semestre de 2023.
// Prof. Dr. Jean M. Simão - DAINF/UTFPR Curitiba-Central.

#include <iostream>
#include <vector>
using namespace std;

#include <windows.h>

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

// (Questão - 1)
class Ponto
{
    protected:
        bool OK;
        int x;
        int y;

    public:

	Ponto(const int _x = -1, const int _y = -1):
        OK(true),
        x(_x),
        y(_y)
    {
    }

    virtual ~Ponto()
    {
    }

    const bool getOK() const { return OK; }

    const int getX() const { return x; }
   // void setX(const int X) { x = X; }

    const int getY() const { return y; }
   // void setY(const int Y) { y = Y; }

    virtual void imprimir() const
    {
       draw(x,y, ".");
    }

    const bool operator==(const Ponto& pp)
    {
         if ( ( pp.getX() == x ) &&
              ( pp.getY() == y ) )
         {
             return true;
         }
         else
         {
             return false;
         }
    }
};

// (Questão - 2)
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
				  pontos[i] = NULL;
                }
			}
			pontos.clear();
        }

		void incluir(Ponto * p)
        {
             if ( p )
             {
                pontos.push_back(p);
             }
             else
             {
                cout << "Endereço nulo não includo!" << endl;
             }
        }

        void percorrer() const
        {
            for(int i = 0; i < getTamanho(); i++)
            {
                pontos[i]->imprimir();
            }
		}

		const int getTamanho() const { return (int) pontos.size(); }
};

// (Questão - 2)
class LinhaOrtogonal : public Ponto
{
    private:
        int xf;
        int yf;
        VetPontos vet;

    public:

	LinhaOrtogonal(const int _x = -1, const int _y = -1, const int _xf = -1, const int _yf = -1)
    :Ponto(_x, _y),
    xf(_xf),
    yf(_yf)
    {

		Ponto* p = NULL;

    	if ( xf == x )
        {
            if (y > yf)
            {
                int temp = y;
                y = yf;
                yf = temp;
            }

			for(int i=y; i<=yf; i++)
            {
				p = new Ponto (x, i);
				vet.incluir(p);
			}
		}
        else
        {
            if (yf == y)

            {
                if (x > xf)
                {
                    int temp = x;
                    x = xf;
                    xf = temp;
                }

                for(int i=x; i<=xf; i++)
                {
    				p = new Ponto (i, y);
				    vet.incluir(p);
			    }
            }
            else
            {
                OK = false;
                cout << "Coordenadas cartesianas inicial e final não permitem reta ortogonal!" << endl;
            }
        }
 	}

 	~LinhaOrtogonal() { }

    void imprimir() const
    {
         if ((OK) && (vet.getTamanho() > 0))
         {
            vet.percorrer();
         }
         else
         {
            cout << "Reta inválida!" << endl;
         }
    }

    //const int getXf() const { return xf; }
    //void setXf(const int X) { xf = X; }

    //const int getYf() const { return yf; }
    //void setYf(const int Y) { yf = Y; }

};

// (Questão - 4)

class Retangulo : public Ponto
{
    private:
        VetPontos vet;
        int A;
        int L;

    public:

    	Retangulo(const int _x = 0, const int _y = 0, const int a = 0, const int l = 0):
    	    Ponto(_x,_y),
    	    A(a),
    	    L(l)
        {
		   LinhaOrtogonal* p = NULL;

		   p = new LinhaOrtogonal(x, y, x, y+A);
		   if ( false == p->getOK() ) { OK = false; return; }
		   vet.incluir(p);

		   p = new LinhaOrtogonal(x, y, x+L, y);
           if ( false == p->getOK() ) { OK = false; return; }
           vet.incluir(p);

		   p = new LinhaOrtogonal(x+L, y, x+L, y+A);
           if ( false == p->getOK() ) { OK = false; return; }
           vet.incluir(p);

		   p = new LinhaOrtogonal(x, y+A, x+L, y+A);
           if ( false == p->getOK() ) { OK = false; return; }
           vet.incluir(p);
	    }

        virtual ~Retangulo() { }

        void imprimir() const
        {
            if (OK)
            {
             vet.percorrer();
            }
        }

        //const int getA() const { return A; }
        //void setA(const int a) { A = a; }
};

// (Questão - 5)

class Principal
{
	private:
		VetPontos conjunto;

		Ponto* p_ponto1;
		Ponto* p_ponto2;

    	//LinhaOrtogonal* p_objeto_linha_horizontal;
        //LinhaOrtogonal* p_objeto_linha_vertical;
        LinhaOrtogonal* p_objeto_linha_nao_ortogonal;

		Retangulo* p_objeto_ret;
        //Retangulo* p_objeto_ret2;
		//Retangulo* p_objeto_ret3;

		static Principal* p_principal;

	private:

		Principal():
        conjunto(),
        p_ponto1(new Ponto(9,9)),
        p_ponto2(new Ponto(12,12)),
        //p_objeto_linha_horizontal(new LinhaOrtogonal(5, 17, 10, 17)),
        //p_objeto_linha_vertical(new LinhaOrtogonal(17, 5, 17, 10)),
        p_objeto_linha_nao_ortogonal( new LinhaOrtogonal(17,18,19,20)),
        p_objeto_ret(new Retangulo(0, 0, 4, 4))
        //p_objeto_ret2(new Retangulo(3, 3, 3, 3)),
        //p_objeto_ret3(new Retangulo(5, 5, 5, 5))
        {
            cin.get();
            system("cls");

            if (p_ponto1->getOK())
            {
                conjunto.incluir(static_cast<Ponto*>(p_ponto1));
            }
            else
            {
                delete p_ponto1;
            }

            if (p_ponto2->getOK())
            {
                conjunto.incluir(static_cast<Ponto*>(p_ponto2));
            }
            else
            {
                delete p_ponto2;
            }

             if (p_objeto_linha_nao_ortogonal->getOK())
            {
                conjunto.incluir(static_cast<Ponto*>(p_objeto_linha_nao_ortogonal));
            }
            else
            {
                delete p_objeto_linha_nao_ortogonal;
            }

             if (p_objeto_ret->getOK())
            {
                conjunto.incluir(static_cast<Ponto*>(p_objeto_ret));
            }
            else
            {
                delete p_objeto_ret;
            }

			executar();
		}

    public:

        ~Principal(){}

		void executar()
        {
             conjunto.percorrer();

             cin.get();
             system("cls");

             if ( ( p_ponto1->operator==(*p_ponto2) )&&
                    p_ponto2->operator==(*p_ponto1) )
             {
                cout << "Pontos coincidentes!" << endl;
             }
             else
             {
                cout << "Pontos não coincidentes!" << endl;
             }
        }

        static Principal* getInstance()
        {
            if ( NULL == p_principal )
            {
                p_principal = new Principal();
            }

            return p_principal;
        }
};

Principal*Principal::p_principal(NULL);

int main()
{
    Principal* pPrincipal = NULL;
	pPrincipal = Principal::getInstance();

    cout << endl << endl << endl << endl;
	cin.get();

	if (pPrincipal) { delete pPrincipal; }

	system("cls");

	return 0;
}
