#ifndef TWIMASTER_H_
#define TWIMASTER_H_


#define F_SCL 100000L

void twi_init(uint16_t scl_frequency);
uint8_t twi_status(uint8_t status);
void twi_start();
void twi_write(uint8_t data);
uint8_t twi_read_ack();
uint8_t twi_read_nack();
void twi_stop();
void twi_transmit(uint8_t addr, uint8_t message[], uint8_t size);
void twi_receive(uint8_t address, uint8_t message[], uint8_t size);


#endif /* TWIMASTER_H_ */