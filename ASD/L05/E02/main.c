#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char color_row;
    int value_row;
    char color_col;
    int value_col;
    int conf_in;
} Tile;

void loadBoardAndTiles(Tile *** board, int * N_row, int * N_col, Tile ** collection_tiles, int * N_collection_tiles);
void printBoard(Tile ** board, int N_row, int N_col);
void perm_s_choose_tiles(int * val, int N, int * mark, int * sol, int pos, Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile *** board_max, int * score_max);
void addTilesToBoard(Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile * tiles_to_add, int N_tiles_to_add, Tile *** board_max, int * score_max);
void disp_rip_rotation(int pos,int *val,int *sol,int n,int k, Tile ** _board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile * tiles_to_add, int N_tiles_to_add, Tile *** board_max, int * score_max);
void rotateTiles(Tile ** board, int N_row, int N_col, int * vet_rotation);
int calculateScore(Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles);
void free2D(Tile ** board, int N);


int main() {
    Tile ** board;
    Tile * collection_tiles;
    int N_row, N_col, N_collection_tiles, N_tiles;
    loadBoardAndTiles(&board, &N_row, &N_col, &collection_tiles, &N_collection_tiles);
    printBoard(board, N_row, N_col);
    int * tilesId;
    tilesId = malloc(sizeof(int) * N_collection_tiles);
    for(int i = 0; i < N_collection_tiles; i++) {
        tilesId[i] = i;
    }

    // Initialize board_max before calculation
    Tile ** board_max;
    int score_max = -1;
    board_max = malloc(sizeof(Tile *) * N_row);
    for(int i = 0; i < N_row; i++) {
        board_max[i] = malloc(sizeof(Tile) * N_col);
        for(int j = 0; j < N_col; j++) {
            board_max[i][j].color_col = ' ';
            board_max[i][j].color_row = ' ';
            board_max[i][j].value_col = -1;
            board_max[i][j].value_row = -1;
        }
    }

    int * sol;
    sol = malloc(sizeof(int)*N_collection_tiles);
    int * mark = malloc(sizeof(int)*N_collection_tiles);
    for(int i = 0; i < 9; i++){
        mark[i] = 0;
    }
    perm_s_choose_tiles(tilesId, N_collection_tiles, mark, sol, 0, board, N_row, N_col, collection_tiles, N_collection_tiles, &board_max, &score_max);
    printBoard(board_max, N_row, N_col);
    printf("Score_max: %d\n", score_max);
    free2D(board_max, N_row);
    free2D(board, N_row);
    free(collection_tiles);
    free(sol);
    free(tilesId);
    
}

