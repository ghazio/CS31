/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */

#include <stdio.h>      // C standard I/O library.
#include <stdlib.h>     // C standard library.
#include <string.h>     // C string library.

#include "readfile.h"   // CS 31 file reading routines.

/* Use #define to define constant values here. */
#define MAXFILENAME (128)
#define ARRAYSIZE   (100)


/* Declare functions and their types here. */
void get_filename_from_commandline(char filename[], int argc, char *argv[]);
int num_list(float nums[],int range);
int bubs_sort(float nums[], int size);

// TODO: Declare your own functions here.

/* Main function.  You don't need to document this one! */
int main (int argc, char *argv[]) {
    /* Create storage space, an array of characters, for the filename string. */
    char filename[MAXFILENAME];

    /* Declare an array to store the floating point values you'll sort. */
    float values[ARRAYSIZE];

    // TODO: Declare any additional variables you need here.
    int check, total;
    float max, min;

    /* This initializes the 'filename' string variable (declared above) with the
     * contents of the command line argument. */
    get_filename_from_commandline(filename, argc, argv);

    // TODO: Open the specified file. (Make sure it succeeded!)
    check = open_file(filename);

    //checks if file is correct, ends program if invalid
    if (check == -1){
      printf("Invaid file name.\n");
      return -1;
    }

    // TODO: Read the file header information.
      read_int(&total);
      read_float(&min);
      read_float(&max);

    // TODO: Tell the user:
    // (1) The name of the file being read
    // (2) How many floats there are
    // (3) The range of values
    printf("The file being reade is %s\n",filename);
    printf("The number of floats is %d\n",total);
    printf("The range of values is from %f to %f\n",min,max);

    // TODO: Read the float values from the file.
    for(int i = 0;i < total;i++){
      read_float(&values[i]);
    }

    // TODO: Print out the unsorted floats on one line, separated by spaces.
    num_list(values,total);

    // TODO: Sort the values in place using your own function.
    bubs_sort(values,total);

    // TODO: Print out the sorted floats on one line, separated by spaces.
    num_list(values,total);

    /* Close the file and terminate the program.
     * Returning 0 from main indicates that the program exited successfully. */
    close_file();
    return 0;
}

// TODO: Define your function body code here.
int num_list(float nums[], int range){
  /* Prints out the values in the array given
   * nums: array given
   * range: range of array given
   * returns 0 when finshed
   */

  printf("The numbers in the file are:\n");

  //prints out values on one line
  for (int i = 0;i < range;i++){
      printf("%f  ", nums[i]);
  }

  printf("\n");
  return 0;
}

int bubs_sort(float nums[], int size){
  /* Sorts the values in an array given from min to max using bubble sort
   * nums
   *
   *
   */
  int temp;
  for(int i = 0; i < size; i++){

    for(int j = 0; j < (size - i-1); j++){

        if (nums[j] > nums[j+1]){

          temp=nums[j];
          nums[j]=nums[j+1];
          nums[j+1]=temp;}}}

return 0;
}

//********************************************************************
// THE FOLLOWING FUNCTION IS PROVIDED FOR YOU
// DO NOT MODIFY, OR DO SO AT YOUR OWN RISK!
//********************************************************************

/* I'm giving you this complete function: DO NOT modify it This function gets
 * the filename passed in as a command line option and copies it into the
 * filename parameter. It exits with an error message if the command line is
 * badly formed.
 *   filename: the string to fill with the passed filename
 *   argc, argv: the command line parameters from main
 *               (number and strings array) */
void get_filename_from_commandline(char filename[], int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: ./sorter <floats file>\n");

        /* exit() function: quits the program immediately... Some errors are
         * not recoverable by the program, so exiting with an error message is
         * reasonable error handling option in this case */
        exit(1);
    }
    if(strlen(argv[1]) >= MAXFILENAME) {
        printf("Filename, %s, is too long, mv to shorter name and try again\n",
                filename);
        exit(1);
    }
    strcpy(filename, argv[1]);
}
