#include <stdlib.h>
#include <string.h>
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
Obj*P;
int Pd,Pu,Pk[2],Kv,Kh,Kp;
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

void loadL(unsigned char*L){
	Pk[0]=Pk[1]=0;
	for(Obj*h=P->n;h;){
		Obj*n=h;
		h=h->n;
		free(n);
	}
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

void del(Obj*o){
	for(Obj*n=P;;n=n->n)
		if(n->n==o){
			n->n=o->n;
			free(o);
			return;
		}
}

int anybut(char t,float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->t!=t&&n->x==x&&n->y==y)
			return 1;
	return 0;
}

int any(float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->x==x&&n->y==y)
			return 1;
	return 0;
}
int main(int argc,char**argv){
	glfwInit();
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	{GLFWvidmode gvm;
	glfwGetDesktopMode(&gvm);
	int wihe=gvm.Height>1024?1024:gvm.Height>512?512:256;
	glfwOpenWindow(wihe,wihe,0,0,0,0,0,0,GLFW_WINDOW);
	glOrtho(0,64,64,0,1,-1);
	glPointSize(wihe/512);}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glGenTextures(1,&Ts);
	glBindTexture(GL_TEXTURE_2D,Ts);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,gF,gW,gH,0,gF,GL_UNSIGNED_BYTE,g);
	P=makeObj(0,0,0,0,"");
	P->n=0;
	if(argc>1)LL+=atoi(argv[1]);
	loadL(*LL);
	srand(glfwGetTime()*10e6);
	for(;;){
		if(P->y>64||glfwGetKey(GLFW_KEY_SPACE))loadL(*LL);
		Kv=glfwGetKey(GLFW_KEY_DOWN)-glfwGetKey(GLFW_KEY_UP);
		Kh=glfwGetKey(GLFW_KEY_RIGHT)-glfwGetKey(GLFW_KEY_LEFT);
		if(Kh)Kp=Kh==1;
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		for(Obj*n=P;n;n=n->n){
			gomo:switch(n->t){
			Obj*o;
			case(0)
				if(n->x!=(int)n->x){
					walk:n->x+=Pd/8.;
				}else if(!Pu&&((o=oat(8,n->x,n->y+1))||Kh)){
					Pd=Kh;
					if(o)Pd+=o->d[1]?-1:1;
					int pd=Pd>0?1:Pd<0?-1:0;
					if(!((o=oat(7,n->x+pd,n->y))&&pd!=(o->d[0]?:-1)||oat(2,n->x+pd,n->y)||oat(3,n->x+pd,n->y)||oat(8,n->x+pd,n->y))){
						if(o=oat(10,n->x+pd,n->y)){
							if(Pk[o->d[0]]){
								Pk[o->d[0]]--;
								del(o);
							}else goto nokey;
						}
						goto walk;
					}
					nokey:;
				}else if(Kv&&((oat(5,n->x,n->y)&&!any(n->x,n->y+Kv))||(oat(4,n->x,n->y)&&!(oat(2,n->x,n->y+Kv)||oat(3,n->x,n->y+Kv)||oat(8,n->x,n->y+Kv)))&&!(((o=oat(6,n->x,n->y+Kv))&&Kv==(o->d[0]?:-1))||oat(8,n->x,n->y+Kv)||oat(10,n->x,n->y+Kv)))){
					Pu=Kv;
					goto vert;
				}else if(Kv==-1&&(o=oat(6,n->x,n->y))&&o->d[0]==1&&!(oat(2,n->x,n->y-1)||oat(3,n->x,n->y-1)||oat(8,n->x,n->y-1))){
					Pu=-1;
					goto vert;
				}else if(Kv==1&&!(oat(2,n->x,n->y+1)||oat(3,n->x,n->y+1)||oat(8,n->x,n->y+1))&&(((o=oat(6,n->x,n->y))&&o->d[0]==0||(o=oat(6,n->x,n->y+1))&&o->d[0]==0)||(oat(4,n->x,n->y+1)&&!(oat(5,n->x,n->y)||((o=oat(6,n->x,n->y))&&o->d[0]==1))))){
					Pu=1;
					goto vert;
				}
				if(oat(1,n->x,n->y)){
					loadL(*++LL);
				}
				if(o=oat(3,n->x,n->y+1)){
					if(!(o->d[0]+=4))
						del(o);
					if(rand()&1){
						o=makeObj(11,n->x+(rand()&7)/8.,n->y,8,"01234567");
						o->n=P->n;
						P->n=o;
						((float*)o->d)[0]=-(rand()&255)/4096.;
						((float*)o->d)[1]=(4-(rand()%9))/96.;
					}
				}
				if((o=oat(9,n->x,n->y))||(!anybut(0,n->x,n->y)&&(o=oat(9,n->x,n->y+1)))){
					Pk[o->d[0]]++;
					del(o);
				}
				if(o=oat(10,n->x,n->y+1)){
					if(Pk[o->d[0]]){
						Pk[o->d[0]]--;
						del(o);
					}
				}
				if(n->y!=(int)n->y){
					vert:
					if(o=oat(5,n->x,n->y))
						o->y+=Pu/8.;
					n->y+=Pu/8.;
				}else if(n->x==(int)n->x&&!any(n->x,n->y+1)&&!anybut(0,n->x,n->y)){
					Pu=4;
					goto vert;
				}else Pu=0;
				drawRect_(n->x,n->y,0,0,Kp,0);
			case(1)drawRect(n->x,n->y,2,0);
			case(2)drawRect(n->x,n->y,0,3);
			case(3)drawRect(n->x,n->y,n->d[0]>>5,2);
			case(4)drawRect(n->x,n->y,3,0);
			case(5)
				int y=n->y;
				n->d[0]-=n->d[0]>0;
				n->d[1]+=n->d[1]<255;
				int lo,hi;
				for(int lo=y-1;lo>=n->d[0]>>2;lo--){
					if(anybut(0,n->x,lo)){
						n->d[0]=4+lo*4;
						break;
					}
				}
				for(int hi=y+1;hi<=n->d[1]>>2;hi++){
					if(anybut(0,n->x,hi)){
						n->d[1]=hi*4;
						break;
					}
				}
				glEnd();
				glBindTexture(GL_TEXTURE_2D,0);
				glBegin(GL_POINTS);
				for(int i=n->d[0];i<n->d[1];i++){
					if(i/4.<n->y||i/4.>=n->y+1){
						glVertex2f(n->x,i/4.+1./8);
						glVertex2f(n->x+1,i/4.+1./8);
					}
				}
				glEnd();
				glBindTexture(GL_TEXTURE_2D,Ts);
				glBegin(GL_QUADS);
				drawRect(n->x,n->y,6,0);
			case(6)drawRect_(n->x,n->y,5,0,0,n->d[0]);
			case(7)drawRect_(n->x,n->y,4,0,n->d[0],0);
			case(8)drawRect(n->x,n->y,(n->d[0]+=(n->d[1]?4:-4))/43,3);
			case(9)drawRect(n->x,n->y,n->d[0],1);
			case(10)drawRect(n->x,n->y,4+n->d[0],1);
			case(11)
				glEnd();
				glBindTexture(GL_TEXTURE_2D,0);
				glBegin(GL_POINTS);
				glVertex2f(n->x+=((float*)n->d)[1],n->y+=((float*)n->d)[0]+=.02);
				glEnd();
				glBindTexture(GL_TEXTURE_2D,Ts);
				glBegin(GL_QUADS);
				if(n->y>64){
					o=n->n;
					del(n);
					if(n=o)goto gomo;
					goto nomo;
				}
			}
		}
		nomo:glEnd();
		glfwSwapBuffers();
		double gT=1./59-glfwGetTime();
		glfwSleep(gT);
		glfwSetTime(0);
		glfwPollEvents();
		if(glfwGetKey('Q')||!glfwGetWindowParam(GLFW_OPENED))return 0;
	}
}