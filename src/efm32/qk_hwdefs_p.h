#ifndef QK_HWDEFS_P_H
#define QK_HWDEFS_P_H

#include "em_rtc.h"
#include "em_int.h"

// MCU
#define	_QK_MCU_INTEN()				INT_Enable()
#define _QK_MCU_INTDIS()			INT_Disable()

// VTIMER
#define QK_VTIMER_CLKFREQ			(32768U)
#define QK_VTIMER_CLKDIV			(4)
#define _QK_VTIMER_TIMEDIFF(a,b)	(((a<<8)-(b<<8)) >> 8)
#define _QK_VTIMER_CNT_MASK			(0x00FFFFFF)
#define _QK_VTIMER_CNT_GET()		RTC_CounterGet()
#define _QK_VTIMER_CNT_INTCLRCOMP()	RTC_IntClear(RTC_IF_COMP0)
#define _QK_VTIMER_CNT_INTENCOMP()	RTC_IntEnable(RTC_IF_COMP0)
#define _QK_VTIMER_CNT_INTDISCOMP()	RTC_IntDisable(RTC_IF_COMP0)
#define _QK_VTIMER_CNT_COMPSET(v)	RTC_CompareSet(0, (v))


#endif /* QK_HWDEFS_P_H */
