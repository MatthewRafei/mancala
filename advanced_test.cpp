int main()
{
    struct MANACALA_BOARD board;

    fill_board(&board);

    print_board(&board);

    // p0
    move_pit(&board, 1);
    print_board(&board);

    //p1
    move_pit(&board, 12);
    print_board(&board);
    
    //p0
    move_pit(&board, 1);
    print_board(&board);

    //p1
    move_pit(&board, 8);
    print_board(&board);

    //p0
    move_pit(&board, 3);
    print_board(&board);

    //p1
    move_pit(&board, 9);
    print_board(&board);

    //p1
    move_pit(&board, 8);
    print_board(&board);

    //p0
    move_pit(&board, 6);
    print_board(&board);

    //p1
    move_pit(&board, 8);
    print_board(&board);

    //p0
    move_pit(&board, 4);
    print_board(&board);

    //p1
    move_pit(&board, 8);
    print_board(&board);

    //p0
    move_pit(&board, 6);
    print_board(&board);
    
    //p0
    move_pit(&board, 5);
    print_board(&board);

    return 0;
}