//#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
//#include <malloc.h>
#include <alloca.h>
//#include <nos.h>

#define WRITE_DATA_SIZE 23
#define CACHE_SIZE 14
#define BLOCK_SIZE 4
char* itob(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
	*p++ = '-';
	i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
	++p;
	shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
	*--p = digit[i%10];
	i = i/10;                                                                
    }while(i);                                                                   
    return b;                                                                    
}             
/*unsigned static inline ccnt_read (void)
{
    unsigned cc;
    __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
    return cc;
}*/
void uart_putss(const char* str)
{
    uart_write((const unsigned char*) str, strlen(str));
}
unsigned c1, c2;

void counter_start(void)
{
    //c1 = ccnt_read();
}

void counter_stop(void)
{
    //c2 = ccnt_read();
}

int readData(int *data,int initial, int length){
    int i,temp;
    unsigned c = 0;
        uart_putss("rwh-up");

   // for(i = 0;i < length / 4; i++){

	//counter_start();

	//temp = *(data + i * 4);
	//counter_stop();
    //uart_puts("rwh-up");

    //}
    /*char buf[32];
    //itob(initial, buf);
    uart_puts("rwh-up");
    uart_puts("buf");
    uart_puts("rwh-down");
    uart_putc(" ");
    
    //itob(initial+length, buf);

    uart_puts("buf");
    uart_putc(" ");

    //itob(c, buf);

    uart_puts("buf");
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
    //for(i = 1 ; i <= 3;i++){
    //memset(data,0,(1 << WRITE_DATA_SIZE));
    readData(data1,0,(1<<WRITE_DATA_SIZE));
    //printf("\n");
    //        calculateTime(data,i);
    //printf("\n");
    //}
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

