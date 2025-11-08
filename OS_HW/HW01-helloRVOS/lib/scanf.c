#include "os.h"

static char input_buf[1000]; // buffer for _vscanf() to store varables

static int _vsnscanf(size_t n, const char* s, va_list vl){
    int format = 0;
	int longarg = 0;
	size_t pos = 0;
	for (; *s; s++) {
		if (format) {
			switch(*s) {
                case 'd': {
                    int sign = 1;
                    int digit = 0;
                    char input = '\0';
                    // 吃掉空白
                    do{
                        input = uart_getc();
                        if(input == 13){
                            uart_putc('\n');
                        }
                        else{
                            uart_putc(input);
                        }
                        
                    }while(input == ' ' || input == '\n');

                    // 判斷正負號
                    if(input == '-') {
                        sign = -1;
                        input = uart_getc();
                        uart_putc(input);
                    }

                    // 處理數字
                    while(1){
                        if(input >= '0' && input <= '9'){
                            digit = digit *10 + (input - '0');
                        }
                        else{
                            digit = sign * digit;
                            break;
                        }
                        input = uart_getc();
                        uart_putc(input);
                    }
                    int *p = va_arg(vl, int *);
                    *p = digit;
                    pos++;
                    longarg = 0;
                    format = 0;
                    break;
                }
                case 's': {
                    
                    break;
                }
                case 'c': {
                    char input = '\0';
                    do{
                        input = uart_getc();
                        uart_putc(input);
                    }while(input == ' ');
                    char *p = va_arg(vl, char *);
                    *p = input;
                    pos++;
                    longarg = 0;
                    format = 0;
                    break;
                }
                default:
                    break;
            }
        } else if (*s == '%') {
			format = 1;
		} else {
			uart_putc(*s);
			pos++;
		}
    }
	uart_putc('\n');
	return pos;
}

static int _vscanf(const char* s, va_list vl){
    int res = 0;
	res = _vsnscanf(1000, s, vl);
	return (res + 1);
}

int kscanf(const char *s, ...)
{
    int res = 0;
    va_list vl;
    va_start(vl, s);
	res = _vscanf(s, vl);
	va_end(vl);
    return res;
}