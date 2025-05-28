#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

//struct for saving names of dirs
typedef struct{
	char **names;
	size_t count;
	size_t capacity;
} DirList;

void add_to_list(DirList *list, const char *name){
	if(list->count == list->capacity){
		list->capacity = list->capacity ? list->capacity *2 : 10;
		list->names = realloc(list->names, list->capacity * sizeof(char *));
	}
	list->names[list->count++] = strdup(name);
}


int compare_names(const void *a, const void *b){
	return strcmp(*(const char **)a, *(const char **)b);
}

void list_subdirs_sorted(const char *path){
	struct dirent *entry;
	DIR *dp = opendir(path);
	if(dp == NULL){
		perror("opendir");
		return;
	}

	DirList list = {NULL, 0, 0};
	
	while((entry = readdir(dp)) != NULL){
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, ".." ) == 0)
			continue;
		
		char fullpath[1024];	
		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
	
		struct stat statbuf;
		if(stat(fullpath, &statbuf) == -1)
			continue;
		
		if(S_ISDIR(statbuf.st_mode)){
			add_to_list(&list, entry->d_name);
		}
	}

	closedir(dp);

	//sorting and printing
	qsort(list.names, list.count, sizeof(char *), compare_names);

	for(size_t i = 0; i < list.count; i++){
		printf("%s\n", list.names[i]);
		free(list.names[i]);
	}

	free(list.names);

}

int main(int argc, char *argv[]){
	const char *path = (argc > 1) ? argv[1] : ".";
	list_subdirs_sorted(path);
	return 0;

}

