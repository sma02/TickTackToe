#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
const int gridSize = 3;
bool player = false;
char board[gridSize][gridSize] = {{' ', ' ', ' '},
                                  {' ', ' ', ' '},
                                  {' ', ' ', ' '}};
char boardGrid[5][10] = {
    "   |  |  ",
    "---------",
    "   |  |  ",
    "---------",
    "   |  |  "};

void placeSymbol(bool playerType, int offsetX, int offsetY);
void printBoard(int offsetX, int offsetY);
void showResults(char symbol);
int takeInput();
void gotoxy(int x, int y);
void consoleCursor(bool visibility);
bool verticalCheck(char symbol)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] == symbol)
            {
                count++;
            }
        }
        if (count == 3)
        {
            return true;
        }
        else
        {
            count = 0;
        }
    }
    return false;
}
bool horiontalCheck(char symbol)
{
    int count = 0;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (board[i][j] == symbol)
            {
                count++;
            }
        }
        if (count == gridSize)
        {
            return true;
        }
        else
        {
            count = 0;
        }
    }
    return false;
}
bool diagonalCheck(char symbol)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][i] == symbol)
        {
            count++;
        }
    }
    if (count == 3)
    {
        return true;
    }
    else
    {
        count = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[2 - i][i] == symbol)
        {
            count++;
        }
    }
    if (count == 3)
    {
        return true;
    }
    else
    {
        count = 0;
    }
    return false;
}
bool isWinner(char symbol)
{
    return verticalCheck(symbol) || horiontalCheck(symbol) || diagonalCheck(symbol);
}
void init()
{
    system("cls");
    printBoard(20, 5);
    player = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
    gotoxy(50, 5);
    cout << "Use Numpad key[1-9] to play";
}
int main()
{
    consoleCursor(false);
    init();
    while (1)
    {
        if (player)
        {
            gotoxy(50, 6);
            cout << "Player X turn";
        }
        else
        {
            gotoxy(50, 6);
            cout << "Player O turn";
        }
        placeSymbol(player, 20, 5);
        player = !player;
        if (isWinner('X'))
        {
            showResults('X');
        }
        else if (isWinner('O'))
        {
            showResults('O');
        }
    }
}
void showResults(char symbol)
{
    gotoxy(20, 15);
    cout << "Winner is Player " << symbol << endl;
    gotoxy(20, 16);
    system("pause");
    init();
}
void placeSymbol(bool playerType, int offsetX, int offsetY)
{
    int choice, x, y;
    choice = takeInput();
    x = (choice) % 3;
    y = 2 - (choice / 3);
    if (board[y][x] == ' ')
    {
        if (playerType)
        {
            board[y][x] = 'X';
        }
        else
        {
            board[y][x] = 'O';
        }
        gotoxy(offsetX + (x * 3) + 1, offsetY + (y * 2));
        cout << board[y][x];
    }
}

void printBoard(int offsetX, int offsetY)
{
    for (int i = 0; i < 5; i++)
    {
        gotoxy(offsetX, offsetY + i);
        cout << boardGrid[i];
    }
}
int takeInput()
{
    int key;
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
        key = getch();
        if (key >= '1' && key <= '9')
        {
            return key - '1';
        }
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void consoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}