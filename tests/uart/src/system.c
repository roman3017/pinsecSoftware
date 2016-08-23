
#include <stdint.h>


void init_bss() {
	extern char _bss_start, _bss_end;
	memset(&_bss_start, 0, &_bss_end - &_bss_start);
	extern char _sdata, _edata, _etext;
	memcpy(&_sdata, &_etext, &_edata - &_sdata);


	typedef void(*ctor_t)();
	extern uint32_t _ctors_start;
	extern uint32_t _ctors_end;


	uint32_t ctor = (uint32_t)&_ctors_start;
	while( ctor < (uint32_t)&_ctors_end )
	{
		//(*ctor)();
		void (*ptr)() = (void (*)())(*((uint32_t*)ctor));
		(*ptr)();
		ctor += 4;
	}
}
/*

extern void irqCpp(uint32_t irq);

void irqC(uint32_t irq){
	irqCpp(irq);
}
*/