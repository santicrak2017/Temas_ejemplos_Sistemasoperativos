#include "sock-lib.h"
#include <string.h>

#define BUFFER_SIZE 4096

int main() {
    int sock_escucha, sock_cliente;
    char buffer[BUFFER_SIZE];
    int bytes_recibidos;
    char respuesta[BUFFER_SIZE];
    int num1, num2, resultado;
    char operacion;
    
    fprintf(stderr, "=== CALCULADORA SERVIDOR ===\n");
    
    
    // Abrir conexión en puerto 8000
    sock_escucha = abrir_conexion(8000, 10, 1);
    
    if (sock_escucha == -1) {
        fprintf(stderr, "Error al abrir conexión\n");
        return 1;
    }
    
    fprintf(stderr, "Esperando cliente...\n");
    
    // Aceptar cliente
    sock_cliente = aceptar_pedidos(sock_escucha, 1);
    
    if (sock_cliente == -1) {
        fprintf(stderr, "Error al aceptar cliente\n");
        close(sock_escucha);
        return 1;
    }
    
    // Recibir operación del cliente
    // Formato esperado: "5+3" o "10*2" o "20-5" o "15/3"
    bytes_recibidos = read(sock_cliente, buffer, BUFFER_SIZE);
    
    if (bytes_recibidos == -1) {
        fprintf(stderr, "Error al recibir datos\n");
        close(sock_cliente);
        close(sock_escucha);
        return 1;
    }
    
    buffer[bytes_recibidos] = '\0';
    fprintf(stderr, "Operación recibida: %s\n", buffer);
    
    // Procesar la operación
    // sscanf extrae los números y la operación del string
    if (sscanf(buffer, "%d%c%d", &num1, &operacion, &num2) == 3) {
        // Calcular según la operación
        switch(operacion) {
            case '+':
                resultado = num1 + num2;
                sprintf(respuesta, "%d + %d = %d", num1, num2, resultado);
                break;
            case '-':
                resultado = num1 - num2;
                sprintf(respuesta, "%d - %d = %d", num1, num2, resultado);
                break;
            case '*':
                resultado = num1 * num2;
                sprintf(respuesta, "%d * %d = %d", num1, num2, resultado);
                break;
            case '/':
                if (num2 != 0) {
                    resultado = num1 / num2;
                    sprintf(respuesta, "%d / %d = %d", num1, num2, resultado);
                } else {
                    sprintf(respuesta, "Error: División por cero");
                }
                break;
            default:
                sprintf(respuesta, "Error: Operación no válida");
        }
    } else {
        sprintf(respuesta, "Error: Formato incorrecto. Use: num1+num2");
    }
    
    // Enviar resultado al cliente
    write(sock_cliente, respuesta, strlen(respuesta));
    fprintf(stderr, "Resultado enviado: %s\n", respuesta);
    
    // Cerrar conexiones
    close(sock_cliente);
    close(sock_escucha);
    
    fprintf(stderr, "=== SERVIDOR FINALIZADO ===\n");
    
    return 0;
}  
//
