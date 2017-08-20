#include "Headers/All.h"

int main() {

    void * Tads[2] = {NULL, NULL}; //Tads[0] é da Arvore | Tads[1] é da Lista

    do {
        showMenu(0);
    } while ( mainExecute ( validadeCommand(1, 5), Tads) );

    return 0;

}
