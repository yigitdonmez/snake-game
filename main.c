#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "linked_list.h"

typedef struct {
    int x;
    int y;
} Food;

const int WIDTH = 50;
const int HEIGHT = 20;

char direction = 'd';
bool game_over = false;

void update_food(Food *food, List *snake){
    int food_x = rand() % WIDTH;
    int food_y = rand() % HEIGHT;
    SnakeSegment *check = snake->head;
    while(check){
        if(check->x == food_x && check->y == food_y){
            food_x = rand() % WIDTH;
            food_y = rand() % HEIGHT;
            check = snake->head;
            continue;
        }
        check = check->next;
    }
    food->x = food_x;
    food->y = food_y;
}

void update_snake(List *list, Food *food){
    int x, y;
    SnakeSegment *check = list->head;
    switch(direction){
        case 'w':
            x = list->head->x;
            y = list->head->y - 1;
            break;
        case 's':
            x = list->head->x;
            y = list->head->y + 1;
            break;
        case 'a':
            x = list->head->x - 1;
            y = list->head->y;
            break;
        case 'd':
            x = list->head->x + 1;
            y = list->head->y;
            break;
    }
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        printf("                   Game Over");
        game_over = true;
        return;
    }
    while(check){
        if (x == check->x && y == check->y){
            printf("                   Game Over");
            game_over = true;
            return;
        }
        check = check->next;
    }
    if(x == food->x && y == food->y){
        add_first(list, x, y);
        update_food(food, list);
    } else {
        add_first(list, x, y);
        remove_last(list);
    }
    if(list->snake_lenght == WIDTH*HEIGHT){
        printf("         YOU WIN! CONGRATILATIONS!");
        game_over = true;
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void update_display(List *snake, Food *food, int score){
    char board[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = ' ';
        }
    }

    board[food->y][food->x] = 'F';

    SnakeSegment *current = snake->head;
    if (current != NULL) {
        board[current->y][current->x] = 'O';
        current = current->next;
    }
    while (current != NULL) {
        board[current->y][current->x] = '*';
        current = current->next;
    }

    gotoxy(0, 0); 

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("                 YOUR SCORE: %d\n", score);

}

int main(){
    srand(time(NULL));
    hide_cursor();
    List *snake = (List*)malloc(sizeof(List));
    init_list(snake);
    add_first(snake, rand() % WIDTH, rand() % HEIGHT);
    Food *food = (Food*)malloc(sizeof(Food));
    update_food(food, snake);
    int score;

    while(!game_over){
        if(_kbhit()){
            char ch = _getch();
            switch (ch) {
                case 'w': 
                    if (direction != 's') direction = 'w'; 
                    break;
                case 'a': 
                    if (direction != 'd') direction = 'a'; 
                    break;
                case 's': 
                    if (direction != 'w') direction = 's'; 
                    break;
                case 'd': 
                    if (direction != 'a') direction = 'd'; 
                    break;
                case 'q': 
                    game_over = true; 
                    break;
            }
        }
        update_snake(snake, food);
        score = snake->snake_lenght * 10;
        update_display(snake, food, score);
        Sleep(70);
    }
    delete_list(snake);
    free(food);
}