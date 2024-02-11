#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a program that concatenates all its arguments into a single string*/

using namespace std;

int main(int argc, char **argv){

    int counter = 0, result_len = 0;
    while(counter < argc){  
        result_len+=strlen(argv[counter]);
        counter++;
    }
    char* conct_str = (char*)malloc(sizeof(char)*result_len);
	if(conct_str==NULL){printf("Allocation error");exit(0);}

	int buff_ind = 0;
	for(int i = 0; i < counter; i++){
		strcpy(conct_str+buff_ind,argv[i]);
		buff_ind+=strlen(argv[i]);
	}
	
	printf("The concatenated string is :\n %s\n",conct_str);
	free(conct_str);	

    return 0;
}
