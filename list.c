#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"


PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	PathNode * temp1 = p -> head;
	PathNode * temp2;
	while(temp1 != NULL)
	{
	temp2 = temp1 -> next;
	freeNode(temp1);
	temp1 = temp2;
	}
	free(p);
	return;
}

PathNode * buildNode(char * path) {//char * path always points to array
	//fill in
	//here we are allocating memory for the string path
	int size = 0;
	while(path[size] != '\0'){
	++size;
	}
	PathNode * node = malloc(sizeof(PathNode));
	node -> next = NULL;
	node -> path = malloc(sizeof(char)*(size+1));
	strcpy(node -> path, path);
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
	return node;
}

void freeNode(PathNode * p) {
	//fill in
	//just free the data we outlined earlier
	free(p -> path);
	free(p);
	return;
}

bool addNode(PathLL * paths, char * path) {
	if(containsNode(paths,path))
	{
	return false;
	}
	PathNode * its;
	PathNode * lit;
	PathNode * migos;
	migos = buildNode(path);
	its = NULL;
	lit = paths -> head;
	if(lit == NULL)
	{
	paths -> head = migos;
	return true;
	}
	if(comparer(path, lit -> path))
	{
	migos -> next = paths -> head;
	paths -> head = migos;
	return true;
	}
	
	its = lit;
	lit = lit->next;
	while(lit != NULL)
	{
	if(comparer(path, lit -> path))
	{
	migos -> next = lit;
	its -> next = migos;
	return true;
	}
	its = lit;
	lit = lit -> next;
	}
	
	its -> next = migos;
	return true;
}

bool comparer(char * d, char * c)
{
	bool s1, s2, s3, r;
	s1 = strlen(d) < strlen(c);
	s2 = ((strlen(d) == strlen(c)) && (turnspath(d) < turnspath(c)));
	s3 = ((strlen(d) == strlen(c)) && (turnspath(d) == turnspath(c)) && (strcmp(d,c) < 0));
	r = (s1 || s2 || s3);
	return r;
}

int turnspath(char * path){
	int counter = 0;
	int turns = 0;
	while(path[counter + 1] != '\0')
	{
	if(path[counter] != path[counter+1])
	{
	turns++;
	}
	counter++;
	}
	return turns;
}

bool removeNode(PathLL * paths, char * path) {
	if(path == NULL)
	{
	return false;
	}
	if(paths == NULL)
	{
	return false;
	}
	PathNode * previous = NULL;
	PathNode * cur = paths -> head;
	while(cur != NULL)
	{
	if(strcmp(path, cur -> path) == 0)
	{
		if(previous == NULL){
		paths -> head = cur -> next;
		}
		else{
		previous -> next = cur -> next;
		}
		freeNode(cur);
		return true;
		}
		previous = cur;
		cur = cur -> next;
	
}
return false;
}

bool containsNode(PathLL * paths, char * path) {
	PathNode * curpath = paths->head;
	while((curpath != NULL) && strcmp(curpath -> path, path))
	{
	curpath = curpath -> next;
	}
	if(curpath != NULL)
	{
	return true;
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
