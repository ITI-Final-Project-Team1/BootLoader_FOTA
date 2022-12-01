#include "GPIO_interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/GPIO/GPIO_private.h"

#if GPIO_CONFIG_TYPE == PREBUILD_CONFIG
void GPIO_vWritePinDirection(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Dir)
{
	if(Copy_u8PinNo < 16)//input validation for pin number
	{
		switch (Copy_u8PortNo) {
			case GPIO_PORTA:
				if(Copy_u8PinNo < 8)
				{
					GPIOA->CRL &=~ ((0b1111) << (Copy_u8PinNo*4));
					GPIOA->CRL |= ((Copy_u8Dir) << (Copy_u8PinNo*4));
				}
				else if(Copy_u8PinNo < 16)
				{
					GPIOA->CRH &=~ ((0b1111) << ((Copy_u8PinNo - 8)*4));
					GPIOA->CRH |= ((Copy_u8Dir) << ((Copy_u8PinNo - 8)*4));
				}
				break;
			case GPIO_PORTB:
				if(Copy_u8PinNo < 8)
				{
					GPIOB->CRL &=~ ((0b1111) << (Copy_u8PinNo*4));
					GPIOB->CRL |= ((Copy_u8Dir) << (Copy_u8PinNo*4));
				}
				else if(Copy_u8PinNo < 16)
				{
					GPIOB->CRH &=~ ((0b1111) << ((Copy_u8PinNo - 8)*4));
					GPIOB->CRH |= ((Copy_u8Dir) << ((Copy_u8PinNo - 8)*4));
				}
				break;
			case GPIO_PORTC:
				if(Copy_u8PinNo < 8)
				{
					GPIOC->CRL &=~ ((0b1111) << (Copy_u8PinNo*4));
					GPIOC->CRL |= ((Copy_u8Dir) << (Copy_u8PinNo*4));
				}
				else if(Copy_u8PinNo < 16)
				{
					GPIOC->CRH &=~ ((0b1111) << ((Copy_u8PinNo - 8)*4));
					GPIOC->CRH |= ((Copy_u8Dir) << ((Copy_u8PinNo - 8)*4));
				}
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}
	else
	{
		/* Error : wrong value for Copy_u8PinNo */
	}
}

void GPIO_vWritePinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Value)
{
	if(Copy_u8PinNo < 16)//input validation for pin number
	{
		if(Copy_u8Value == HIGH)
		{
			switch (Copy_u8PortNo)
			{
				case GPIO_PORTA:
					GPIOA->BSRR = (1 << Copy_u8PinNo);
					break;
				case GPIO_PORTB:
					GPIOB->BSRR = (1 << Copy_u8PinNo);
					break;
				case GPIO_PORTC:
					GPIOC->BSRR = (1 << Copy_u8PinNo);
					break;
				default:
					/* Error : wrong value for Copy_u8PortNo */
					break;
			}
		}
		else if(Copy_u8Value == LOW)
		{
			switch (Copy_u8PortNo)
			{
				case GPIO_PORTA:
					GPIOA->BRR = (1 << Copy_u8PinNo);
					break;
				case GPIO_PORTB:
					GPIOB->BRR = (1 << Copy_u8PinNo);
					break;
				case GPIO_PORTC:
					GPIOC->BRR = (1 << Copy_u8PinNo);
					break;
				default:
					/* Error : wrong value for Copy_u8PortNo */
					break;
			}
		}
	}
	else
	{
		/* Error : wrong value for Copy_u8PinNo */
	}
}

