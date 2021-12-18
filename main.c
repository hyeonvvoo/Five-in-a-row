#include<stdio.h>
#include<Windows.h>

#define UP 72  //���� ����Ű
#define DOWN 80 //�Ʒ� ����Ű
#define LEFT 75 //���� ����Ű
#define RIGHT 77 //������ ����Ű
#define ENTER 13 //����
#define ESC 27 //esc
#define BACKSPACE 8 //�齺���̽�
#define SPACEBAR 32 //�����̽���

void setConsole(); //�ܼ� ũ��,���� ����
void intro(); //����ȭ��
void gotoxy(int, int); //Ŀ���� ��ġ�� �Ű����� ������ �̵�
int menu(); //����ȭ�� �޴���� ������ �޴��� ��ȯ
void cursorView(int, int); //�Ű� ������ Ŀ���� ���̰� ����, Ŀ���� ũ�⸦ �޴´�
int keyPush(); //������ Ű�� �������� ��ȯ��.
void menu_gameStart(); //�޴����� ���� ������ ������ �� �Լ��� ����
void menu_manual(); //�޴����� ���۹��� ������ �� �Լ��� ����
void menu_rule(); //�޴����� ���� ���� ������ �� �Լ��� ����
void drawBoard(); // �������� �׸�
void drawStone(); // Ű���� ����, ���� ���
void win(); //5���� �Ǿ����� Ȯ��

int board[15][15] = { 0, }; //15 x 15 �������� ������ �迭�� ��Ÿ��


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
            menu_gameStart();//���ӽ���
        }
        else if (selectMenu == 2)
        {
            menu_manual();//���۹�
        }
        else if (selectMenu == 4)
        {
            menu_rule();//���� ��
        }
        else if (selectMenu == 6)
        {
            exit(1); //����
        }
    }

    return 0;
}

void setConsole() //�ܼ� ����
{
    system("title omok game"); //�ܼ�â ����
    system("mode con cols=100 lines=33"); //�ܼ�â ũ��
}

void intro() //�ܼ�â ���� ȭ��
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
    printf(" EnterŰ�� ���� �ϼ���");
}

void gotoxy(int x, int y) //Ŀ�� ��ġ ����
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
    printf("> ���� ����");
    gotoxy(x, y + 2);
    printf("���۹�");
    gotoxy(x, y + 4);
    printf("���� ��");
    gotoxy(x, y + 6);
    printf("������");
    puts("");

    while (1)
    {
        switch (keyPush())
        {
        case UP: //�� ����Ű�� ������
            if (y == 14) //�̹� �� �� �޴��̸�
            {
                gotoxy(x - 2, y);
                printf(" "); // ��µǾ��ִ� >�� �������� ����� ����
                gotoxy(x - 2, y + 6);
                printf(">"); // �ǹ����� �̵��Ͽ� >�� ���
                y = y + 6;
            }
            else
            {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, y - 2);
                printf(">"); // �ٷ� ���� �̵�
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
            return y - 14; //���õ� �޴��� ���� 0,2,4,6�� ��ȯ
        }

    }
}

void cursorView(int x, int y)  //Ŀ�� ����
{
    CONSOLE_CURSOR_INFO cursorControl = { 0 };
    cursorControl.dwSize = y;  // Ŀ�� ũ�� ����(1~100) �ݵ�� ���� ������ �Է�
    cursorControl.bVisible = x;  //Ŀ�� �����(0=�����,1=���̱�)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorControl);
}

