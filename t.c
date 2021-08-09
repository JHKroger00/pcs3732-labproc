/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#include "defines.h"
#include "string.c"

char *tab = "0123456789ABCDEF";
int color;

#include "timer.c"
#include "vid.c"
#include "interrupts.c"
#include "kbd.c"
#include "uart.c"

void copy_vectors(void) {
    extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;

    while(vectors_src < &vectors_end)
       *vectors_dst++ = *vectors_src++;
}

int kprintf(char *fmt, ...);
void timer_handler();

void uart0_handler() {
  uart_handler(&uart[0]);
}
void uart1_handler() {
  uart_handler(&uart[1]);
}

TIMER *tp[4];

void IRQ_handler()
{
    int vicstatus, sicstatus;
    int ustatus, kstatus;

    // read VIC SIV status registers to find out which interrupt
    vicstatus = VIC_STATUS;
    sicstatus = SIC_STATUS;
	
    // kprintf("vicstatus=%x sicstatus=%x\n", vicstatus, sicstatus);
    // VIC status BITs: timer0,1=4, uart0=13, uart1=14, SIC=31: KBD at 3

    if (vicstatus & (1<<4)){   // timer0,1=bit4
       timer_handler(0);
    }   
    if (vicstatus & (1<<12)){   // bit 12: uart0 
         uart0_handler();
    }
    if (vicstatus & (1<<13)){   // bit 13: uart1
         uart1_handler();
    }

    if (vicstatus & (1<<31)){
      if (sicstatus & (1<<3)){
          kbd_handler();
       }
    }
}

int main()
{
   int i; 
   char line[128], string[32]; 
   UART *up;
   
   color = YELLOW;
   row = col = 0; 
   fbuf_init();

   kbd_init();
   
   /* enable timer0,1, uart0,1 SIC interrupts */
   VIC_INTENABLE |= (1<<4);  // timer0,1 at bit4 
   VIC_INTENABLE |= (1<<5);  // timer2,3 at bit5 

   VIC_INTENABLE |= (1<<12); // UART0 at 12
   VIC_INTENABLE |= (1<<13); // UART1 at 13
 
   UART0_IMSC = 1<<4;  // enable UART0 RXIM interrupt
   UART1_IMSC = 1<<4;  // enable UART1 RXIM interrupt

   VIC_INTENABLE |= 1<<31;   // SIC to VIC's IRQ31

   /* enable KBD IRQ */
   SIC_ENSET = 1<<3;  // KBD int=3 on SIC
   SIC_PICENSET = 1<<3;  // KBD int=3 on SIC

   kprintf("Inicio da experiencia de integracao teclado + UART\n");
   timer_init();
   timer_start(0);
   uart_init();
   up = &uart[0]; 

   unlock();
   while(1){
      color = CYAN;
      kprintf("Enter a line from KBD\n");
      kgets(line);
      color = CYAN;
      uprintf("line = %s\n", line);
   }
}
