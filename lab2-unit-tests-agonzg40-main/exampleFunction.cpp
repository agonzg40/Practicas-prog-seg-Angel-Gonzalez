#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h> 

unsigned int wrapFunctionAdd(unsigned int ui_a, unsigned int ui_b) {
  unsigned int usum = 0;
  if(UINT_MAX - ui_a < ui_b){
    //Error
  }else{
    usum = ui_a + ui_b;
  }
  
  return usum;
}

unsigned int wrapFunctionMul(unsigned int ui_a, unsigned int ui_b) {
  unsigned umul = 0;

  if(UINT_MAX / ui_a < ui_b){
    //Error
    umul = 1;
  }else {
    umul = ui_a*ui_b;
  }

  return umul;
}


uint32_t wrapFunctionShift(uint32_t ui_a, unsigned int ui_b) {
  uint32_t uShift = 0; 

  if(ui_b >= UINT_MAX){
    //Error
  }else{
    uShift = ui_a << ui_b | ui_a >> (32 - ui_b); 
  }

  return uShift;
}
