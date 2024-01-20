#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Snake
{
private:
    bool isGameOver;
    int width;
    int height;

    int snakeHeadX;
    int snakeHeadY;

    int foodX;
    int foodY;
    int score;

    vector<int> snakeTailX, snakeTailY;
    int snakeTailLen;

    enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

    direction dir;

public:
    bool getIsGameOver() { return isGameOver; }

    void Setup()
    {
        isGameOver = false;
        score = 0;

        width = 20;
        height = 20;

        dir = STOP;
        snakeHeadX = width / 2;
        snakeHeadY = height / 2;

        srand(time(NULL));
        foodX = rand() % width;
        foodY = rand() % height;

        snakeTailX.resize(100);
        snakeTailY.resize(100);
    }

    void Draw()
    {
        system("cls");

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width + 1; j++) {
                if (j == 0 || j == width) cout << "#";
                if (i == snakeHeadY && j == snakeHeadX) cout << "O";
                else if (i == foodY && j == foodX) cout << "X";
                else {
                    bool isSnakeTailCoord = false;
                    for (int k = 0; k < snakeTailLen; k++)
                    {
                        if (snakeTailX[k] == j && snakeTailY[k] == i)
                        {
                            cout << "o";
                            isSnakeTailCoord = true;
                        }
                    }
                    if (!isSnakeTailCoord) cout << " ";
                }
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl << endl;
        cout << "Score: " << score << endl;

    }

    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 27:
                isGameOver = true;
                break;
            }
        }
    }
    void Logic()
    {
        int prevX = snakeTailX[0];
        int prevY = snakeTailY[0];
        int prev2X, prev2Y;

        snakeTailX[0] = snakeHeadX;
        snakeTailY[0] = snakeHeadY;

        for (int i = 1; i < snakeTailLen; i++)
        {
            prev2X = snakeTailX[i];
            prev2Y = snakeTailY[i];
            snakeTailX[i] = prevX;
            snakeTailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (dir)
        {
        case LEFT:
            snakeHeadX--;
            break;
        case RIGHT:
            snakeHeadX++;
            break;
        case UP:
            snakeHeadY--;
            break;
        case DOWN:
            snakeHeadY++;
            break;
        }
        if (snakeHeadX > width - 1 || snakeHeadX<0 || snakeHeadY>height - 1 || snakeHeadY < 0) isGameOver = true;;
        if (snakeHeadX >= width) snakeHeadX = 0;
        else if (snakeHeadX < 0) snakeHeadX = width - 1;

        if (snakeHeadY >= height) snakeHeadY = 0;
        else if (snakeHeadY < 0) snakeHeadY = height - 1;

        for (int i = 0; i < snakeTailLen; i++)
        {
            if (snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY) isGameOver = true;
        }
        if (snakeHeadX == foodX && snakeHeadY == foodY)
        {
            snakeTailLen++;
            score++;

            srand(time(NULL));
            foodX = rand() % width;
            foodY = rand() % height;
        }
    }


};

int main()
{
    Snake snake;

    snake.Setup();

    while (!snake.getIsGameOver())
    {
        snake.Draw();
        snake.Input();
        snake.Logic();
        Sleep(100);
    }
}
