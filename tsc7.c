#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<time.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//����ڵ����� 
typedef struct _snake_t
{
	int x;
	int y;
	struct _snake_t *next;
}snake_t;
typedef struct inf{
    char name[30];
    int score;
}inf;

typedef struct list{
    inf data;
    struct list* next;
}list;

list*L;
inf new_info;
int current =0;
char exitFlag = 1;
int number=0;
int score = 0;
int add = 1;
int direction = RIGHT;
int sleepTime = 350;
int endStatus = 0;


snake_t *head = NULL;
snake_t *foodNode = NULL;
snake_t *save = NULL;

//�������� 
int Setcolor(int c); 
int printsnake(void);
int WelcomeGame(void);
int aboutGame(void);
int RunningGame(void);
int printMap(void);
int showScoreTips(void);
int readFile(void);
int initSnake(void);
int randFood(void);
int moveSnake(void);
int moveKeyControl(void);
int speedUp(void);
int speedDown(void);
int isHitWall(void);
int isHitSelf(void);
void printFailed(void);
int endGame(void);
int writeFile(int score);
int desSnake(void);


//������ɫ 
int Setcolor(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}
//��λ���� 
int Setcursor(int x,int y){

	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}
//��ӭ�����ߵĻ滭 
int printsnake(void)
{
	//���� 
	system("cls");
	

	Setcursor(35,1);
	Setcolor(6);
	printf("/^\\/^\\");
	
	Setcursor(34,2);
	printf("|__|  0|");
	
	Setcursor(33,2);
	Setcolor(2);
	printf("_");
	
	Setcursor(25,3);
	Setcolor(12);
	printf("\\/");
	
	Setcursor(31,3);
	Setcolor(2);
	printf("/");
	
	Setcursor(37,3);
	Setcolor(6);
	printf("\\_/");
	
	Setcursor(41,3);
	Setcolor(10);
	printf("\\");
	
	Setcursor(26,4);
	Setcolor(12);
	printf("\\______");
	
	Setcursor(32,4);
	printf("___________/");
	
	Setcursor(31,4);
	Setcolor(2);
	printf("|");
	
	Setcursor(43,4);
	Setcolor(10);
	printf("\\");
	
	Setcursor(32,5);
	Setcolor(12);
	printf("\\________");
	
	Setcursor(44,5);
	Setcolor(10);
	printf("\\");
	
	Setcursor(39,6);
	Setcolor(12);
	printf("/       /                    \\");
	
	Setcursor(38,7);
	printf("/       /                     \\");
	
	Setcursor(37,8);
	printf("/       /                      \\ \\");
	
	Setcursor(35,9);
	printf("/      /                         \\ \\");
	
	Setcursor(34,10);
	printf("/      /                           \\ \\");
	
	Setcursor(33,11);
	printf("/      /              _===_          \\ \\");
	
	Setcursor(32,12);
	printf("/      /           _=-     -=_         |  |");
	
	Setcursor(31,13);
	printf("(      (         _=-    _==_   -=_    _/    |");
	
	Setcursor(32,14);
	printf("\\     -=____=-    _-=   =-_    =-_-=      /");
	
	Setcursor(33,15);
	printf("=-_           _-=         =-_        _-=");
	
	Setcursor(35,16);
	printf("=--________-=               =-____-=");
	
	return 0;

}
//��ӭ���� 
int WelcomeGame(void)
{
	printsnake();
	Setcolor(11);
	Setcursor(45,18);
	printf("̰����");/*printf����*/
	Setcolor(14);
	int i,j;
	int n=0;
	for(i = 20; i <= 26; i++)
	{
		for(j = 27; j <= 74; j++)
		{
			if(i == 20 || i == 26)
			{
				Setcursor(j,i);
				printf("-");
			}
			else if(j == 27 || j==74)
			{
				Setcursor(j,i);
				printf("|");
			}
		}
	}
	Setcolor(13);
	

	Setcursor(35,22);
	printf("1, ��Ϸ��ʼ");
	
	Setcursor(55,22);
	printf("2, ��Ϸ˵��");
	
	Setcursor(35,24);
	printf("3, �˳���Ϸ");
	
	Setcursor(55,24);
	printf("4, �ɼ���ѯ");
	
	Setcolor(15);
	Setcursor(27,27);
	printf("��ѡ��:1,2,3,4:  ");
	
	scanf("%d",&n);
	getchar();
	return n;

}
//��Ϸ˵�� 
int aboutGame(void)
{
	int i,j;
	system("cls");
	Setcolor(11);
	for(i=6;i<=22;i++)
	{
	for(j=20;j<=90;j++)
		{
			if(i==6||i==22)
			{
				Setcursor(j,i);
				printf("=");
				

			}
			else if(j==20||j==90)
			{
				Setcursor(j,i);
				printf("|");
			}
	
		}
	}
	
	Setcolor(3);
	Setcursor(30,8);
	printf("1,����ײ��ǽ�����Լ�");
	
	Setcolor(5);
	Setcursor(30,11);
	printf("2,��Shift����,��Ctrl����");
	
	Setcolor(11);
	Setcursor(30,14);
	printf("3,���¿ո����ͣ��Ϸ�������Ϸ");
	
	Setcolor(13);
	Setcursor(30,17);
	printf("4,�÷���������ƶ�����");
	
	Setcolor(14);
	Setcursor(30,20);
	printf("5,����ESC�˳���Ϸ");
	
	Setcolor(12);
	Setcursor(20,24);
	printf("����Enter����");
	
	return 0;

}
//�ɼ���ѯ 
int aboutgrade()
{
	int i,j;
	system("cls");
	Setcolor(11);
	for(i=6;i<=22;i++)
	{
	for(j=20;j<=90;j++)
		{
			if(i==6||i==22)
			{
				Setcursor(j,i);
				printf("=");
				
			}
			else if(j==20||j==90)
			{
				Setcursor(j,i);
				printf("|");
			}

		}
	}
	Setcursor(38,5);
	printf("��ѯ��ʷ�ɼ����������մӸߵ�������\n");
	Setcursor(21,7);
	return 0;	
}
/*�����ֺ���*/ 
void read_line(char str[], int n)
{
	int ch, i = 0;
 
	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return;
}
/*���溯��*/
int save_to_file(list *L) {
    if(L == NULL)
        return 0;
    list *p = L->next;
    FILE *fp;
    if ((fp = fopen("rank.txt", "w")) == NULL)
    {
        printf("��ʾ�����ܴ��ļ�\n");
        return 0;
    }
    int save_count = 0;
    while (p != NULL)
    {
        fprintf(fp, "%s\t", p->data.name);
        fprintf(fp, "%d\n", p->data.score);
        p = p->next;
        save_count++;
    }
    fclose(fp);
    return save_count;
} 
/*�ͷ��ڴ�*/
void destory_list(list **L) {
	if (L == NULL || *L == NULL)
		return;
	list *pre = *L, *p = (*L)->next;
	while(p!=NULL){
        pre->next=NULL;
        free(pre);
        pre=p;
        p=p->next;
        
    }
    free(pre);
    pre=NULL;
     number=0;
    (*L)=NULL;
} 
/*��ʼ������ȡ���еļ�¼,����ֵ����������Ƿ�ɹ�*/
list* innert(list**L){  
FILE*fp;
inf p;
list*new_node,*last=NULL;
(*L)=(list*)malloc(sizeof(list));
(*L)->next=NULL;
last=(*L);


fp=fopen("rank.txt","r");
if(fp==NULL){
    printf("δ���������ļ���\n");
    return NULL;
}
else{
    fgetc(fp);
    if(!feof(fp)){
        while(!feof(fp)){
            fseek(fp,-1,SEEK_CUR); 
            fscanf(fp,"%s",p.name);
            fscanf(fp,"\t%d\n",&p.score);
            new_node=(list*)malloc(sizeof(list));
            new_node->data=p;
            last->next=new_node;
            last=new_node;
            number++;
            fgetc(fp);

            }
    
        }
    }

fclose(fp);
last->next=NULL;
last=(*L);
printf("�ɼ���¼�����ѽ���������%d����¼��\n",number);
    return (*L);
}
/*�ֶ������¼�¼*/
inf read_score_info(){
	inf new_info;
	printf("������Ҫ����ķ�����Ϣ��\n");
	printf("��ս��:");
	 read_line(new_info.name,30);
	printf("������");
	scanf("%d",&new_info.score);
	return new_info;
}
 
 
 
 void insert_item(list *L, inf new_info){
  	list*temp;
   	list*pre=L;
	list*p=L->next;
   
 
   
       
               while(p!=NULL){
                    pre=pre->next;
                    p=p->next;
               }
                temp=(list*)malloc(sizeof(list));
                temp->data=new_info;
                pre->next=temp;
                temp->next=p;
                number++;
                return;
        
	
       
}
/*����Ѱ�Ҽ�¼���ҷ����ʼ��������м�¼��������ˣ���������Ҳû��ϵ���͵�ʡ���Լ������ҵ�ʱ��*/
list* search(list*L,char*name){/*����ط�͵����ûд�������ֵĺ��������β�*/
	list*p=L->next;
    while(p!=NULL){
        if(!strcmp(p->data.name,name)){
            return p;
        }
        p=p->next;
    }
    return NULL;
}
/*ð������*/
void bubble_sort(list*L) {
    FILE*fp;
	list *p;
    inf temp;
	fp=fopen("rank.txt","w+");
    int n = number;
    int i, j;
    
    if (L == NULL || L->next == NULL){
    Setcursor(21,9);
        printf("��ǰ������û�м�¼\n");}
    for (j = 1; j < n; ++j) {
        p = L->next;
        for (i = 0; i < n - j; ++i) {
            if (p->data.score > p->next->data.score) {
                 temp=p->data;
                p->data=p->next->data;
                p->next->data=temp;
            }
            p = p->next;
        }
    }
    	p=L->next;
		while(p!=NULL){
        
		fprintf(fp,"%s\t",p->data.name);
        fprintf(fp,"%d\n",p->data.score);
        p=p->next;
    }
   	p=L->next;
    while(p!=NULL){
	
    printf("��ս��%s�ĵ÷�Ϊ%d\n",p->data.name,p->data.score);
	p=p->next;
}
	fclose(fp);

    
}

