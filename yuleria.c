// Lic:
//   yuleria.c
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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "yuleria.h"

yul_obj yq_first = NULL;
yul_obj yq_last  = NULL;

void * yul_xnew(void * obj,long int size,void (* constructor)(void * self), void (* destructor)(void * self)){
	void  * rob      = obj; //malloc(size); // rob = returnable object
	yul_obj ret      = malloc(sizeof(struct yul_s_object));
	ret->yobject     = rob;
	ret->ycount      = 1;
	ret->ydestructor = destructor;
	ret->ysize       = size;
	ret->yq_next     = NULL;
	if (yq_first==NULL) {
		 yq_first = ret;
	} else {
		 ret->yq_prev=yq_last;
		 yq_last->yq_next=ret;
	}
	yq_last = ret;
	if (constructor!=NULL) constructor(rob);
	return ret; // warning preventer (will be removed later);
}

yul_obj yul_newstring(char *newstring){
	unsigned long l=strlen(newstring)+1;
	char *wstring = malloc(l); strcpy(wstring,newstring);
	return yul_xnew(wstring,l,NULL,NULL);
}

void yul_redef(yul_obj target,char * source){
	unsigned long l=strlen(source);
	char *tstring = malloc(l); strcpy(tstring,source);
	char *ostring = target->yobject;
	target->yobject=tstring;
	free(ostring);
}

// I recommend NOT to call this directly, but to use the macro in stead
yul_obj _yulstrcpy(yul_obj atarget,yul_obj source){
	yul_obj target=atarget;
	if(target==NULL) target=yul_newstring("");
	unsigned long l=strlen(source->yobject);
	char *tstring = malloc(l); strcpy(tstring,source->yobject);
	char *ostring = target->yobject;
	target->yobject=tstring;
	free(ostring);
	return target;
}

yul_obj _yulstr_concat(yul_obj target,yul_obj str1, yul_obj str2){
	char * tstring = malloc(strlen(str1->yobject)+strlen(str2->yobject)+1); // +1 for the nul terminator
    int point1=0;
    int point2=0;
    int pointt=0;
    char *wstr1=str1->yobject;
    char *wstr2=str2->yobject;
    while(wstr1[point1] || wstr2[point2]){
    	if (wstr1[point1]){
    		tstring[pointt]=wstr1[point1];
    		point1++;
    	} else {
    		tstring[pointt]=wstr2[point2];
    		point2++;
    	}
    	pointt++;
		tstring[pointt]=0;
    }
    if (target==NULL) return yul_newstring(tstring);
    else {
    	yul_redef(target,tstring);
    	return target;
    }
}


void _yulnull_do(yul_obj obj,bool noq){
	yul_obj o=obj;
	o->ycount--;
	if (o->ycount==0){
		if (o->ydestructor!=NULL) o->ydestructor(o->yobject);
		if (o->yq_prev==NULL) {
			yq_first=o->yq_next;
		} else {
			o->yq_prev=o->yq_next;
		}
		free(o->yobject);
		free(o);
	}
	//obj=NULL;
}

void yul_point(yul_obj yobjtar,yul_obj yobjfrom){
	if (yobjtar!=yobjfrom){
		yul_null(yobjtar);
		yobjtar=yobjfrom;
		yobjtar->ycount++;
	}
}

void yul_disposeall(){
	if (yq_first!=NULL){
			for (yul_obj killme=yq_first;killme!=NULL;killme=killme->yq_next) _yulnull_do(killme->yq_prev,true);
			free(yq_last);
			yq_first=NULL;
			yq_last=NULL;
	}
}
