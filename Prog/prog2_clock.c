#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WRITE_DATA_SIZE 20
#define BLOCK_SIZE 4

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

int main(int argc, char *argv[]){
        int i;
    int j;
    int k;
        int *data ;
    unsigned adj;
    adj = 32 - ((unsigned)data%32);
    data = data +adj;
    data= (int *)malloc(sizeof(int) * (1 <<(WRITE_DATA_SIZE-2)) * 10 +64);
    int arrary_size = (1 <<(WRITE_DATA_SIZE-2)) * 10;
    memset(data,0,(1<<(WRITE_DATA_SIZE-2)) * 10);
    for(j = 1; j<=100; j = j*10){
    counter_start();
        while(*data < j){
            for(k = 0; k<=7;k++){
                for (i =k; i<arrary_size;i=i+8){
                    *(data+i) = *(data+i) +1;
                }
            }
        }
    counter_stop();
    printf("N = %6d  time = %u s\n",j,c2-c1);
    }
    free(data);
    return 0;
}


