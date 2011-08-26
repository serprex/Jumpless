#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glfw.h>
#include "tgen.h"
#include "j.h"
#define case(x) break;case x:;
#define else(x) else if(x)
GLuint Ts;
typedef struct Obj{
	struct Obj*n;
	float x,y;
	char t;
	unsigned char d[];
}Obj;
Obj**Ps,*P,*Rost;
int Pp,KT,BT,Ls=sizeof(L)/sizeof(char*),et;
Obj*makeObj(char t,float x,float y,int l,char*d){
	Obj*r=malloc(l+sizeof(Obj));
	r->t=t;
	r->x=x;
	r->y=y;
	memcpy(r->d,d,l);
	return r;
}
unsigned char sizeObj[]={0,0,0,1,0,2,1,1,2,1,1};

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
void drawObj(Obj*n){
	switch(n->t){
	case(0)drawRect(n->x,n->y,0,0);
	case(1)drawRect(n->x,n->y,2,0);
	case(2)drawRect(n->x,n->y,0,3);
	case(3)drawRect(n->x,n->y,(n->d[0]++)>>5,2);
	case(4)drawRect(n->x,n->y,3,0);
	case(5)drawRect(n->x,n->y,6,0);
	case(6)drawRect_(n->x,n->y,5,0,0,n->d[0]);
	case(7)drawRect_(n->x,n->y,4,0,n->d[0],0);
	case(8)drawRect(n->x,n->y,(n->d[0]+=(n->d[1]?4:-4))/43,3);
	case(9)drawRect(n->x,n->y,n->d[0],1);
	case(10)drawRect(n->x,n->y,4+n->d[0],1);
	}
}

char*chmem[]={"","","","\1","","\2\0\377","\1","\1\1","\1","\1\1","\2\0\1","\2\0","\1","\1\1","\1","\1\1"},
	chtype[]={0,1,2,3,4,5,6,6,7,7,8,8,9,9,10,10};

void loadL(unsigned char*L){
	float Lx=64-L[0]>>1,Ly=64-L[1]>>1;
	P->x=Lx+L[2];
	P->y=Ly+L[3];
	Obj*h=P;
	for(char*p=L+4;*p;p+=3+sizeObj[*p])
		h=h->n=makeObj(*p,Lx+p[1],Ly+p[2],sizeObj[*p],p+3);
	h->n=0;
}

Obj*oat(char t,float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->t==t&&n->x==x&&n->y==y)
			return n;
	return 0;
}

void dat(float x,float y){
	for(Obj*n=P;n&&n->n;n=n->n)
		if(n->n->x==x&&n->n->y==y){
			Obj*o=n->n;
			n->n=n->n->n;
			free(o);
			return;
		}
}

void del(Obj*o){
	for(Obj*n=P;;n=n->n)
		if(n->n==o){
			n->n=o->n;
			free(o);
			return;
		}
}

int main(int argc,char**argv){
	glfwInit();
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	GLFWvidmode gvm;
	glfwGetDesktopMode(&gvm);
	int wihe=gvm.Height>1024?1024:gvm.Height>512?512:256;
	glfwOpenWindow(wihe,wihe,0,0,0,0,0,0,GLFW_WINDOW);
	glOrtho(0,64,64,0,1,-1);
	glPointSize(wihe/512);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glLogicOp(GL_XOR);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glGenTextures(1,&Ts);
	glBindTexture(GL_TEXTURE_2D,Ts);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,gF,gW,gH,0,gF,GL_UNSIGNED_BYTE,g);
	Ps=malloc(sizeof(Obj*)*Ls);
	for(int i=0;i<Ls;i++){
		Ps[i]=P=makeObj(0,0,0,0,"");
		P->n=0;
		loadL(LL[i]);
	}
	Rost=makeObj(0,0,0,0,"");
	Obj*ro=Rost;
	for(int i=1;i<16;i++){
		ro=ro->n=makeObj(chtype[i],i,0,*chmem[i],chmem[i]+1);
	}
	ro->n=0;
	for(;;){
		KT-=KT>0;
		BT-=BT>0;
		if(glfwGetKey(GLFW_KEY_SPACE)&&!KT){
			KT=6;
			Pp++;
			if(Pp==Ls)Pp=0;
			P=Ps[Pp];
		}else if(glfwGetKey('N')&&P->n){
			Ps=realloc(Ps,sizeof(Obj*)*++Ls);
			Ps[Pp=Ls-1]=P=makeObj(0,64,64,0,"");
			P->n=0;
		}else if(glfwGetKey(GLFW_KEY_BACKSPACE)&&!BT&&Ls>1){
			BT=9;
			memmove(Ps+Pp,Ps+Pp+1,(Ls-Pp-1)*sizeof(Obj*));
			for(Obj*n=P,*o;n;o=n,n=n->n,free(o));
			Ps=realloc(Ps,sizeof(Obj*)*--Ls);
			P=Ps[Pp-=Pp==Ls];
		}
		int b;
		if((glfwGetMouseButton(b=0)||glfwGetMouseButton(b=1)||glfwGetMouseButton(b=2))&&!BT){
			BT=6;
			Obj*o;
			int x,y;
			glfwGetMousePos(&x,&y);
			x/=wihe/64;
			y/=wihe/64;
			if(y==0&&x<16){
				et=x;
			}else if(!et){
				P->x=x;
				P->y=y;
			}else if(o=oat(chtype[et],x,y)){
				del(o);
			}else{
				if(b!=1)dat(x,y);
				if(b!=2){
					o=makeObj(chtype[et],x,y,*chmem[et],chmem[et]+1);
					o->n=P->n;
					P->n=o;
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		for(Obj*n=P;n;n=n->n)
			drawObj(n);
		for(Obj*n=Rost;n;n=n->n)
			drawObj(n);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glEnable(GL_COLOR_LOGIC_OP);
		glRecti(et,0,et+1,1);
		glDisable(GL_COLOR_LOGIC_OP);
		glBindTexture(GL_TEXTURE_2D,Ts);
		glfwSwapBuffers();
		glfwSleep(1./30);
		glfwPollEvents();
		if(glfwGetKey('S')&&!KT){
			KT=9;
			FILE*f=fopen("j.h","w");
			fputs("unsigned char*L[]={",f);
			for(int i=0;i<Ls;i++){
				int mnx=255,mny=255,mxx=0,mxy=0;
				for(Obj*n=Ps[i];n;n=n->n){
					if(n->x<mnx)mnx=n->x;
					if(n->x>mxx)mxx=n->x;
					if(n->y<mny)mny=n->y;
					if(n->y>mxy)mxy=n->y;
				}
				fprintf(f,"\"\\%o\\%o\\%o\\%o",mxx-mnx+1,mxy-mny+1,(int)Ps[i]->x-mnx,(int)Ps[i]->y-mny);
				for(Obj*n=Ps[i]->n;n;n=n->n){
					fprintf(f,"\\%o\\%o\\%o",n->t,(int)n->x-mnx,(int)n->y-mny);
					switch(n->t){
					case(3)case 6:case 7:case 9:case 10:fprintf(f,"\\%o",n->d[0]);
					case(8)case 5:fprintf(f,"\\%o\\%o",n->d[0],n->d[1]);
					}
				}
				fputs(i+1==Ls?"\"},**LL=L;":"\",",f);
			}
			fclose(f);
		}
		if(glfwGetKey('Q')||!glfwGetWindowParam(GLFW_OPENED))return 0;
	}
}