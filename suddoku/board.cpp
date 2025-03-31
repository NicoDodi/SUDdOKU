#include "board.h"
#include <algorithm>
#include <random>

cell::cell() {
}



Board::Board() {
    generate_full_board();  
    int cellsToShow = 26;
    while (cellsToShow > 0) {
        int i = generate_random_number(0, 8);
        int j = generate_random_number(0, 8);
        if (!board[i][j].visible) {
            board[i][j].visible = true;
            cellsToShow--;
        }
    }
}

void Board::generate_full_board() {
    fill_board(0, 0);  
}

bool Board::fill_board(int row, int col) {
    if (col == 9) {
        col = 0;
        row++;
        if (row == 9) return true;  
    }

    int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle_numbers(numbers);  

    for (int num : numbers) {
        if (is_valid(row, col, num)) {
            board[row][col].number = num;
            if (fill_board(row, col + 1)) return true;  
            else
            {
                board[row][col].number = 0;
            }
        }
    }
    return false;  
}

bool Board::is_valid(int row, int col, int num) {
        board[row][col].number = num;
        if(validate_board(row, col)) return true;
        board[row][col].number = 0;
        return false;
    }

void Board::shuffle_numbers(int numbers[]) {
    std::shuffle(numbers, numbers + 9, std::mt19937{std::random_device{}()});
}

int generate_random_number(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}


void Board::print_board() {
    int startx = 2, starty = 1; 
    move(starty, startx);       

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            mvprintw(starty + i * 2, startx, "+------------+------------+------------+");
        }

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                mvprintw(starty + i * 2 + 1, startx + j * 4, "| ");
            }
            
            move(starty + i * 2 + 1, startx + j * 4 + 2);
            print_cell(i, j);
        }

        mvprintw(starty + i * 2 + 1, startx + 37, "|");
    }

    mvprintw(starty + 18, startx,"+------------+------------+------------+");

    refresh();
}

bool Board::validate_row(int x) {
    bool used[10] = {false};
    int num;
    for(int i = 0; i < 9; i++){
        num = board[x][i].number;
        if(num != 0 && used[num]) return false;
        else used[num] = true;
    }
    return true;
}

bool Board::validate_column(int y) {
    bool used[10] = {false};
    int num;
    for(int i = 0; i < 9; i++){
        num = board[i][y].number;
        if(num != 0 && used[num]) return false;
        else used[num] = true;
    }
    return true;
}

bool Board::validate_subgrid(int x, int y) {
    bool used[10] = {false};
    int startRow = (x / 3) * 3;
    int startCol = (y / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = board[startRow + i][startCol + j].number;
            if (num != 0) {
                if (used[num]) 
                    return false;
                used[num] = true;
            }
        }
    }
    return true;
}

bool Board::validate_board(int x, int y) {
    if(validate_row(x) && validate_column(y) && validate_subgrid(x, y))
        return true;
    return false;
}

void Board::make_cells_visible(int cellsToShow) {
    while (cellsToShow > 0) {
        int i = generate_random_number(0, 8); 
        int j = generate_random_number(0, 8); 
        if (!board[i][j].visible) {           
            board[i][j].visible = true;  
            board[i][j].initial = true;
            cellsToShow--;
        }
    }
}



void Board::highlight_cell(int highlight_x, int highlight_y) {
    cell &current_cell = board[highlight_x][highlight_y]; 
    
    int pos_y = 1 + highlight_x * 2 + 1; 
    int pos_x = 2 + highlight_y * 4 + 2;  

    
    move(pos_y, pos_x);
    attron(COLOR_PAIR(3));
    if(current_cell.visible){
        printw("%d", current_cell.number);
    }else{
        printw(" _ ");
    }
    attroff(COLOR_PAIR(3));
    refresh(); 
}

