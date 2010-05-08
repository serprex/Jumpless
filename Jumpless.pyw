#!/usr/bin/env python
from __future__ import division
from pyglet import options as a
a["debug_gl"]=False
from pyglet.gl import glEnable,glDisable,glBlendFunc as awds,glClear,glVertex2f,glBegin,glEnd,glColor3fv,GLfloat as GLF1
from pyglet.clock import set_fps_limit as a,tick,get_fps
a(30)
from pyglet.image import load as ioad,TileableTexture
from pyglet.window import Window as W
from random import randint,random
from os import listdir as LvL
from itertools import cycle,imap as map
from collections import defaultdict
GLF0=(GLF1*3)(0.,0.,0.)
GLF1=(GLF1*3)(1.,1.,1.)
LvL=iter(sorted(LvL for LvL in LvL(".") if LvL.endswith(".txt")))
W=W(style="borderless",vsync=1)
awds=[not not W.set_exclusive_mouse(),not not W.maximize(),not not glEnable(3042),not not awds(768,769)]
@W.event
def on_key_press(k,m):
	if 65360<k<65365:awds[k-65361]=1
	elif k in (65293,32):kenter()
@W.event
def on_key_release(k,m):
	if 65360<k<65365:awds[k-65361]=0
class Obj:
	Z=S=1
	def __init__(s,x,y,*z):
		s.x=x<<3
		s.y=y<<3
		getattr(s,"init",lambda s=s.__class__:hasattr(s,"Img") or setattr(s,"Img",ioad(s.__name__+".bmp").blit))(*z)
	def __call__(s):return
	def blit(s):return s.Img(s.x,s.y)
class Ply(Obj):
	Z=S=-9
	def init(s):
		global P
		P=s
		s.xp=s.x
		s.k=[0,0]
		s.v=s.V=s.e=0
	def __call__(s):
		x=s.x
		y=s.y
		glDisable(3042)
		glColor3fv(GLF0)
		glBegin(7)
		glVertex2f(x-8,y-8)
		glVertex2f(x-8,y+16)
		glVertex2f(x+16,y+16)
		glVertex2f(x+16,y-8)
		glEnd()
		glColor3fv(GLF1)
		gn=ge=gs=gw=Nil
		x16=set(xrange(x-16,x+17))
		y16=set(xrange(y-16,y+17))
		s.e=glEnable(3042)
		for a in obj:
			if a.x in x16 and a.y in y16:
				a.blit()
				if a.x==x:
					if a.y==y:
						if a.__class__ is Ele:s.e=1
						g=a
					elif a.y==y+8:gn=a
					elif a.y==y-8:gs=a
				elif a.y==y:
					if a.x==x+8:ge=a
					elif a.x==x-8:gw=a
		if x&7:s.x-=cmp(s.xp,x)
		else:
			s.xp=x
			if s.V:s.v,s.V=((-8,-6),(-5,-6),(-3,-5),(-3,-4),(-2,-3),(-2,-2))[s.V]
			if not y&7:
				a=g.__class__
				if a in (Lok,Key):
					s.k[g.k]+=(a is Key)or-(a is Lok)
					die.add(g)
					g=s
					a=Ply
					s.V=s.v=0
				elif a is Win:makeLv(LvL.next())
				s.v=awds[1] if a is Uwl else awds[1]-awds[3] if a in (Lad,Ele) else -awds[3] if a is Dwl or gs.__class__ in (Lad,Dwl) else (s.v,)
				setattr(s,"Vv"[s.v.__class__ is tuple],s.v.__class__ is tuple and s.v[0])
				if (gs.__class__ in (Nil,Key) or (gs.__class__ is Lok and s.k[gs.k])) and g is s:
					if not s.V:s.v=s.V=-1
				else:
					a=((gs.__class__ is Rfl)or-(gs.__class__ is Lfl))<<1 or awds[2]-awds[0]
					if not (ge if a>0 else gw).S:s.x+=a
			if (s.v<0 and gs.S) or (s.v>0 and gn.S) or s.x&7:s.V=s.v=0
			s.y+=s.v
			s.y&7 or setattr(s,"vV"[not s.v],0)
		return Fld and glDisable(3042)
	def blit(s,I=(ioad("Plyr.bmp").blit,ioad("Plyl.bmp").blit)):return I[s.xp>s.x](s.x,s.y)
class Wal(Obj):pass
a=[ioad("Fl"+str(i)+".bmp").blit for i in xrange(6)]
RfI=cycle(reversed(a)).next
LfI=cycle(a).next
Lfi=LfI()
Rfi=RfI()
Fld=0
class Rfl(Obj):
	Z=-8
	def init(s):return
	def __call__(s):return Fld and Rfi(s.x,s.y)
	def blit(s):return Rfi(s.x,s.y)
class Lfl(Obj):
	Z=-8
	def init(s):return
	def __call__(s):return Fld and Lfi(s.x,s.y)
	def blit(s):return Lfi(s.x,s.y)
class Opa(Obj):
	def init(s):s.h=7
	def __call__(s):
		if s.y+8==P.y and abs(P.x-s.x)<8:
			s.h-=.31
			s.h<0. and die.add(s)
			deb.append(Deb(s.x+randint(-2,10),s.y))
	def blit(s,I=[ioad("Opa"+str(i)+".bmp").blit for i in xrange(8)]):return I[int(s.h)](s.x,s.y)
