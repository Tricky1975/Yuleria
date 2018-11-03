#include <stdio.h>
#include <stdlib.h>
#include "yuleria.h"

void * yul_xnew(void * obj,long int size,void (* constructor)(void * self), void (* destructor)(void * self)){
	void  * rob      = malloc(size); // rob = returnable object
	yul_obj ret      = malloc(sizeof(struct yul_s_object));
	ret->yobject     = rob;
	ret->ycount      = 1;
	ret->ydestructor = destructor;
	if (constructor!=NULL) constructor(rob);
	return ret; // warning preventer (will be removed later);
}

void yul_null(yul_obj* obj){
	yul_obj o=*obj;
	o->ycount--;
	if (o->ycount==0){
		if (o->ydestructor!=NULL) o->ydestructor(o->yobject);
		free(o->yobject);
		free(o);
	}
	obj=NULL;
}

void yul_point(yul_obj yobjtar,yul_obj yobjfrom){
	if (yobjtar!=yobjfrom){
		yul_null(&yobjtar);
		yobjtar=yobjfrom;
		yobjtar->ycount++;
	}
}
