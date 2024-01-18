#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#define _CPU_ISR_Disable( _isr_cookie ) do { \
		register uint32_t _disable_mask = 0; \
		_isr_cookie = 0; \
		__asm__ __volatile__ ( \
		  "mfmsr %0\n" \
		  "rlwinm %1,%0,0,17,15\n" \
		  "mtmsr %1\n" \
		  "extrwi %0,%0,1,16" \
		  : "=&r" ((_isr_cookie)), "=&r" ((_disable_mask)) \
		  : "0" ((_isr_cookie)), "1" ((_disable_mask)) \
		); \
	} while (0)

#define _CPU_ISR_Restore( _isr_cookie ) do { \
		register uint32_t _enable_mask = 0; \
		__asm__ __volatile__ ( \
		"    cmpwi %0,0\n" \
		"    beq 1f\n" \
		"    mfmsr %1\n" \
		"    ori %1,%1,0x8000\n" \
		"    mtmsr %1\n" \
		"1:" \
		: "=r"((_isr_cookie)),"=&r" ((_enable_mask)) \
		: "0"((_isr_cookie)),"1" ((_enable_mask)) \
		); \
	} while (0)

#endif