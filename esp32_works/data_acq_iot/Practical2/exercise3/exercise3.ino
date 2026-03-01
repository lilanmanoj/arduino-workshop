#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc.h"
#include "driver/dac.h"

void setup() {
  // Setup Serial terminal
  Serial.begin(115200);
  delay(1000);
  SET_PERI_REG_MASK(SENS_SAR_DAC_CTRL1_REG, SENS_SW_TONE_EN);
  SET_PERI_REG_MASK(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_CW_EN1_M);
  SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_INV1, 2, SENS_DAC_INV1_S);
  // Invert MSB
  SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_SCALE1, 0, SENS_DAC_SCALE1_S); // set 0 -> 100% Amplitude
  SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL2_REG, SENS_DAC_DC1, 0, SENS_DAC_DC1_S); // set offset 0 -> mid point
  // the frequency into 1000Hz
  long freqHz = 1000;
  int result = 0;
  double f, fTarget, delta, delta_min=99999.0;
  int stepTarget=0, divTarget=0;

  for (int step=1; step<2000; step++) {
    for (int divi=0; divi<8; divi++) {
      f = 125.6*(double)step/(double)(divi+1);
      delta = abs((freqHz - f));
      if(delta < delta_min){
        delta_min = delta;
        stepTarget = step;
        divTarget = divi;
        fTarget = f;
      }
    }
  }
  REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_CK8M_DIV_SEL, divTarget);
  SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL1_REG, SENS_SW_FSTEP, stepTarget, SENS_SW_FSTEP_S);
  dac_output_enable(DAC_CHANNEL_1);
  result = fTarget;
  Serial.println("DAC Sin Started on GPIO25 ");
  Serial.print(result); Serial.println(" Hz");
  Serial.print(stepTarget); Serial.println(" Steps");
  Serial.print(divTarget); Serial.println(" Div");
}

void loop() {
  // put your main code here, to run repeatedly:
}
