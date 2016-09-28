#ifndef Filters_h
#define Filters_h

#include "def.h"
#include "Types.h"

extern int32_t                          debug[4];

class Filters
{
  public:
                                        Filters();
    static double                       RunIIRBiquadForm1(float Input, biquad *coeff, biquad_reg *Regs, uint8_t NumSections);
    static double                       RunFIRFilter(double *FirCoeff, int NumTaps, double *Signal);
    static float                        applyDeadband(float value, float deadband);
    static float                        fixed_gain_Kalman(float Filtered, float Ref, float k);
    static int16_t                      Vbat_comp(int16_t init_throttle_pos, uint8_t init_vbat, uint8_t VBat);
  private:
    static double                       SectCalcForm1(int k, double x, biquad *coeff, biquad_reg *Regs);
};

#endif // Filters_h
