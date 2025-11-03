#include "sock-lib.h"
#include <string.h>

#define BUFFER_SIZE 4096

int main (){
	int sock;
	char operacion[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	int bytes_recibidos;


	fprintf(stderr, "____ Calculadora cliente___\n" );

	 // Pedir al usuario que ingrese la operación
    printf("Ingrese la operación (ejemplo: 5+3): ");
    fgets(operacion, BUFFER_SIZE, stdin);
    
    // Eliminar el salto de línea que deja fgets
    operacion[strcspn(operacion, "\n")] = '\0';
    
    // Conectar al servidor
    sock = conectar("localhost", 8000, 1);
    
    if (sock == -1) {
        fprintf(stderr, "Error al conectar\n");
        return 1;
    }
    
    // Enviar operación al servidor
    write(sock, operacion, strlen(operacion));
    fprintf(stderr, "Operación enviada: %s\n", operacion);
    
    // Recibir resultado
    bytes_recibidos = read(sock, buffer, BUFFER_SIZE);
    
    if (bytes_recibidos == -1) {
        fprintf(stderr, "Error al recibir resultado\n");
        close(sock);
        return 1;
    }
    
    buffer[bytes_recibidos] = '\0';
    printf("\n*** RESULTADO: %s ***\n", buffer);
    
    // Cerrar socket
    close(sock);
    
    fprintf(stderr, "=== CLIENTE FINALIZADO ===\n");

return 0;

}
