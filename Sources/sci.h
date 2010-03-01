
#ifndef __sci_H
#define __sci_H


extern void sci_tx_byte(char s_char);
extern char sci_rx_byte(void);
extern void send_msg(char msg[]);
extern void * HexToAsc(char byte, char *number_str);
extern void * HexToBin(char byte, char *number_str);
extern void * bcd(char byte, char number_str[]);

#endif /* __sci_H */