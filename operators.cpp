#include <iostream>

class Operadores {
private:
    int num1;
    int num2;

public:
    // Construtor
    Operadores(int a, int b) : num1(a), num2(b) {}

    // Sobrecarga de operadores
    Operadores operator+(const Operadores& other) const {
        return Operadores(num1 + other.num1, num2 + other.num2);
    }

    Operadores operator-(const Operadores& other) const {
        return Operadores(num1 - other.num1, num2 - other.num2);
    }

    Operadores operator*(const Operadores& other) const {
        return Operadores(num1 * other.num1, num2 * other.num2);
    }

    Operadores operator/(const Operadores& other) const {
        if (other.num1 != 0 && other.num2 != 0) {
            return Operadores(num1 / other.num1, num2 / other.num2);
        } else {
            std::cerr << "Erro: Divisao por zero!" << std::endl;
            return Operadores(0, 0);
        }
    }

    // M�todos para imprimir os valores
    void imprimir() const {
        std::cout << "Numero 1: " << num1 << ", Numero 2: " << num2 << std::endl;
    }
};

int main() {
    // Exemplo de uso da classe Operadores com sobrecarga de operadores
    Operadores operacoes1(10, 5);
    Operadores operacoes2(3, 2);

    Operadores resultadoSoma = operacoes1 + operacoes2;
    std::cout << "Soma: ";
    resultadoSoma.imprimir();

    Operadores resultadoSubtracao = operacoes1 - operacoes2;
    std::cout << "Subtracao: ";
    resultadoSubtracao.imprimir();

    Operadores resultadoMultiplicacao = operacoes1 * operacoes2;
    std::cout << "Multiplicacao: ";
    resultadoMultiplicacao.imprimir();

    Operadores resultadoDivisao = operacoes1 / operacoes2;
    std::cout << "Divisao: ";
    resultadoDivisao.imprimir();

    return 0;
}

