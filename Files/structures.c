#include <stdio.h>

struct box{
    char *product[5];
};



int main(){

    struct box almacen[5];

    almacen[0].product[0]="Amadeus";
    almacen[1].product[1]="Yi yi";
    almacen[2].product[2]="Despicable 3";
    almacen[3].product[3]="Resident Evil";
    almacen[4].product[4]="Kimetsu no Yaiba";

    int i=0;
    while(i<5){
        printf("Nombre de película: %s\n",(*(almacen+i)).product[i]);
        i=i+1;
    }
      
    return 0;
}
