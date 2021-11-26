#ifndef buzzer_included
#define buzzer_included

#define numerator 2000000
#define D_5 587.330
#define G_5 783.991
#define F_sharp_5 739.989
#define E_5 659.255
#define C_5 523.251
#define B_4 493.883
#define A_4 440.00
#define G_4 391.995
#define D_6 1174.66
#define C_sharp_6 1108.73
#define B_5 987.767
#define A_5 880.00
#define G_sharp_5 830.609

void buzzer_init();
void buzzer_set_period(short cycles) ;
void buzzerOff();
void songOne();
#endif // included
