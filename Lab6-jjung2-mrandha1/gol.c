/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professors Tia Newhall, Kevin Webb, Vasanta Chaganti
 */

#include <cgridvisi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/* The three possible output modes your GOL simulation might be using. */
#define OUTPUT_NONE (0)
#define OUTPUT_TEXT (1)
#define OUTPUT_VISI (2)

/* This struct represents all the data you need to keep track of your GOL
 * simulation.  Rather than passing individual arguments into each function,
 * we'll pass in everything in just one of these structs.
 *
 * NOTE: You need to use the provided fields here, but you'll also need to
 * add some of your own. */
struct gol_data {
    /* The number of rows on your GOL game board. */
    int rows;

    /* The number of columns on your GOL game board. */
    int cols;

    /* The number of iterations to run your GOL simulation. */
    int iters;

    /* Which form of output we're generating:
     * 0: only print the first and last board (good for timing).
     * 1: print the board to the terminal at each round.
     * 2: draw the board using the visualization library. */
    int output_mode;

    /* The initial number of alive cells in our GOL game board */
    int numAlive;

    /* This keeps a record of our game board in terms of 0 for dead, 1 for
    alive */
    int* board;

    /*This keeps a record of the indices of our intial alive coordinates */
    int* indicesAlive;

    /*This records the next step for each coordinate*/
    int* nextStepBoard;

};

/* These are necessary for the visualization library.  Don't change these! */
void visi_run_animation(struct gol_data *data);
void initializer(char* file_name, char* mode, struct gol_data* data);
void nextstepcalc(struct gol_data* data, int i, int j, int index);
int getNeighbors(int x, int y, struct gol_data* data);
void updateBoard(struct gol_data*data);
int checkNeighbor(int x, int y, struct gol_data* data);

static char visi_name[] = "GOLVisi";

/* Prints the board to the terminal.*/

void print_board(struct gol_data *data, int round) {
    int i, j;
    int live = 0;
    int index=0;
    /* Print the round number. */
    fprintf(stderr, "Round: %d\n", round);

    for (i = 0; i < data->rows; ++i) {
        for (j = 0; j < data->cols; ++j) {
            index = data->rows *(i) + j;
            //if cell is alive
            if (data->board[index]==1){
              live += 1;
              fprintf(stderr, " @");
            }

          //otherwise
            else{
              fprintf(stderr, " _");
              }
        }
        fprintf(stderr, "\n");
    }

    /* Print the total number of live cells. */
    fprintf(stderr, "Live cells: %d\n", live);

    /* Add some blank space between rounds. */
    fprintf(stderr, "\n\n");
}

/* Performs one round of the GOL simulation.*/

void gol_step(color3 *buff, struct gol_data* data) {
    int i, j, index;

    //dynamically allocate our next step board
    data->nextStepBoard = malloc(sizeof(int)*(data->rows)*(data->cols));
    if (data->nextStepBoard == NULL){
      printf("ERROR: Out of memory\n");
  		exit(1);
    }

    for (i = 0; i < data->rows; ++i) {
        for (j = 0; j < data->cols; ++j) {
          index = data->cols *(i) + j;
          nextstepcalc(data, i, j, index);

            /* When using visualization, also update the graphical board. */
            if (buff != NULL) {
                /* Convert row/column number to an index into the
                 * visualization grid.  The graphics library uses coordinates
                 * that place the origin at a different location from your
                 * GOL board. You shouldn't need to change this. */
                int buff_index = (data->rows - (i + 1)) * data->cols + j;

                // TODO: if the cell should be displayed as alive
                if (data->board[index]==1){
                    buff[buff_index].r = 0;
                    buff[buff_index].g = 255;
                    buff[buff_index].b = 0;
                  }
                else{
                    buff[buff_index].r = 0;
                    buff[buff_index].g = 0;
                    buff[buff_index].b = 0;
                  }
            }
        }
    }
    updateBoard(data);
    free(data->nextStepBoard);

    /* When using text/graphical output, add a delay and clear the terminal.
     * You can adjust/disable these however you like while debugging. */
    if (data->output_mode > 0) {
        usleep(100000);
        system("clear");
    }
}

