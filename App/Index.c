#include "Headers/All.h"

//Assinaturas de Funções

void debug(); //FUNÇÃO PARA DEBUG

int main() {

    debug();
    return 0;

}

//Funções Complementares

void debug() {
    
    do {
        showMenu(0);
    }while ( mainExecute(validadeCommand(1, 5)) );
}
