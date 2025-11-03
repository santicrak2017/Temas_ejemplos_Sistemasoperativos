#include "sock-lib.h"
#include <stdint.h>

// Definir las variables 
#define SYMBOL 0xAABBCCDD

int main(){

int sock;
int32_t entero= SYMBOL;
int r;
//conectarse 
sock=conectar ("localhost",8000,1);

//write

r=write(sock, &entero, sizeof(int32_t));
if(r== -1){
fprintf(stderr,"error al intentar escribir");
	
}
// cerrar 

close(sock);







return 0;
}
