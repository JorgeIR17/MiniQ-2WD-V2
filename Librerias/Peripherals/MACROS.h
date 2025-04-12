#ifndef MACROS_H_
#define MACROS_H_

#define SETBIT(ADDRESS, BIT)		(ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS, BIT)		(ADDRESS &= ~(1<<BIT))
#define TOGGLEBIT(ADDRESS, BIT)		(ADDRESS ^= (1<<BIT))

#define READ_PIN(ADDRESS, BIT)		(ADDRESS & (1 << BIT))
#define BUTTON_PRESSED				0

#endif /* MACROS_H_ */