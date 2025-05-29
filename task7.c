#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024

int is_executable_by_user(const struct stat *st){
	return st->st_mode & S_IXUSR;
}

void process_file(const char *filepath, const char *filename){
	struct stat st;
	if(stat(filepath, &st) != 0 || !S_ISREG(st.st_mode)){
		return;
	}

	if(is_executable_by_user(&st)){
		printf("- %s\n", filename);
		printf("Provide read access for others? (y/n): ");
		char answer;
		scanf(" %c", &answer);
		
		if(answer == 'y' || answer == 'Y'){
			mode_t new_mode = st.st_mode | S_IROTH;
			if(chmod(filepath, new_mode) == 0){
				printf("Read permission provided\n");
			}else{
				perror("Unavailable to change roots");
			}

		}

	}

}


void list_executables_in_current_dir(){
	DIR *dir = opendir(".");
	if(!dir){
		perror("opendir");
		exit(1);
	}

	struct dirent *entry;
	char path[MAX_PATH];

	printf("List of executables files in current directory:\n");
	
	while((entry = readdir(dir)) != NULL){
		snprintf(path, MAX_PATH,"./%s", entry->d_name);
		process_file(path, entry->d_name);
	}

	closedir(dir);
}

int main(){
	list_executables_in_current_dir();
	return 0;
}
