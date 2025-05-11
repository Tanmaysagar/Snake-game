#include <iostream>
#include <conio.h> 
#include <windows.h> 
using namespace std;
const int WIDTH = 20;
const int HEIGHT = 10;
bool gameOver = false;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
struct Segment {
    int x, y;
};
Segment snake[100];
int length;
int foodX, foodY;
void Setup() {
    gameOver = false;
    dir = STOP;
    length = 1;
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}
void Draw() {
    system("cls"); 
    for (int i = 0; i < WIDTH + 2; ++i)
        cout << "#";
    cout << endl;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0)
                cout << "#";
            if (x == foodX && y == foodY)
                cout << "*"; 
            else {
                bool print = false;
                for (int i = 0; i < length; ++i) {
                    if (snake[i].x == x && snake[i].y == y) {
                        cout << "O"; 
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (x == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < WIDTH + 2; ++i)
        cout << "#";
    cout << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    int prevX = snake[0].x;
    int prevY = snake[0].y;
    int prev2X, prev2Y;
    snake[0].x += (dir == RIGHT) - (dir == LEFT);
    snake[0].y += (dir == DOWN) - (dir == UP);

    for (int i = 1; i < length; ++i) {
        prev2X = snake[i].x;
        prev2Y = snake[i].y;
        snake[i].x = prevX;
        snake[i].y = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    if (snake[0].x >= WIDTH || snake[0].x < 0 || snake[0].y >= HEIGHT || snake[0].y < 0)
        gameOver = true;
    for (int i = 1; i < length; ++i) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
            gameOver = true;
    }
    if (snake[0].x == foodX && snake[0].y == foodY) {
        length++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); 
    }

    cout << "Game Over!" << endl;
    return 0;
}
