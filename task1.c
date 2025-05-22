#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file;
	char buffer[1024]; //1 mb

	//opening rwho for reading
	file = popen("rwho", "r");
	if(file == NULL){
		perror("popen rwho");
		exit(EXIT_FAILURE);
	}

	//opening "more" for writing
	FILE *more_file = popen("more", "w");
	if(more_file == NULL){
		perror("popen more");
		pclose(file);
		exit(EXIT_FAILURE);
	}

	//passing the output of "rwho" to "more"
	while(fgets(buffer, sizeof(buffer), file) != NULL){
		fputs(buffer, more_file);
	}

	pclose(file);
	pclose(more_file);

	return 0;
}
