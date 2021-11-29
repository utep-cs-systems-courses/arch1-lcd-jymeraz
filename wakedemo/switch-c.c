#include "wakedemo.h"

int jumpTable(int sw) {
  switch (sw) {
  case 1:
    snowFlakes++;
    if (snowFlakes > 5) {
      snowFlakes = 5;
    }
    break;
  case 2:
    color = ((color+3)%64) & 63;
    break;
  case 3:
    break;
  default:
    break;
  }
}
