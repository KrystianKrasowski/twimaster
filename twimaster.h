#ifndef TWIMASTER_H_
#define TWIMASTER_H_


#define F_CPU 1000000UL
#define SCL_CLOCK 10000L

uint8_t twi_status(uint8_t status);
void twi_init();
void twi_start();
void twi_write(uint8_t data);
void twi_stop();
void twi_transmit(uint8_t addr, uint8_t message[], uint8_t size);


#endif /* TWIMASTER_H_ */