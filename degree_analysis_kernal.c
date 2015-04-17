//#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
//#include <malloc.h>
#include <alloca.h>
//#include <nos.h>

#define WRITE_DATA_SIZE 17
#define CACHE_SIZE 14
#define BLOCK_SIZE 4

int readData(int *data,int initial, int length){
    int cc1,cc2;
    int i,temp;

    for(i = 0;i < length / 4; i++){
	cc1 = counter_start();
	temp = *(data + i * 4);
	cc2 = counter_stop();
    }
    char buf[32];
    itob(55555, null);
/*    uart_puts(buf);
    uart_putc(" ");
    
    itoa(initial+length, buf);

    uart_puts(buf);
    uart_putc(" ");

    itoa(cc2-cc1, buf);

    uart_puts(buf);
    uart_putc("\n");*/
    return 0;
}

int calculateTime(int *data, int log_of_associativity){
    long dataNumber = 1 << (CACHE_SIZE - log_of_associativity);
    long dataSize = dataNumber>>2;
    int associativity = 1 << (log_of_associativity - 1);
    int i;
    for(i = 0; i < associativity + 1;i++){
	readData(data + 2 * i * dataNumber,2 * i * dataNumber, dataSize);
    }
    readData(data,0,dataSize);
    readData(data,0,dataSize);
    return 0;
}

/*int init_ccr(void)
{
     asm volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));
        uart_puts("User-level access to CCR has been turned on.\r\n");
	  return 0;
}*/

int degreeCalculateTime(){
    int *data = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int *data1 = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i=1;
    //uart_init();
    for(i = 1 ; i <= 3;i++){
//    memset(data,0,(1 << WRITE_DATA_SIZE));
    readData(data1,0,(1 << WRITE_DATA_SIZE));
  //  printf("\n");
            calculateTime(data,i);
 //   printf("\n");
    }
    return 0;
}
int main(){
    int *data = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int *data1 = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 3;i++){
	//memset(data,0,(1 << WRITE_DATA_SIZE));
	readData(data1,0,(1<<WRITE_DATA_SIZE));
	//printf("\n");
	calculateTime(data,i);
	//printf("\n");
    }
    return 0;
}