int main(int argc, char **argv) {
    int i;
    struct gol_data data;
    double secs = 0.0;
    struct timeval start_time, end_time;

    /* Ensures that the user gives us the correct number of arguments. */
    if (argc != 3) {
        printf("Wrong number of arguments.\n");
        printf("Usage: %s <input file> <0|1|2>\n", argv[0]);
        return 1;
    }

    //initializes our struct
    initializer(argv[1],argv[2], &data);
    //stores the time at start_time struct
    gettimeofday(&start_time, NULL);

    //selects the output mode as per input
    if(data.output_mode == OUTPUT_NONE) {

        /* Run with no output. */
        for (i = 0; i < data.iters; i++) {
            gol_step(NULL, &data);
        }

    } else if (data.output_mode == OUTPUT_TEXT) {

        /* Print at each round. */
        for (i = 0; i < data.iters; i++) {
            print_board(&data, i);
            gol_step(NULL, &data);
        }

        /* Print final board state. */
        print_board(&data, data.iters);
    } else if (data.output_mode == OUTPUT_VISI) {

        /* Run the simulation with graphics. */
        visi_run_animation(&data);

    } else {
        /* User asked for an invalid output mode. */
        printf("Unknown output mode: %d\n", data.output_mode);
        exit(1);
    }
    gettimeofday(&end_time, NULL);

    secs = end_time.tv_sec*1000000+end_time.tv_usec
     -(start_time.tv_sec*1000000+start_time.tv_usec);
     secs=secs/1000000;


    /* Print the total runtime, in seconds. */
    printf("\nTotal time: %0.3f seconds.\n", secs);

    free(data.board);

    return 0;
}
/*
Inputs: The name of the file that is inputted into the command line, the
mode that we want to run, and the pointer to our gol_data data struct
Purpose: The purpose of this function is to initialize our game of life
data struct.
Returns: none
*/
void initializer(char* file_name, char* mode, struct gol_data* data){
  FILE* infile;
  int output_mode,ret;
  int x_value, y_value, index;
  int trackerIndex=0;

  infile=fopen(file_name,"r"); //opens the file in read-only mode
  if (infile == NULL) { //tells us if the file did not open
    perror("fopen");
    exit(1);
  }
  //fscanf reads each successive line and stores the integer value in the given
  //address
  fscanf(infile, "%d", &data->rows);
  fscanf(infile, "%d", &data->cols);
  fscanf(infile, "%d", &data->iters);
  fscanf(infile, "%d", &data->numAlive);

  //dynamically allocate an array that stores the indices of our initial
  //alive coordinates
  data->indicesAlive = malloc(sizeof(int)*(data->numAlive));

  //quits if there is no space available
  if (data->indicesAlive == NULL){
    printf("ERROR: Out of memory\n");
		exit(1);
  }
  //dynamically allocate an array that stores the state of our board
  data->board = malloc(sizeof(int)*(data->rows)*(data->cols));
  //quits if there is no space available
  if (data->board == NULL){
    printf("ERROR: Out of memory\n");
		exit(1);
  }
  //reads and stores the coordinates of our initially alive

  for (int i=0; i<data->numAlive; i++){
    ret = fscanf(infile, "%d %d", &x_value, &y_value);
    if (ret != 2){
      printf("invalid data in file\n");
      exit(1);
    }
    index = data->cols *(x_value) + y_value;
    data->indicesAlive[i]= index;

}

  //initializes our board with 0's in all coordinates
  for (int i=0; i<(data->rows)*(data->cols); i++){
      data->board[i] = 0;
  }

  //inserts 1 in the initially alive coordinates 
  for (int i=0; i<data->numAlive; i++){
    trackerIndex=data->indicesAlive[i];
    data->board[trackerIndex]=1;
  }

  output_mode = atoi(mode);
  data->output_mode = output_mode;

  free(data->indicesAlive);
  //close file
  fclose(infile);

}
/*
Inputs: The pointer to our gol_data data struct, our x and y coordinates, and
the corresponding index for our dynamically allocated array
Purpose: The purpose of this function is to find the state of the board given
the state of its neighbors
Returns: none
*/
void nextstepcalc(struct gol_data* data, int i, int j,int index){
  int  n_aliveNeighbors; //number of neighbors that are currently alive
  n_aliveNeighbors = getNeighbors(i, j, data);

  if (data->board[index] == 1){
    if (n_aliveNeighbors <= 1){
      data->nextStepBoard[index] = 0;
    }
    else if (n_aliveNeighbors >= 4){
      data->nextStepBoard[index] = 0;
    }
    else{
      data->nextStepBoard[index] = data->board[index];
    }
  }
  else {
    if (n_aliveNeighbors == 3){
      data->nextStepBoard[index] = 1;
    }
    else {
      data->nextStepBoard[index] = data->board[index];
    }

  }

}
/*
Inputs: The pointer to our gol_data data struct, our x and y coordinates
Purpose: The purpose of this function is to find the number of alive neighbors
given a certain x and y coordinate
Returns: the number of alive neighbors
*/
int getNeighbors(int x, int y, struct gol_data* data){

    int alive_neighbors, n1, n2, n3, n4, n5, n6, n7, n8 = 0;

    n1 =checkNeighbor(((x-1)+data->cols)%data->cols,y%data->rows,data);
    n2 =checkNeighbor(((x-1)+data->cols)%data->cols,((y-1)+data->rows)%data->rows,data);
    n3 =checkNeighbor(x%data->cols,((y-1)+data->rows)%data->rows,data);
    n4 =checkNeighbor(((x+1)+data->cols)%data->cols,((y-1)+data->rows)%data->rows,data);
    n5 =checkNeighbor(((x+1)+data->cols)%data->cols,y%data->rows,data);
    n6 =checkNeighbor(((x+1)+data->cols)%data->cols,((y+1)+data->rows)%data->rows,data);
    n7 =checkNeighbor(x%data->cols,((y+1)+data->rows)%data->rows,data);
    n8 =checkNeighbor(((x-1)+data->cols)%data->cols,((y+1)+data->rows)%data->rows,data);
    alive_neighbors = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;

    return alive_neighbors;
    }

/*
Inputs: The pointer to our gol_data data struct, our x and y coordinates
Purpose: The purpose of this function is to see if the cell is alive or dead
Returns: 1 if alive, 0 if dead
*/
int checkNeighbor(int x, int y, struct gol_data* data){
    int index = 0;

    index = data->cols *x + y;
    if (data->board[index] == 1){
      return 1;
  }
    return 0;
}

/*
Inputs: The pointer to our gol_data data struct
Purpose: The purpose of this function is to copy the next step onto our board
Returns: none
*/
void updateBoard(struct gol_data* data) {
  for (int i = 0; i<(data->rows)*(data->cols); i++){
    data->board[i] = data->nextStepBoard[i];
  }
}



/**********************************************************/
/* DO NOT modify the functions below!                     */
/**********************************************************/
void run_gol(color3 *buff, void *appl_data) {
    gol_step(buff, (struct gol_data *)appl_data);
}
void visi_run_animation(struct gol_data *data) {
    init_and_run_animation(data->rows, data->cols, (void *)data, run_gol,
            visi_name, data->iters);
}
