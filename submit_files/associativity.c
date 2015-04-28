#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WRITE_DATA_SIZE 25 
#define CACHE_SIZE 14
#define BLOCK_SIZE 4
#define TIMES 10000
static inline unsigned ccnt_read (void)
{
      unsigned cc;
        __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
          return cc;
}

unsigned c1, c2 ;
void counter_start(void)
{
      c1 = ccnt_read();
}

void counter_stop(void)
{
      c2 = ccnt_read();
}

int calculateTime(int *data, int log_of_associativity){
    unsigned c =0;
    long dataNumber = 1 << (CACHE_SIZE - log_of_associativity);
    long dataSize = 1;
    int associativity = 1 << (log_of_associativity - 1);
    int i,counter;
    for(counter = 0; counter < TIMES;counter++){
       for(i = 0; i < associativity;i++){ 
           counter_start();
           counter_stop();
           counter_start();
           (*(data + 2 * i * dataNumber))++;
           counter_stop();
           c += c2-c1;
       }
    }
    double times = TIMES * associativity;
    printf("Cycles for %3d way: %u\n", associativity,c/associativity );
    return 0;
}

int main(){
    int *data1 = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    printf("***************************************\n");
    printf("result for read one integer 10000 times\n");
    printf("***************************************\n");
    for(i = 1 ; i <= 8;i++){
        void *p;
        int *data_i ;
        p = malloc(sizeof(int) * (1 <<WRITE_DATA_SIZE)+32);
        unsigned adj;
        adj = 32 - ((unsigned)p%32);
        p = p +adj;
        data_i = (int *) p;

        memset(data_i,0,(1 << WRITE_DATA_SIZE));
        memset(data1,0,(1 << WRITE_DATA_SIZE));

        calculateTime(data_i,i);
    }
    return 0;
}
