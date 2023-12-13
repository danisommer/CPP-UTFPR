#include <iostream>
#include <cstring>
#define ANO_ATUAL 2023

using namespace std;

class Equipamento {
private:
    char nome[150];
    int ano_fabricacao, antiguidade;
public:
    Equipamento() : nome(), ano_fabricacao(0), antiguidade(-1) {

    }
    ~Equipamento()= default;
    void descobreAntiguidade(int ano_atual){
        antiguidade = ano_atual - ano_fabricacao;
    }
    void setNome(char *n){
        strcpy(nome, n);
    }
    void setAnoFab(int ano){
        ano_fabricacao = ano;
    }
    char *getNome(){
        return nome;
    }
    int getAntiguidade() const{
        return antiguidade;
    }
    Equipamento *prox;
    Equipamento *ant;
};

class Lista_Equipamentos {
private:
    Equipamento *lista;
    int nEquipamentos;
    int contador;
public:
    Lista_Equipamentos(int nE) : lista{}, nEquipamentos(), contador(0) {
        nEquipamentos = nE;
        lista = new Equipamento[nEquipamentos];
    }
    ~Lista_Equipamentos() {
        delete[] lista;
    }
    void incluirEquip(int anoFab, int anoAtual, char *nome){
        if (contador < nEquipamentos){
            Equipamento novoEquip;
            novoEquip.setAnoFab(anoFab);
            novoEquip.descobreAntiguidade(anoAtual);
            novoEquip.setNome(nome);
            lista[contador] = novoEquip;
            contador++;
        }
        else{
            cout << "Lista cheia, nao foi possivel incluir novo equipamento" << endl;
        }
    }
    void listaElementos(){
        int i = 0;
        while (i < contador){
            cout << "O equipamento " << lista[i].getNome() << " tem " << lista[i].getAntiguidade() << " anos de fabricacao." << endl;
            i++;
        }
    }
};

class Principal {
private:
    Lista_Equipamentos lista;
public:
    Principal() : lista(10) {

    }
    ~Principal() = default;
    void executar(){
        lista.incluirEquip(1996, ANO_ATUAL,"robo transportador" );
        lista.incluirEquip(1986, ANO_ATUAL, "prensa leve");
        lista.incluirEquip(2005, ANO_ATUAL, "empilhadeira");
        lista.listaElementos();
    }
};
int main (){

    Principal classePrincipal;
    classePrincipal.executar();
    return 0;
}