class Deb:
	def __init__(s,*x):
		s.x,s.y=x
		s.v=4
	def __call__(s):
		glColor3fv(GLF0)
		glVertex2f(s.x,s.y)
		blt.add((s.x&-8,int(s.y)&-8))
		s.y+=s.v
		s.v-=random()
		if s.v<-8:s.v=-8
		if s.y<-8:die.add(s)
		glColor3fv(GLF1)
		return glVertex2f(s.x,s.y)
class Rwl(Obj):
	def __call__(s):s.S=P.y!=s.y or s.x+8==P.x
class Lwl(Obj):
	def __call__(s):s.S=P.y!=s.y or s.x-8==P.x
class Uwl(Obj):
	def __call__(s):s.S=s.y-8!=P.y
class Dwl(Obj):
	def __call__(s):s.S=s.y+8!=P.y
class Lad(Obj):
	def __call__(s):s.S=P.e and P.y!=s.y
class Key(Obj):
	def init(s,k):s.k=k
	def __call__(s):s.S=P.e and P.y!=s.y
	def blit(s,I=(ioad("Key0.bmp").blit,ioad("Key1.bmp").blit)):I[s.k](s.x,s.y)
class Lok(Obj):
	def init(s,k):s.k=k
	def __call__(s):s.S=not P.k[s.k] or (P.e and P.y!=s.y)
	def blit(s,I=(ioad("Lok0.bmp").blit,ioad("Lok1.bmp").blit)):I[s.k](s.x,s.y)
class Win(Obj):
	Z=-7
	def __call__(s):
		s.S=P.y!=s.y
		return Fld and glEnable(3042)
class Ele(Obj):
	Z=S=0
	def init(s):
		s.T=not any(a.__class__ is Ele and a.x==s.x for a in obj)
		s.Mx=W.height
		s.L=s.Mn=-8
	def __call__(s,o=False,R=TileableTexture.create_for_image(ioad("Eler.bmp")).blit_tiled):
		x=s.x
		if not (o or P.x-16<=x<=P.x+16):return
		if s.L!=len(obj):
			Eleb.add(x)
			s.Mx=W.height
			s.Mn=-8
			for a in obj:a.x==x and EleTst[a.__class__](s,a) and setattr(s,("Mx" if a.y<s.Mx else "y") if a.y>s.y else "Mn" if s.Mn<a.y<s.y else "y",a.y)
			if s.T:
				if s.L==-8:
					s.gMx=s.Mx
					s.gMn=s.Mn
				for a in obj:
					if a.__class__ is Ele and a.x==x and a.y<s.Mn:a.L=a.T=-8
			s.L=len(obj)
		if s.T:
			(s.gMx!=s.Mx or s.gMn!=s.Mn) and Eleb.add(x)
			if s.gMx!=s.Mx:s.gMx-=cmp(s.gMx,s.Mx)<<2
			if s.gMn!=s.Mn:s.gMn-=cmp(s.gMn,s.Mn)<<2
			R(x,s.gMn,0,8,s.gMx-s.gMn)
		if P.x==x and P.y-s.y in (-1,1):
			if not s.y&7:s.L=0
			s.y=P.y
		s.S=P.y!=s.y
	def blit(s,I=ioad("Ele.bmp").blit):
		s(True)
		return I(s.x,s.y)
a=lambda s,a:0
EleTst=defaultdict(lambda:lambda s,a:1,{Key:a,Ply:a,Ele:a,Uwl:lambda s,a:s.y>=a.y,Dwl:lambda s,a:s.y<=a.y})
class Nil:S=0
Nil.__class__=Nil
def makeLv(Lv):
	global kenter,obj,deb
	kenter=lambda:makeLv(Lv)
	deb=[]
	a=[a.rstrip() for a in open(Lv).read().strip("\n").lower().split("\n")]
	w=(W.width>>4)-(max(map(len,a))>>1)
	h=(W.height>>4)+(len(a)>>1)
	obj=[]
	D={"#":Wal,">":Rfl,"<":Lfl,")":Rwl,"(":Lwl,"^":Uwl,"v":Dwl,"=":Ele,"-":Lad,"%":Opa,"!":Win,"@":Ply}
	for y,a in enumerate(a):
		for x,a in enumerate(a):
			if a in D:obj+=D[a](w+x,h-y),
			elif a in ":;.,":obj+=(Key if a in ".," else Lok)(w+x,h-y,a in ";,"),
	obj.sort(key=lambda x:x.Z)
	glClear(16384)
	W.dispatch_events()
	for a in obj:a.blit()
	W.flip()
Eleb=set()
makeLv(LvL.next())
c=5
try:
	while not W.has_exit:
		c-=1
		if not c:
			Fld=c=5
			Lfi=LfI()
			Rfi=RfI()
		tick()
		P.y==-8 and kenter()
		W.dispatch_events()
		if Eleb:
			glDisable(3042)
			glColor3fv(GLF0)
			glBegin(7)
			for die in Eleb:
				glVertex2f(die,0.)
				glVertex2f(die+8,0.)
				glVertex2f(die+8,W.height)
				glVertex2f(die,W.height)
			glEnd()
			glColor3fv(GLF1)
			glEnable(3042)
			for a in obj:a.x in Eleb and a.blit()
			Eleb.clear()
		die=set()
		for a in obj:a()
		Fld=0
		for a in die:obj.remove(a)
		if deb:
			die.clear()
			blt=set()
			glDisable(3042)
			glBegin(0)
			for a in deb:a()
			glEnd()
			glEnable(3042)
			for a in die:deb.remove(a)
			for a in obj:(a.x,a.y) in blt and a.blit()
		W.flip()
finally:W.close()
