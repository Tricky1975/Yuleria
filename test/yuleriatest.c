#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "../yuleria.h"

void destructor(void * test){
	printf("text %s will be destroyed\n",test);
}

void constructor(void * test){
	printf("text %s has been assigned\n",test);
}

int main(void){
	printf("Time to test Yuleria\n");
	char*n=malloc(7); strcpy(n,"Jeroen"); // I cannot use ready to go strings, I see! True string workout comes later
	yul_obj ytest = yul_xnew(n,7,constructor,destructor);
	printf("%s == %s\n",n,ytest->yobject);
	yul_null(ytest);
	printf("destruction done!\n");
	//printf("%s == NULL?\n",n);
	if (n    ==NULL) printf("sub object is nul!\n");
	if (ytest==NULL) printf("yul object is nul!\n");
}
