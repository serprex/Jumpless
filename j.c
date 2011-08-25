#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <GL/glfw.h>
#include "tgen.h"
#define case(x) break;case x:
#define else(x) else if(x)
#include <stdio.h>
GLuint Ts;
typedef struct Obj{
	struct Obj*n;
	float x,y;
	char t;
	unsigned char d[];
}Obj;
Obj*P;
int Pd,Pu,Pk[2],Kv,Kh;
Obj*makeObj(char t,float x,float y,int d){
	Obj*r=malloc(d+sizeof(Obj));
	r->t=t;
	r->x=x;
	r->y=y;
	return r;
}
typedef struct{
	short w,h;
	char*s;
}Lt;
Lt L0={9,7,
"!:       "
" #=-@    "
"   #;-%%%"
"  v ,-   "
"    ^-   "
"   .-    "
"   #     "},
L1={2,19,
"@ "
"vv"
".,"
"%:"
": "
"; "
"  "
"vv"
".,"
"%:"
": "
"; "
"  "
"vv"
".."
"%:"
": "
";!"
": "},*LL;

void bindTex(GLuint t){
	glBindTexture(GL_TEXTURE_2D,t);
}
int makeTex(const void*px,int w,int h,int f){
	bindTex(Ts);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,f,w,h,0,f,GL_UNSIGNED_BYTE,px);
}

void drawRect(float x,float y,float tx,float ty){
	tx/=8;
	ty/=8;
	glTexCoord2f(tx,ty);
	glVertex2f(x,y);
	glTexCoord2f(tx+1./8,ty);
	glVertex2f(x+1,y);
	glTexCoord2f(tx+1./8,ty+1./8);
	glVertex2f(x+1,y+1);
	glTexCoord2f(tx,ty+1./8);
	glVertex2f(x,y+1);
}

void loadL(Lt*L){
	Obj*h=P;
	LL=L;
	for(int x=0;x<L->w;x++)
		for(int y=0;y<L->h;y++){
			int t;
			switch(L->s[y*L->w+x]){
			case('@')
				P->x=x;
				P->y=y;
			case('!')h=h->n=makeObj(1,x,y,0);
			case('#')h=h->n=makeObj(2,x,y,0);
			case('%')
				h=h->n=makeObj(3,x,y,1);
				h->d[0]=0;
			case('-')h=h->n=makeObj(4,x,y,0);
			case('=')h=h->n=makeObj(5,x,y,0);
			case('v')h=h->n=makeObj(6,x,y,0);
			case('^')h=h->n=makeObj(7,x,y,0);
			case('(')h=h->n=makeObj(8,x,y,0);
			case(')')h=h->n=makeObj(9,x,y,0);
			case('<')
				h=h->n=makeObj(10,x,y,1);
				h->d[0]=0;
			case('>')
				h=h->n=makeObj(11,x,y,1);
				h->d[0]=0;
			case('.')
				h=h->n=makeObj(12,x,y,1);
				h->d[0]=0;
			case(',')
				h=h->n=makeObj(12,x,y,1);
				h->d[0]=1;
			case(':')
				h=h->n=makeObj(13,x,y,1);
				h->d[0]=0;
			case(';')
				h=h->n=makeObj(13,x,y,1);
				h->d[0]=1;
			}
		}
	h->n=0;
}

Obj*oat(char t,float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->t==t&&n->x==x&&n->y==y)
			return n;
	return 0;
}

void del(Obj*o){
	for(Obj*n=P;;n=n->n)
		if(n->n==o){
			n->n=o->n;
			free(o);
			return;
		}
}

int any(float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->x==x&&n->y==y)
			return 1;
	return 0;
}

