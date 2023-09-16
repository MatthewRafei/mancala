#include <iostream>

#define BOARD_INDEX 13
#define PLAYER_ONE_GOAL 0
#define PLAYER_TWO_GOAL 7


struct MANACALA_BOARD{
    int pits[14];
    int player_one_score = 0;
    int player_two_score = 0;
    bool current_player_turn = 0;
};

void fill_board(struct MANACALA_BOARD *board)
{
    for(int i = 0; i <= BOARD_INDEX; i++){
        if(i == PLAYER_ONE_GOAL || i == PLAYER_TWO_GOAL){
            board->pits[i] = 0;
        }
        else{
            board->pits[i] = 4;
        }
    }
}

// Gonna need to make you look a lot prettier
void print_board(struct MANACALA_BOARD *board)
{
    for(int i = 0; i <= BOARD_INDEX; i++){
        std::cout << board->pits[i] << std::endl;
    }
}

void move_pit(struct MANACALA_BOARD *board, int index_pick, int pieces_in_hand)
{

    if(index_pick == PLAYER_ONE_GOAL || index_pick == PLAYER_TWO_GOAL){
        std::cout << "You can not pick a player goal" << std::endl;
        return;
    }

    if(board->pits[index_pick] == 0){
        std::cout << "Nothing to grab. SKIP" << std::endl;
        return;
    }

    // We need to come up with a way to move counter clockwise while decrementing and adding +1 to every pit along the way excluding the other players goal.
    // Maybe subtracting and finding the difference from the board and what we have in hand?
    for(int i = board->pits[index_pick] + pieces_in_hand, current_index = index_pick; i > 0;){

        current_index += 1;

        if(current_index != PLAYER_ONE_GOAL || current_index != PLAYER_TWO_GOAL){
            // This adds 1 to whatever the value of that index is
            board->pits[current_index] += 1;
            i--;
            //std::cout << board->pits[current_index] << std::endl;
        }
    }

    /*if(board->pits[current_index] > 0){
        move_pit(board, current_index, pieces_in_hand);
    }*/
}

int main()
{
    struct MANACALA_BOARD board;

    fill_board(&board);

    //print_board(&board);

    move_pit(&board, 1, 0);

    print_board(&board);
    
    return 0;
}