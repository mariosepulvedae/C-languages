#include <stdio.h>

void mostrar(int numero){
    int seg[4];
    int conversion = 1000;
    int i = 0;

    printf("Valor en display: ");
    while(i < 4){
        seg[i]=(numero/conversion);
        numero = numero - (seg[i]*conversion);
        conversion=conversion/10;
        printf("%i",seg[i]);
        i=i+1;
    }
    printf("\n");

}



int main(){

    mostrar(0xFF);

    return 0;

} 