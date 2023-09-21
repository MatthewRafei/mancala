#include <iostream>
#include <iomanip>
#include <sstream>

#define PLAYER_ONE_GOAL 7
#define PLAYER_TWO_GOAL 0

struct MANACALA_BOARD{
    int pits[14];
    bool current_player_turn = 0;
};

void print_current_player(MANACALA_BOARD *board)
{
    std::cout << "CURRENT PLAYER: " << board->current_player_turn << std::endl;
}

void fill_board(struct MANACALA_BOARD *board)
{
    for(int i = 0; i <= 13; i++){
        if(i == PLAYER_ONE_GOAL || i == PLAYER_TWO_GOAL){
            board->pits[i] = 0;
        }
        else{
            board->pits[i] = 4;
        }
    }

    // Test players goals
    //board->pits[PLAYER_ONE_GOAL] = 1;
    //board->pits[PLAYER_TWO_GOAL] = 2;

    // Test functionality of move
    //board->pits[1] = 1;
    //board->pits[13] = 1;
}

bool is_player_field_empty(struct MANACALA_BOARD *board)
{
    if(board->pits[8] == 0 && board->pits[9] == 0 && board->pits[10] == 0 && board->pits[11] == 0 && board->pits[12] == 0 && board->pits[13] == 0){
        for(int i = 1; i <= 6; i++){
            board->pits[PLAYER_ONE_GOAL] += board->pits[i];
            board->pits[i] = 0;
        }
        return true;
    }

    if(board->pits[1] == 0 && board->pits[2] == 0 && board->pits[3] == 0 && board->pits[4] == 0 && board->pits[5] == 0 && board->pits[6] == 0){
        for(int i = 8; i <= 13; i++){
            board->pits[PLAYER_TWO_GOAL] += board->pits[i];
            board->pits[i] = 0;
        }
        return true;
    }

    return false;
}

void print_board(struct MANACALA_BOARD *board)
{
    std::stringstream current_board;

    current_board << " " << board->pits[PLAYER_TWO_GOAL] << " |";

    for(int i{0}; i < 6; i++){
        current_board << std::setw(3) << std::right << board->pits[13 - i];
    }

    current_board << " |";

    if(board->current_player_turn == 0){
        current_board << " *\n - |";
    }
    else{
        current_board << " -\n * |";
    }

    for(int j{1}; j < 7; j++){
        current_board << std::setw(3) << std::right << board->pits[j];
    }

    current_board << " |" << std::setw(3) << std::right << board->pits[PLAYER_ONE_GOAL] << "\n";

    std::cout << current_board.str() << std::endl;
}

