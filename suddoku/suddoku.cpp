#include <iostream>
#include <ncurses.h>
#include <string>
#include <random>
#include "board.h"

using namespace std;

//Board board;

void Play(){
    //board = new Board();
    
}



void Banner() {
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1)); 
    printw(" ____    __  __  ____       __  _____   __  __  __  __     \n");
    printw("/\\  _`\\ /\\ \\/\\ \\/\\  _`\\    /\\ \\/\\  __`\\/\\ \\/\\ \\/\\ \\/\\ \\    \n");
    printw("\\ \\L\\L\\_\\ \\ \\ \\ \\ \\ \\L\\ \\  \\_\\ \\ \\ \\L\\ \\ \\ \\' /\\ \\ \\ \\ \\   \n");
    printw(" \\/_\\__ \\\\ \\ \\ \\ \\ \\ \\ \\ \\ /'_` \\ \\ \\ \\ \\ \\ , <   \\ \\ \\ \\  \n");
    printw("   /\\ \\L\\ \\ \\ \\_\\ \\ \\ \\_\\ /\\ \\L\\ \\ \\ \\_\\ \\ \\ \\` \\\\ \\ \\_\\ \\ \n");
    printw("   \\ `\\____\\ \\_____\\ \\____\\ \\___,_\\ \\_____\\ \\_\\ \\_\\ \\_____\\\n");
    printw("    \\/_____/\\/_____/\\/___/ \\/__,_ /\\/_____/\\/_/\\/_/\\/_____/ \n");
    attroff(COLOR_PAIR(1));
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
    
    
    start_color();      
    noecho();           
    cbreak();           
    curs_set(0);        
    keypad(stdscr, TRUE); 
    Menu();             
    return 0;
}
