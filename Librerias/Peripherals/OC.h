#ifndef OC_H_
#define OC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "MACROS.h"
#include "TMR0.h"
#include "TMR1.h"

static inline void OC_init()
{
    DDRB |= (1 << DDB2); // Pin MOSI (PB2) as output
}

#endif /* OC_H_ */
