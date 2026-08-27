#include <stdio.h>

int main(){

    int *p;
    int numero = 5;

    printf("El numero %d antes de usar el apuntador\n",numero);

    p=&numero;
    *p=10;

    printf("Después de usar el apuntador: %d \n",numero);

    printf("Dirección de memoria: %x \n ",p);
    printf("Valor interno: %d \n",&p);


    return 0;
}

