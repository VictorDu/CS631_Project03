#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define LOOPNUMBER 10000
#define DATASIZE 20
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

unsigned long long c1, c2,time, counterTime ;

void counter_start(void)
{
      c1 = ccnt_read();
}

void counter_stop(void)
{
      c2 = ccnt_read();
      time += (c2-c1);
}
void freshMemory(int *data, int size){
    int j;
    for (j = 0; j < size; ++j){
            (*(data + j)) = 0;;
        }
}

void readData(int *data, int cache){
        int count,i;
        int cacheSize;
        cacheSize = (1 << cache);
        time = 0;
        printf("%6dbyte ",cacheSize*4);
        for(count = 0; count < LOOPNUMBER;count++){
                for(i = 0 ; i < cacheSize; i = i + 8){
                reset();
                counter_start();
                counter_stop();
                }
        }
	counterTime = time;
	time = 0;
        for(count = 0; count < LOOPNUMBER;count++){
                for(i = 0 ; i < cacheSize; i = i + 8){
                reset();
                counter_start();
                        (*(data + i))++;
                counter_stop();
                }
        }
	time -= counterTime;
	time = time / (cacheSize / 8);
        printf("%10llu cycles\n",time);
        return;
}

int main(){
        int cache;
        int *data ;
        unsigned adj;
        adj = 32 - ((unsigned)data%32);
        data = data +adj;
        int arrary_size = (1 << DATASIZE-2);
        data= (int *)malloc(sizeof(int) * arrary_size +64);
        freshMemory(data,arrary_size);
        for(cache = 3;cache < 15;cache++){
                freshMemory(data,arrary_size);
                readData(data,cache);
        }
        return 0;
}
