#include <iostream>
#include <ncurses.h>
#include <string>

using namespace std;


struct cell {
    int number;
    int notes[9];

    cell() {
        number = 0;
        for (int i = 0; i < 9; i++) {
            notes[i] = 0;
        }
    }
};

void print_cell(cell c){
    printw("%d", c.number);
    printw("%s", c.notes.c_str());
}

void print_board(cell** board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printw("+---------+---------+---------+\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printw("| ");
            }
            if (board[i][j].number == 0) {
                for (int k = 0; k < 9; k++) {
                    if (board[i][j].notes[k] != 0) {
                        printw("%d", board[i][j].notes[k]);
                    } else {
                        printw(".");
                    }
                    if ((k + 1) % 3 == 0) {
                        printw(" ");
                    }
                }
            } else {
                printw("  %d  ", board[i][j].number);
            }
        }
        printw("|\n");
    }
    printw("+---------+---------+---------+\n");
}

void Play(){
    const int size = 9;
    cell** board = new cell*[size];
    for (int i = 0; i < size; i++) {
        board[i] = new cell[size];
    }
    print_board(board);
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
    printw("en menu");
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
            printw("Iniciando el juego...\n");
            Play();
            break;
        case 2:
            printw("Mostrando la puntuación...\n");
            break;
        case 3:
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
