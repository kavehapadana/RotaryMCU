#include <stdint.h>

extern	void external_Interrupt_Fnc(uint8_t _mask);
	void TIMER0_IRQHandler(void);
	void Init_Timer0(void);
	void Trans_2FixedMic_Message(void);
	void UART0_IRQHandler(void);
