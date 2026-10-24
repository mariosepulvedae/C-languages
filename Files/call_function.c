#include <stdio.h>

enum boolean{True,False};

void see(){
    printf("Bivian\n");  
}

int summ(int a, int b){
    return a+b;
}

int main(){

    int box[3] = {7,8,9};
    
    see();
    printf("La suma es: %i\n",summ(5,4));

    for(int i=0; i<3; i++){
        printf("%i\n",box[i]);
    }   

    printf("true es: %i\n",True);
 
    return 0;
}   