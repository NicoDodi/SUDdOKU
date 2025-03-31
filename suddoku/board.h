#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

struct cell {
    int number = {0};
    int notes[9] = {0};
    bool visible = {false};
    bool initial = {false};
    cell();
};

class Board {
public:
    cell board[9][9];  
    int emptyCells = 55;
    int tries = 3;
    Board();  
    
    bool validate_row(int x);
    bool validate_column(int y);
    bool validate_subgrid(int x, int y);
    bool validate_board(int x, int y);
    
    void generate_full_board();
    
    void print_board();
    bool fill_number(int i, int j);
    void highlight_cell(int highlight_x, int highlight_y);
    void print_option(int x, int y, int opt);
    void print_cell(int x, int y);

    void end_game();

private:
    void highlight_cell(cell c);
    bool fill_board(int row, int col);  
    bool is_valid(int row, int col, int num);  
    void shuffle_numbers(int numbers[]); 
    void make_cells_visible(int n); 
    void game_over_banner();
};

int generate_random_number(int min, int max);  
void print_cell(cell c);  
void print_board(cell board[9][9]);  

#endif
