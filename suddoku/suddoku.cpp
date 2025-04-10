#include <iostream>
#include <ncurses.h>
#include <string>
#include <random>
#include "board.h"

using namespace std;

Board board;




void Banner() {
    attron(COLOR_PAIR(6)); 
    printw(" ____    __  __  ____       __  _____   __  __  __  __     \n");
    printw("/\\  _`\\ /\\ \\/\\ \\/\\  _`\\    /\\ \\/\\  __`\\/\\ \\/\\ \\/\\ \\/\\ \\    \n");
    printw("\\ \\L\\L\\_\\ \\ \\ \\ \\ \\ \\L\\ \\  \\_\\ \\ \\ \\L\\ \\ \\ \\' /\\ \\ \\ \\ \\   \n");
    printw(" \\/_\\__ \\\\ \\ \\ \\ \\ \\ \\ \\ \\ /'_` \\ \\ \\ \\ \\ \\ , <   \\ \\ \\ \\  \n");
    printw("   /\\ \\L\\ \\ \\ \\_\\ \\ \\ \\_\\ /\\ \\L\\ \\ \\ \\_\\ \\ \\ \\` \\\\ \\ \\_\\ \\ \n");
    printw("   \\ `\\____\\ \\_____\\ \\____\\ \\___,_\\ \\_____\\ \\_\\ \\_\\ \\_____\\\n");
    printw("    \\/_____/\\/_____/\\/___/ \\/__,_ /\\/_____/\\/_/\\/_/\\/_____/ \n");
    attroff(COLOR_PAIR(6));
}

void show_opts(int actual) {
    const char *choices[] = { "Play", "Score", "Exit" };
    int num_choices = sizeof(choices) / sizeof(char *);

    for (int i = 0; i < num_choices; ++i) {
        if (actual == i + 1) { 
            attron(A_REVERSE); 
            printw("-> %s\n", choices[i]);
            attroff(A_REVERSE); 
        } else {
            printw("  %s\n", choices[i]);
        }
    }
}


void move_cursor(int x, int y){
    board.highlight_cell(x, y);
    refresh();
}

void move(){
    int col = 0, row = 0;
    int c;
    while((c = getch()) != 'q') { 
        board.print_cell(row, col);
        switch (c)
        {
        case KEY_UP:
            if(row > 0){
                row--;
                move_cursor(row, col);
            }
            break;
        case KEY_DOWN:
            if(row < 8){
                row++;
                move_cursor(row, col);
            }
            break;
        case KEY_LEFT:
            if(col > 0){
                col--;
                move_cursor(row, col);
            }
            break;
        case KEY_RIGHT:
            if(col < 8){
                col++;
                move_cursor(row, col);
            }
            break;
            case '1'...'9':
                board.print_option(row, col, c - '0'); 
                 refresh();
                break;
        default:
            break;
        }
    }
}


void Play() {
    clear(); 
    printw("Sudoku Board:\n");

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); 

    int board_width = max_x / 2; 
    int info_x = board_width + 2;

    for (int i = 0; i < max_y; i++) {
        mvprintw(i, board_width, "|");
    }

    mvprintw(0, board_width / 2 - 3, "Sudoku");
    mvprintw(0, info_x, "Información");

    mvprintw(2, info_x, "Opciones:");
    mvprintw(3, info_x, " - Usa flechas para moverte");
    mvprintw(4, info_x, " - Presiona 'q' para salir");
    mvprintw(5, info_x, "Quedan: " + board.emptyCells);


    board.print_board();
    move();
    printw("\nPress any key to return to the menu...");
    getch();
}

void init_colors(){
    init_pair(1, COLOR_RED, COLOR_BLACK);   
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

}




void Menu() {
    int choice = 0; 
    int highlight = 1; 
    int c; 
    while (1) {
        clear(); 
        Banner(); 
        show_opts(highlight); 
        refresh(); 

        c = getch(); 

        switch (c) {
            case KEY_UP: 
                highlight--;
                if (highlight < 1) 
                    highlight = 3;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 3) 
                    highlight = 1;
                break;
            case 10: 
                choice = highlight; 
                break;
            default:
                break;
        }

        if (choice != 0) 
            break; 
    }

    clear(); 
    switch (choice) {
        case 1:
            printw("Starting Game...\n");
            Play();
            break;
        case 2:
            printw("Showing Score...\n");
            break;
        case 3:
            printw("Closing game...");
            endwin();
            break;
    }

    getch(); 
}

int main() {
    initscr();          
    board = Board();
    start_color(); 
    noecho();           
    cbreak();           
    curs_set(0);        
    keypad(stdscr, TRUE); 
    init_colors();
    Menu();             
    return 0;
}
