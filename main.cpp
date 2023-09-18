#include <iostream>
#include <iomanip>
#include <sstream>

#define BOARD_INDEX 13
#define PLAYER_ONE_GOAL 7
#define PLAYER_TWO_GOAL 0

struct MANACALA_BOARD{
    int pits[14];
    bool current_player_turn = 1;
};

void print_current_player(MANACALA_BOARD *board)
{
    std::cout << "CURRENT PLAYER: " << board->current_player_turn << std::endl;
}

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

    //board->pits[1] = 1;
    //board->pits[13] = 1;
}

void print_board(struct MANACALA_BOARD *board)
{
    print_current_player(board);


    // STRING STREAM?
    std::stringstream current_board;

    // Player 1 goal print
    current_board << " " << board->pits[PLAYER_TWO_GOAL] << " |";

    for(int i{0}; i < 6; i++){
        current_board << std::setw(3) << std::right << board->pits[13 - i];
    }

    current_board << " |";

    // This prints the active player symbol
    if(board->current_player_turn == 1){
        current_board << " *\n - |";
    }
    else{
        current_board << " -\n * |";
    }

    for(int j{1}; j < 7; j++){
        current_board << std::setw(3) << std::right << board->pits[j];
    }

    current_board << " |" << std::setw(3) << std::right << board->pits[PLAYER_ONE_GOAL] << "\n";

    // This prints the board
    std::cout << current_board.str() << std::endl;
}

void move_pit(struct MANACALA_BOARD *board, int index_pick)
{
    if(index_pick == PLAYER_ONE_GOAL || index_pick == PLAYER_TWO_GOAL){
        std::cout << "You can not pick a player goal" << std::endl;
        return;
    }

    // Change this too while your at it
    if(board->current_player_turn == 0 && (index_pick > 6 || index_pick < 1)){
        std::cout << "Pick from the pits only avalible to you" << std::endl;
        return;
    }
    else if(board->current_player_turn == 1 && (index_pick > 13 || index_pick < 8)){
        std::cout << "Pick from the pits only avalible to you" << std::endl;
        return;
    }

    if(board->pits[index_pick] == 0){
        std::cout << "Nothing to grab. SKIP" << std::endl;
        return;
    }

    int pieces_in_hand = board->pits[index_pick];
    board->pits[index_pick] = 0;

    int current_player_goal = (board->current_player_turn == 0) ? PLAYER_ONE_GOAL : PLAYER_TWO_GOAL;
    int opponet_goal = (current_player_goal == PLAYER_ONE_GOAL) ? PLAYER_TWO_GOAL : PLAYER_ONE_GOAL;

    while(pieces_in_hand != 0){

        index_pick = (index_pick + 1) % 14;

        if(index_pick != opponet_goal && pieces_in_hand > 0){
            if((pieces_in_hand == 1 && board->pits[index_pick] == 0) && board->pits[index_pick] != current_player_goal && board->pits[14 - index_pick] > 0){
                board->pits[current_player_goal] += (board->pits[14 - index_pick] + pieces_in_hand);
                pieces_in_hand--;
                board->pits[14 - index_pick] = 0;
            }
            else{
                pieces_in_hand--;
                board->pits[index_pick] += 1;
            }
        }
    }

    // Terrible code to jot the logic down so I can work on it later
    if(board->current_player_turn == 0){
        int current_player_total_pieces = 0;
        for(int i = 1; i < 6; i++){
            current_player_total_pieces += board->pits[i];
        }
        if(current_player_total_pieces == 0){
            for(int i = 8; i < 13; i++){
                //current_player_total_pieces += board->pits[i];
                board->pits[PLAYER_TWO_GOAL] += board->pits[i];
                board->pits[i] = 0;
            }
        }
    }
    else{
        int current_player_total_pieces = 0;
        for(int i = 8; i < 13; i++){
            current_player_total_pieces += board->pits[i];
        }
        if(current_player_total_pieces == 0){
            for(int i = 1; i < 6; i++){
                //current_player_total_pieces += board->pits[i];
                board->pits[PLAYER_ONE_GOAL] += board->pits[i];
                board->pits[i] = 0;
            }
        }
    }
    // END OF TERRIBLE CODE.... I HOPE LOL

    board->current_player_turn = !board->current_player_turn;
    print_board(board);
}


int main()
{
    struct MANACALA_BOARD board;

    fill_board(&board);

    print_board(&board);

    move_pit(&board, 13);

    std::cout << std::endl;

    return 0;
}