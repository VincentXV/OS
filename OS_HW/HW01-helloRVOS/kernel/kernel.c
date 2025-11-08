#include "os.h"

void start_kernel(void)
{
	uart_init();
	uart_puts("Hello, RVOS!\n");

	int i=10;
	int x = 0, y = 0;
	char a = '\0';
	char input = '\0';
	//char input_buf[100];

	kprintf("i=%d\n",i);
	//kscanf("input :%c" ,&a);
	//kprintf("You input char = %c\n", a);
	kscanf("input two integer: %d %d", &x, &y);
	kprintf("You input interger  x = %d, y = %d\n", x, y);
	while(1) {
		
		input = uart_getc();
		if(input != '\0'){
			if(input == 13){
				uart_putc('\n');
				continue;
			}
			uart_putc(input);
		}
	}
}

