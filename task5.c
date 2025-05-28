#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path){
	struct dirent *entry;
	DIR *dp = opendir(path);
	
	if(dp == NULL){
		perror("opendir");
		return;
	}

	while ((entry = readdir(dp)) != NULL){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
	
		char fullpath[1024];
		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
		
		struct stat statbuf;
		if(stat(fullpath, &statbuf) == -1){
			perror("stat");
			continue;
		}

		if(S_ISDIR(statbuf.st_mode)){
			list_files(fullpath);
		} else if(S_ISREG(statbuf.st_mode)){
			printf("%s\n", fullpath);
		}

	}

	closedir(dp);
	
}


int main(){
	list_files(".");
	return 0;
}