void Board::print_cell(int x, int y) {
    cell &current_cell = board[x][y]; 
    
    int pos_y = 1 + x * 2 + 1; 
    int pos_x = 2 + y * 4 + 2;  

    
    move(pos_y, pos_x);
    if (current_cell.visible) {
        if(current_cell.initial){
            attron(COLOR_PAIR(4));
            printw("%d", current_cell.number);
            attroff(COLOR_PAIR(4)); 
        }else{
            attron(COLOR_PAIR(2));
            printw("%d", current_cell.number);
            attroff(COLOR_PAIR(2)); 
        }
    } else {
        printw(" _ ");       
    }
    refresh(); 
}

void Board::print_option(int x, int y, int opt) {
    cell &current_cell = board[x][y]; 
    
    int pos_y = 1 + x * 2 + 1; 
    int pos_x = 2 + y * 4 + 2;  
    
    move(pos_y, pos_x);
    
    if (current_cell.number == opt) {
        current_cell.visible = true;
        attron(COLOR_PAIR(2)); 
        printw("%d", opt);
        attroff(COLOR_PAIR(2));
    } else {
        attron(COLOR_PAIR(5)); 
        printw("%d", opt);
        attroff(COLOR_PAIR(5));
        tries --;
        if(!tries){
            end_game();
        }

    }

    
    refresh(); 
}

void Board::end_game(){
    clear();
    game_over_banner();
}


