#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  if (switches & SW2) {
    songOne();
  } else {
    buzzerOff();
  }
  static int secCount = 0;
  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void update_shape();
void drawSnowFlake(char pixelSize, char centerR, char centerC, u_int color);
void updateLocations();
void addSnowFlake();

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}
    
char rowLocations[] = {0,0,0,0,0,0};
char colLocations[] = {15,35,55,75,95,115};
char snowFlakes = 0;
char pixelSize = 2;
u_int color = COLOR_WHITE;
char blue = 31, green = 0, red = 31;

void
update_shape()
{
    drawString8x12(20,20, "LET IT SNOW", COLOR_BLACK, COLOR_BLUE);

    if (switches & SW4) return;

    for (int i = 0; i < snowFlakes; i++) {
      drawSnowFlake(pixelSize, rowLocations[i], colLocations[i], color);
      updateLocations();
    }
    
    if (switches & SW1) {
      snowFlakes++;
      if (snowFlakes > 5) {
	snowFlakes = 5;
      }
    }

    if (switches & SW3) {
      color = ((color+3)%64) & 63;
    }
}

void updateLocations()
{
  for (int i = 0; i < snowFlakes; i++) {
      rowLocations[i]++;
      if (rowLocations[i] >= screenHeight) {
	rowLocations[i] = 0;
      }
  }
}

void drawSnowFlake(char pixelSize, char centerR, char centerC, u_int color)
{
  char dim = 6;
  for (char row = 0; row <= (pixelSize/2)+(dim*pixelSize)-1; row++) {
    char prev = 0;
    char curr = pixelSize/2;
    for (char col = prev; col < curr; col++) {
      drawPixel(centerC+col, centerR+row, color);
      drawPixel(centerC+col, centerR-row, color);
      drawPixel(centerC-col, centerR+row, color);
      drawPixel(centerC-col, centerR-row, color);
    }
    drawPixel(centerC-curr+1, centerR-row-1, COLOR_BLUE);
    drawPixel(centerC-curr+1, centerR-row-2, COLOR_BLUE);
    drawPixel(centerC-curr+1, centerR-row-3, COLOR_BLUE);
    drawPixel(centerC-curr+1, centerR-row-4, COLOR_BLUE);
    drawPixel(centerC-curr+1, centerR-row-5, COLOR_BLUE);
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col ++) {
      if (row < (pixelSize+(pixelSize/2)) || (row > ((pixelSize/2)+(pixelSize*4)) && row < ((pixelSize/2)+(pixelSize*5)))) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
	drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row-1, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row-1, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row-2, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row-2, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row-3, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row-3, COLOR_BLUE);
      }
    }
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col++) {
      if (row < (pixelSize/2) || (row > ((pixelSize/2)+(pixelSize)) && row < ((pixelSize/2)+(pixelSize*2)))) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
	drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
      }
    }
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col++) {
      if (row < (pixelSize/2) || (row > ((pixelSize/2)+(pixelSize*2)) && row < ((pixelSize/2)+(pixelSize*4)))) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
        drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row-1, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row-1, COLOR_BLUE);
      }
    }
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col++) {
      if (row < (pixelSize/2) || (row > ((pixelSize/2)+(pixelSize*2)) && row < ((pixelSize/2)+(pixelSize*3)))) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
	drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
      }
    }
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col++) {
      if (row < ((pixelSize/2)+(pixelSize))) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
	drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
      }
    }
    prev = curr;
    curr += pixelSize;
    for (char col = prev; col < curr; col++) {
      if (row < (pixelSize/2)) {
	drawPixel(centerC+col, centerR+row, color);
	drawPixel(centerC+col, centerR-row, color);
	drawPixel(centerC-col, centerR+row, color);
	drawPixel(centerC-col, centerR-row, color);
      } else {
	drawPixel(centerC+col, centerR+row, COLOR_BLUE);
	drawPixel(centerC+col, centerR-row, COLOR_BLUE);
	drawPixel(centerC-col, centerR+row, COLOR_BLUE);
	drawPixel(centerC-col, centerR-row, COLOR_BLUE);
      }
    }
  }
}

/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
