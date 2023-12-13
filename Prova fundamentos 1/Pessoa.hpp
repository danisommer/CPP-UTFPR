#pragma once
#include <string>

using namespace std;

struct Data {

	int dia;
	int mes;
	int ano;

};

class Pessoa
{
private:
	Data nasc;
	int idade;
	string nome;
public:
	Pessoa(int dia, int mes, int ano, string n);
	Pessoa();
	~Pessoa();
	void Inicializa(int dia, int mes, int ano, string n);
	int getIdade();
	string getNome();
	void calcIdade(Data atual);
};

