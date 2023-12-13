#include <iostream>

template <typename T>
class ListaElementos {
private:
    class Elemento {
    public:
        T dado;
        Elemento* proximo;
        Elemento* anterior;

        Elemento(const T& valor) : dado(valor), proximo(nullptr), anterior(nullptr) {}
    };

    Elemento* inicio;
    Elemento* fim;

public:
    ListaElementos() : inicio(nullptr), fim(nullptr) {}

    ~ListaElementos() {
        limpar();
    }

    void alocarElemento(Elemento*& elemento, const T& valor) {
        elemento = new Elemento(valor);
    }

    void desalocarElemento(Elemento* elemento) {
        delete elemento;
    }

    void inserirNoInicio(const T& valor) {
        Elemento* novoElemento;
        alocarElemento(novoElemento, valor);

        if (!inicio) {
            inicio = fim = novoElemento;
        } else {
            novoElemento->proximo = inicio;
            inicio->anterior = novoElemento;
            inicio = novoElemento;
        }
    }

    void inserirNoFim(const T& valor) {
        Elemento* novoElemento;
        alocarElemento(novoElemento, valor);

        if (!fim) {
            inicio = fim = novoElemento;
        } else {
            novoElemento->anterior = fim;
            fim->proximo = novoElemento;
            fim = novoElemento;
        }
    }

    void removerNoInicio() {
        if (!inicio) {
            return; // Lista vazia, nada para remover
        }

        Elemento* temp = inicio;

        if (inicio == fim) {
            // �nico elemento na lista
            inicio = fim = nullptr;
        } else {
            inicio = inicio->proximo;
            inicio->anterior = nullptr;
        }

        desalocarElemento(temp);
    }

    void removerNoFim() {
        if (!fim) {
            return; // Lista vazia, nada para remover
        }

        Elemento* temp = fim;

        if (inicio == fim) {
            // �nico elemento na lista
            inicio = fim = nullptr;
        } else {
            fim = fim->anterior;
            fim->proximo = nullptr;
        }

        desalocarElemento(temp);
    }

    void limpar() {
        while (inicio) {
            Elemento* temp = inicio;
            inicio = inicio->proximo;
            desalocarElemento(temp);
        }

        fim = nullptr;
    }

    void percorrer() const {
        Elemento* atual = inicio;
        while (atual) {
            std::cout << atual->dado << " ";
            atual = atual->proximo;
        }
        std::cout << std::endl;
    }
};

int main() {
    ListaElementos<int> lista;

    lista.inserirNoInicio(1);
    lista.inserirNoInicio(2);
    lista.inserirNoFim(3);

    std::cout << "Lista: ";
    lista.percorrer();

    lista.removerNoInicio();
    lista.removerNoFim();

    std::cout << "Lista apos remover no inicio e no fim: ";
    lista.percorrer();

    lista.limpar();

    std::cout << "Lista apos limpar: ";
    lista.percorrer();

    return 0;
}
