#include<stdio.h>
#include<time.h>

int main(){
clock_t begin, end;
double time_spent;
int i;
int elements[100];
begin = clock();
/* here, do your time-consuming job */
for(i=0;i<100;i++){
  elements[i]=0; 
}
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("the time for array initialize is %f seconds\n",time_spent);
printf("the time for array initialize is %f seconds\n",time_spent);
return 0;
//return 0;
}

