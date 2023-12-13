#include <iostream>

using namespace std;

int main () {

    int N;
    char piramide = '#', lateral = '*';

    cout << "Digite o tamanho da piramide: ";
    cin >> N;


    for(size_t i = 0; i < N; i++) {

        for(size_t j = N; j > i; j--){
            cout << " ";
        }

        for(size_t k = 0; k < i; k++){
            cout << piramide;
        }

        for(size_t l = 1; l < i; l++){
            cout << piramide;
        }

        if(i <(2 * N/3)){
            for(size_t m = 0; m < i; m++){
                cout << lateral;
            }
        } else {
            for(size_t m = 2 * (N - i) - 1; m != 0; m--){
                cout << lateral;
            }
        }
        cout << "\n";
    }
    return 0;
}
