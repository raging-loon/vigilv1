#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MALE 2
#define FEMALE 1
struct person{
  int gender;
};

struct person people[30];
int main(){
  srand(time(NULL));
  const int num_students = 30.0;
  const int num_cricket_plyrs = 15.0;
  double num_m = 0.0, num_f = 0.0;
  for(int i = 0; i < num_students; i++){
    struct person * ppl = &people[i];
    printf("Person at %d is ",i);
    if(rand() % 2){
      ppl->gender = MALE;
      printf("MALE\n");
      num_m += 1.0;
    } 
    else {
      ppl->gender = FEMALE;
      printf("FEMALE\n");
      num_f += 1.0;
    }
  }
  printf("Number of MALE: %f\nNumber of FEMALE: %f\n",num_m,num_f);
  double pc_m = num_f/num_students;
  double num_f_cp = (pow(num_f, 2)) + (pow(10.0 - num_f,2));
  printf("Percentage of female cricket players: %f\n",num_f_cp); 
  printf("%02f\n",pc_m);
}