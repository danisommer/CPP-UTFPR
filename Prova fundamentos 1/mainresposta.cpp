
// Resolução feita por GIOVANE LIMAS SALVI - giovanesalvi@alunos.utfpr.edu.br - em 20 de abril de 2023.


#include <iostream>
#include <string.h>

/*
    Correção da Prova 1 disponibilizado em 16/04/2008
    Feito pelo monitor da disciplina de Técnicas de Programção,
    Giovane Limas Salvi
*/

//Criação da Classe Pessoa
class Pessoa {
    protected:
        int dia;
        int mes;
        int ano;
        int idade;
        std::string nome;
    public:
        //construtora padrão sem parâmtro
        Pessoa(){

        }
        //Construtora padrão com parâmetro(polimorfismo)
        Pessoa(int dia, int mes, int ano, const std::string nome){
            this->dia = dia;
            this->mes = mes;
            this->ano = ano;
            this->nome = nome;
            idade = 0;
        }
        //destrutora
        ~Pessoa(){

        }
        //Método que retorna o nome de Pessoa
        const std::string getNome() const{
            return nome;
        }
        //Método que retorna o ano de Pessoa
        const int getAno() const{
            return ano;
        }
        //Método que calcula a idade de Pessoa
        int calcIdade(const int anoAtual){
            if(ano > anoAtual){
                return -1;
            }
            return anoAtual - ano;
        }
};

//Criação da classe Aluno derivada de Pessoa
class Aluno: public Pessoa {
    private:
        int RA;
    public:
        //Construtora
        Aluno(int dia, int mes, int ano, const std::string nome):
            Pessoa(dia, mes, ano, nome)
        {
            RA = -1;
        }
        //Destrutora
        ~Aluno(){

        }
        //Respectivos métodos get e set
        void setRa(int RA){
            this->RA = RA;
        }
        int getRA(){
            return RA;
        }
};

//Criação da classe Elemento Pessoa para auxiliar a construção da ListaPessoa.
class ElementoPessoa {
    private:
        ElementoPessoa* pProx;
        ElementoPessoa* pAnt;
        Pessoa* pPessoa;
    public:
        //Construtora de ElementoPessoa
        ElementoPessoa(){
            //Na construtora de alguma classe, devemos aterrar todos os ponteiros;
            pPessoa = nullptr;
            pProx = nullptr;
            pAnt = nullptr;
        }
        ~ElementoPessoa(){

        }
        //Um método apenas para verificação de ponteiro, apenas para enxugar o código.
        void verificacao(ElementoPessoa* p){
            if(p == nullptr){
                std::cout << "Ponteiro nulo" << std::endl;
                exit(1);
            }
        }
        //Respectivos get e set do atributo pessoa
        void setPessoa(Pessoa* pPessoa){
            if(pPessoa == nullptr){
                std::cout << "Ponteiro nulo" << std::endl;
                exit(1);
            }
            this->pPessoa = pPessoa;
        }
        Pessoa* getPessoa(){
            return pPessoa;
        }
        //Respectivos get set do atributo pProx
        void setProx(ElementoPessoa* pProx){
            verificacao(pProx);
            this->pProx = pProx;
        }
        ElementoPessoa* getProx(){
            return pProx;
        }
        //Respectivos get e set do atributo pAnt
        void setAnt(ElementoPessoa* pAnt){
            verificacao(pAnt);
            this->pAnt = pAnt;
        }
        ElementoPessoa* getAnt(){
            return pAnt;
        }
};

//Criação da classe Lista Pessoa
class ListaPessoa {
    private:
        unsigned int tam;
        ElementoPessoa* pInicio;
        ElementoPessoa* pUltimo;
        ElementoPessoa* pAtual;
    public:
        //Construtora
        ListaPessoa(){
            //Na construtra, devemos aterrar todos os ponteiros
            pInicio = nullptr;
            pUltimo = nullptr;
            pAtual = nullptr;
        }
        //Destrutora da classe ListaPessoa, delete todos os ponteiros existentes
        ~ListaPessoa(){

            //OBS: Se a pessoa em que estamos trabalhando fosse criado dinamicamente no meu
            //objeto principal eu utilizaria o código abaixo para deletar e evitar o
            //vazamento de memória. Entretando, estamos trabalhando apenas o a referência
            //do tipo Pessoa.

            // if(pInicio != nullptr){
            //     ElementoPessoa* pAux = pInicio;
            //     ElementoPessoa* pAux2 = nullptr;
            //     Pessoa* pessoa = nullptr;
            //     while(pAux != nullptr){
            //         pAux2 = pAux->getProx();
            //         pessoa = pAux->getPessoa();
            //         if(pessoa != nullptr){
            //             delete(pessoa);
            //             pessoa = nullptr;
            //         }
            //         pAux = pAux2;
            //     }
            // }
        }
        //Adiciona uma pessoa na lista de pessoa
        void addPessoa(Pessoa* pessoa){
            //Cria uma Pessoa
            ElementoPessoa* elementPessoa = nullptr;
            if(pessoa == nullptr){
                std::cout << "Ponteiro pessoa é nulo" << std::endl;
                exit(1);
            } else {
                elementPessoa = new ElementoPessoa();
                if(elementPessoa == nullptr){
                    std::cout << "Nao foi possivel criar um elemento pessoa" << std::endl;
                    exit(1);
                }
                elementPessoa->setPessoa(pessoa);
            }
            //Se não tiver nenhuma pessoa na lista, eu inicio ela; caso contrário eu adiciono ela no final
            //da lista em questão
            if(pInicio == nullptr){
                pInicio = elementPessoa;
                pUltimo = elementPessoa;
                pAtual = elementPessoa;
            } else {
                //Lista duplamente encadeada
                pAtual->setProx(elementPessoa);
                elementPessoa->setAnt(pAtual);
                pAtual = elementPessoa;
            }
            tam++;
        }
        //Método que imprimi todos os elementos Pessoa da lista de Pessoas
        void imprimir(){
            ElementoPessoa* pAux = pInicio;
            while(pAux != nullptr){
                Pessoa* pessoa = pAux->getPessoa();
                std::cout << pessoa->getNome() << std::endl;
                pAux = pAux->getProx();
            }
        }
        //retorna o tamanho da lista de pessoas;
        const unsigned int getTam() const{
            return tam;
        }
};

//Criação da Classe Principal
class Principal {
    private:
        Pessoa Einstein;
        Pessoa Newton;
        ListaPessoa listPessoa;
        const unsigned int anoAtual;
    public:
        //Construtora da classe Principal
        Principal():
            Einstein(2, 5, 1980, "Einstein"),
            Newton(2, 5, 2005, "Newton"),
            anoAtual(2023),
            listPessoa()
        {
            executar();
        }
        //Destrutora da Clasee Principal
        ~Principal(){

        }
        //Método para adicionar pessoa na lista de pessoa
        void addPessoa(Pessoa* pessoa){
            listPessoa.addPessoa(pessoa);
        }
        //Método para imprimir lista de pessoa
        void imprimir(){
            listPessoa.imprimir();
        }
        //Método para executar meu objeto principal
        void executar(){
            std::cout << Einstein.getNome() << " - idade: " << Einstein.calcIdade(anoAtual) << std::endl;
            std::cout << Newton.getNome() << " - idade: " << Newton.calcIdade(anoAtual) << std::endl;

            addPessoa(&Einstein);
            addPessoa(&Newton);

            imprimir();
        }
};


int main(){
    Principal objPrincipal;
    return 0;
}
