#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

#define MAX_DEPTH 20

typedef struct VisitedNode{
	dev_t dev;
	ino_t ino;
	struct VisitedNode *next;
} VisitedNode;

VisitedNode* visited = NULL;

int  already_visited(dev_t dev, ino_t ino){
	VisitedNode* current = visited;
	while(current){
		if(current->ino == ino && current->dev == dev){
			return 1;
		}
		current = current->next;
	}

	VisitedNode* new_node = malloc(sizeof(VisitedNode));
	if(!new_node){
		perror("malloc");
		exit(1);
	}

	new_node->ino = ino;
	new_node->dev = dev;
	new_node->next = visited;
	visited = new_node;
	return 0;
}

void print_indent(int depth){
	for(int i = 0; i < depth; i++){
		printf(" ");
	}
}

void traverse(const char* path, int depth){
	if(depth > MAX_DEPTH) return;
	
	DIR* dir = opendir(path);
	if(!dir) return;
	
	struct dirent* entry;
	while((entry = readdir(dir)) != NULL){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
			continue;
		}

		char fullpath[PATH_MAX];
		snprintf(fullpath, sizeof(fullpath), "%s%s", path, entry->d_name);
		
		struct stat sb;
		if(lstat(fullpath, &sb) == -1){
			perror("lstat");
			continue;
		}

		print_indent(depth);
		printf("%s\n", entry->d_name);

		if(S_ISLNK(sb.st_mode)){
			continue;
		}

		if(S_ISDIR(sb.st_mode)){
			if(!already_visited(sb.st_dev, sb.st_ino)){
				traverse(fullpath, depth+1);
			}

		}

	}

	closedir(dir);

}


int main(){
	printf("/\n");
	traverse("/", 1);
	return 0;

}
