#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

class VectorClass {
private:
    std::vector<int*> ponteiros;

public:
    void alocar(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.push_back(novoInteiro);
    }

    void desalocar() {
        for (int* ptr : ponteiros) {
            delete ptr;
        }
        ponteiros.clear();
    }

    void inserir(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.push_back(novoInteiro);
    }

    void remover() {
        if (!ponteiros.empty()) {
            delete ponteiros.back();
            ponteiros.pop_back();
        }
    }

    void limpar() {
        ponteiros.clear();
    }

    void percorrer() {
        for (int* ptr : ponteiros) {
            std::cout << *ptr << " ";
        }
        std::cout << std::endl;
    }
};

class ListClass {
private:
    std::list<int*> ponteiros;

public:
    void alocar(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.push_back(novoInteiro);
    }

    void desalocar() {
        for (int* ptr : ponteiros) {
            delete ptr;
        }
        ponteiros.clear();
    }

    void inserir(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.push_back(novoInteiro);
    }

    void remover() {
        if (!ponteiros.empty()) {
            delete ponteiros.back();
            ponteiros.pop_back();
        }
    }

    void limpar() {
        ponteiros.clear();
    }

    void percorrer() {
        for (int* ptr : ponteiros) {
            std::cout << *ptr << " ";
        }
        std::cout << std::endl;
    }
};

class SetClass {
private:
    std::set<int*> ponteiros;

public:
    void alocar(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.insert(novoInteiro);
    }

    void desalocar() {
        for (int* ptr : ponteiros) {
            delete ptr;
        }
        ponteiros.clear();
    }

    void inserir(int valor) {
        int* novoInteiro = new int(valor);
        ponteiros.insert(novoInteiro);
    }

    void remover(int valor) {
        auto it = ponteiros.begin();
        while (it != ponteiros.end()) {
            if (**it == valor) {
                delete *it;
                it = ponteiros.erase(it);
            } else {
                ++it;
            }
        }
    }

    void limpar() {
        ponteiros.clear();
    }

    void percorrer() {
        for (int* ptr : ponteiros) {
            std::cout << *ptr << " ";
        }
        std::cout << std::endl;
    }
};

class MapClass {
private:
    std::map<int, int*> mapa;

public:
    void alocar(int chave, int valor) {
        int* novoInteiro = new int(valor);
        mapa[chave] = novoInteiro;
    }

    void desalocar() {
        for (auto& par : mapa) {
            delete par.second;
        }
        mapa.clear();
    }

    void inserir(int chave, int valor) {
        int* novoInteiro = new int(valor);
        mapa[chave] = novoInteiro;
    }

    void remover(int chave) {
        auto it = mapa.find(chave);
        if (it != mapa.end()) {
            delete it->second;
            mapa.erase(it);
        }
    }

    void limpar() {
        mapa.clear();
    }

    void percorrer() {
        for (const auto& par : mapa) {
            std::cout << "Chave: " << par.first << ", Valor: " << *(par.second) << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Exemplo usando a classe com std::vector
    VectorClass vectorInstance;
    vectorInstance.alocar(10);
    vectorInstance.inserir(20);
    vectorInstance.inserir(30);
    vectorInstance.percorrer();
    vectorInstance.remover();
    vectorInstance.inserir(40);
    vectorInstance.percorrer();
    vectorInstance.limpar();
    vectorInstance.percorrer();
    vectorInstance.desalocar();

    // Exemplo usando a classe com std::list
    ListClass listInstance;
    listInstance.alocar(10);
    listInstance.inserir(20);
    listInstance.inserir(30);
    listInstance.percorrer();
    listInstance.remover();
    listInstance.inserir(40);
    listInstance.percorrer();
    listInstance.limpar();
    listInstance.percorrer();
    listInstance.desalocar();

    // Exemplo usando a classe com std::set
    SetClass setInstance;
    setInstance.alocar(10);
    setInstance.inserir(20);
    setInstance.inserir(30);
    setInstance.percorrer();
    setInstance.remover(20);
    setInstance.inserir(40);
    setInstance.percorrer();
    setInstance.limpar();
    setInstance.percorrer();
    setInstance.desalocar();

    // Exemplo usando a classe com std::map
    MapClass mapInstance;
    mapInstance.alocar(1, 10);
    mapInstance.inserir(2, 20);
    mapInstance.inserir(3, 30);
    mapInstance.percorrer();
    mapInstance.remover(2);
    mapInstance.inserir(4, 40);
    mapInstance.percorrer();
    mapInstance.limpar();
    mapInstance.percorrer();
    mapInstance.desalocar();

    return 0;
}
