#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char **argv){

    int counter = 0, result_len = 0;
    while(counter < argc){  
        result_len+=strlen(argv[counter]);
        counter++;
    }
    char* conct_str = (char*)malloc(sizeof(char)*result_len);
    return 0;
}