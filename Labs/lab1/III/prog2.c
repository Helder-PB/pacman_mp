#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

/* include the correct .h file */


int main(){
	int a;
	char line[100];
	char library_name[100];
	char *error;

	printf("What version of the functions you whant to use?\n");
	printf("\t1 - Normal    (lib1)\n");
	printf("\t2 - Optimized (lib2)\n");
	fgets(line, 100, stdin);
	sscanf(line,"%d", &a);
	if (a == 1){
		strcpy(library_name, "./lib1.so");
		printf("running the normal versions from %s \n", library_name);
	}else{
		if(a== 2){
			strcpy(library_name, "./lib2.so");
			printf("running the normal versions %s \n", library_name);
		}else{
			printf("Not running anything\n");
			exit(-1);
		}
	}
	/* load library from name library_name */

	void *lib;
	lib = dlopen(library_name,RTLD_LAZY);
	if(!lib){
		fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
	}
	/* declare pointers to functions */

	
	void (*func_1)(void);
	void (*func_2)(void);
	
	
	/*load func_1 from loaded library */
	func_1 = dlsym(lib,"func_1");
	error = dlerror();
	if(error != NULL){
		fprintf(stderr,"%s\n",error);
		exit(EXIT_FAILURE);
	}
	/*load func_2 from loaded library */
	func_2 = dlsym(lib,"func_2");
	error = dlerror();
	if(error != NULL){
		fprintf(stderr,"%s\n",error);
		exit(EXIT_FAILURE);
	}

	/* call func_1 from whichever library was loaded */
	(*func_1)();
	/* call func_2 from whichever library was loaded */
	(*func_2)();

	dlclose(lib);
	exit(0);
}
