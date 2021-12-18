#include<stdio.h>
#include<Windows.h>

#define UP 72  //위쪽 방향키
#define DOWN 80 //아래 방향키
#define LEFT 75 //왼쪽 방향키
#define RIGHT 77 //오른쪽 방향키
#define ENTER 13 //엔터
#define ESC 27 //esc
#define BACKSPACE 8 //백스페이스
#define SPACEBAR 32 //스페이스바

void setConsole(); //콘솔 크기,제목 설정
void intro(); //시작화면
void gotoxy(int, int); //커서의 위치를 매개변수 값으로 이동
int menu(); //시작화면 메뉴기능 선택한 메뉴를 반환
void cursorView(int, int); //매개 변수로 커서를 보이게 할지, 커서의 크기를 받는다
int keyPush(); //눌려진 키가 무엇인지 반환함.
void menu_gameStart(); //메뉴에서 게임 시작을 누르면 이 함수를 실행
void menu_manual(); //메뉴에서 조작법을 누르면 이 함수를 실행
void menu_rule(); //메뉴에서 게임 룰을 누르면 이 함수를 실행
void drawBoard(); // 오목판을 그림
void drawStone(); // 키보드 제어, 돌을 출력
void win(); //5목이 되었는지 확인

int board[15][15] = { 0, }; //15 x 15 오목판을 이차원 배열로 나타냄


int main()
{
    setConsole();


    while (1)
    {
        cursorView(0, 1);
        intro();

        int selectMenu = menu();

        if (selectMenu == 0)
        {
            cursorView(1, 5);
            menu_gameStart();//게임시작
        }
        else if (selectMenu == 2)
        {
            menu_manual();//조작법
        }
        else if (selectMenu == 4)
        {
            menu_rule();//게임 룰
        }
        else if (selectMenu == 6)
        {
            exit(1); //종료
        }
    }

    return 0;
}

void setConsole() //콘솔 세팅
{
    system("title omok game"); //콘솔창 제목
    system("mode con cols=100 lines=33"); //콘솔창 크기
}

void intro() //콘솔창 시작 화면
{
    printf("\n\n\n");
    printf("         #######     ########    \n");
    printf("         ##          ##    ##    \n");
    printf("         ##          ########    \n");
    printf("         #######        ##       \n");
    printf("               ##   #########    \n");
    printf("               ##                \n");
    printf("         #######     #######     \n");
    printf("                          ##     \n");
    gotoxy(30, 14);
    printf(" Enter키로 선택 하세요");
}

void gotoxy(int x, int y) //커서 위치 지정
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int menu()
{
    int x = 15;
    int y = 14;

    gotoxy(x - 2, y);
    printf("> 게임 시작");
    gotoxy(x, y + 2);
    printf("조작법");
    gotoxy(x, y + 4);
    printf("게임 룰");
    gotoxy(x, y + 6);
    printf("나가기");
    puts("");

    while (1)
    {
        switch (keyPush())
        {
        case UP: //위 방향키를 누르면
            if (y == 14) //이미 맨 위 메뉴이면
            {
                gotoxy(x - 2, y);
                printf(" "); // 출력되어있던 >를 공백으로 덮어씌어 지움
                gotoxy(x - 2, y + 6);
                printf(">"); // 맨밑으로 이동하여 >를 출력
                y = y + 6;
            }
            else
            {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, y - 2);
                printf(">"); // 바로 위로 이동
                y = y - 2;
            }
            break;

        case DOWN:
            if (y == 20)
            {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, y - 6);
                printf(">");
                y = y - 6;
            }
            else
            {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, y + 2);
                printf(">");
                y = y + 2;
            }
            break;

        case ENTER:
            return y - 14; //선택된 메뉴에 따라 0,2,4,6을 반환
        }

    }
}

void cursorView(int x, int y)  //커서 세팅
{
    CONSOLE_CURSOR_INFO cursorControl = { 0 };
    cursorControl.dwSize = y;  // 커서 크기 조정(1~100) 반드시 범위 안으로 입력
    cursorControl.bVisible = x;  //커서 숨기기(0=숨기기,1=보이기)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorControl);
}

int keyPush() //키보드 이벤트
{
    int key = getch();
    if (key == 224)
    {
        key = getch();
        switch (key)
        {
        case UP:
            return UP;
            break;
        case DOWN:
            return DOWN;
            break;
        case RIGHT:
            return RIGHT;
            break;
        case LEFT:
            return LEFT;
            break;
        }
    }
}

void menu_gameStart()
{
    system("cls");
    drawBoard();

}

void menu_manual()
{
    system("cls");
    gotoxy(10, 5);
    printf("    조작법                  \n\n\n");
    printf("           위     : ↑           \n\n");
    printf("          아래    : ↓           \n\n");
    printf("         오른쪽   : →           \n\n");
    printf("          왼쪽    : ←           \n\n");
    printf("          착수    : Spacebar     \n\n");
    printf("         뒤로가기 : Backspace    \n\n");

    gotoxy(10, 25);
    printf("메뉴 화면으로 돌아가려면 Backspace를 누르세요.");

    while (1)
    {
        if (keyPush() == BACKSPACE) //백스페이스바를 누르면 원래 메뉴화면을 출력
        {
            system("cls");
            break;
        }
    }
}

