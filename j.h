#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glfw.h>
#include "tgen.h"
#include "jgen.h"
GLuint Ts;
typedef struct Obj{
	struct Obj*n;
	float x,y;
	unsigned char t,d[];
}Obj;
char sizeObj[]={0,0,0,1,0,2,1,1,2,1,1,0,1};
void drawRect_(float x,float y,float a,float b,float h,float v){
	a/=8;
	b/=4;
	glTexCoord2f(a,b);
	glVertex2f(x+h,y+v);
	glTexCoord2f(a+1./8,b);
	glVertex2f(x+1-h,y+v);
	glTexCoord2f(a+1./8,b+1./4);
	glVertex2f(x+1-h,y+1-v);
	glTexCoord2f(a,b+1./4);
	glVertex2f(x+h,y+1-v);
}
void drawRect(float x,float y,float a,float b){
	drawRect_(x,y,a,b,0,0);
}
#define case(x) break;case x:;
#define else(x) else if(x)