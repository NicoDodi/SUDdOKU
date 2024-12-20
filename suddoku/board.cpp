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
            if (fill_board(row, col + 1)) return true;  
            board[row][col].number = 0; 
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

void print_cell(cell c) {
     if (c.visible) {
        attron(COLOR_PAIR(4));
        printw("%d", c.number);
        attroff(COLOR_PAIR(4)); 
    } else {
        printw("_");       
    }
}


void Board::print_board() {
    int startx = 2, starty = 1; 
    move(starty, startx);       

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            mvprintw(starty + i * 2, startx, "+---------+---------+---------+");
        }

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                mvprintw(starty + i * 2 + 1, startx + j * 4, "| ");
            }
            
            move(starty + i * 2 + 1, startx + j * 4 + 2);
            print_cell(board[i][j]);
        }

        mvprintw(starty + i * 2 + 1, startx + 37, "|");
    }

    mvprintw(starty + 18, startx, "+---------+---------+---------+");

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
        int i = generate_random_number(0, 8); // Genera una fila aleatoria
        int j = generate_random_number(0, 8); // Genera una columna aleatoria
        if (!board[i][j].visible) {           // Solo afecta celdas no visibles
            board[i][j].visible = true;       // Marca la celda como visible
            cellsToShow--;
        }
    }
}

void Board::highlight_cell(cell c){
    attron(COLOR_PAIR(3));
    if(c.visible){
        printw("%d", c.number);
    }else{
        printw("%d", "_");
    }
    attroff(COLOR_PAIR(3));
}

void Board::print_board_with_highlight(int highlight_x, int highlight_y) {
    int startx = 2, starty = 1; 
    move(starty, startx);      

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            mvprintw(starty + i * 2, startx, "+---------+---------+---------+");
        }

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                mvprintw(starty + i * 2 + 1, startx + j * 4, "| ");
            }
            
            move(starty + i * 2 + 1, startx + j * 4 + 2);

            if (i == highlight_x && j == highlight_y) {
                highlight_cell(board[i][j]); 
            } else {
                print_cell(board[i][j]); 
            }
        }

        mvprintw(starty + i * 2 + 1, startx + 37, "|");
    }

    mvprintw(starty + 18, startx, "+---------+---------+---------+");
    refresh(); 
}