void move(struct MANACALA_BOARD *board, int current_index)
{
    if(current_index == PLAYER_ONE_GOAL || current_index == PLAYER_TWO_GOAL){
        std::cout << "You can not pick a player goal" << std::endl;
        return;
    }

    int index_modifier = 7 * board->current_player_turn;
    int current_player_min_range = 1 + index_modifier;
    int current_player_max_range = 6 + index_modifier;

    if(current_index < current_player_min_range || current_index > current_player_max_range){
        std::cout << "Pick from the pits only avalible to you" << std::endl;
        return;
    }

    if(board->pits[current_index] == 0){
        std::cout << "Nothing to grab. SKIP" << std::endl;
        return;
    }

    // Because there was one last index I was putting in the hand making all indexs on player side zero these conditions ran pre-maturely
    // But now this condition isn't getting checked after a move is finished....
    int pieces_in_hand = board->pits[current_index];
    board->pits[current_index] = 0;

    int current_player_goal = (board->current_player_turn == 0) ? PLAYER_ONE_GOAL : PLAYER_TWO_GOAL;
    int opponet_goal = (current_player_goal == PLAYER_ONE_GOAL) ? PLAYER_TWO_GOAL : PLAYER_ONE_GOAL;

    while(pieces_in_hand != 0){
        
        current_index = (current_index + 1) % 14;

        if(current_index == opponet_goal){
            continue;
        }

        if(pieces_in_hand == 1 && board->pits[current_index] == 0 && current_index > current_player_min_range && current_index < current_player_max_range){
            board->pits[current_player_goal] += (board->pits[14 - current_index] + pieces_in_hand);
            pieces_in_hand--;
            board->pits[14 - current_index] = 0;
            board->current_player_turn = !board->current_player_turn;
            // check if player field is empty
            if(board->pits[1] == 0 && board->pits[2] == 0 && board->pits[3] == 0 && board->pits[4] == 0 && board->pits[5] == 0 && board->pits[6] == 0 && pieces_in_hand <= 0){
                for(int i = 8; i <= 13; i++){
                    board->pits[PLAYER_TWO_GOAL] += board->pits[i];
                    board->pits[i] = 0;
                }
            }
            if(board->pits[8] == 0 && board->pits[9] == 0 && board->pits[10] == 0 && board->pits[11] == 0 && board->pits[12] == 0 && board->pits[13] == 0 && pieces_in_hand <= 0){
                for(int i = 1; i <= 6; i++){
                    board->pits[PLAYER_ONE_GOAL] += board->pits[i];
                    board->pits[i] = 0;
                }
            }
            return;
        }

        // This block of code returns to give the player another pick of a pit.
        // Because of this we can't check to see if his field is empty.
        if(pieces_in_hand == 1 && current_index == current_player_goal){
            pieces_in_hand--;
            board->pits[current_index]++;
            if(board->pits[1] == 0 && board->pits[2] == 0 && board->pits[3] == 0 && board->pits[4] == 0 && board->pits[5] == 0 && board->pits[6] == 0 && pieces_in_hand <= 0){
                for(int i = 8; i <= 13; i++){
                    board->pits[PLAYER_TWO_GOAL] += board->pits[i];
                    board->pits[i] = 0;
                }
            }
            if(board->pits[8] == 0 && board->pits[9] == 0 && board->pits[10] == 0 && board->pits[11] == 0 && board->pits[12] == 0 && board->pits[13] == 0 && pieces_in_hand <= 0){
                for(int i = 1; i <= 6; i++){
                    board->pits[PLAYER_ONE_GOAL] += board->pits[i];
                    board->pits[i] = 0;
                }
            }
            return;
        }
        
        pieces_in_hand--;
        board->pits[current_index]++;

    }

        if(board->pits[1] == 0 && board->pits[2] == 0 && board->pits[3] == 0 && board->pits[4] == 0 && board->pits[5] == 0 && board->pits[6] == 0 && pieces_in_hand <= 0){
            for(int i = 8; i <= 13; i++){
                board->pits[PLAYER_TWO_GOAL] += board->pits[i];
                board->pits[i] = 0;
            }
        }
        if(board->pits[8] == 0 && board->pits[9] == 0 && board->pits[10] == 0 && board->pits[11] == 0 && board->pits[12] == 0 && board->pits[13] == 0 && pieces_in_hand <= 0){
            for(int i = 1; i <= 6; i++){
                board->pits[PLAYER_ONE_GOAL] += board->pits[i];
                board->pits[i] = 0;
            }
        }

    board->current_player_turn = !board->current_player_turn;
}

int main()
{
    struct MANACALA_BOARD board;

    fill_board(&board);

    print_board(&board);

    // p0
    print_current_player(&board);
    move(&board, 1);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 12);
    print_board(&board);
    
    //p0
    print_current_player(&board);
    move(&board, 1);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 8);
    print_board(&board);

    //p0
    print_current_player(&board);
    move(&board, 3);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 9);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 8);
    print_board(&board);

    //p0
    print_current_player(&board);
    move(&board, 6);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 8);
    print_board(&board);

    //p0
    print_current_player(&board);
    move(&board, 4);
    print_board(&board);

    //p1
    print_current_player(&board);
    move(&board, 8);
    print_board(&board);

    //p0
    print_current_player(&board);
    move(&board, 6);
    print_board(&board);
    
    //p0
    print_current_player(&board);
    move(&board, 5);
    print_board(&board);

    // These two aren't in the original test case?
    // Re-check indexing conversion to make sure you did it right or if original test is actually incorrect.
    //p1
    /*
    print_current_player(&board);
    move(&board, 9);
    print_board(&board);

    //p0
    print_current_player(&board);
    move(&board, 6);
    print_board(&board);
    */

    return 0;
}