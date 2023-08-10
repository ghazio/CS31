/* Names: Sidhika Tripathee and Ghazi
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readfile.h"


float *get_values(int *size, int *capacity, char *filename);
void printer(float* array, int* num_count);
void copy_array(float* old_array, float* new_array, int initial_size);
void bubs_sort(float* array, int* size);
double mean_calc(float* array,int* size);
double median_calc(float* array,int* size);
double stddev(float* array,int* size, double mean);


int main(int argc, char **argv) {
  int size;
  int capacity;
    if(argc != 2) {
        printf ("usage: ./stats filename\n");
        exit(1);
    }

    /* argv[1] contains filename string (pass argv[1] as the
     * third argument to get_values) */
    printf("Reading from file: %s\n", argv[1]);
    float *array=get_values(&size, &capacity, argv[1]);
    bubs_sort(array, &size);
    double mean= mean_calc(array,&size);
    double median= median_calc(array,&size);
    double std= stddev(array,&size,mean);

    printf("Results: \n-----------\n");
    printf("num values:\t %d\n", size);
    printf("mean:\t %f\n", mean);
    printf("median:\t %f\n", median);
    printf("std dev:\t %f\n", std);
    printf("unused array capacity:\t %d\n", capacity-size);

    close_file();
    }


/*
 *Returns an array of float values that stores the values read in from the file
  Assigns size and capacity values
 */
float *get_values(int *size, int *capacity, char *filename){
    int ret, ret_float, i;
    ret_float=0;
    i=0;
    *size =-1;
    *capacity =20;
    float* new_array;
    //allocates memory to an array with initial capacity of 20
    float* array_one = malloc((*capacity) * (sizeof(float)));

    //returns null if malloc fails
    if(array_one==NULL){
      printf("Malloc error");
      return NULL;
    }

    //opens file
    ret= open_file(filename);
    if(ret == -1) { //if open_file is not succesful
      printf("This file cannot be opened, try again!\n");
      return NULL;
    }
      //reads next value of file until there is no more left
      while(ret_float!=-1){
      //  ret_float= read_float(&array_one[*size]);
        *size= *size+1;
        //if size is greater than capacity
        if(*size>=*capacity){
          *capacity= *capacity*2; //double capacity
          //creates new array with double capacity
          new_array = malloc((*capacity)*(sizeof(float)));
          //if malloc fails, returns null
          if(new_array==NULL){
            printf("Malloc error");
            return NULL;
          }
          //copies values of old array to new array
          copy_array(array_one,new_array,*size);
          free(array_one);
          array_one=new_array;

        }
        //reads floats from file and assigns it as value of array's next element
        ret_float= read_float(&array_one[*size]);

      }

return array_one;
}

//Takes in an array and the array size
//prints the array
//used for testing purposes
void printer(float* array, int* num_count){
    for (int i =0; i<*num_count-1; i++){
      printf("%f, ", array[i]);
    }
    printf("%f\n", array[*num_count-1]);
  }

/* Takes in two array and size of the old array
  Copies values of the first array into second array
*/
 void copy_array(float* old_array, float* new_array, int initial_size){
   for (int i=0; i<initial_size;i++){
     new_array[i]=old_array[i];
      }
 }

/*Takes in a dynamically allocated array and its size
Sorts the array using bubble sort from least to greatest
*/
 void bubs_sort(float* array, int* size){
   float temp;
   for(int i = 0; i < *size; i++){
     for(int j = 0; j < (*size - i-1); j++){
       //if first value is larger than second value
         if (array[j] > array[j+1]){
           //swap values
           temp=array[j];
           array[j]=array[j+1];
           array[j+1]=temp;}}}
 }

/*Takes in a dynamically allocated array and its size
Calculates the mean of the values in the array
returns the mean as a double
*/
 double mean_calc(float* array,int* size){
  double sum=0;
  double mean;
  //Calculates sum of values in array
  for(int i = 0; i<*size;i++){
      sum+=array[i];
    }
    mean=sum/(*size);
    return mean;
  }

  /*Takes in a dynamically allocated array and its size
  Calculates the median of the values in the array assuming it is already sorted
  returns the median as a double
  */
 double median_calc(float* array,int* size){
   int middle_index;
   double median;
   //if there are an even number of elements in array
   if (*size%2 == 0){
     middle_index=*size/2;
     //Calculates the average of the two middle values
     median=(array[middle_index]+array[middle_index+1])/2.0;
   }
   else{ //if there are an odd number of elements in array
     middle_index=(*size+1)/2;
     median=array[middle_index];
   }
   return median;
 }

 /*Takes in a dynamically allocated array, mean of the array and its size
 Calculates the standard deviation of the values in the array
 returns the standard deviation as a double
 */
 double stddev(float* array,int* size, double mean){
   double std,difference,diff_squared;
   double sum_diff_squared=0;

   for(int i=0;i<*size;i++){
     //Calculates the difference between each value of the array
     //and the mean of all the values in the array
      difference=array[i]-mean;
    //squares the difference calculated above
      diff_squared=pow(difference,2);
    //sums up the square of the differences
      sum_diff_squared+=diff_squared;
   }
   //divides the sum calculated above with size-1 (N-1)
   double undersqrt=(sum_diff_squared/((*size)-1));
   //takes the square root of the value calculated above to get the
   //standard deviation of all the values in the array
   std=sqrt(undersqrt);

   return std;
 }
