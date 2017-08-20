#ifndef TIME_INCLUDED
#define TIME_INCLUDED

//Dependências
#include <time.h>
#include <stdio.h>

//Calcula o Tempo Passado op = 1, retorna o tempo em segundos desde a última vez que a função foi gerada no modo 0.
double TimePass(int op) {
    static clock_t timeInput;

    if ( op ) {
        return (double) (clock() - timeInput)/CLOCKS_PER_SEC;
    } else {
        timeInput = clock();
        return 0;
    }
}

void showTime(double numberInput) {
    printf("\n\n***********Essa operação levou: %f segundos**********\n\n", numberInput);
}
#endif
