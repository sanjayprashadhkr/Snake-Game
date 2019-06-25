#include<stdio.h>
#include<conio.h>
#include<bios.h>
#include<stdlib.h>
#include<process.h>
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define DIM 7
#define WIDTH 5
#define HEIGHT 1
#define VL 179
#define HL 196
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define TT 194
#define BT 193
#define LST 180
#define RST 195
#define CROSS 197
#define BS 8
#define SP 32
#define LEFT 19200
#define RIGHT 19712
#define UP 18432
#define DOWN 20480
#define ESC 283
#define HOME 18176
#define END 20224
#include<dos.h>
#include<time.h>
typedef struct orb
{
	int posx;
	int posy;
	struct orb* prev;
	struct orb* next;
}ORB;
ORB *head=NULL;
int bodylength=0,snake_direction=RIGHT;
void drawmaze();
int s_pos[2]={38,12};
void insertorb();
void debug();
void display_snake();
void movesnake(int);
int isgameover();
int* generatefruit();
int gameover=0;
int main()
{
	int key,*fruitpos,fx,fy;
	clrscr();
	srand(time(0));
	insertorb();
	insertorb();
	insertorb();
	insertorb();
	insertorb();
	display_snake();
	fruitpos=generatefruit();
	/*while(1)
	{
		delay(100);
		generatefruit();
	}*/
	fx=fruitpos[0];
	fy=fruitpos[1];
	drawmaze();
	gotoxy(s_pos[0],s_pos[1]);
	key=RIGHT;
	do
	{
		key=bioskey(0);
		while(!bioskey(1))
		{
			delay(200);
			//key=bioskey(1);
			if(key==RIGHT)
			{
				snake_direction=RIGHT;
				clrscr();
				gotoxy(fx,fy);
				printf("F");
				drawmaze();
				movesnake(RIGHT);
				if(isgameover())
					break;
				if(head->posx==fx && head->posy==fy)
				{
					generatefruit();
					fx=fruitpos[0];
					fy=fruitpos[1];
					insertorb();
				}
				display_snake();
			}
			else if(key==LEFT)
			{
				snake_direction=LEFT;
				clrscr();
				gotoxy(fx,fy);
				printf("F");
				drawmaze();
				movesnake(LEFT);
				if(isgameover())
					break;
				if(head->posx==fx && head->posy==fy)
				{
					generatefruit();
					fx=fruitpos[0];
					fy=fruitpos[1];
					insertorb();
				}
				display_snake();
			}
			else if(key==UP)
			{
				snake_direction=UP;
				clrscr();
				gotoxy(fx,fy);
				printf("F");
				drawmaze();
				movesnake(UP);
				if(isgameover())
				{
					break;
				}
				if(head->posx==fx && head->posy==fy)
				{
					generatefruit();
					fx=fruitpos[0];
					fy=fruitpos[1];
					insertorb();
				}
				display_snake();
			}
			else if(key==DOWN)
			{
				snake_direction=DOWN;
				clrscr();
				gotoxy(fx,fy);
				printf("F");
				drawmaze();
				movesnake(DOWN);
				if(isgameover())
					break;
				if(head->posx==fx && head->posy==fy)
				{
					generatefruit();
					fx=fruitpos[0];
					fy=fruitpos[1];
					insertorb();
				}
				display_snake();
			}
		}
	}while(key!=ESC && gameover!=1);
	if(gameover==1)
	{
		getch();
		gotoxy(32,12);
		printf("GAME OVER!!!");
	}
	getch();
	return 0;
}
int isgameover()
{
	int miny=2,maxy=22,minx=2,maxx=75;
	if(head->posx==minx || head->posx==maxx)
	{
		gameover=1;
		return 1;
	}
	else if(head->posy==miny || head->posy==maxy)
	{
		gameover=1;
		return 1;
	}
	return 0;

}
int* generatefruit()
{
	int fruitpos[2]={0},flag=0;
	ORB *temp=head;
	int fruitx,fruity,minx=3,miny=3,maxx=74,maxy=21;
	do
	{
		fruitx=(rand()%(maxx-minx+1))+minx;
		fruity=(rand()%(maxy-miny+1))+miny;
		while(temp!=NULL)
		{
			if(temp->posx==fruitx && temp->posy==fruity)
			{
				flag=0;
				break;
			}
			else
			{
				flag=1;
			}
			temp=temp->next;
		}
	}while(flag!=1);
	fruitpos[0]=fruitx;
	fruitpos[1]=fruity;
	gotoxy(fruitx,fruity);
	printf("F");
	return fruitpos;
}
void movesnake(int key)
{
   ORB* temp=head;
   int savex=temp->posx,savey=temp->posy,newposx,newposy;
   if(key==RIGHT)
   {
	newposy=(head->posy);
	newposx=(head->posx)+1;
	while(temp!=NULL)
	{
		savex=temp->posx;
		savey=temp->posy;
		temp->posx=newposx;
		temp->posy=newposy;
		newposx=savex;
		newposy=savey;
		temp=temp->next;
	}
   }
   else if(key==LEFT)
   {
	newposy=(head->posy);
	newposx=(head->posx)-1;
	while(temp!=NULL)
	{
		savex=temp->posx;
		savey=temp->posy;
		temp->posx=newposx;
		temp->posy=newposy;
		newposx=savex;
		newposy=savey;
		temp=temp->next;
	}
   }
   else if(key==DOWN)
   {
	newposy=(head->posy)+1;
	newposx=(head->posx);
	while(temp!=NULL)
	{
		savex=temp->posx;
		savey=temp->posy;
		temp->posx=newposx;
		temp->posy=newposy;
		newposx=savex;
		newposy=savey;
		temp=temp->next;
	}
   }
    else if(key==UP)
   {
	newposy=(head->posy)-1;
	newposx=(head->posx);
	while(temp!=NULL)
	{
		savex=temp->posx;
		savey=temp->posy;
		temp->posx=newposx;
		temp->posy=newposy;
		newposx=savex;
		newposy=savey;
		temp=temp->next;
	}
   }
}
void display_snake()
{
   ORB* temp=head;
   while(temp!=NULL)
   {
	gotoxy(temp->posx,temp->posy);
	printf("O");
	temp=temp->next;
   }
}
void insertorb()
{
	ORB* neworb=(ORB*)malloc(sizeof(ORB));
	neworb->next=NULL;
	neworb->prev=NULL;
	//neworb->dat=bodylength;
	int headposx=38,headposy=12;
	if(head==NULL)
	{
		neworb->posx=38;
		neworb->posy=12;
		head=neworb;
	}
	else
	{
		//bodylength++;
		ORB* temp=head;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=neworb;
		neworb->prev=temp;
		if(snake_direction==RIGHT)
		{
			neworb->posx=(temp->posx)-1;
			neworb->posy=(temp->posy);
		}
		else if(snake_direction==LEFT)
		{
			neworb->posx=(temp->posx)+1;
			neworb->posy=(temp->posy);
		}
		if(snake_direction==UP)
		{
			neworb->posx=(temp->posx);
			neworb->posy=(temp->posy)+1;
		}
		if(snake_direction==DOWN)
		{
			neworb->posx=(temp->posx);
			neworb->posy=(temp->posy)-1;
		}
	}
}

void drawmaze()
{
	int i;
	int count,MAZE_HEIGHT=21,MAZE_WIDTH=75;
	int bcol=(80-MAZE_WIDTH)/2,brow=(25-MAZE_HEIGHT)/2;
	//TOP LINE
	gotoxy(bcol,brow);
	printf("%c",LT);
	for(i=bcol+1;i<MAZE_WIDTH;i++)
	{
		gotoxy(i,2);
		printf("%c",HL);
	}
	printf("%c",RT);
	for(count=1;count<=MAZE_HEIGHT-2;count++)
	{
		bcol=(80-MAZE_WIDTH)/2;
		gotoxy(bcol,++brow);
		printf("%c",VL);
		bcol+=(MAZE_WIDTH-bcol);
		gotoxy(bcol,brow);
		printf("%c",VL);
	}
	bcol=(80-MAZE_WIDTH)/2;
	gotoxy(bcol,++brow);
	printf("%c",LB);
	for(i=bcol+1;i<MAZE_WIDTH;i++)
	{
		printf("%c",HL);
	}
       printf("%c",RB);
}