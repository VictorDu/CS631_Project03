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

static inline unsigned reset(void)
{
   int control=0;
   control|=(0x5<<20);  /* evtcount0 = 0x5 = branches */
   control|=(0x7<<12);  /* evtcount1 = 0x7  = instructions */

   /* x = 0 */
   /* CCR overflow interrupts = off = 0 */
   /* 0 */
   /* ECC overflow interrupts = off = 0 */
   /* D div/64 = 0 = off */
   control|=(1<<2); /* reset cycle-count register */
   control|=(1<<1); /* reset count registers */
   control|=(1<<0); /* start counters */
   unsigned cc;
    __asm__ volatile ("mcr p15, 0, %0, c15, c12, 0\n" : "+r" (control));
   return cc;
}

int init_ccr(void)
{
  asm volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));
  return 0;
}

unsigned long long c1, c2, time, counterTime;

void counter_start(void)
{
      c1 = ccnt_read();
}
void counter_stop(void)
{
      c2 = ccnt_read();
      time += (c2 - c1) ;
}

unsigned long long write_prog1(int *data, int loopNumner, int size){
    int i,j;
    for(i = 0;i<loopNumner;++i){
        reset();
        counter_start();
        for (j = size -1; j>=0 ;j-- )
        {
        }
        counter_stop();
    }
	counterTime = time;
	time = 0;
    for(i = 0;i<loopNumner;++i){
        reset();
        counter_start();
        for (j = size -1; j>=0 ;j-- )
        {
            (*(data + j))++;
        }
        counter_stop();
    }
    return time - counterTime;
}

void freshMemory(int *data, int size){
    int j;
    for (j = 0; j < size; ++j){
            (*(data + j)) = 0;;
        }
}
int main(int argc, char *argv[]){
    time = 0;
    int j;
    int *data ;
    unsigned adj;
    adj = 32 - ((unsigned)data%32);
    data = data +adj;
    data= (int *)malloc(sizeof(int) * (1 <<(WRITE_DATA_SIZE-2)) * 10 +64);
    int arrary_size = (1 <<(WRITE_DATA_SIZE-2)) * 10;
    init_ccr();
    for(j = 1; j<=10000; j = j*10){
        freshMemory(data,arrary_size);
        printf("N = %5d  Time = %llu\n", j, write_prog1(data,j,arrary_size));
    }
    free (data);
    return 0;
}