//�����߿���ʱ���ã�
int RunningGame(void) 
{
	system("cls");
	Setcolor(12);
	int i,j;
	for(i=0;i<=28;i++)
	{
	for(j=0;j<=80;j++)
		{
			if(i==0||i==28)
			{
				Setcursor(j,i);
				printf("-");
				

			}
			else if(j==0||j==80)
			{
				Setcursor(j,i);
				printf("|");
			}
	
		}
	}
	return 0;

}
//�����ϸ�����   ���Ƶ�ͼ 
int printMap(void)
{
	int i=0;
	int j=0;
	system("cls");
	

	for(i=0;i<=26;i++)
	{
		for(j=0;j<=56;j=j+2)
		{
			Setcursor(j,i);
			if(0==i || 26==i || 0==j || 56==j)
			{
				Setcolor(12);
				printf("��");
			}
			else
			{
				Setcolor(7);
				printf("��");
			}
		}
	}
	//�Ľ��趨 
	Setcolor(11);
		Setcursor(0,0);
		printf("��");
		
		Setcursor(56,0);
		printf("��");
		
		Setcursor(0,26);
		printf("��");
		
		Setcursor(56,26);
		printf("��");

}
//��Ϸ��ע�� 
int showScoreTips(void)
{	
	int highScore=0;
	

	highScore=readFile();
	
	Setcolor(3);
	Setcursor(64,4);
	printf("**��ߵ÷ּ�¼: %d",highScore);
	
	Setcolor(7); 
	Setcursor(64,8);
	printf("�÷�: %d",score);
	
	Setcolor(12);
	Setcursor(72,11);
	printf("�� ܰ �� ʾ");
	
	Setcolor(13);
	Setcursor(64,14);
	printf("*�Ե�ÿ��ʳ��÷֣�%d��",add);
	 
	Setcursor(64,16);
	printf("*����ײ��ǽ�ڣ�����ҧ���Լ�");
	
	Setcursor(64,18);
	printf("*Shift����ǰ����Ctrl����ǰ��");
	
	Setcursor(64,20);
	printf("*ʹ�ÿո����ͣ��Ϸ�ͼ�����Ϸ");
	
	Setcursor(64,22);
	printf("*ʹ�á�����������ǰ���ķ���");
	
	Setcursor(64,24);
	printf("*����ESC���˳���Ϸ"); 
	
	Setcursor(64,26);
    printf("������Ϸ����������������ͳɼ��Խ�������");
}
//��ȡ�ļ�����߷֣� 
int readFile()
{
	int ret=-1;
	FILE *fp=NULL;
	char buf[32];
	

	fp=fopen("save.txt","r");
	if(NULL==fp)
	{
		printf("fopen failed.\n");
		return 0;
	}
	//���㷽ʽ 
	memset(buf,0,sizeof(buf));
	ret=fread(buf,sizeof(char),sizeof(buf),fp);
	if(ret<=0)
	{
		printf("fread failed.\n");
		return 0;
	}
	
	fclose(fp);
	
	return atoi(buf);

}
//�����ļ�����߷֣� 
int writeFile(int score)
{
	FILE *fp=NULL;
	

	fp=fopen("save.txt","w+");
	if(fp==NULL)
	{
		printf("File opening failed.\n");
		return -1;
	}
	
	fprintf(fp,"%d",score);
	
	fclose(fp);
	
	return 0;

}
//�ߵĳ�ʼ�� 
int initSnake(void)
{
	int i=0;
	

	snake_t *hed =NULL;
	snake_t *tmp =NULL;
	
	for(i=0;i<4;i++)
	{
		hed = (snake_t*)malloc(sizeof(snake_t));
		if(NULL==hed)
		{
			printf("malloc initSnake failed.\n");
			return -1;
		}
		memset(hed,0,sizeof(snake_t));
		//�ߵĳ�ʼλ��ȷ�� 
		hed->x=24+(i*2);
		hed->y=5;
		
		hed->next=head;
		head=hed;
	}
	
	tmp=head;
	
	while(NULL != tmp)
	{
		Setcolor(14);
		Setcursor(tmp->x,tmp->y);
		//���� 
		if(head==tmp)
		{
			printf("O");
		}
		else
		{
		printf("o");
		}
		tmp = tmp->next;
	}

}
//�������ʳ�� 
int randFood(void)
{
	snake_t *tmp=NULL;
	foodNode=(snake_t*)malloc(sizeof(snake_t));
	if(NULL==foodNode)
	{
		Setcursor(1,28);
		printf("malloc failed.\n");
		return -1;
	}
	memset(foodNode,0,sizeof(snake_t));
	

	while(1)
	{


	
		while(1)
		{
			foodNode->x=rand() % 53 + 2 ;
			
			if(0==foodNode->x % 2)
			{
				break;
			}
	 	}
			foodNode->y=rand() % 25 + 1 ;
		
			tmp=head;
			while(NULL!=tmp)
			{
				if((foodNode->x==tmp->x) && (foodNode->y==tmp->y))
				{
					break;
				}
				tmp=tmp->next;
			}
			if(NULL==tmp)
			{
				Setcursor(foodNode->x,foodNode->y);
				Setcolor(13);
				printf("@");
				break;
			}
			else
			{
				continue;
			}
	}

}
//�ߵ��ƶ� 
int moveSnake(void)
{
	snake_t *hed=NULL;
	snake_t *tmp=NULL;
	

	hed=(snake_t*)malloc(sizeof(snake_t));
	if(NULL==hed)
	{
		printf("malloc failed.\n");
		return -1;
	}
	memset(hed,0,sizeof(snake_t));
	//�ߵķ��� 
	if(UP==direction)
	{
		hed->x=head->x;
		hed->y=head->y-1;
	}
	if(DOWN==direction)
	{
		hed->x=head->x;
		hed->y=head->y+1;
	}
	if(LEFT==direction)
	{
		hed->x=head->x-2;
		hed->y=head->y;
	}
	if(RIGHT==direction)
	{
		hed->x=head->x+2;
		hed->y=head->y;
	}
	
	hed->next=head;
	head=hed;
	
	tmp=head;
	Setcolor(14);
	
	if((hed->x==foodNode->x) && (hed->y==foodNode->y))
	{
		while(NULL!=tmp)
		{
			Setcursor(tmp->x,tmp->y);
			if(head==tmp)
			{
				printf("O");
			}
			else
			{
				printf("o");
			}
			
			tmp=tmp->next;
		}
		//��ʳ��ӷ� 
		score=score+add;
		
		randFood();
	}
	else
	{
		while(NULL!=tmp->next)
		{
			save=tmp->next;
			Setcursor(tmp->x,tmp->y);
			if(head==tmp)
			{
				printf("O");
			}
			else
			{
				printf("o");
			}
			save=tmp;
			tmp=tmp->next;
		}
		//����β�滻Ϊ ��
		Setcursor(tmp->x,tmp->y);
		Setcolor(7);
		printf("��");
		
		save->next=NULL;
		
		free(tmp);
	}

}
//�������� 
int moveKeyControl(void)
{		
	//��ʼ�������� 
	direction=RIGHT;
	while(1)
	{
		showScoreTips();
		

		//���밴������ ��GetAsyncKeyState(VK_  �� 
		if(GetAsyncKeyState(VK_UP) && direction != DOWN)
		{
			direction=UP;
		}
		if(GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction=DOWN;
		}
		if(GetAsyncKeyState(VK_LEFT) && direction != RIGHT)
		{
			direction=LEFT;
		}
		if(GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction=RIGHT;
		}
		
		if(GetAsyncKeyState(VK_SPACE))
		{
			while(1)
			{
				Sleep(300);
				if(GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}
		
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			endStatus=3;
			endGame();
			break;
		}
		//���� 
		if(GetAsyncKeyState(VK_SHIFT))
		{
			speedUp();
		}
		//���� 
		if(GetAsyncKeyState(VK_CONTROL))
		{
			speedDown();
		}
		
		Sleep(sleepTime);
		
		moveSnake();
		
		//ײǽ 
		if(isHitWall())
		{
			endStatus = 1;
			endGame();
			break;
		}
		//ҧ���Լ� 
		if(isHitSelf())
		{
			endStatus = 2;
			endGame();
			break;
		}
	}

}
//���� ������Ϊ50ms�� 
int speedUp(void)
{
	if(sleepTime>50)
	{
		sleepTime=sleepTime-20;
		add=add+2;
	}
}
//���� ������Ϊ350ms�� 
int speedDown(void)
{
	if(sleepTime<350)
	{
		sleepTime=sleepTime+20;
		add=add-2;
	}
	if(add<=0)
	{
		add=1;
	}
}
//�ж��Ƿ�ײǽ 
int isHitWall(void)
{	
	int q;
	if(head->x==0 || head->x==56|| head->y==0 || head->y==26)
	{
		q=1;
	}
	else 
	{
		q=0;
	}
	return q;
}
//�ж��Ƿ�ҧ���Լ� 
int isHitSelf(void)
{
	snake_t *tmp = NULL;
	tmp=head->next;
	

	while(NULL!=tmp)
	{
		if((head->x==tmp->x)&&(head->y==tmp->y))
		{
			return 1;
		}
		
		else tmp=tmp->next;
	}
	return 0;

}
//ʧ�ܽ��� 
void printFailed(void)
{	
	int i=0;
	system("cls");
	Setcolor(15);
	Setcursor(44,3);
	printf("�� Ϸ �� �� ��");
	

	Setcolor(11);
	Setcursor(17,5);
	printf("+----------------------------------------------------------------+");
	
	Setcursor(17,20);
	printf("+----------------------------------------------------------------+");
	
	for(i=6;i<20;i++)
	{
		Setcursor(17,i);
		printf("|");
		
		Setcursor(82,i);
		printf("|");
	}

}
//������Ϸ��ʽ 
int endGame(void)
{
	int highScore=0;
	int choice=0;
	

	while(1)
	{
	
		printFailed();
		switch(endStatus)
		{
			case 1://ײǽ 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("С��ײ��ǽ����");
					break;
				}
			case 2://ҧ���Լ� 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("����̰�Ե����Լ�������");
					break;
				}
			case 3://ESC�˳� 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("����ô���ˣ���");
					break;
				}
			default:
				;
		}
		Setcolor(13);
		Setcursor(38,12);
		printf("�÷�: %d",score);
		
		Setcolor(10);
		highScore=readFile();
		if(score>highScore)
		{
			Setcursor(38,16);
			printf("�����˼�¼Ү��");
			writeFile(score);
		}
		else
		{
			Setcursor(38,16);
			printf("�㲻��Ŭ�������� %d ����߷�!�ò�QAQ",highScore-score);
		}
	    L=innert(&L);
	    new_info=read_score_info();
	    insert_item(L, new_info);
	    current=save_to_file(L);
	    destory_list(&L);
	    printf("�ѱ��棬��%d������",current);
		Setcursor(25,23);
		Setcolor(13);
		printf("����һ�ְ�! : 1");
		
		Setcursor(53,23);
		printf("���ܾ̾� : 2");
		
		Setcursor(40,25);
		Setcolor(15);
		printf("�������ѡ�� : ");
		
		scanf("%d",&choice);
		getchar();
		
		if(choice==1)
		{
			score=0;
			sleepTime=350;
			add=1;
			desSnake();
			break;
		}
		else if(choice==2)
		{
			exit(0);
		}
		else
		{
			Setcursor(30,27);
			Setcolor(12);
			printf("�����ɶ��������һ�Σ�");
			getchar();
		}
	}
	
	return 0;

}
//������ 
int desSnake(void)
{
	snake_t *tmp=NULL;
	snake_t *save=NULL;
	

	tmp=head;
	while(tmp!=NULL)
	{
		save=tmp->next;
		free(tmp);
		tmp=save;
	}
	head=NULL;
	
	return 0;

}
//������ 
int main()
{
	int choice=0;
	system("mode con cols=100 lines=30");
	srand(time(NULL));
	Setcolor(13);
	Setcursor(44,3);
	printf("��Ϸ˵��");
	int i,j;
	char name[1024];
	list*p;

	while(1)
	{
		choice=WelcomeGame();
		
		switch(choice)
		{
			case 1:
			//��ӡ��ͼ 
			printMap();	
			//չʾ��ʾ 
			showScoreTips();
			//��ʼ���� 
			initSnake();
			//�������ʳ�� 
			randFood();
			//�������� 
			moveKeyControl();
			break;
			
			case 2:
			//������Ϸ 
			aboutGame();
			break;
			
			case 3:
			//�˳� 
			exit(0);
			break;
			
			case 4:
			//�ɼ���ѯ
    		
			while((exitFlag = getchar()) != '\n');
			while(1){
        	
			
        	aboutgrade();
        	L = innert(&L); // ����Lָ��ĵ�ַ
       		 bubble_sort(L); // �������������
        	printf("��������ս�����ƣ�");
        	scanf("%s", name);
        	p = search(L, name);
        	if(p != NULL){
            	printf("���ҳɹ�! ��ս��%s�ĵ÷�Ϊ%d\n", name, p->data.score);
        				}
			else {
            	printf("��������ִ������������벢�����ظ���ѯ����������һ�κ��ٴβ�ѯ��\n"); 
        		}
        	printf("����1�ɼ������沢��ѯ��");
        	while((exitFlag = getchar()) != '\n'); // ���������
       			 if(exitFlag == '0' || exitFlag == '\n'){
            		break;
        	}
         }
         break;
   
			
			default:
		    Setcolor(12);
		    Setcursor(45,28);
		    
			printf("���Ϸ���������ѡ��!");
		}
		
		getchar();
	}
	
	return 0;

}