void loadBoardAndTiles(Tile *** board, int * N_row, int * N_col, Tile ** collection_tiles, int * N_collection_tiles) {
    FILE *fin_board;
    FILE *fin_tiles;
    if((fin_board = fopen("board.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }
    if((fin_tiles = fopen("tiles.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }
    fscanf(fin_tiles, "%d\n", N_collection_tiles);

    Tile * tmp_collection_tiles = malloc(sizeof(Tile) * *N_collection_tiles);
    int * collection_tiles_id_used = malloc(sizeof(int) * *N_collection_tiles);
    int N_collection_tiles_id_used = 0;

    for(int i = 0; i < *N_collection_tiles; i++) {
        fscanf(fin_tiles, "%c %d %c %d\n", &(tmp_collection_tiles[i].color_row), &(tmp_collection_tiles[i].value_row), &(tmp_collection_tiles[i].color_col), &(tmp_collection_tiles[i].value_col));
    }

    fscanf(fin_board, "%d %d", N_row, N_col);
    (*board) = malloc(sizeof(Tile *) * *N_row);
    for(int i = 0; i < *N_row; i++) {
        (*board)[i] = malloc(sizeof(Tile) * *N_col);
        for(int j = 0; j < *N_col; j++) {
            int id, rotation;
            fscanf(fin_board, "%d/%d", &id, &rotation);
            if(id != -1 && rotation != -1) {
                (*board)[i][j].conf_in = 1;
                collection_tiles_id_used[N_collection_tiles_id_used] = id;
                N_collection_tiles_id_used++;
                if(rotation == 1) {
                    // load with rotation
                    (*board)[i][j].color_col = tmp_collection_tiles[id].color_row;
                    (*board)[i][j].value_col = tmp_collection_tiles[id].value_row;
                    (*board)[i][j].color_row = tmp_collection_tiles[id].color_col;
                    (*board)[i][j].value_row = tmp_collection_tiles[id].value_col;
                }
                else {
                    (*board)[i][j].color_col = tmp_collection_tiles[id].color_col;
                    (*board)[i][j].value_col = tmp_collection_tiles[id].value_col;
                    (*board)[i][j].color_row = tmp_collection_tiles[id].color_row;
                    (*board)[i][j].value_row = tmp_collection_tiles[id].value_row;
                }
            }
            else {
                (*board)[i][j].conf_in = 0;
                (*board)[i][j].color_col = ' ';
                (*board)[i][j].value_col = -1;
                (*board)[i][j].color_row = ' ';
                (*board)[i][j].value_row = -1;
            }
        }
    }

    // Update the tiles collection with only the tiles left
    int N_collection_tiles_left = *N_collection_tiles - N_collection_tiles_id_used;
    Tile * collection_tiles_left = malloc(sizeof(Tile) * N_collection_tiles_left);
    int cnt = 0;
    for(int i = 0; i < *N_collection_tiles; i++) {
        int j = 0;
        int found = 0;
        while(j < N_collection_tiles_id_used && found == 0) {
            if(collection_tiles_id_used[j] == i)
                found = 1;
            j++;
        }
        if(found == 0) {
            collection_tiles_left[cnt] = tmp_collection_tiles[i];
            cnt++;
        }
    }
    *collection_tiles = collection_tiles_left;
    *N_collection_tiles = N_collection_tiles_left;
    free(tmp_collection_tiles);

    fclose(fin_board);
    fclose(fin_board);
}

void printBoard(Tile ** board, int N_row, int N_col) {
    for(int i = 0; i < N_row; i++) {
        for(int j = 0; j < N_col; j++) {
            printf("|   %c   |", board[i][j].color_col);
        }
        printf("\n");
        for(int j = 0; j < N_col; j++) {
            if(board[i][j].value_row != -1)
                printf("|%c     %d|", board[i][j].color_row, board[i][j].value_row);
            else
                printf("|%c    %d|", board[i][j].color_row, board[i][j].value_row);
        }
        printf("\n"); 
        for(int j = 0; j < N_col; j++) {
            if(board[i][j].value_col != -1)
                printf("|   %d   |", board[i][j].value_col);
            else
                printf("|   %d  |", board[i][j].value_col);
        }
        printf("\n"); 
        for(int j = 0; j < N_col; j++) {
            printf("|_______|", board[i][j].value_col);
        }
        printf("\n"); 
    }
    printf("\n");
}

void perm_s_choose_tiles(int * val, int N, int * mark, int * sol, int pos, Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile *** board_max, int * score_max) {
    // Generate the possible tiles and the order of how the will be insert in the board
    if(pos >= N) {
        for(int i = 0; i < N; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        Tile * tiles_to_add = malloc(N * sizeof(Tile));
        for(int i = 0; i < N; i++) {
            tiles_to_add[i] = collection_tiles[sol[i]];
        }
        addTilesToBoard(board, N_row, N_col, collection_tiles, N_collection_tiles, tiles_to_add, N, board_max, score_max);
    }
    else {
        for(int i = 0; i < N; i++) {
            if(mark[i] == 0) {
                sol[pos] = val[i];
                mark[i] = 1;
                perm_s_choose_tiles(val, N, mark, sol, pos+1, board, N_row, N_col, collection_tiles, N_collection_tiles, board_max, score_max);
                mark[i] = 0;
            }
            
        }
    }
}

void addTilesToBoard(Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile * tiles_to_add, int N_tiles_to_add, Tile *** board_max, int * score_max) {
    int val[2] = {0, 1};
    int sol[N_tiles_to_add];
    //printf("Disp rip:\n");
    disp_rip_rotation(0, val, sol, 2, N_tiles_to_add, board, N_row, N_col, collection_tiles, N_collection_tiles, tiles_to_add, N_tiles_to_add, board_max, score_max);
    //printf("\n");
}

void disp_rip_rotation(int pos,int *val,int *sol, int n,int k, Tile ** _board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles, Tile * tiles_to_add, int N_tiles_to_add, Tile *** board_max, int * score_max) {
    if(pos >= k) {
        //for(int i = 0; i < k; i++) {
        //    printf("%d ", sol[i]);
        //}
        //printf("\n");

        // Copying _board in order not to alterate the initial state
        Tile ** board;
        int cnt = 0;
        board = malloc(sizeof(Tile *) * N_row);
        for(int i = 0; i < N_row; i++) {
            board[i] = malloc(sizeof(Tile) * N_col);
            for(int j = 0; j < N_col; j++) {
                if(_board[i][j].color_col == ' ' && _board[i][j].value_col == -1 && _board[i][j].color_row == ' ' && _board[i][j].value_row == -1) {
                    board[i][j].color_col = tiles_to_add[cnt].color_col;
                    board[i][j].color_row = tiles_to_add[cnt].color_row;
                    board[i][j].value_col = tiles_to_add[cnt].value_col;
                    board[i][j].value_row = tiles_to_add[cnt].value_row;
                    board[i][j].conf_in = 0;
                    cnt++;
                }
                else {
                    board[i][j].color_col = _board[i][j].color_col;
                    board[i][j].color_row = _board[i][j].color_row;
                    board[i][j].value_col = _board[i][j].value_col;
                    board[i][j].value_row = _board[i][j].value_row;
                    board[i][j].conf_in = _board[i][j].conf_in;
                }
            }
        }
        //printBoard(board, N_row, N_col);
        rotateTiles(board, N_row, N_col, sol);
        //printBoard(board, N_row, N_col);
        int score = calculateScore(board, N_row, N_col, collection_tiles, N_collection_tiles);
        //printf("Score: %d\n", score);
        if(score > *score_max) {
            for(int i = 0; i < N_row; i++) {
                for(int j = 0; j < N_col; j++) {
                    (*board_max)[i][j].color_col = board[i][j].color_col;
                    (*board_max)[i][j].color_row = board[i][j].color_row;
                    (*board_max)[i][j].value_col = board[i][j].value_col;
                    (*board_max)[i][j].value_row = board[i][j].value_row;
                }
            }
            *score_max = score;
        }
        free2D(board, N_row);
    }
    else {
        for(int i = 0; i < n; i++) {
            sol[pos] = val[i];
            disp_rip_rotation(pos+1, val, sol, n, k, _board, N_row, N_col, collection_tiles, N_collection_tiles, tiles_to_add, N_tiles_to_add, board_max, score_max);
        }
    }
}

void rotateTiles(Tile ** board, int N_row, int N_col, int * vet_rotation) {
    int idx_vet_rotation = 0;
    for(int i = 0; i < N_row; i++) {
        for(int j = 0; j < N_col; j++) {
            if(board[i][j].conf_in == 0) {
                if(vet_rotation[idx_vet_rotation] == 1) {
                    // Rotate the tile
                    char tmp_value_row = board[i][j].value_row;
                    char tmp_color_row = board[i][j].color_row;
                    board[i][j].value_row = board[i][j].value_col;
                    board[i][j].color_row = board[i][j].color_col;
                    board[i][j].value_col = tmp_value_row;
                    board[i][j].color_col = tmp_color_row;
                }
                idx_vet_rotation++;
            }
        }
    }
}

int calculateScore(Tile ** board, int N_row, int N_col, Tile * collection_tiles, int N_collection_tiles) {
    int score = 0;
    // Rows score
    for(int i = 0; i < N_row; i++) {
        int j = 0;
        int sum = board[i][j].value_row;
        int same_color = 1;
        while(j < N_col -1) {
            if(board[i][j].color_row != board[i][j+1].color_row) {
                same_color = 0;
            }
            sum+=board[i][j+1].value_row;
            j++;
        }
        if(same_color == 1) {
            score+=sum;
        }
    }
    // Columns score
    for(int j = 0; j < N_col; j++) {
        int i = 0;
        int sum = board[i][j].value_col;
        int same_color = 1;
        while(i < N_row -1) {
            if(board[i][j].color_col != board[i+1][j].color_col) {
                same_color = 0;
            }
            sum+=board[i+1][j].value_col;
            i++;
        }
        if(same_color == 1) {
            score+=sum;
        }
    }
    return score;
} 

void free2D(Tile ** board, int N) {
    for(int i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
}