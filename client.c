#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define TAG_CLIENT_MESSAGE 2
#define TAG_SERVER_RESULT 3
#define SIZE_RESULT 1024

int main( int argc, char **argv ){
	MPI_Comm server;
	MPI_Status status;
	char port_name[MPI_MAX_PORT_NAME];
	char text[SIZE_RESULT];
	char result[SIZE_RESULT];

	if (argc < 2) {
		fprintf(stderr, "server port name required.\n");
		exit(EXIT_FAILURE);
	}

	MPI_Init(&argc, &argv);
	strcpy(port_name, argv[1]); 
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &server);
	
	while (1) {
		printf(">client: ");
		scanf("%[^\n]%*c", text);

		// Client sends here
		MPI_Send(&text, strlen(text) + 1, MPI_CHAR, 0, TAG_CLIENT_MESSAGE, server);

		// Client receives here
		MPI_Recv(&result, SIZE_RESULT, MPI_CHAR, MPI_ANY_SOURCE, TAG_SERVER_RESULT, server, MPI_STATUS_IGNORE);
		printf("Server sent: \n%s\n", result);
	}

	MPI_Comm_disconnect(&server);
	MPI_Finalize();
	return 0;
}