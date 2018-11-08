// Lic:
//   yuleriatest.c
//
//   version: 18.11.05
//   Copyright (C) 2018 Jeroen P. Broks
//   This software is provided 'as-is', without any express or implied
//   warranty.  In no event will the authors be held liable for any damages
//   arising from the use of this software.
//   Permission is granted to anyone to use this software for any purpose,
//   including commercial applications, and to alter it and redistribute it
//   freely, subject to the following restrictions:
//   1. The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software
//      in a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
//   2. Altered source versions must be plainly marked as such, and must not be
//      misrepresented as being the original software.
//   3. This notice may not be removed or altered from any source distribution.
// EndLic
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../yuleria.h"

void destructor(void * test){
	printf("text %s will be destroyed\n",(char*)test);
}

void constructor(void * test){
	printf("text %s has been assigned\n",(char*)test);
}

int main(void){
	printf("Time to test Yuleria\n");
	char*n=malloc(7); strcpy(n,"Jeroen"); // I cannot use ready to go strings, I see! True string workout comes later
	yul_obj ytest = yul_xnew(n,7,constructor,destructor);
	printf("%s == %s\n",n,(char*)(ytest->yobject));
	yul_obj ytest2=NULL;
	yul_strcpy(ytest2,ytest);
	printf("Did I copy %s?\n",(char*)(ytest->yobject));
	yul_null(ytest);
	yul_null(ytest2);
	printf("destruction done!\n");
	//printf("%s == NULL?\n",n);
	if (n    ==NULL) printf("sub object is nul!\n");
	if (ytest==NULL) printf("yul object is nul!\n");
}
