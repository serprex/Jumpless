#include "j.h"
Obj*P;
int Pd,Pu,Pk[4],Kv,Kh,Kp,dott,dote;
float*dots;
GLFWwindow*wnd;
Obj*makeObj(char t,float x,float y,char*d){
	Obj*r=malloc(sizeof(Obj)+sizeObj[t]);
	r->t=t;
	r->x=x;
	r->y=y;
	memcpy(r->d,d,sizeObj[t]);
	return r;
}

void loadL(unsigned char*L){
	dott=dote=0;
	memset(Pk,0,sizeof(Pk));
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
		h=h->n=makeObj(*p,Lx+p[1],Ly+p[2],p+3);
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
		if(n->t!=12&&n->t!=t&&n->x==x&&n->y==y)
			return 1;
	return 0;
}

int any(float x,float y){
	for(Obj*n=P;n;n=n->n)
		if(n->t!=12&&n->x==x&&n->y==y)
			return 1;
	return 0;
}
int main(int argc,char**argv){
	glfwInit();
	const GLFWvidmode*gvm=glfwGetVideoMode(glfwGetPrimaryMonitor());
	int wihe=gvm->height>1024?1024:gvm->height>512?512:256;
	wnd=glfwCreateWindow(wihe,wihe,"",0,0);
	glfwMakeContextCurrent(wnd);
	glOrtho(0,64,64,0,1,-1);
	glPointSize(wihe/512);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glGenTextures(1,&Ts);
	glBindTexture(GL_TEXTURE_2D,Ts);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,gF,gW,gH,0,gF,GL_UNSIGNED_BYTE,g);
	P=makeObj(0,0,0,"");
	P->n=0;
	if(argc>1)LL+=atoi(argv[1]);
	loadL(*LL);
	initrand();
	for(;;){
		if(P->y>64||glfwGetKey(wnd,GLFW_KEY_SPACE))loadL(*LL);
		if(glfwGetKey(wnd,GLFW_KEY_ENTER)&&(LL[0][0]||LL[0][1])){
			sleepd(.3);
			loadL(*++LL);
		}
		Kv=glfwGetKey(wnd,GLFW_KEY_DOWN)-glfwGetKey(wnd,GLFW_KEY_UP);
		Kh=glfwGetKey(wnd,GLFW_KEY_RIGHT)-glfwGetKey(wnd,GLFW_KEY_LEFT);
		if(Kh)Kp=Kh==1;
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		for(Obj*n=P;n;n=n->n){
			gomo:switch(n->t){
			Obj*o;
			case(0)
				if(n->x!=(int)n->x){
					walk:n->x+=Pd/8.;
				}else(!Pu&&((!anybut(0,n->x,n->y)&&(o=oat(8,n->x,n->y+1)))||Kh)){
					Pd=Kh;
					if(o)Pd+=o->d[1]?-1:1;
					int pd=(Pd>0)-(Pd<0);
					if(!((o=oat(7,n->x+pd,n->y))&&pd!=(o->d[0]?:-1)||oat(2,n->x+pd,n->y)||oat(3,n->x+pd,n->y)||oat(8,n->x+pd,n->y)||(oat(11,n->x+pd,n->y)&&any(n->x+pd*2,n->y)))){
						if(o=oat(10,n->x+pd,n->y)){
							if(Pk[o->d[0]]){
								Pk[o->d[0]]--;
								del(o);
							}else goto nokey;
						}
						goto walk;
					}
					nokey:;
				}else(Kv&&((oat(5,n->x,n->y)&&!any(n->x,n->y+Kv))||(oat(4,n->x,n->y)&&!(oat(1,n->x,n->y+Kv)||oat(2,n->x,n->y+Kv)||oat(3,n->x,n->y+Kv)||oat(8,n->x,n->y+Kv)))&&!(((o=oat(6,n->x,n->y+Kv))&&Kv==(o->d[0]?:-1))||oat(8,n->x,n->y+Kv)||oat(10,n->x,n->y+Kv)))){
					Pu=Kv;
					goto vert;
				}else(Kv==-1&&(o=oat(6,n->x,n->y))&&o->d[0]==1&&!(oat(1,n->x,n->y-1)||oat(2,n->x,n->y-1)||oat(3,n->x,n->y-1)||oat(8,n->x,n->y-1))){
					Pu=-1;
					goto vert;
				}else(Kv==1&&!(oat(1,n->x,n->y+1)||oat(2,n->x,n->y+1)||oat(3,n->x,n->y+1)||oat(8,n->x,n->y+1))&&(((o=oat(6,n->x,n->y))&&o->d[0]==0||(o=oat(6,n->x,n->y+1))&&o->d[0]==0)||(oat(4,n->x,n->y+1)&&!(oat(5,n->x,n->y)||((o=oat(6,n->x,n->y))&&o->d[0]==1))))){
					Pu=1;
					goto vert;
				}
				if(oat(1,n->x,n->y)){
					loadL(*++LL);
				}
				if(o=oat(3,n->x,n->y+1)){
					if(!(o->d[0]+=4))
						del(o);
					if(randint()&1){
						if(dott==dote)dots=realloc(dots,(dote+=4)*4);
						dots[dott]=n->x+(randbyte()&7)/8.;
						dots[dott+1]=n->y;
						dots[dott+2]=(4-(randto(9)))/96.;
						dots[dott+3]=-(randbyte())/4096.;
						dott+=4;
					}
				}
				if((o=oat(9,n->x,n->y))||(!anybut(0,n->x,n->y)&&(o=oat(9,n->x,n->y+1)))){
					Pk[o->d[0]]++;
					del(o);
				}
				if(!anybut(0,n->x,n->y)&&(o=oat(10,n->x,n->y+1))&&Pk[o->d[0]]){
					Pk[o->d[0]]--;
					del(o);
				}
				if(n->y!=(int)n->y){
					vert:
					if(o=oat(5,n->x,n->y))o->y+=Pu/8.;
					n->y+=Pu/8.;
				}else(n->x==(int)n->x&&!any(n->x,n->y+1)&&!anybut(0,n->x,n->y)){
					Pu=4;
					goto vert;
				}else Pu=0;
				drawRect_(n->x,n->y,0,0,Kp,0);
			case(1)drawRect(n->x,n->y,2,0);
			case(2)drawRect(n->x,n->y,1,0);
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
				if(P->x<n->x&&n->x-P->x<1)n->x=P->x+1;
				else(n->x<P->x&&P->x-n->x<1)n->x=P->x-1;
				else((o=oat(8,n->x,n->y+1))&&!oat(1,n->x+(o->d[1]?2:-2),n->y)&&!oat(2,n->x+(o->d[1]?2:-2),n->y)&&!oat(3,n->x+(o->d[1]?2:-2),n->y))n->x+=(o->d[1]?:-1)/8.;
				drawRect(n->x,n->y,7,3);
				if(n->x==(int)n->x&&!any(n->x,n->y+1))n->y+=.5;
			case(12)
				if(n->x==(int)n->x&&(anybut(0,n->x+(n->d[0]?:-1),n->y)||!anybut(0,n->x+(n->d[0]?:-1),n->y+1)))n->d[0]=!n->d[0];
				n->x+=(n->d[0]?:-1)/8.;
				drawRect_(n->x,n->y,0,0,n->d[0],0);
				if(n->x>P->x-1&&n->x<P->x+1){
					if(n->y==P->y){
						loadL(*LL);
						goto nomo;
					}else(n->y>P->y&&n->y<P->y+1){
					   o=n->n;
					   del(n);
					   if(n=o)goto gomo;
					   goto nomo;
					}
				}
			}
		}
		nomo:glEnd();
		if(dott){
			glBindTexture(GL_TEXTURE_2D,0);
			glBegin(GL_POINTS);
			for(int i=0;i<dott;i+=4){
				glVertex2f(dots[i]+=dots[i+2],dots[i+1]+=dots[i+3]+=.03);
				if(dots[i+1]>64)memmove(dots+i,dots+i+4,((dott-=4)-i)*4);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D,Ts);
		}
		glfwSwapBuffers(wnd);
		endframe(60);
		glfwPollEvents();
		if(glfwGetKey(wnd,'Q')||glfwWindowShouldClose(wnd))return 0;
	}
}