int main(int argc,char**argv){
	glfwInit();
	srand(glfwGetTime()*10e5);
	glfwOpenWindow(512,512,0,0,0,0,0,0,GLFW_WINDOW);
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	glOrtho(0,64,64,0,1,-1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glGenTextures(1,&Ts);
	makeTex(g,gW,gH,gF);
	P=makeObj(0,0,0,0);
	loadL(&L0);
	for(;;){
		if(P->y>64)loadL(LL);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		Kv=glfwGetKey(GLFW_KEY_DOWN)-glfwGetKey(GLFW_KEY_UP);
		Kh=glfwGetKey(GLFW_KEY_RIGHT)-glfwGetKey(GLFW_KEY_LEFT);
		for(Obj*n=P;n;n=n->n){
			switch(n->t){
			Obj*o;
			case(0)
				if(Pu!=4&&Kh){
					Pd=Kh;
					goto walk;
				}
				if(n->x!=(int)n->x){
					walk:if(!oat(2,n->x+Pd,n->y)){
						if(o=oat(13,n->x+Pd,n->y)){
							if(Pk[o->d[0]]){
								Pk[o->d[0]]--;
								del(o);
							}else goto nokey;
						}
						n->x+=Pd/8.;
						nokey:;
					}
				}else if(oat(5,n->x,n->y)&&Kv&&!(Kv==1&&oat(7,n->x,n->y+1)||Kv==-1&&oat(6,n->x,n->y-1))){
					Pu=Kv;
					goto vert;
				}else if(Kv==-1&&(oat(4,n->x,n->y)||oat(7,n->x,n->y))){
					Pu=-1;
					goto vert;
				}else if(Kv==1&&(oat(4,n->x,n->y)||oat(6,n->x,n->y)||oat(6,n->x,n->y+1)||(oat(4,n->x,n->y+1)&&!oat(7,n->x,n->y)))){
					Pu=1;
					goto vert;
				}
				if(oat(1,n->x,n->y)){
					loadL(&L1);
				}
				if(o=oat(3,n->x,n->y+1)){
					if(!(o->d[0]+=4))
						del(o);
				}
				if((o=oat(12,n->x,n->y))||(o=oat(12,n->x,n->y+1))){
					Pk[o->d[0]]++;
					del(o);
				}
				if(o=oat(13,n->x,n->y+1)){
					if(Pk[o->d[0]]){
						Pk[o->d[0]]--;
						del(o);
					}
				}
				if(n->y!=(int)n->y){
					vert:
					if(o=oat(5,n->x,n->y))o->y+=Pu/8.;
					n->y+=Pu/8.;
				}else if(n->x==(int)n->x&&!any(n->x,n->y+1)&&!(oat(4,n->x,n->y)||oat(5,n->x,n->y)||oat(6,n->x,n->y)||oat(7,n->x,n->y)||oat(8,n->x,n->y)||oat(9,n->x,n->y))){
					Pu=4;
					Pd=0;
					goto vert;
				}else Pu=0;
				drawRect(n->x,n->y,Pd==1,0);
			case(1)drawRect(n->x,n->y,3,0);
			case(2)drawRect(n->x,n->y,2,0);
			case(3)drawRect(n->x,n->y,n->d[0]>>5,3);
			case(4)drawRect(n->x,n->y,4,0);
			case(5)drawRect(n->x,n->y,6,4);
			case(6)drawRect(n->x,n->y,7,0);
			case(7)drawRect(n->x,n->y,7,1);
			case(8)drawRect(n->x,n->y,5,0);
			case(9)drawRect(n->x,n->y,6,0);
			case(10)drawRect(n->x,n->y,4,n->d[0]++/51);
			case(11)drawRect(n->x,n->y,4,n->d[0]--/51);
			case(12)drawRect(n->x,n->y,n->d[0],1);
			case(13)drawRect(n->x,n->y,n->d[0],2);
			}
		}
		glEnd();
		glfwSwapBuffers();
		double gT=1./59-glfwGetTime();
		glfwSleep(gT);
		glfwSetTime(0);
		glfwPollEvents();
		if(glfwGetKey(GLFW_KEY_ESC)||!glfwGetWindowParam(GLFW_OPENED))return 0;
	}
}