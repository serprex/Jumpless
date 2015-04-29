#include "j.h"
Obj**Ps,*P,*Rost;
int Pp,KT,BT,Ls=sizeof(L)/sizeof(char*)-1,et;
Obj*makeObj(char t,float x,float y,char*d){
	Obj*r=malloc(sizeof(Obj)+sizeObj[t]*2);
	r->t=t;
	r->x=x;
	r->y=y;
	memcpy(r->d,d,sizeObj[t]);
	memcpy(r->d+sizeObj[t],d,sizeObj[t]);
	return r;
}

void drawObj(Obj*n){
	switch(n->t){
	case(0)drawRect(n->x,n->y,0,0);
	case(1)drawRect(n->x,n->y,2,0);
	case(2)drawRect(n->x,n->y,1,0);
	case(3)drawRect(n->x,n->y,n->d[0]++>>5,2);
	case(4)drawRect(n->x,n->y,3,0);
	case(5)drawRect(n->x,n->y,6,0);
	case(6)drawRect_(n->x,n->y,5,0,0,n->d[0]);
	case(7)drawRect_(n->x,n->y,4,0,n->d[0],0);
	case(8)drawRect(n->x,n->y,(n->d[0]+=(n->d[1]?4:-4))/43,3);
	case(9)drawRect(n->x,n->y,n->d[0],1);
	case(10)drawRect(n->x,n->y,4+n->d[0],1);
	case(11)drawRect(n->x,n->y,7,3);
	case(12)drawRect_(n->x,n->y,0,0,1,0);
	}
}

char*chmem[]={"","","","\0","","\0\377","\0","\1","\0","\1","\0\1","\0\0","","\1","\0","\1","\2","\3","\0","\1","\2","\3"},
	chtype[]={0,1,2,3,4,5,6,6,7,7,8,8,11,12,9,9,9,9,10,10,10,10};

void loadL(unsigned char*L){
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

void dat(float x,float y){
	for(Obj*n=P;n->n;n=n->n)
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

void scrollcb(GLFWwindow*wnd, double dx, double dy){
	double sc=dx+dy;
	et+=(sc>0)-(sc<0);
	if(et==sizeof(chtype))et=0;
	else(et==-1)et=sizeof(chtype);
}

int main(int argc,char**argv){
	glfwInit();
	const GLFWvidmode*gvm=glfwGetVideoMode(glfwGetPrimaryMonitor());
	int wihe=gvm->height>1024?1024:gvm->height>512?512:256;
	wnd=glfwCreateWindow(wihe,wihe,"",0,0);
	glfwMakeContextCurrent(wnd);
	glfwSetScrollCallback(wnd,scrollcb);
	glOrtho(0,64,64,0,1,-1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glLogicOp(GL_XOR);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glGenTextures(1,&Ts);
	glBindTexture(GL_TEXTURE_2D,Ts);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,gF,gW,gH,0,gF,GL_UNSIGNED_BYTE,g);
	Ps=malloc(sizeof(Obj*)*Ls);
	for(int i=0;i<Ls;i++){
		Ps[i]=P=makeObj(0,0,0,"");
		P->n=0;
		loadL(LL[i]);
	}
	P=Ps[Pp=0];
	Rost=makeObj(0,0,0,"");
	Obj*ro=Rost;
	for(int i=1;i<sizeof(chtype);i++)
		ro=ro->n=makeObj(chtype[i],i,0,chmem[i]);
	ro->n=0;
	for(;;){
		int b;
		KT-=KT>0;
		BT-=BT>0;
		if((b=glfwGetKey(wnd,GLFW_KEY_RIGHT)-glfwGetKey(wnd,GLFW_KEY_LEFT))&&!KT){
			KT=6;
			Pp+=b;
			if(Pp==Ls)Pp=0;
			else(Pp==-1)Pp=Ls-1;
			P=Ps[Pp];
		}else((b=glfwGetKey(wnd,'X')-glfwGetKey(wnd,'Z'))&&!KT){
			KT=6;
			b+=Pp;
			if(b==Ls)b=0;
			else(b==-1)b=Ls-1;
			P=Ps[Pp];
			Ps[Pp]=Ps[b];
			Ps[Pp=b]=P;
		}else(glfwGetKey(wnd,'N')&&!KT){
			KT=12;
			Ps=realloc(Ps,sizeof(Obj*)*++Ls);
			Ps[Pp=Ls-1]=P=makeObj(0,31,31,"");
			P->n=0;
		}else(glfwGetKey(wnd,GLFW_KEY_BACKSPACE)&&!BT&&Ls>1){
			BT=9;
			memmove(Ps+Pp,Ps+Pp+1,(Ls-Pp-1)*sizeof(Obj*));
			for(Obj*n=P,*o;n;o=n,n=n->n,free(o));
			Ps=realloc(Ps,sizeof(Obj*)*--Ls);
			P=Ps[Pp-=Pp==Ls];
		}
		if((glfwGetMouseButton(wnd,b=0)||glfwGetMouseButton(wnd,b=1)||glfwGetMouseButton(wnd,b=2))&&!BT){
			BT=6;
			Obj*o;
			double dx,dy;
			glfwGetCursorPos(wnd,&dx,&dy);
			int x=dx,y=dy;
			x/=wihe/64;
			y/=wihe/64;
			if(y==0&&x<sizeof(chtype)){
				et=x;
			}else(!et&&b!=2){
				P->x=x;
				P->y=y;
			}else(et&&(o=oat(chtype[et],x,y))){
				del(o);
			}else{
				if(b!=1)dat(x,y);
				if(b!=2){
					o=makeObj(chtype[et],x,y,chmem[et]);
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
		glfwSwapBuffers(wnd);
		sleepd(1./30);
		glfwPollEvents();
		if((glfwGetKey(wnd,'S')||glfwGetKey(wnd,'Q'))&&!KT){
			KT=9;
			FILE*f=fopen("jgen.h","w");
			fputs("unsigned char ",f);
			for(int i=0;i<Ls;i++){
				int mnx=255,mny=255,mxx=0,mxy=0,ns=1;
				for(Obj*n=Ps[i];n;n=n->n){
					ns+=3+sizeObj[n->t];
					if(n->x<mnx)mnx=n->x;
					if(n->x>mxx)mxx=n->x;
					if(n->y<mny)mny=n->y;
					if(n->y>mxy)mxy=n->y;
				}
				fprintf(f,"L%x[%d]=\"\\%o\\%o\\%o\\%o",i,ns,mxx-mnx,mxy-mny,(int)Ps[i]->x-mnx,(int)Ps[i]->y-mny);
				for(Obj*n=Ps[i]->n;n;n=n->n){
					fprintf(f,"\\%o\\%o\\%o",n->t,(int)n->x-mnx,(int)n->y-mny);
					for(int i=0;i<sizeObj[n->t];i++)
						fprintf(f,"\\%o",n->d[i+sizeObj[n->t]]);
				}
				fputs("\",",f);
			}
			fprintf(f,"*L[%d]={",Ls+1);
			for(int i=0;i<Ls;i++)
				fprintf(f,"L%x,",i);
			fputs("\"\\0\\0\\0\"},**LL=L;",f);
			fclose(f);
		}
		if(glfwGetKey(wnd,'Q')||glfwWindowShouldClose(wnd))return 0;
	}
}