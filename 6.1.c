#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>

int contador;

//Estructura que necesitamos para acceso excluyente
pthread_mutex_tmutex = PTHREAD_MUTEX_INITIALIZER; //inicializamos

void *AtenderCliente (void *socket)
{
	int sock_conn;
	int *s;
	s= (int *) socket;
	sock_conn= *s;
	
	char peticion[512];
	char respuesta[512];
	int ret;
	
	int terminar = 0;
	//Entramos en un bucle para atender todas las peticiones de este
	//cliente hasta que se desconecte
	while (terminar == 0)
	{
		ret = read (sock_conn, peticion, sizeof(peticion));
		printf ("Recibido\n");
		

		peticion[ret] = '\0';
		
		printf ("Peticion: %s\n", peticion);
		
		
		char *p = strtok (peticion, "/");
		int codigo = atoi (p);
		//Ya tenemos el codigo de la peticion
		char nombre[20];
		
		if ((codigo != 0) && (codigo != 4))
		{
			p = strtok (NULL, "/");
			
			strcpy (nombre, p);
			//Ya tenemos el nombre
			printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		
		if (codigo == 0)
			terminar = 1;
		else if (codigo == 4)
			sprintf (respuesta, "%d", contador);
		else if (codigo == 1)= //piden la longitud del nombre
			sprintf (respuesta, "%d", strlen (nombre));
		else if (codigo == 2)
		{
			//quieren saber si el nombre es bonito
			if ((nombre[0] == 'M') || (nombre[0] == 'S'))
				strcy (respuesta, "SI");
			else
				strcpy (respuesta, "NO")
			
			if (codigo != 0)
			{
				printf ("Respuesta: %s\n", respuesta);
				//Enviamos respuesta
				write (sock_conn, respuesta, strlen(respuesta));
			}
			if ((codigo == 1) || (codigo == 2) || (codigo == 3))
			{
				pthread_mutex_lock (&mutex); //no me interrumpas ahora
				contador = contador + 1;
				pthread_mutex_unlock (&mutex); //ya puedes interrumpirme
			}
		}
		close (sock_conn);
	}
}