void menu_rule()
{
    system("cls");
    gotoxy(10, 5);
    printf("게임 룰");
    printf(" 이 게임은 렌즈룰을 기반으로 제작되었습니다.             \n\n\n");
    printf("          1. 먼저 5개의 돌을 나란히 놓으면 승리합니다.   \n\n");
    printf("          2. 첫 수는 항상 가운데입니다.                  \n\n");
    printf("          3. 흑돌부터 시작합니다.                        \n\n  ");
    printf("          3. 흑돌의 경우 33, 44, 6목을 둘 수 없습니다.   \n\n");

    gotoxy(10, 20);
    printf("메뉴 화면으로 돌아가려면 Backspace를 누르세요.");


    while (1)
    {
        if (keyPush() == BACKSPACE) //백스페이스바를 누르면 원래 메뉴화면을 출력
        {
            system("cls");
            break;
        }
    }
}

void drawBoard()
{

    int i, j;
    char a = 0xa6;
    char b[12];

    for (i = 1; i < 12; i++)
    {
        b[i] = 0xa0 + i;
    }

    printf("\033[0;33m"); //갈색으로 출력
    printf("%c%c", a, b[3]);
    printf("%c%c", a, b[1]);
    for (i = 0; i < 13; i++)
    {

        printf("%c%c", a, b[8]);
        printf("%c%c", a, b[1]);
    }
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < 13; i++)
    {
        printf("%c%c", a, b[7]);
        for (j = 0; j < 13; j++)
        {

            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[11]);
        }
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }
    printf("%c%c", a, b[6]);
    printf("%c%c", a, b[1]);
    for (i = 0; i < 13; i++)
    {
        printf("%c%c", a, b[10]);
        printf("%c%c", a, b[1]);
    }
    printf("%c%c", a, b[5]);
    printf("\n");

    gotoxy(14, 7); //첫 수는 가운데
    printf("○");
    board[7][7] = 2;

    drawStone();
    //win();
}

void drawStone()
{
    gotoxy(14, 7);

    int x = 14;
    int y = 7;
    int a = 0;

    while (1)
    {
        switch (keyPush())
        {
        case UP:
            if (y == 0)
                break;
            gotoxy(x, y - 1);
            y = y - 1;
            break;
        case DOWN:
            if (y == 14)
                break;
            gotoxy(x, y + 1);
            y = y + 1;
            break;
        case RIGHT:
            if (x == 28)
                break;
            gotoxy(x + 2, y);
            x = x + 2;
            break;
        case LEFT:
            if (x == 0)
                break;
            gotoxy(x - 2, y);
            x = x - 2;
            break;
        case SPACEBAR:
            if ((board[y][x / 2] == 1) || (board[y][x / 2] == 2)) //이미 돌이 착수되어 있을 때
            {
                printf("\a");
                gotoxy(40, 7);

                printf("이미 착수된 자리입니다.");
                break;
            }
            else
            {
                if (a % 2 == 0)
                {
                    board[y][x / 2] = 1;
                    printf("●");
                }
                else
                {
                    board[y][x / 2] = 2;
                    printf("○");
                }
                a++;
                win();
                break;
            }
        }
    }
}

void win()
{
    int i, j; // i = x축, j = y축
    for (i = 2; i < 12; i++)
    {
        for (j = 2; j < 12; j++)
        {
            if ((board[i - 2][j] == 1) && (board[i - 1][j] == 1) && (board[i][j] == 1) && (board[i + 1][j] == 1) && (board[i + 2][j] == 1))   //백돌 세로
            {
                gotoxy(1, 30);
                printf("백돌 승리");
                exit(1);
                break;
            }
            else if ((board[i][j - 2] == 1) && (board[i][j - 1] == 1) && (board[i][j] == 1) && (board[i][j + 1] == 1) && (board[i][j + 2] == 1)) //백돌 가로
            {
                gotoxy(1, 30);
                printf("백돌 승리");
                exit(1);
                break;
            }
            if ((board[i - 2][j] == 2) && (board[i - 1][j] == 2) && (board[i][j] == 2) && (board[i + 1][j] == 2) && (board[i + 2][j] == 2))   //흑돌 세로
            {
                gotoxy(1, 30);
                printf("흑돌 승리");
                exit(1);
                break;
            }
            else if ((board[i][j - 2] == 2) && (board[i][j - 1] == 2) && (board[i][j] == 2) && (board[i][j + 1] == 2) && (board[i][j + 2] == 2)) //흑돌 가로
            {
                gotoxy(1, 30);
                printf("흑돌 승리");
                exit(1);
                break;
            }
            else if ((board[i - 2][j - 2] == 1) && (board[i - 1][j - 1] == 1) && (board[i][j] == 1) && (board[i + 1][j + 1] == 1) && (board[i + 2][j + 2] == 1)) //백돌 ↖↘
            {
                gotoxy(1, 30);
                printf("백돌 승리");
                exit(1);
                break;
            }
            else if ((board[i - 1][j + 1] == 1) && (board[i - 2][j + 2] == 1) && (board[i][j] == 1) && (board[i + 1][j - 1] == 1) && (board[i + 2][j - 2] == 1)) //백돌 ↗↙
            {
                gotoxy(1, 30);
                printf("백돌 승리");
                exit(1);
                break;
            }
            else if ((board[i - 2][j - 2] == 2) && (board[i - 1][j - 1] == 2) && (board[i][j] == 2) && (board[i + 1][j + 1] == 2) && (board[i + 2][j + 2] == 2)) //흑돌 ↖↘
            {
                gotoxy(1, 30);
                printf("흑돌 승리");
                exit(1);
                break;
            }
            else if ((board[i - 1][j + 1] == 2) && (board[i - 2][j + 2] == 2) && (board[i][j] == 2) && (board[i + 1][j - 1] == 2) && (board[i + 2][j - 2] == 2)) //흑돌 ↗↙
            {
                gotoxy(1, 30);
                printf("흑돌 승리");
                exit(1);
                break;
            }
        }
    }

}