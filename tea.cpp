#include<assert.h>
#include<errno.h>
#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<unistd.h>

// macro

#define ctrl_key(x) ((x)&0x1f)
#define max(x,y) ((x)<(y)?(y):(x))
#define min(x,y) ((x)<(y)?(x):(y))

// data

struct editor_config{
	termios origin;
	int row,col;
	int cx,cy;
};

struct optbuf{
	char *b;
	int l;
};

editor_config editor;

// term

void real_coder_wont_die(const char *s){
	write(STDOUT_FILENO,"\x1b[2J",4);
	write(STDOUT_FILENO,"\x1b[1;1H",6);
	perror(s);
	assert(0);
}

void reset_raw_mode(){
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&editor.origin)==EOF){
		real_coder_wont_die("tcsetattr0");
	}
}

void set_raw_mode(){
	if(tcgetattr(STDIN_FILENO,&editor.origin)==EOF){
		real_coder_wont_die("tcsetattr1");
	}	termios x(editor.origin);
	x.c_iflag^=IXON;
	x.c_lflag^=ECHO|ICANON|ISIG;
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&x)==EOF){
		real_coder_wont_die("tcsetattr2");
	}       atexit(reset_raw_mode);
}

char cin(){
	int f;
	char x;
	while((f=read(STDIN_FILENO,&x,1))!=1){
		if(f==EOF&&errno!=EAGAIN){
			real_coder_wont_die("read");
		}
	}       return x;
}

int get_term_size(int *r,int *c){
	winsize ws;
	if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)==-1||ws.ws_col==0){
		return -1;
	}else{
		*r=ws.ws_row;
		*c=ws.ws_col;
		return 0;
	}
}

void buf_push(optbuf *x,char *s,int l){
	char *p((char*)realloc(x->b,x->l+l));
	if(p==NULL){
		p=(char*)malloc(x->l+l);
		if(p==NULL){
			return;
		}	memcpy(p,x->b,x->l);
		free(x->b);
	}	memcpy(p+x->l,s,l);
	x->b=p;
	x->l+=l;
}

void buf_free(optbuf *x){
	free(x->b);
	x->l=0;
}

// input

void key_input(){
	char x(cin());
	if(x=='\033'){
		x=cin();
		if(x==':'){
			x=cin();
			if(x=='w'){
				x=cin();
				if(x=='q'){
					write(STDOUT_FILENO,"\x1b[2J",4);
					write(STDOUT_FILENO,"\x1b[1;1H",6);
					exit(0);
				}
			}else if(x=='q'){
				x=cin();
				if(x=='!'){
					write(STDOUT_FILENO,"\x1b[2J",4);
					write(STDOUT_FILENO,"\x1b[1;1H",6);
					exit(0);
				}
			}
		}
	}else if(x=='h'){
		editor.cx=max(editor.cx-1,0);
	}else if(x=='j'){
		editor.cy=min(editor.cy+1,editor.row-1);
	}else if(x=='k'){
		editor.cy=max(editor.cy-1,0);
	}else if(x=='l'){
		editor.cx=min(editor.cx+1,editor.col-1);
	}
}

// output

void print_row(optbuf *x){
	buf_push(x,"~\x1b[K",4);
	for(int i(1);i<editor.row;i++){
		buf_push(x,"\n",1);
		if(i==editor.row>>1){
			int t(editor.col-20>>1);
			if(t){
				buf_push(x,"~",1);
				t--;
			}	while(t--){
				buf_push(x," ",1);
			}       buf_push(x,"real coder won`t die",20);
		}else{
			buf_push(x,"~",1);
		}
	}
}

void refresh_term(){
	optbuf x{NULL,0};
	buf_push(&x,"\x1b[?25l",6);
	buf_push(&x,"\x1b[1;1H",6);
	print_row(&x);
	char buf[32];
	sprintf(buf,"\x1b[%d;%dH",editor.cy+1,editor.cx+1);
	buf_push(&x,buf,strlen(buf));
	buf_push(&x,"\x1b[?25h",6);
	write(STDOUT_FILENO,x.b,x.l);
	buf_free(&x);
}

// main

void init_editor(){
	editor.cx=editor.cy=0;
	if(get_term_size(&editor.row,&editor.col)==EOF){
		real_coder_wont_die("get term size");
	}
}

signed main(){
	set_raw_mode();
	init_editor();
	char op;
	while(1){
		refresh_term();
		key_input();
	}
	return 0;
}
