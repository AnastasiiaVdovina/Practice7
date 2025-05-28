#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
	DIR *dir = opendir(".");
	struct dirent *entry;
	struct stat st;
	char answer[10];
	
	if(dir == NULL){
		perror("opendir");
		return 1;
	}

	while((entry = readdir(dir)) != NULL){
		if(entry->d_name[0] == '.')
			continue;
	
		if(stat(entry->d_name, &st) == -1)
			continue;
	
		if(S_ISREG(st.st_mode)){
			printf("Do you want to delete file \"%s\"? (yes, no): ", entry->d_name);
			fgets(answer, sizeof(answer), stdin);
			answer[strcspn(answer, "\n")] = '\0';

			if(strcmp(answer, "yes") == 0 || strcmp(answer, "y") == 0){
				if(remove(entry->d_name) == 0){
					printf("File %s was deleted.\n", entry->d_name);
				}else{
					perror("deletion error");
				}

			}else {
				printf("File %s was skipped.\n", entry->d_name);
			}

		}

	}

	closedir(dir);
	return 0;
}
