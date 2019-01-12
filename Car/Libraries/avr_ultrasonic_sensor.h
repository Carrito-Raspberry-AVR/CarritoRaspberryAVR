#ifndef AVR_ULTRASONIC_H_
#define AVR_ULTRASONIC_H_

#define trigger_pin 4
#define echo_pin 5
#define led_pin 0

#define CA20 0
#define CA21 1
#define CA22 2

#define calcular_OCR1A_ms(tiempo_ms) (tiempo_ms * F_CPU / 64 / 1000)
#define calcular_OCR1A_us(tiempo_ms) (tiempo_ms * F_CPU / 64 / 1000000)
#define velocidad_sonido  34000
#define distancia_ultrasonic(n_ciclos) ((n_ciclos / (F_CPU / 64) )* velocidad_sonido / 2)
#define recibido 0x00
#define envio    0xff

#define OCIEA 1

#define d_30cm 30 
#define d_20cm 20
#define d_10cm 10

uint16_t cuenta;
double echo;
char ultrasonido_distancia;

void inicializar_ultrasonido();

#endif 
