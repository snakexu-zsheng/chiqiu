/*********************************************************
**********************************************************                                                   
** IDE(集成开发环境):Microsoft Visual Stdio 2010 旗舰版***                                        
** 电脑版本：Windows7专业版*******************************                     
** 图形库：easyX******************************************                                 
** 制作人：徐宗盛*****************************************                                            
**********************************************************                                                 
**********************************************************                                                  
*********************************************************/       
#include<graphics.h>//图形库头文件
#include<conio.h>//按键相关的头文件
#include<time.h>
#include<imapi.h>
#include<windows.h>
#include<mmsystem.h>//播放音乐的文件，不能少！
#pragma comment(lib,"winmm.lib")//播放音乐的文件，不能少！
#define MAX 1000//蛇的最大节数，可以修改
#define N 30//蛇的尺寸,可以修改
IMAGE sheadup, sheaddown, sheadleft, sheadright,body, sfood;

struct COOR//坐标类
{
    int x;
    int y;
};
enum CH
{
    up=72,//键码值
    down=80,
    left=75,
    right=77
};
//蛇类
struct SNAKE
{
    int n;//蛇的节数
    COOR scr[MAX];//蛇的坐标
    CH ch;//蛇的方向
}snake;

struct FOOD//食物类    
{
    COOR fcr;//食物坐标
    int  flag;//食物是否生成的标志
}food;

void initGame()
{
	
    initgraph(640, 480);//窗口宽度，高度

    setbkcolor(WHITE);
    cleardevice();
    //加载图片
    loadimage(&sheadup, L"5.jpg", N, N);//可以自己更换图片，很简单。
    loadimage(&sheaddown, L"10.jpg", N, N);
    loadimage(&sheadleft, L"61.jpg", N, N);
    loadimage(&sheadright, L"35.jpg", N, N);
    loadimage(&body, L"66.jpg", N, N);
    loadimage(&sfood, L"21.jpg", N, N);
    snake.n = 1;//蛇的节数初始化
    snake.scr[0].x = 0;//蛇的坐标
    snake.scr[0].y = 0;
    snake.ch = down;//定义蛇开始的时候是向哪走
    food.flag = 0;//生成食物
	mciSendString(_T("play 7895.mp3 repeat"),0,0,0);//把自己的音乐放到源文件，按着上面改就行

}

//绘制蛇
void SnakePaint()
{
    //绘制蛇头
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
    //绘制蛇身
    for (int i = snake.n - 1; i > 0; i--)
    {
        /*fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + \
            SIZE, snake.scr[i].y + SIZE);*/
        putimage(snake.scr[i].x, snake.scr[i].y, &body);
    }
}
//蛇的移动
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
//控制蛇的方向
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
//生成食物坐标
void FoodCoor()
{
  
	
     //随机数种子
    srand((unsigned)time(NULL));
    food.fcr.x = rand() %16* N;//改数字,但是不要改太多，因为会不生成食物
    food.fcr.y = rand() % 12*N;
    //food.flag = 1;//生成坐标以后先不生成食物
	food.flag=1;


	
} 
void FoodPaint()//定义食物
{
		putimage(food.fcr.x,food.fcr.y,&sfood);
  
  
}

//吃食物
void EatFood()
{
	 
    if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
    {
        snake.n++;
        food.flag = 0;
    }
}

void judge()//定义结束游戏
{
    cleardevice();//清屏
    settextcolor(LIGHTRED);//可以改颜色
    settextstyle(45, 0, L"楷体");//可以改字体
    outtextxy(100, 100, L"对不起虚坤,游戏结束!");//可以改结束字

    Sleep(1000);
    exit(0);
}
//判断游戏结束
void GameOver()
{
	

    //蛇头撞到了墙
    if (snake.scr[0].x<0 || snake.scr[0].x>620 ||\
        snake.scr[0].y<0 || snake.scr[0].y>460)
    {
        judge();
    }
    //蛇头撞到了蛇身
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
        while (!_kbhit())//当按下按键退出循环
        {
            if (food.flag == 0)
                FoodCoor();
            cleardevice();//刷新屏幕
            FoodPaint();
            SnakeMove();//蛇的移动
            SnakePaint();//蛇的绘制
            Sleep(300);
            EatFood();
            GameOver();
        }

        ChangeSnakech();
    }

    return 0;
}
