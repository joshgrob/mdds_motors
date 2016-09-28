#include "Arduino.h"
#include "filters.h"

Filters::Filters()
{
}

/**
* @fn: RunIIRBiquadForm1(float Input, biquad *coeff, biquad_reg *Regs, uint8_t NumSections);
*
* @brief: Executes n-section Form 1 biquad IIR filter
* @params: Variable to be filtered, coefficient structure, shift register structure, number of sections
* @returns: Filtered variable
*/
double Filters::RunIIRBiquadForm1(float Input, biquad *coeff, biquad_reg *Regs, uint8_t NumSections)
{
  double y;
  uint8_t k;
  
  y = Filters::SectCalcForm1(0, (double)Input, coeff, Regs);
  for(k=1; k<NumSections; k++)
  {
    y = Filters::SectCalcForm1(k, y, coeff, Regs);
  }
  return(y);
}

/**
* @fn: SectCalcForm1(int k, double x, biquad *coeff, biquad_reg *Regs);
*
* @brief: Executes one section of a Form 1 biquad IIR filter
* 
* @params: Section index number, variable to be filtered, coefficient structure, shift register structure
* @returns: Filtered variable
*/
double Filters::SectCalcForm1(int k, double x, biquad *coeff, biquad_reg *Regs)
{
 double y, CenterTap;
 
 CenterTap = x * coeff[k].b0 + coeff[k].b1 * Regs[k].X1 + coeff[k].b2 * Regs[k].X2;
 y = coeff[k].a0 * CenterTap - coeff[k].a1 * Regs[k].Y1 - coeff[k].a2 * Regs[k].Y2;
 Regs[k].X2 = Regs[k].X1;
 Regs[k].X1 = x;
 Regs[k].Y2 = Regs[k].Y1;
 Regs[k].Y1 = y;
 return(y);
}

/**
* @fn: RunFIRFilter(double *FirCoeff, int NumTaps, double *Signal, double *FilteredSignal, int NumSigPts);
*
* @brief: Evaluates a general Nth-order FIR filter
* 
* @params: FIR coefficient matrix, number of taps and signal matrix (Dimension of matricies equals NumTaps)
* @returns: Filtered variable
*/
double Filters::RunFIRFilter(double *FirCoeff, int NumTaps, double *Signal)
{
  double y = 0;

  for(uint8_t j=0; j<NumTaps; j++)
  {
    y += FirCoeff[j] * Signal[j];
  }
  // Shift signal matrix values right by one
  for(uint8_t i=NumTaps; i>1; i--)
  {
    Signal[i-1] = Signal[i-2];
  }
  // Re-initialize 0th element to 0
  Signal[0] = 0.0f;
  return(y);
}

/**
* @fn: applyDeadband(float value, float deadband);
*
* @brief: Subtracts deadband from input
* 
* @params: Input to be dead-banded, deadband width
* @returns: Dead-banded input
*/
float Filters::applyDeadband(float value, float deadband)
{
  if(abs(value) < deadband)
  {
    value = 0;
  } else if(value > 0)
  {
    value -= deadband;
  } else if(value < 0)
  {
    value += deadband;
  }
  return(value);
}

/**
* @fn: fixed_gain_Kalman(float Filtered, float Ref, float k);
*
* @brief: Executes fixed gain 1D simple Kalman filter
* 
* @params: Input to be filtered, measured reference value, Kalman gain
* @returns: Dead-banded input
*/
float Filters::fixed_gain_Kalman(float Filtered, float Ref, float k)
{
   // NaN trap 
   if (Filtered == Filtered) {} else {Filtered = 0;}

   // NaN trap
   if (Ref == Ref) {} else {Ref = 0;}
   
   Filtered = Filtered + (Ref - Filtered) * k;
   return(Filtered);
}


/**
* @fn: Vbat_comp(int16_t init_throttle_pos, uint8_t init_vbat, uint8_t VBat)
*
* @brief: Compensates battery voltage sag during altitude hold
* 
* @params: Throttle position and battery voltage when altitude hold was engaged and most recent battery voltage
* @returns: Altitude hold initial throttle position compensated for battery voltage sag
*/
int16_t Filters::Vbat_comp(int16_t init_throttle_pos, uint8_t init_vbat, uint8_t VBat)
{
  static float init_vcomp, vcomp;
  static float init_comp_throttle, comp_throttle;
  static int16_t Vcomp_init_throttle_pos;

  init_vcomp = VBATNOMINAL/(float)init_vbat;
  vcomp = VBATNOMINAL/(float)VBat;
  init_comp_throttle = (float)init_throttle_pos*init_vcomp;
  comp_throttle = init_comp_throttle + ALTHOLD_VOLTAGE_COMP_SLOPE*(VBat - init_vbat);
  Vcomp_init_throttle_pos = comp_throttle/vcomp;
  
  return Vcomp_init_throttle_pos;
}

