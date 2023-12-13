
// Exame recuperacao TecProg S73 1 Sem 2021 - 25 de setembro de 2021 - DAINF / UTFFPR - Campus Curitiba - Prof J. M. Simão.

#include <string>
#include <iostream>
using namespace std;

class Animal
{
protected:
    string  nome;
	Animal* pAnimal;

public:
	Animal(const string n = "") :
	    nome    ( n ),
	    pAnimal ( NULL )
    {
    }

	virtual ~Animal()
	{
	    nome = "";
	    pAnimal = NULL;
	}

	const string getNome() const { return nome;     }

	void setAnimal(Animal* pA)   { pAnimal = pA;    }

	virtual void atacar () const = 0;
	virtual const bool informar () const = 0;

};

// *************

class Reptil : public Animal
{
protected:
    short int temp;

public:
	Reptil(const string n = "", const short int t = 0) :
	    Animal  ( n ),
	    temp    ( t )
    {
    }
	virtual ~Reptil()
	{
	    temp = -1;
    }

	virtual void atacar () const = 0;
	virtual const bool informar () const = 0;
};

class Mamifero : public Animal
{
protected:
    static int cont;

public:
	Mamifero(const string n = "") :
	    Animal(n)
	{
	    cont++;
    }

	virtual ~Mamifero()
	{
	    cont--;
    }

	virtual void atacar () const = 0;
	virtual const bool informar () const = 0;
};

int Mamifero::cont(0);

// *************

class Cobra	: public Reptil
{
protected:
    bool veneno;

public:

	Cobra(const string n = "", const short int t = 0, const bool v = false) :
	    Reptil  (n, t),
	    veneno  (v)
    {
    }

	~Cobra()
	{
	    veneno = false;
	}

	void atacar() const
	{
	    if (pAnimal)
        {
            if (    (  true == veneno )                  &&
                    (  ( temp >= 0 ) && ( temp <= 30 ) ) &&
                    (  pAnimal->informar() ) )
            {
                cout    << " A cobra " << nome << " com temperatura " << temp
                        << " atacou a presa " << pAnimal->getNome() << "."
                        << endl;
            }
            else
            {
                cout    << " A cobra " << nome << " com temperatura " << temp
                        << " NAO atacou a presa " << pAnimal->getNome() << "."
                        << endl;
            }
        }
        else
        {
            cout << "Ponteiro nulo em cobra." << endl;
        }
        cout << endl;
	}

	const bool informar() const
	{
	    return veneno;
    }
};


// *************


class Tigre : public Mamifero
{
protected:
    bool fraco;

public:
	Tigre(const string n = "", const bool f = false) :
	    Mamifero( n ),
	    fraco   ( f )
    {
    }

	~Tigre()
	{
	    fraco = false;
	}

	void atacar () const
	{
	    if (pAnimal)
        {
            if (    (  ! fraco ) &&
                    (  ! pAnimal->informar() ) )
            {
                cout    << " O tigre " << nome << " atacou a presa "
                        << pAnimal->getNome() << "." << endl;
            }
            else
            {
                cout    << " O tigre " << nome << " NAO atacou a presa "
                        << pAnimal->getNome() << "." << endl;
            }
        }
        else
        {
            cout << "Ponteiro nulo em tigre." << endl;
        }
        cout << endl;
	}

	const bool informar() const
	{
	    return fraco;
    }
};


class Zebra : public Mamifero
{
protected:
    short int filhotes;

public:
	Zebra(const string n =  "", const short int nf = 0 ) :
	    Mamifero ( n ),
	    filhotes ( nf )
    {
    }

	~Zebra()
	{
	    filhotes = -1;
	}

	void atacar() const
	{
       cout << " A zebra " << nome << " não ataca nenhum dos outros " << cont << " mamíferos." << endl;
       cout << endl;
	}

	const bool informar() const
	{
	    if (filhotes > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

// *************

class Habitat
{
private:
    Cobra C1, C2;
    Tigre T1, T2;
    Zebra Z1, Z2;

public:
	Habitat():
	    C1 ("Cobra 1", 15, true) ,
	    C2 ("Cobra 2", 31, false) ,
	    T1 ("Tigre 1", false) ,
	    T2 ("Tigre 2", true) ,
	    Z1 ("Zebra 1", 0) ,
	    Z2 ("Zebra 2", 1)
	{
	    C1.setAnimal( static_cast<Animal*>(&T2) );
	    C2.setAnimal( static_cast<Animal*>(&T1) );

	    T1.setAnimal( static_cast<Animal*>(&Z1) );
	    T2.setAnimal( static_cast<Animal*>(&Z2) );

		executar();		// chama o menu quando um objeto de Principal é criado;
	}

	~Habitat()
	{
	}

	void executar()	const // lista os elementos da lista através do iterator;
	{
        C1.atacar();
        C2.atacar();

        T1.atacar();
        T2.atacar();

        Z1.atacar();
        Z2.atacar();
	}
};


int main()
{
	Habitat H;

    return 0;
}

