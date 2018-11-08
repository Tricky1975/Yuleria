// Lic:
//   yuleria.h
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
#ifndef __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define yul_new(size) yul_xnew(malloc(size),size,NULL,NULL)
#define yul_object    yul_obj
#define yul_null(obj) _yulnull_do(obj); obj=NULL;
#define yul_strcpy(target,source) target=_yulstrcpy(target,source)
#define yul_str_concat(target,str1,str2) target=_yulstr_concat(target,str1,str2)
#define yul_strsame(o1,o2) strcmp(o1->yobject,o2->yobject)==0


// types
typedef struct yul_s_object {
	void * yobject;
	void (* ydestructor)(void * yself);
	int    ycount;
	int    ysize;
	// These can be used for the total release of all memory
	struct yul_s_object * yq_prev;
	struct yul_s_object * yq_next;
} * yul_obj;

typedef struct yul_s_node {
	struct yul_s_node * prev;
	struct yul_s_node * next;
	yul_obj             obj;
} * yul_node;

// functions
void * yul_xnew(void * obj,long int size,void (* constructor)(void * self), void (* destructor)(void * self));
void _yulnull_do(yul_obj obj); // should never be used directly but through the macro!
void yul_point(yul_obj yobjtar,yul_obj yobjfrom);
yul_obj yul_newstring(char *newstring);
void yul_redef(yul_obj target,char * source);
yul_obj _yulstrcpy(yul_obj target,yul_obj source);
yul_obj _yulstr_concat(yul_obj target,yul_obj str1, yul_obj str2);
/*
 * functions prefixed as "yul_" should be directly usable
 * functions prefixed as "_yul" should only be used through the macro I set up for it.
 * This is the safest way to go ;)
 */


#endif

// TODO:total clean
