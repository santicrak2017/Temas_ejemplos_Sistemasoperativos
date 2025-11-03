#include "sock-lib.h"
#include <stdint.h>

int main (){

int sock;
int sockdup;
int32_t entero;

	sock=abrir_conexion(8000,10,1);
	if(sock ==  -1)
	{

	fprintf(stderr, "fallo la creacion de la conexion");
	exit(-1);

	}
	while(1){

	sockdup = aceptar_pedidos(sock,1);

	read(sockdup,&entero,sizeof(int32_t));
	
	fprintf(stderr, "debug  rx=%x\n",entero);

	close (sockdup);

	}

close (sock);




}
