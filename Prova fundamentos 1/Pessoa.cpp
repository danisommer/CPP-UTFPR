#include "Pessoa.hpp"
#include <iostream>

using namespace std;

Pessoa::Pessoa(int dia, int mes, int ano, string n) : nome(), nasc(), idade()
{
    Inicializa(dia, mes, ano, n);
}

Pessoa::Pessoa()
{
}

Pessoa::~Pessoa() = default;

void Pessoa::Inicializa(int dia, int mes, int ano, string n)
{
    nasc.ano = ano;
    nasc.mes = mes;
    nasc.dia = dia;
    nome = n;
}

int Pessoa::getIdade() {

    return idade;
}

string Pessoa::getNome()
{
    return nome;
}

void Pessoa::calcIdade(Data atual)
{
    idade = atual.ano - nasc.ano;

    if (nasc.mes > atual.mes) {
        idade--;
    }
    else if (nasc.mes == atual.mes) {
        if (nasc.dia > atual.dia) {
            idade--;
        }
    }
}