int keyPush() //Ű���� �̺�Ʈ
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
    printf("    ���۹�                  \n\n\n");
    printf("           ��     : ��           \n\n");
    printf("          �Ʒ�    : ��           \n\n");
    printf("         ������   : ��           \n\n");
    printf("          ����    : ��           \n\n");
    printf("          ����    : Spacebar     \n\n");
    printf("         �ڷΰ��� : Backspace    \n\n");

    gotoxy(10, 25);
    printf("�޴� ȭ������ ���ư����� Backspace�� ��������.");

    while (1)
    {
        if (keyPush() == BACKSPACE) //�齺���̽��ٸ� ������ ���� �޴�ȭ���� ���
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
    printf("���� ��");
    printf(" �� ������ ������� ������� ���۵Ǿ����ϴ�.             \n\n\n");
    printf("          1. ���� 5���� ���� ������ ������ �¸��մϴ�.   \n\n");
    printf("          2. ù ���� �׻� ����Դϴ�.                  \n\n");
    printf("          3. �浹���� �����մϴ�.                        \n\n  ");
    printf("          3. �浹�� ��� 33, 44, 6���� �� �� �����ϴ�.   \n\n");

    gotoxy(10, 20);
    printf("�޴� ȭ������ ���ư����� Backspace�� ��������.");


    while (1)
    {
        if (keyPush() == BACKSPACE) //�齺���̽��ٸ� ������ ���� �޴�ȭ���� ���
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

    printf("\033[0;33m"); //�������� ���
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

    gotoxy(14, 7); //ù ���� ���
    printf("��");
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
            if ((board[y][x / 2] == 1) || (board[y][x / 2] == 2)) //�̹� ���� �����Ǿ� ���� ��
            {
                printf("\a");
                gotoxy(40, 7);

                printf("�̹� ������ �ڸ��Դϴ�.");
                break;
            }
            else
            {
                if (a % 2 == 0)
                {
                    board[y][x / 2] = 1;
                    printf("��");
                }
                else
                {
                    board[y][x / 2] = 2;
                    printf("��");
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
    int i, j; // i = x��, j = y��
    for (i = 2; i < 12; i++)
    {
        for (j = 2; j < 12; j++)
        {
            if ((board[i - 2][j] == 1) && (board[i - 1][j] == 1) && (board[i][j] == 1) && (board[i + 1][j] == 1) && (board[i + 2][j] == 1))   //�鵹 ����
            {
                gotoxy(1, 30);
                printf("�鵹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i][j - 2] == 1) && (board[i][j - 1] == 1) && (board[i][j] == 1) && (board[i][j + 1] == 1) && (board[i][j + 2] == 1)) //�鵹 ����
            {
                gotoxy(1, 30);
                printf("�鵹 �¸�");
                exit(1);
                break;
            }
            if ((board[i - 2][j] == 2) && (board[i - 1][j] == 2) && (board[i][j] == 2) && (board[i + 1][j] == 2) && (board[i + 2][j] == 2))   //�浹 ����
            {
                gotoxy(1, 30);
                printf("�浹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i][j - 2] == 2) && (board[i][j - 1] == 2) && (board[i][j] == 2) && (board[i][j + 1] == 2) && (board[i][j + 2] == 2)) //�浹 ����
            {
                gotoxy(1, 30);
                printf("�浹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i - 2][j - 2] == 1) && (board[i - 1][j - 1] == 1) && (board[i][j] == 1) && (board[i + 1][j + 1] == 1) && (board[i + 2][j + 2] == 1)) //�鵹 �آ�
            {
                gotoxy(1, 30);
                printf("�鵹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i - 1][j + 1] == 1) && (board[i - 2][j + 2] == 1) && (board[i][j] == 1) && (board[i + 1][j - 1] == 1) && (board[i + 2][j - 2] == 1)) //�鵹 �֢�
            {
                gotoxy(1, 30);
                printf("�鵹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i - 2][j - 2] == 2) && (board[i - 1][j - 1] == 2) && (board[i][j] == 2) && (board[i + 1][j + 1] == 2) && (board[i + 2][j + 2] == 2)) //�浹 �آ�
            {
                gotoxy(1, 30);
                printf("�浹 �¸�");
                exit(1);
                break;
            }
            else if ((board[i - 1][j + 1] == 2) && (board[i - 2][j + 2] == 2) && (board[i][j] == 2) && (board[i + 1][j - 1] == 2) && (board[i + 2][j - 2] == 2)) //�浹 �֢�
            {
                gotoxy(1, 30);
                printf("�浹 �¸�");
                exit(1);
                break;
            }
        }
    }

}