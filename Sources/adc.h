#ifndef __adc_H
#define __adc_H
  
uint8_t get_adc(a2d_channels_t chan);
uint8_t interrupt_get_adc(a2d_channels_t chan);

#endif /* __adc_H */