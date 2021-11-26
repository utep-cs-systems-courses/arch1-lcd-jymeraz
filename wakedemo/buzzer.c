#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    timerAUpmode();
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		
}

void buzzer_set_period(short cycles) 
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		
}

void buzzerOff() {
  buzzer_set_period(0);
}

static int song_one_count = 0;
void songOne() {                   /* Adventure Time theme song */
   song_one_count ++;
   
   if (song_one_count == 125) // d eighth
     buzzer_set_period(numerator/D_5); 
   if (song_one_count == 250) // off
     buzzer_set_period(0); 
   if (song_one_count == 260) // g eighth
     buzzer_set_period(numerator/G_5);   
   if (song_one_count == 385) // off
     buzzer_set_period(0); 
   if (song_one_count == 395) // g quarter
     buzzer_set_period(numerator/G_5); 
   if (song_one_count == 645) // off
     buzzer_set_period(0); 
   if (song_one_count == 655)
     buzzer_set_period(numerator/G_5); // g quarter tied
   if (song_one_count == 905)
     buzzer_set_period(0); // off
   if (song_one_count == 915) // g quarter tied
     buzzer_set_period(numerator/G_5); 
   if (song_one_count == 1165) // f eighth
     buzzer_set_period(numerator/F_sharp_5); 
   if (song_one_count == 1290) // off
     buzzer_set_period(0); 
   if (song_one_count == 1300) // f quarter
     buzzer_set_period(numerator/F_sharp_5); 
   if (song_one_count == 1550) // off
     buzzer_set_period(0); 
   if (song_one_count == 1560) // e eighth
     buzzer_set_period(numerator/E_5); 
   if (song_one_count == 1685) // off
     buzzer_set_period(0);
   if (song_one_count == 1695) // d eighth
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 1820) // e eighth 
     buzzer_set_period(numerator/E_5);
   if (song_one_count == 1945) // d quarter
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 2195) // off
     buzzer_set_period(0);
   if (song_one_count == 2205) // d eigth 
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 2330) // off
     buzzer_set_period(0);
   if (song_one_count == 2340) // c quarter
     buzzer_set_period(numerator/C_5);
   if (song_one_count == 2590) // b for 3
     buzzer_set_period(numerator/B_4);
   if (song_one_count == 2840) // a quarter
     buzzer_set_period(numerator/A_4);
   if (song_one_count == 3090) // g for 3
     buzzer_set_period(numerator/G_4);
   if (song_one_count == 3340) // off
     buzzer_set_period(0);
   if (song_one_count == 3465) // c quarter
     buzzer_set_period(numerator/C_5);
   if (song_one_count == 3715) // b eighth
     buzzer_set_period(numerator/B_4);
   if (song_one_count == 3840) // a eighth
     buzzer_set_period(numerator/A_4);
   if (song_one_count == 3965) // g quarter
     buzzer_set_period(numerator/G_4);
   if (song_one_count == 4215) // off eighth
     buzzer_set_period(0);
   if (song_one_count == 4340) // g eighth
     buzzer_set_period(numerator/G_5);
   if (song_one_count == 4465) // off eighth
     buzzer_set_period(0);
   if (song_one_count == 4590) // g eighth
     buzzer_set_period(numerator/G_5);
   if (song_one_count == 4715) // off
     buzzer_set_period(0);
   if (song_one_count == 4725) // g quarter
     buzzer_set_period(numerator/G_5);
   if (song_one_count == 4975) // off eighth
     buzzer_set_period(0);
   if (song_one_count == 5100) // g quarter
     buzzer_set_period(numerator/G_5);
   if (song_one_count == 5350) // f eighth
     buzzer_set_period(numerator/F_sharp_5);
   if (song_one_count == 5475) // off eighth
     buzzer_set_period(0);
   if (song_one_count == 5600) // e eighth
     buzzer_set_period(numerator/E_5);
   if (song_one_count == 5725) // off
     buzzer_set_period(0);
   if (song_one_count == 5735) // e quarter
     buzzer_set_period(numerator/E_5);
   if (song_one_count == 5985) // d quarter
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 6235) // off
     buzzer_set_period(0);
   if (song_one_count == 6245) // d eighth
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 6360) // c for 3
     buzzer_set_period(numerator/C_5);
   if (song_one_count == 6735) // off
     buzzer_set_period(0);
   if (song_one_count == 6745) // c eighth
     buzzer_set_period(numerator/C_5);
   if (song_one_count == 6870) // off
     buzzer_set_period(0);
   if (song_one_count == 6880) // c eighth
     buzzer_set_period(numerator/C_5);
   if (song_one_count == 7005) // d for 3
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 7280) // off
     buzzer_set_period(0);
   if (song_one_count == 7290) // d for 3
     buzzer_set_period(numerator/D_5);
   if (song_one_count == 7665) // a eighth
     buzzer_set_period(numerator/A_4);
   if (song_one_count == 7790) // b quarter
     buzzer_set_period(numerator/B_4);
   if (song_one_count == 8040) // a eighth
     buzzer_set_period(numerator/A_4);
   if (song_one_count == 8165) // g eighth
     buzzer_set_period(numerator/G_4);
   if (song_one_count == 8290) // g half
     buzzer_set_period(numerator/G_5);
   if (song_one_count >= 8790) // off
     buzzer_set_period(0);
}

