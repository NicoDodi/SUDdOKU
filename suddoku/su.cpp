#include <iostream>
#include <ncurses.h>

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
            printw("%s\n", choices[i]);
            attroff(A_REVERSE); 
        } else {
            printw("%s\n", choices[i]);
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
            break;
        case 2:
            printw("Mostrando la puntuación...\n");
            break;
        case 3:
            printw("Saliendo...\n");
            break;
    }

    getch(); 
}




int main() {
    initscr();          
    
    
    start_color();      // Inicializa colores
    noecho();           // No muestra la entrada del usuario
    cbreak();           // Modo de entrada sin buffer
    curs_set(0);        // Oculta el cursor
    keypad(stdscr, TRUE); // Habilita las teclas especiales
    Menu();             // Llama al menú
    getch();
    endwin();           // Finaliza ncurses y devuelve la terminal a su estado normal
    return 0;
}
