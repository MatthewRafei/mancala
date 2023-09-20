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

    //board->pits[1] = 1;
    //board->pits[13] = 1;
}

void print_board(struct MANACALA_BOARD *board)
{
    // STRING STREAM?
    std::stringstream current_board;

    // Player 1 goal print
    current_board << " " << board->pits[PLAYER_TWO_GOAL] << " |";

    for(int i{0}; i < 6; i++){
        current_board << std::setw(3) << std::right << board->pits[13 - i];
    }

    current_board << " |";

    // This prints the active player symbol
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

    // This prints the board
    std::cout << current_board.str() << std::endl;
}

void move_pit(struct MANACALA_BOARD *board, int current_index)
{
    /*
        current_player_turn returns 0 or 1 depending on which player is the current player.
        
        1 + (7 * current_player_turn) = 1 || 8
        6 + (7 * current_player_turn) = 6 || 13

        player 1 range is 1 to 6
        player 2 range is 8 to 13

    */
    int index_modifier = 7 * board->current_player_turn;
    int current_player_min_range = 1 + index_modifier;
    int current_player_max_range = 6 + index_modifier;


    if(current_index == PLAYER_ONE_GOAL || current_index == PLAYER_TWO_GOAL){
        std::cout << "You can not pick a player goal" << std::endl;
        return;
    }

    if(current_index > current_player_max_range && current_index < current_player_min_range){
        std::cout << "Pick from the pits only avalible to you" << std::endl;
        return;
    }

    // This is valid. IDK why
    if(board->pits[current_index] == 0){
        std::cout << "Nothing to grab. SKIP" << std::endl;
        return;
    }

    // Take the pieces and put them in the hand
    // then make pit we took pieces from equivlent to 0
    int pieces_in_hand = board->pits[current_index];
    board->pits[current_index] = 0;

    // Conditional if we use to determine current and opposing player goal
    int current_player_goal = (board->current_player_turn == 0) ? PLAYER_ONE_GOAL : PLAYER_TWO_GOAL;
    int opponet_goal = (current_player_goal == PLAYER_ONE_GOAL) ? PLAYER_TWO_GOAL : PLAYER_ONE_GOAL;


    // While pieces in the hand do not equal 0
    while(pieces_in_hand != 0){

        // if current index exceeds 14 reset to 0
        current_index = (current_index + 1) % 14;

        // If current index doesn't equal opponet's goal and pieces in hand are greater than 0
        if(current_index != opponet_goal && pieces_in_hand > 0){
            /*
                if current player places the last piece on and empty pit on their side of the board and mirroring opponet side has pieces greater than 0. 
                Take the last piece the placed down and the pieces in the mirroring pit and put them in current player's goal
            */
            if(pieces_in_hand == 1 && board->pits[current_index] == 0 && board->pits[14 - current_index] > 0 && current_index < current_player_max_range && current_index > current_player_min_range){
                board->pits[current_player_goal] += (board->pits[14 - current_index] + pieces_in_hand);
                pieces_in_hand--;
                board->pits[14 - current_index] = 0;
                board->current_player_turn = !board->current_player_turn;
                return;
            }
            // if player ends in their goal get another turn by returning and skipping the player switch at the end
            else if(pieces_in_hand == 1 && current_index == current_player_goal){
                pieces_in_hand--;
                board->pits[current_index] += 1;
                return;
            }
            // remove a piece from the hand and place it on the current index
            else{
                pieces_in_hand--;
                board->pits[current_index] += 1;
            }
        }
    }
    // This code doesnt work i think
    // Terrible code to jot the logic down so I can work on it later
    /*
    if(board->current_player_turn == 0){
        int current_player_total_pieces = 0;
        for(int i = 1; i < 6; i++){
            current_player_total_pieces += board->pits[i];
        }
        if(current_player_total_pieces == 0){
            for(int i = 8; i < 13; i++){
                current_player_total_pieces += board->pits[i];
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
                current_player_total_pieces += board->pits[i];
                board->pits[PLAYER_ONE_GOAL] += board->pits[i];
                board->pits[i] = 0;
            }
        }
    }
    */
    // END OF TERRIBLE CODE.... I HOPE LOL
    print_current_player(board);

    // Switch boolean current player value
    board->current_player_turn = !board->current_player_turn;
}


int main()
{
    struct MANACALA_BOARD board;

    fill_board(&board);

    print_board(&board);

    return 0;
}