void GPIO_vTogglePin(u8 Copy_u8PortNo, u8 Copy_u8PinNo)
{
	if(Copy_u8PinNo < 16)//input validation for pin number
	{
		switch (Copy_u8PortNo)
		{
			case GPIO_PORTA:
				GPIOA->ODR ^= (1 << Copy_u8PinNo);
				break;
			case GPIO_PORTB:
				GPIOB->ODR ^= (1 << Copy_u8PinNo);
				break;
			case GPIO_PORTC:
				GPIOC->ODR ^= (1 << Copy_u8PinNo);
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}
	else
	{
		/* Error : wrong value for Copy_u8PinNo */
	}
}

u8   GPIO_u8GetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo)
{
	u8 Local_u8ReturnVal = -1;
	if(Copy_u8PinNo < 16)//input validation for pin number
	{
		switch (Copy_u8PortNo)
		{
			case GPIO_PORTA:
				Local_u8ReturnVal = GET_BIT(GPIOA->IDR, Copy_u8PinNo);
				break;

			case GPIO_PORTB:
				Local_u8ReturnVal = GET_BIT(GPIOB->IDR, Copy_u8PinNo);
				break;

			case GPIO_PORTC:
				Local_u8ReturnVal = GET_BIT(GPIOC->IDR, Copy_u8PinNo);
				break;

			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}
	else
	{
		/* Error : wrong value for Copy_u8PinNo (Exceeds 16)*/
	}
	return Local_u8ReturnVal;
}

void GPIO_vWritePortDirection_High(u8 Copy_u8PortNo, u32 Copy_u8Dir)
{
	switch (Copy_u8PortNo)
	{
		case GPIO_PORTA:
			for(u8 i=0; i<8; i++)
			{
				GPIOA->CRH &=~ ((0b1111) << (i*4));
				GPIOA->CRH |= ((Copy_u8Dir) << (i*4));
			}
			break;
		case GPIO_PORTB:
			for(u8 i=0; i<8; i++)
			{
				GPIOB->CRH &=~ ((0b1111) << (i*4));
				GPIOB->CRH |= ((Copy_u8Dir) << (i*4));
			}
			break;
		case GPIO_PORTC:
			for(u8 i=0; i<8; i++)
			{
				GPIOC->CRH &=~ ((0b1111) << (i*4));
				GPIOC->CRH |= ((Copy_u8Dir) << (i*4));
			}
			break;
		default:
			/* Error : wrong value for Copy_u8PortNo */
			break;
	}
}

void GPIO_vWritePortDirection_Low(u8 Copy_u8PortNo, u32 Copy_u8Dir)
{
	switch (Copy_u8PortNo)
	{
		case GPIO_PORTA:
			for(u8 i=0; i<8; i++)
			{
				GPIOA->CRL &=~ ((0b1111) << (i*4));
				GPIOA->CRL |= ((Copy_u8Dir) << (i*4));
			}
			break;
		case GPIO_PORTB:
			for(u8 i=0; i<8; i++)
			{
				GPIOB->CRL &=~ ((0b1111) << (i*4));
				GPIOB->CRL |= ((Copy_u8Dir) << (i*4));
			}
			break;
		case GPIO_PORTC:
			for(u8 i=0; i<8; i++)
			{
				GPIOC->CRL &=~ ((0b1111) << (i*4));
				GPIOC->CRL |= ((Copy_u8Dir) << (i*4));
			}
			break;
		default:
			/* Error : wrong value for Copy_u8PortNo */
			break;
	}
}



void GPIO_vWritePortValue_High(u8 Copy_u8PortNo, u8 Copy_u8Value)
{
	switch (Copy_u8PortNo)
	{
		case GPIO_PORTA:
			GPIOA->ODR = (Copy_u8Value << 8);
			break;
		case GPIO_PORTB:
			GPIOB->ODR = (Copy_u8Value << 8);
			break;
		case GPIO_PORTC:
			GPIOC->ODR = (Copy_u8Value << 8);
			break;
		default:
			/* Error : wrong value for Copy_u8PortNo */
			break;
	}
}


void GPIO_vWritePortValue_Low(u8 Copy_u8PortNo, u8 Copy_u8Value)
{
	switch (Copy_u8PortNo)
	{
		case GPIO_PORTA:
			GPIOA->ODR = Copy_u8Value;
			break;
		case GPIO_PORTB:
			GPIOB->ODR = Copy_u8Value;
			break;
		case GPIO_PORTC:
			GPIOC->ODR = Copy_u8Value;
			break;
		default:
			/* Error : wrong value for Copy_u8PortNo */
			break;
	}
}
#elif GPIO_CONFIG_TYPE == LINKTIME_CONFIG

	void GPIO_vInit(GPIO_Config_t* P_xGpio)
	{
		if(P_xGpio->Pin < 16)//input validation for pin number
		{
			switch (P_xGpio->Port) {
				case GPIO_PORTA:
					if(P_xGpio->Pin < 8)
					{
						GPIOA->CRL &=~ ((0b1111) << (P_xGpio->Pin*4));
						GPIOA->CRL |= ((P_xGpio->Direction) << (P_xGpio->Pin*4));
					}
					else if(P_xGpio->Pin < 16)
					{
						GPIOA->CRH &=~ ((0b1111) << ((P_xGpio->Pin - 8)*4));
						GPIOA->CRH |= ((P_xGpio->Direction) << ((P_xGpio->Pin - 8)*4));
					}
					break;
				case GPIO_PORTB:
					if(P_xGpio->Pin < 8)
					{
						GPIOB->CRL &=~ ((0b1111) << (P_xGpio->Pin*4));
						GPIOB->CRL |= ((P_xGpio->Direction) << (P_xGpio->Pin*4));
					}
					else if(P_xGpio->Pin < 16)
					{
						GPIOB->CRH &=~ ((0b1111) << ((P_xGpio->Pin - 8)*4));
						GPIOB->CRH |= ((P_xGpio->Direction) << ((P_xGpio->Pin - 8)*4));
					}
					break;
				case GPIO_PORTC:
					if(P_xGpio->Pin < 8)
					{
						GPIOC->CRL &=~ ((0b1111) << (P_xGpio->Pin*4));
						GPIOC->CRL |= ((P_xGpio->Direction) << (P_xGpio->Pin*4));
					}
					else if(P_xGpio->Pin < 16)
					{
						GPIOC->CRH &=~ ((0b1111) << ((P_xGpio->Pin - 8)*4));
						GPIOC->CRH |= ((P_xGpio->Direction) << ((P_xGpio->Pin - 8)*4));
					}
					break;
				default:
					/* Error : wrong value forP_xGpio->Port */
					break;
			}
		}
		else
		{
			/* Error : wrong value for P_xGpio->Pin */
		}
	}

	void GPIO_vWritePinValue(GPIO_Config_t* P_xGpio, u8 Copy_u8Value)
	{
		if(P_xGpio->Pin < 16)//input validation for pin number
			{
				if(Copy_u8Value == HIGH)
				{
					switch (P_xGpio->Port)
					{
						case GPIO_PORTA:
							GPIOA->BSRR = (1 << P_xGpio->Pin);
							break;
						case GPIO_PORTB:
							GPIOB->BSRR = (1 << P_xGpio->Pin);
							break;
						case GPIO_PORTC:
							GPIOC->BSRR = (1 << P_xGpio->Pin);
							break;
						default:
							/* Error : wrong value for Copy_u8PortNo */
							break;
					}
				}
				else if(Copy_u8Value == LOW)
				{
					switch (P_xGpio->Port)
					{
						case GPIO_PORTA:
							GPIOA->BRR = (1 << P_xGpio->Pin);
							break;
						case GPIO_PORTB:
							GPIOB->BRR = (1 << P_xGpio->Pin);
							break;
						case GPIO_PORTC:
							GPIOC->BRR = (1 << P_xGpio->Pin);
							break;
						default:
							/* Error : wrong value for Copy_u8PortNo */
							break;
					}
				}
			}
			else
			{
				/* Error : wrong value for Copy_u8PinNo */
			}

	}

	void GPIO_vTogglePin(GPIO_Config_t* P_xGpio)
	{
		if(P_xGpio->Pin < 16)//input validation for pin number
		{
			switch (P_xGpio->Port)
			{
				case GPIO_PORTA:
					GPIOA->ODR ^= (1 << P_xGpio->Pin);
					break;
				case GPIO_PORTB:
					GPIOB->ODR ^= (1 << P_xGpio->Pin);
					break;
				case GPIO_PORTC:
					GPIOC->ODR ^= (1 << P_xGpio->Pin);
					break;
				default:
					/* Error : wrong value for Copy_u8PortNo */
					break;
			}
		}
		else
		{
			/* Error : wrong value for Copy_u8PinNo */
		}

	}

	u8   GPIO_u8GetPinValue(GPIO_Config_t* P_xGpio)
	{
		u8 Local_u8ReturnVal = -1;
		if(P_xGpio->Pin < 16)//input validation for pin number
		{
			switch (P_xGpio->Port)
			{
				case GPIO_PORTA:
					Local_u8ReturnVal = GET_BIT(GPIOA->IDR, P_xGpio->Pin);
					break;

				case GPIO_PORTB:
					Local_u8ReturnVal = GET_BIT(GPIOB->IDR, P_xGpio->Pin);
					break;

				case GPIO_PORTC:
					Local_u8ReturnVal = GET_BIT(GPIOC->IDR, P_xGpio->Pin);
					break;

				default:
					/* Error : wrong value for Copy_u8PortNo */
					break;
			}
		}
		else
		{
			/* Error : wrong value for Copy_u8PinNo (Exceeds 16)*/
		}
		return Local_u8ReturnVal;
	}

	void GPIO_vWritePortDirection_High(GPIO_Config_t* P_xGpio)
	{
		switch (P_xGpio->Port)
		{
			case GPIO_PORTA:
				for(u8 i=0; i<8; i++)
				{
					GPIOA->CRH &=~ ((0b1111) << (i*4));
					GPIOA->CRH |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			case GPIO_PORTB:
				for(u8 i=0; i<8; i++)
				{
					GPIOB->CRH &=~ ((0b1111) << (i*4));
					GPIOB->CRH |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			case GPIO_PORTC:
				for(u8 i=0; i<8; i++)
				{
					GPIOC->CRH &=~ ((0b1111) << (i*4));
					GPIOC->CRH |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}

	void GPIO_vWritePortDirection_Low(GPIO_Config_t* P_xGpio)
	{
		switch (P_xGpio->Port)
		{
			case GPIO_PORTA:
				for(u8 i=0; i<8; i++)
				{
					GPIOA->CRL &=~ ((0b1111) << (i*4));
					GPIOA->CRL |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			case GPIO_PORTB:
				for(u8 i=0; i<8; i++)
				{
					GPIOB->CRL &=~ ((0b1111) << (i*4));
					GPIOB->CRL |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			case GPIO_PORTC:
				for(u8 i=0; i<8; i++)
				{
					GPIOC->CRL &=~ ((0b1111) << (i*4));
					GPIOC->CRL |= ((P_xGpio->Direction) << (i*4));
				}
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}

	void GPIO_vWritePortValue_High(GPIO_Config_t* P_xGpio, u8 Copy_u8Value)
	{
		switch (P_xGpio->Port)
		{
			case GPIO_PORTA:
				GPIOA->ODR = (Copy_u8Value << 8);
				break;
			case GPIO_PORTB:
				GPIOB->ODR = (Copy_u8Value << 8);
				break;
			case GPIO_PORTC:
				GPIOC->ODR = (Copy_u8Value << 8);
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}

	void GPIO_vWritePortValue_Low(GPIO_Config_t* P_xGpio, u8 Copy_u8Value)
	{
		switch (P_xGpio->Port)
		{
			case GPIO_PORTA:
				GPIOA->ODR = Copy_u8Value;
				break;
			case GPIO_PORTB:
				GPIOB->ODR = Copy_u8Value;
				break;
			case GPIO_PORTC:
				GPIOC->ODR = Copy_u8Value;
				break;
			default:
				/* Error : wrong value for Copy_u8PortNo */
				break;
		}
	}

#endif
