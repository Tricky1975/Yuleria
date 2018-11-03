#ifndef __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define yul_new(size) yul_xnew(malloc(size),size,NULL,NULL)
#define yul_object    yul_obj
#define yul_null(obj) _yulnull_do(obj); obj=NULL;

// types
typedef struct yul_s_object {
	void * yobject;
	void (* ydestructor)(void * yself);
	int    ycount;
	int    ysize;
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

#endif

// TODO:total clean
