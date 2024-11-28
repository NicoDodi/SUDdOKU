#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

struct cell {
    int number = {0};
    int notes[9] = {0};
    bool visible = {false};
    cell();
};

class Board {
public:
    cell board[9][9];  

    Board();  
    void print_board();

    bool validate_row(int x);
    bool validate_column(int y);
    bool validate_subgrid(int x, int y);
    bool validate_board(int x, int y);

    void generate_full_board();  
    bool fill_number(int i, int j);
    void print_board_with_highlight(int highlight_x, int highlight_y);



private:
    void highlight_cell(cell c);
    bool fill_board(int row, int col);  
    bool is_valid(int row, int col, int num);  
    void shuffle_numbers(int numbers[]); 
    void make_cells_visible(int n); 
};

int generate_random_number(int min, int max);  
void print_cell(cell c);  
void print_board(cell board[9][9]);  

#endif
