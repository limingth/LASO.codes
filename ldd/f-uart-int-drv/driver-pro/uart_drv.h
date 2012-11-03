

int uart_putchar(char c);
void uart_write_utxh(char c);

char uart_getchar(void);
char uart_read_urxh(void);

void uart_init(int which);
void uart_set_baudrate(int br);
void uart_enable_fifo(void);

