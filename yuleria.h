#ifndef __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define __YULERIA_HAS_ALREADY_BEEN_LOADED__
#define yul_new(size) yul_xnew(size,NULL,NULL)
#define yul_object    yul_obj

// types
typedef struct yul_s_object {
	void * yobject;
	void (* ydestructor)(void * yself);
	int    ycount;
} * yul_obj;

typedef struct yul_s_node {
	struct yul_s_node * prev;
	struct yul_s_node * next;
	yul_obj             obj;
} * yul_node;

// functions
void * yul_xnew(void * obj,long int size,void (* constructor)(void * self), void (* destructor)(void * self));
void yul_null(yul_obj* obj);
void yul_point(yul_obj yobjtar,yul_obj yobjfrom);

#endif
