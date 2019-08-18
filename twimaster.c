#include <avr/io.h>
#include <util/twi.h>
#include "twimaster.h"

uint8_t twi_status(uint8_t status)
{
	uint8_t current = TW_STATUS;
	return current == status;
}

void twi_init(uint16_t scl_frequency)
{
	TWSR = 0;
	TWBR = (uint8_t) ((F_CPU/scl_frequency)-16)/2;
}

void twi_start()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)));
}

void twi_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t twi_read_ack()
{
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t twi_read_nack()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void twi_stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while (TWCR & (1 << TWSTO));
}

void twi_transmit(uint8_t addr, uint8_t message[], uint8_t size)
{
	twi_start();
	
	if (!twi_status(TW_START))
	{
		TWSR = TW_BUS_ERROR;
		return;
	}
	
	twi_write(addr | TW_WRITE);
	
	if (twi_status(TW_MT_SLA_ACK))
	{
		for (uint8_t i = 0; i < size; i++)
		{
			twi_write(message[i]);
			
			if (twi_status(TW_MT_DATA_NACK))
			{
				twi_stop();
				break;
			}
		}
	}
	else
	{
		twi_stop();
	}
}

void twi_receive(uint8_t address, uint8_t message[], uint8_t size)
{
	twi_start();
	
	if (!twi_status(TW_START))
	{
		TWDR = TW_BUS_ERROR;
		return;
	}
	
	twi_write(address | TW_READ);
	
	if (twi_status(TW_MR_SLA_ACK))
	{
		for (uint8_t i = 0; i < size; i++)
		{
			if (i == size - 1)
			{
				message[i] = twi_read_nack();
				twi_stop();
			}
			else
			{
				message[i] = twi_read_ack();
			}
		}
	}
	else
	{
		twi_stop();
	}
}