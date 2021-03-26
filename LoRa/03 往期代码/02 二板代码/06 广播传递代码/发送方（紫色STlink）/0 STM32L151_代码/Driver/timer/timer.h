#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "general_type.h"

void TIM5_Int_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);
#endif
