/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Vasanta Chaganti
 */

#include <stdio.h>
/* Name is Muhammad Ghazi Randhawa*/



/* TODO: Add more functions, one for each question here. */

/* Q1: What is the maximum positive value that can be stored in a C int
 * variable? */
 /*my code in this shows that the maximum positive
 signed possible value is at 2^(n-1)-1 where n is the number of bits*/
void question1() {

  int n_bits,max_val;
  char count;
  n_bits=8;
  max_val=1;
  printf("\n**** Question 1 ****\n");
  printf("An int has 8 bits. However, its first digit would be 0 when it is\n");
  printf("postive. We start with a maximum value of 1.\n");
  printf("We find maximum value by multiplying maximum value by2, 7 times\n");
  for (count=0;count<(n_bits-1);count++){

  max_val=2*max_val;

  printf("maximum: %d\n",max_val);}

  max_val=max_val-1;
  printf("Last step is when subtracting 1 from maximum\n" );
  printf("maximum-1 = %d\n",max_val );
  printf("Hence, an int can store the maximum signed value: %d\n", max_val);
  printf("This is equivalent to 0b11111111. If we add 1, it would overflow\n");
  printf("and would become 0b00000000\n");}
  /*my code in this shows that the maximum positive
  unsigned possible value is at 2^n-1 where n is the number of bits*/

void question2(){
  unsigned int n_bits,max_val;
  char count;
  n_bits=8;
  max_val=1;
  printf("\n**** Question 2 ****\n");
  printf("An unsigned int has 8 bits. However, its 1st digit would be 0 when");
  printf("it is postive. We start with a maximum value of 1 for one bit.\n");
  printf("We find maximum value by multiplying maximum value by2, 8 times\n");
  for (count=0;count<(n_bits);count++){

  max_val=2*max_val;

  printf("maximum: %d\n",max_val);}

  max_val=max_val-1;
  printf("Last step is when subtracting 1 from maximum\n");
  printf("maximum-1 = %d\n",max_val );
  printf("Hence, an int can store the maximum signed value: %d\n", max_val);
  printf("This is equivalent to 0b11111111. If we add 1, it would overflow\n");
  printf("and would become 0b00000000\n");

}
/*my code shows three examples for leftshifting by 1 and then makes the con
*clusion */
void question3(){
  int value1,value2,value3,new_value1,new_value2,new_value3;
  value1=3;
  new_value1=value1<<1;

  value2=7;
  new_value2=value2<<1;

  value3=10;
  new_value3=value3<<1;

  printf("\n**** Question 3 ****\n");

  printf("The result of leftshifting %d by 1 is %d\n",value1,new_value1);
  printf("The result of leftshifting %d by 1 is %d\n",value2,new_value2);
  printf("The result of leftshifting %d by 1 is %d\n",value3,new_value3);
  printf("We can seen that leftshifting by 1 has arithmetic equivalent\n");
  printf("to multiplying the number by 2 \n");

}
/*my code shows three examples for leftshifting by 2 and then makes the con
*clusion */
void question4(){
  int value1,value2,value3,new_value1,new_value2,new_value3;
  value1=11;
  new_value1=value1<<2;

  value2=13;
  new_value2=value2<<2;

  value3=17;
  new_value3=value3<<2;

  printf("\n**** Question 4 ****\n");

  printf("The result of leftshifting %d by 2 is %d\n",value1,new_value1);
  printf("The result of leftshifting %d by 2 is %d\n",value2,new_value2);
  printf("The result of leftshifting %d by 2 is %d\n",value3,new_value3);
  printf("We can see that leftshifting by 2 has arithmetic equivalent\n");
  printf("to multiplying the number by 4 \n");

}
/*my code shows three examples for rightshifting by 1 and then makes the con
*clusion */
void question5(){
  int value1,value2,value3,new_value1,new_value2,new_value3;
  value1=16;
  new_value1=value1>>1;

  value2=20;
  new_value2=value2>>1;

  value3=23;
  new_value3=value3>>1;

  printf("\n**** Question 5 ****\n");

  printf("The result of leftshifting %d by 1 is %d\n",value1,new_value1);
  printf("The result of leftshifting %d by 1 is %d\n",value2,new_value2);
  printf("The result of leftshifting %d by 1 is %d\n",value3,new_value3);
  printf("We can see that leftshifting by 2 has arithmetic equivalent\n");
  printf("to dividing the number by 2 \n");

}


int main() {

  printf("%s's solution to Lab 1 Part2:\n", "GHAZI RANDHAWA");

  /* TODO: Add calls to your question functions here. */
  question1();
  question2();
  question3();
  question4();
  question5();
  return 0;
}
