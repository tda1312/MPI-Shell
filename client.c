#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main( int argc, char **argv ){
	MPI_Comm server;
	char port_name[MPI_MAX_PORT_NAME];
	int j, tag;
	char text[100];

	if (argc < 2) {
		fprintf(stderr, "server port name required.\n");
		exit(EXIT_FAILURE);
	}

	MPI_Init(&argc, &argv);
	strcpy(port_name, argv[1]); /* assume server's name is cmd-line arg */
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &server);
	
	while (1) {
		int n;
		printf(">client: ");
		scanf("%s", &text);
		// for (j = 0; j < n; j++) {
		// 	tag = 2; /* Action to perform */
		// 	MPI_Send(&j, 1, MPI_INT, 0, tag, server);
		// }
		MPI_Send(&text, 1, MPI_CHAR, 0, tag, server);
	}

	// MPI_Send(&i, 0, MPI_INT, 0, 1, server);
	MPI_Comm_disconnect(&server);
	MPI_Finalize();
	return 0;
}