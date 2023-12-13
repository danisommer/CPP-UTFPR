
#include <iostream>
#include <string>
#include <set>
using namespace std;

namespace Automoveis
{
    class Veiculo
    {
        protected:
            string nome;
            float x, y;

        public:

            Veiculo(const string n = "", const float x1 = 0.0, const float y1 = 0.0):
            nome (n),
            x (x1),
            y (y1)
            {
            }

            virtual ~Veiculo()
            {
            }

            virtual void atualizar() = 0;

            void mostrar()
            {
                atualizar();
                cout << nome << " " << x << " " <<  y << endl;
            }

            //string& getNome() { return nome; }

            const int getX() const { return x; }
            const int getY() const { return y; }
    };

    class Carro : public Veiculo
    {
        protected:
            int multas;
            float fator;

        public:
            Carro(const string n = "", const float x1 = 0.0, const float y1 = 0.0, const int mult = 0, const float fat = 1.0):
            Veiculo(n, x1, y1),
            multas(mult),
            fator(fat)
            {
            }

            virtual ~Carro()
            {
            }

            void operator+=(const float param)
            {
                x+= param;
                y+= param;
            }

            virtual void atualizar()
            {
                operator+=(fator);

                //(*this)+= fator;
                //*this+= fator;
            }
    };

    class Viatura : public Carro
    {
        private:
            bool sirene;

        public:
            Viatura(const string n = "", const float x1 = 0.0, const float y1 = 0.0, const int mult = 0, const float fat = 1.0, const bool sir = true) :
            Carro(n, x1, y1, mult, fat),
            sirene(sir)
            {
            }

            ~Viatura()
            {
            }

            void operator++()
            {
                operator+=(2*fator);
                //x+= (2*fator);
                //y+= (2*fator);
            }

            void atualizar()
            {
                operator++();
            }
    };
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
               // Atençao com a deleção de objetos estáticos - não é todo compilador que aceita...
               /* Veiculo* paux = NULL;
                i = conjunto.rbegin();
                while (i != conjunto.rend())
                {
                    paux = *i;
                    if (paux != NULL)
                    {
                        delete paux;
                        paux = NULL;
                    }
                    i++;
                } */

                excluir();
            }

            void incluir(Veiculo* pv)
            {

                if (pv != NULL)
                {
                    conjunto.insert(pv);
                }
                else
                {
                    cerr << "Erro - apontamento nulo no parâmetro do método incluir." << endl;
                }

            }

            void excluir()
            {
                conjunto.clear();
            }

            void percorrer()
            {
                i = conjunto.rbegin();

                while (i != conjunto.rend())
                {
                    (*i)->mostrar();
                    i++;
                }
                cout << endl;


                 /* for ( int i = (int)conjunto.size()-1; i > 0; i--)
                {
                    (conjunto[i])->mostrar();  // NÃO HÁ COLCEHTES EM set.
                } */



            }
    };
    // Se classe frota for feita com outro componente, lembrar que supostamente teria
    // que programar a funcionalidade do set de não permitir elemento repetido...

    class Simulador
    {
        private:
            Carro      c1;
            Carro      c2;
            Viatura    v1;
            Frota      f;
        public:

        Simulador() :
            c1("cidadão", 2, 2, 0, 0.5),
            c2("meliante", 50, 50, 500, 1),
            v1("policial", 0, 0, -1, 3, true),
            f()
        {
            f.incluir(static_cast<Veiculo*>(&c1));
            f.incluir(static_cast<Veiculo*>(&c2));
            f.incluir(static_cast<Veiculo*>(&v1));

            executar();
        }

        ~Simulador()
        {
        }

        void executar()
        {
            for (int i = 0; i < 100; i++)
            {
                f.percorrer();

                if (
                    (c2.getX() <= v1.getX()) &&
                    (c2.getY() <= v1.getY())
                   )
                {
                    cout << endl << "Meliante está preso!" << endl;

                    //cout << "O nome da viatura é:" << v1.getNome() << endl;
                    return;
                }
            }

            cout << endl << "Meliante escapou!" << endl;
            cout << endl;


        }
    };

}

using namespace Gerenciadores;

int main()
{
    Simulador simulador;

    return 0;
}




