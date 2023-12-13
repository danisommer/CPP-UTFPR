#include "Principal.hpp"

Principal::Principal() = default;

void Principal::Executar()
{
	Data dataAtual = {21, 9, 2023};

	Einstein.Inicializa(14, 3, 1879, "Einstein");
	Newton.Inicializa(4, 1, 1643, "Newton");

	Einstein.calcIdade(dataAtual);
	Newton.calcIdade(dataAtual);

	cout << Einstein.getNome() << " teria " << Einstein.getIdade() << " anos " << endl;
	cout << Newton.getNome() << " teria " << Newton.getIdade() << " anos " << endl;
}