void Board::game_over_banner() {
    attron(COLOR_PAIR(6));
        attron(COLOR_PAIR(6));
        
        printw("          _____                   _____                    _____                    _____                  \n");
        refresh();
        napms(100);
        printw("         /\\    \\                 /\\    \\                  /\\    \\                  /\\    \\                 \n");
        refresh();
        napms(100);
        printw("        /::\\    \\               /::\\    \\                /::\\____\\                /::\\    \\                \n");
        refresh();
        napms(100);
        printw("       /::::\\    \\             /::::\\    \\              /::::|   |               /::::\\    \\               \n");
        refresh();
        napms(100);
        printw("      /::::::\\    \\           /::::::\\    \\            /:::::|   |              /::::::\\    \\              \n");
        refresh();
        napms(100);
        printw("     /:::/\\:::\\    \\         /:::/\\:::\\    \\          /::::::|   |             /:::/\\:::\\    \\             \n");
        refresh();
        napms(100);
        printw("    /:::/__\\:::\\    \\       /:::/__\\:::\\    \\        /:::/|::|   |            /:::/__\\:::\\    \\            \n");
        refresh();
        napms(100);
        printw("   /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\      /:::/ |::|   |           /::::\\   \\:::\\    \\           \n");
        refresh();
        napms(100);
        printw("  /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\    /:::/  |::|___|______    /::::::\\   \\:::\\    \\          \n");
        refresh();
        napms(100);
        printw(" /:::/\\:::\\   \\:::\\    \\ /:::/\\:::\\   \\:::\\    \\  /:::/   |::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\         \n");
        refresh();
        napms(100);
        printw("/:::/__\\:::\\   \\:::\\____/:::/__\\:::\\   \\:::\\____\\/:::/    |:::::::::\\____\\/:::/__\\:::\\   \\:::\\____\\        \n");
        refresh();
        napms(100);
        printw("\\:::\\   \\:::\\   \\::/    /\\:::\\   \\:::\\   \\::/    /\\::/    / ~~~~~/:::/    /\\:::\\   \\:::\\   \\::/    /        \n");
        refresh();
        napms(100);
        printw(" \\:::\\   \\:::\\   \\/____/  \\:::\\   \\:::\\   \\/____/  \\/____/      /:::/    /  \\:::\\   \\:::\\   \\/____/         \n");
        refresh();
        napms(100);
        printw("  \\:::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\                  /:::/    /    \\:::\\   \\:::\\    \\             \n");
        refresh();
        napms(100);
        printw("   \\:::\\   \\:::\\____\\       \\:::\\   \\:::\\____\\                /:::/    /      \\:::\\   \\:::\\____\\            \n");
        refresh();
        napms(100);
        printw("    \\:::\\   \\::/    /        \\:::\\   \\::/    /               /:::/    /        \\:::\\   \\::/    /            \n");
        refresh();
        napms(100);
        printw("     \\:::\\   \\/____/          \\:::\\   \\/____/               /:::/    /          \\:::\\   \\/____/             \n");
        refresh();
        napms(100);
        printw("      \\:::\\    \\               \\:::\\    \\                  /:::/    /            \\:::\\    \\                 \n");
        refresh();
        napms(100);
        printw("       \\:::\\____\\               \\:::\\____\\                /:::/    /              \\:::\\____\\                \n");
        refresh();
        napms(100);
        printw("        \\::/    /                \\::/    /                \\::/    /                \\::/    /                \n");
        refresh();
        napms(100);
        printw("         \\/____/                  \\/____/                  \\/____/                  \\/____/                 \n");
        refresh();
        napms(100);
        
        printw("        /::\\    \\            /\\    \\                  /\\    \\                  /\\    \\                     \n");
        refresh();
        napms(100);
        printw("       /::::\\    \\          /::\\____\\                /::\\    \\                /::\\    \\                    \n");
        refresh();
        napms(100);
        printw("      /::::::\\    \\        /:::/    /               /::::\\    \\              /::::\\    \\                   \n");
        refresh();
        napms(100);
        printw("     /::::::::\\    \\      /:::/    /               /::::::\\    \\            /::::::\\    \\                  \n");
        refresh();
        napms(100);
        printw("    /:::/~~\\:::\\    \\    /:::/    /               /:::/\\:::\\    \\          /:::/\\:::\\    \\                 \n");
        refresh();
        napms(100);
        printw("   /:::/    \\:::\\    \\  /:::/____/               /:::/__\\:::\\    \\        /:::/__\\:::\\    \\                \n");
        refresh();
        napms(100);
        printw("  /:::/    / \\:::\\    \\ |::|    |               /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\               \n");
        refresh();
        napms(100);
        printw(" /:::/____/   \\:::\\____\\|::|    |     _____    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\              \n");
        refresh();
        napms(100);
        printw("|:::|    |     |:::|    |::|    |    /\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\             \n");
        refresh();
        napms(100);
        printw("|:::|____|     |:::|    |::|    |   /::\\____\\/:::/__\\:::\\   \\:::\\____\\/:::/  \\:::\\   \\:::|    |            \n");
        refresh();
        napms(100);
        printw(" \\:::\\    \\   /:::/    /|::|    |  /:::/    /\\:::\\   \\:::\\   \\::/    /\\::/   |::::\\  /:::|____|            \n");
        refresh();
        napms(100);
        printw("  \\:::\\    \\ /:::/    / |::|    | /:::/    /  \\:::\\   \\:::\\   \\/____/  \\/____|:::::\\/:::/    /             \n");
        refresh();
        napms(100);
        printw("   \\:::\\    /:::/    /  |::|____|/:::/    /    \\:::\\   \\:::\\    \\            |:::::::::/    /              \n");
        refresh();
        napms(100);
        printw("    \\:::\\__/:::/    /   |:::::::::::/    /      \\:::\\   \\:::\\____\\           |::|\\::::/    /               \n");
        refresh();
        napms(100);
        printw("     \\::::::::/    /    \\::::::::::/____/        \\:::\\   \\::/    /           |::| \\::/____/                \n");
        refresh();
        napms(100);
        printw("      \\::::::/    /      ~~~~~~~~~~               \\:::\\   \\/____/            |::|  ~|                      \n");
        refresh();
        napms(100);
        printw("       \\::::/    /                                 \\:::\\    \\                |::|   |                      \n");
        refresh();
        napms(100);
        printw("        \\::/____/                                   \\:::\\____\\               \\::|   |                      \n");
        refresh();
        napms(100);
        printw("         ~~                                          \\::/    /                \\:|   |                      \n");
        refresh();
        napms(100);
        printw("                                                      \\/____/                  \\|___|                      \n");
        refresh();
        napms(100);
        
        refresh();
        napms(300);
        
        attroff(COLOR_PAIR(6));
    refresh();
    attroff(COLOR_PAIR(6));
}


