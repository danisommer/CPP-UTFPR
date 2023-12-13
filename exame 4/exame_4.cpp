#include <iostream>
using namespace std;

class Animal
{
protected:
    string nome;
    Animal *pAnimal;

public:
    Animal(const string n = ""):
    nome(n),
    pAnimal(nullptr)
    {

    }

    virtual ~Animal()
    {
        nome = "";
        pAnimal = nullptr;
    }

    const string getNome() const { return nome; }

    void setAnimal(Animal* pA) { if(pA) pAnimal = pA; }

    virtual void atacar() const = 0;
    
    virtual const bool informar() const = 0;   
}; //2.0 pontos

class Reptil : public Animal
{
protected:
    short int temp;

public:
    Reptil(const string n = "", const short int t = 0):
    temp(t),
    Animal(n)
    {
    }
    ~Reptil()
    {
        temp = -1;
    }

    virtual void atacar() const = 0;
    virtual const bool informar() const = 0;

}; //1.0 ponto

class Mamifero : public Animal
{
protected:
    static int cont;

public:
    Mamifero(const string n = ""):
    Animal(n)
    {
        cont++;
    }

    ~Mamifero()
    {
          cont--;
    }

    virtual void atacar() const = 0;
    virtual const bool informar() const = 0;

}; //1.0 ponto

int Mamifero::cont(0);

class Cobra : public Reptil
{
protected:
bool veneno;

public:
    Cobra(const string n = "", const short int t = 0, const bool v = false):
    Reptil(n, t),
    veneno(v)
    {
    }
    ~Cobra()
    {
         veneno = false;
    }

    void atacar() const 
    {
        if(pAnimal)
        {
            if((temp > 0 && temp < 30) && veneno && pAnimal->informar())
            {
                cout << getNome() << " atacou o " << pAnimal->getNome() << endl;
            }
            else
            {
                cout << getNome() << " não atacou o " << pAnimal->getNome() << endl;
            }
        }
    }
    const bool informar() const
    {
        return veneno;
    }

}; //1.5

class Tigre : public Mamifero
{
protected:
bool fraco;

public:
    Tigre(const string n = "", const bool f = false):
    Mamifero(n),
    fraco(f)
    {

    }
    ~Tigre()
    {
        fraco = false;
    }

    void atacar() const
    {
        if (pAnimal)
        {
            if(!fraco && pAnimal->informar())
            {
                cout << getNome() << " atacou o " << pAnimal->getNome() << endl;
            }
            else
            {
                cout << getNome() << " não atacou o " << pAnimal->getNome() << endl;

            }
        }

    }
    const bool informar() const
    {
        return fraco;
    }
}; //1.0 ponto

class Zebra : public Mamifero
{
protected:
short int filhotes;

public:
    Zebra(const string n = "", const short int nf = 0):
    Mamifero(n),
    filhotes(nf)
    {
    }

    ~Zebra()
    {
    }

    void atacar() const
    {
       cout << " A zebra " << nome << " n�o ataca nenhum dos outros " << cont << " mam�feros." << endl;
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
}; //0.8 pontos


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
        executar();
    }
    ~Habitat()
    {

    }
    void executar() const
    {
        C1.atacar();
        C2.atacar();

        T1.atacar();
        T2.atacar();

        Z1.atacar();
        Z2.atacar();
    }


}; // 1.0 ponto

int main ()
{
    Habitat H;
    return 0;
}

//total: 8.3 pontos