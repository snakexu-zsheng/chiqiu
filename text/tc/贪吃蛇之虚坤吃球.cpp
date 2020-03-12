/*********************************************************
**********************************************************                                                   
** IDE(���ɿ�������):Microsoft Visual Stdio 2010 �콢��***                                        
** ���԰汾��Windows7רҵ��*******************************                     
** ͼ�ο⣺easyX******************************************                                 
** �����ˣ�����ʢ*****************************************                                            
**********************************************************                                                 
**********************************************************                                                  
*********************************************************/       
#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<conio.h>//������ص�ͷ�ļ�
#include<time.h>
#include<imapi.h>
#include<windows.h>
#include<mmsystem.h>//�������ֵ��ļ��������٣�
#pragma comment(lib,"winmm.lib")//�������ֵ��ļ��������٣�
#define MAX 1000//�ߵ��������������޸�
#define N 30//�ߵĳߴ�,�����޸�
IMAGE sheadup, sheaddown, sheadleft, sheadright,body, sfood;

struct COOR//������
{
    int x;
    int y;
};
enum CH
{
    up=72,//����ֵ
    down=80,
    left=75,
    right=77
};
//����
struct SNAKE
{
    int n;//�ߵĽ���
    COOR scr[MAX];//�ߵ�����
    CH ch;//�ߵķ���
}snake;

struct FOOD//ʳ����    
{
    COOR fcr;//ʳ������
    int  flag;//ʳ���Ƿ����ɵı�־
}food;

void initGame()
{
	
    initgraph(640, 480);//���ڿ�ȣ��߶�

    setbkcolor(WHITE);
    cleardevice();
    //����ͼƬ
    loadimage(&sheadup, L"5.jpg", N, N);//�����Լ�����ͼƬ���ܼ򵥡�
    loadimage(&sheaddown, L"10.jpg", N, N);
    loadimage(&sheadleft, L"61.jpg", N, N);
    loadimage(&sheadright, L"35.jpg", N, N);
    loadimage(&body, L"66.jpg", N, N);
    loadimage(&sfood, L"21.jpg", N, N);
    snake.n = 1;//�ߵĽ�����ʼ��
    snake.scr[0].x = 0;//�ߵ�����
    snake.scr[0].y = 0;
    snake.ch = down;//�����߿�ʼ��ʱ����������
    food.flag = 0;//����ʳ��
	mciSendString(_T("play 7895.mp3 repeat"),0,0,0);//���Լ������ַŵ�Դ�ļ�����������ľ���

}

//������
void SnakePaint()
{
    //������ͷ
    /*fillrectangle(snake.scr[0].x, snake.scr[0].y, snake.scr[0].x + SIZE, \
        snake.scr[0].y + SIZE);*/
    switch (snake.ch)
    {
    case up:
        putimage(snake.scr[0].x, snake.scr[0].y, &sheadup);
        break;
    case down:
        putimage(snake.scr[0].x, snake.scr[0].y, &sheaddown);
        break;
    case left:
        putimage(snake.scr[0].x, snake.scr[0].y, &sheadleft);
        break;
    case right:
        putimage(snake.scr[0].x, snake.scr[0].y, &sheadright);
        break;
    default:
        break;
    }
    //��������
    for (int i = snake.n - 1; i > 0; i--)
    {
        /*fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + \
            SIZE, snake.scr[i].y + SIZE);*/
        putimage(snake.scr[i].x, snake.scr[i].y, &body);
    }
}
//�ߵ��ƶ�
void SnakeMove()
{
    for (int i = snake.n - 1; i > 0; i--)
    {
        snake.scr[i].x = snake.scr[i - 1].x;
        snake.scr[i].y = snake.scr[i - 1].y;
    }
    switch (snake.ch)
    {
    case up:
        snake.scr[0].y -= N;
        break;
    case down:
        snake.scr[0].y += N;
        break;
    case left:
        snake.scr[0].x -= N;
        break;
    case right:
        snake.scr[0].x += N;
        break;
    default:
        break;
    }
}
//�����ߵķ���
void ChangeSnakech()
{
    switch (_getch())
    {
    case 72:
        if (snake.ch != down)
            snake.ch = up;
        break;
    case 80:
        if (snake.ch != up)
            snake.ch = down;
        break;
    case 75:
        if (snake.ch != right)
            snake.ch = left;
        break;
    case 77:
        if (snake.ch != left)
            snake.ch = right;
        break;
    default:
        break;
    }
}
//����ʳ������
void FoodCoor()
{
  
	
     //���������
    srand((unsigned)time(NULL));
    food.fcr.x = rand() %16* N;//������,���ǲ�Ҫ��̫�࣬��Ϊ�᲻����ʳ��
    food.fcr.y = rand() % 12*N;
    //food.flag = 1;//���������Ժ��Ȳ�����ʳ��
	food.flag=1;


	
} 
void FoodPaint()//����ʳ��
{
		putimage(food.fcr.x,food.fcr.y,&sfood);
  
  
}

//��ʳ��
void EatFood()
{
	 
    if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
    {
        snake.n++;
        food.flag = 0;
    }
}

void judge()//���������Ϸ
{
    cleardevice();//����
    settextcolor(LIGHTRED);//���Ը���ɫ
    settextstyle(45, 0, L"����");//���Ը�����
    outtextxy(100, 100, L"�Բ�������,��Ϸ����!");//���ԸĽ�����

    Sleep(1000);
    exit(0);
}
//�ж���Ϸ����
void GameOver()
{
	

    //��ͷײ����ǽ
    if (snake.scr[0].x<0 || snake.scr[0].x>620 ||\
        snake.scr[0].y<0 || snake.scr[0].y>460)
    {
        judge();
    }
    //��ͷײ��������
    for (int i = snake.n - 1; i > 0; i--)
    {
        if (snake.scr[0].x == snake.scr[i].x\
            &&snake.scr[0].y == snake.scr[i].y)
        {
            judge();
        }
    }
}
int main()
{
	initGame();  
    while (1)
    {
        while (!_kbhit())//�����°����˳�ѭ��
        {
            if (food.flag == 0)
                FoodCoor();
            cleardevice();//ˢ����Ļ
            FoodPaint();
            SnakeMove();//�ߵ��ƶ�
            SnakePaint();//�ߵĻ���
            Sleep(300);
            EatFood();
            GameOver();
        }

        ChangeSnakech();
    }

    return 0;
}
