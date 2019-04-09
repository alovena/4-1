/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2019-04-09
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 7.372800 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

//#include <io.h>
#include <mega128.h>
#include <delay.h>
#include <stdio.h>

const unsigned char fnd_font[] = 

{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,
   // C,    d,    A,    u,    T,    r,   b,  blk
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c, 0x00
};

// fnd maseg display             
#define O   0x0d   //o display
#define F   0x0f    // F display  
#define H   0x0a    // H   "
#define L   0x0b    // L   "
#define E   0x0c    // E   "
#define P   0x0e    // P   " 
#define C   0x10    // C   "
#define D   0x11    // d   "
#define A   0x12    // A   "  
#define U   0x13    // u   "
#define T   0x14    // t   "
#define R   0x15    // r   "    
#define b   0x16    // b   "
#define BLK 0x00   // fnd blk display

#define fnd_out(val)  PORTD = val
#define fnd_outa(val) PORTF = val
#define led_out(val)  PORTE = val

#define x1000 PORTA.0
#define x100  PORTA.1
#define x10   PORTA.2
#define x1    PORTA.3

#define x1000a PORTE.0
#define x100a  PORTE.1
#define x10a   PORTE.2
#define x1a    PORTE.3

bit run_flag = 0;
bit on_flag;
bit tg_flag = 0;

char scan = 0, scan_a=0;

struct loop
 {
   int cnt;
   int loop; 
 }cnt = {0,0};
 


void fnd_dis_k(int data)
{
 scan++;
 if(scan > 4) scan = 1;
 
 switch(scan)
 {
  case 1: // x1000
          x1 = 1; // 1 digit off
          fnd_out(fnd_font[data/1000]);
          x1000 = 0; // 1000 digit on 
    break;        
    
  case 2: // x100
          x1000 = 1; // 1000 digit off
          fnd_out(fnd_font[data%1000/100] | 0x80);
          x100 = 0; // 100 on 
    break;        
  
  case 3: // x1000
          x100 = 1; // 100 digit off
          fnd_out(fnd_font[data%100/10]);
          x10 = 0; // 10 on 
    break;        
  
  case 4: // x1
          x10 = 1; // 10 digit off 
          if(tg_flag)fnd_out(fnd_font[data%10] |0x80);
          else fnd_out(fnd_font[data%10] & 0x7f);
          x1 = 0; 
    break;        
 } 
}


void fnd_dis_a(int data)
{
 scan_a++;
 if(scan_a > 4) scan_a = 1;
 
 switch(scan_a)
 {
  case 1: // x1000
          x1a = 0; // 1 digit off
          fnd_outa(~fnd_font[data/1000]);
          x1000a = 1; // 1000 digit on 
    break;        
    
  case 2: // x100
          x1000a = 0; // 1000 digit off
          fnd_outa(~fnd_font[data%1000/100]);
          x100a = 1; // 100 on 
    break;        
  
  case 3: // x1000
          x100a = 0; // 100 digit off
          fnd_outa(~fnd_font[data%100/10]);
          x10a = 1; // 10 on 
    break;        
  
  case 4: // x1
          x10a = 0; // 10 digit off 
          fnd_outa(~fnd_font[data%10]);
          x1a = 1; 
    break;        
 } 
}

void main(void)
{
  DDRA = 0xff;
  DDRF = 0xff;
  DDRD = 0xff;
  DDRE = 0xff;
   
while (1)
      {   
        delay_ms(1);   
        cnt.loop++;
        if(cnt.loop > 380)
         {
           cnt.loop = 0;
           cnt.cnt++;
           if(cnt.cnt > 9999) cnt.cnt = 0;   
           
           tg_flag = ~tg_flag;
         }
      
       fnd_dis_k(cnt.cnt);
       fnd_dis_a(9999-cnt.cnt);
      }
}
