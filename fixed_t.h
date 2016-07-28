#ifndef FIXED_T_IN
#define FIXED_T_IN

#include <stdio.h>

#include <limits.h>
#include <math.h>

typedef int 						fixed_t;
typedef unsigned int				ufixed_t;

// need changes depending on data type used
#define FIXED_MAX					(signed)(0x7fffffff)
#define FIXED_MIN					(signed)(0x80000000)

#define FIXED_T_SIZE ((sizeof(fixed_t) * CHAR_BIT) >> 1) // we use half bits for integer part and the other half for after dp


fixed_t makeFixedFromInt(int from) {
	return from << FIXED_T_SIZE;
}

fixed_t makeFixedFromFloat(float from) {
	return (fixed_t) ((from) * (1 << FIXED_T_SIZE));
}

fixed_t makeFixedFromDouble(double from) {
	return (fixed_t) ((from) * (1 << FIXED_T_SIZE));
}



int makeIntFromFixed(fixed_t fx) {
	return fx >> FIXED_T_SIZE;
}

float makeFloatFromFixed(fixed_t fx) {
	return (float) (fx) / (float) (1 << FIXED_T_SIZE);
}

double makeDoubleFromFixed(fixed_t fx) {
	return (double) (fx) / (double) (1 << FIXED_T_SIZE);
}

// Fixed point multiplication

inline fixed_t FixedMul (fixed_t a, fixed_t b) {
	return (fixed_t)(((long long int) a * b) >> FIXED_T_SIZE);	
}

// Fixed point division

inline fixed_t DivScale (fixed_t a, fixed_t b) {
	return (!b) ? FIXED_MAX : (fixed_t) (((long long int) a << FIXED_T_SIZE) / b);
}

inline fixed_t FixedDiv (fixed_t a, fixed_t b) {
	if ((ufixed_t)abs(a) >> (31 - FIXED_T_SIZE) >= (ufixed_t)abs (b))
		return (a ^ b) < 0 ? FIXED_MIN : FIXED_MAX;
	return DivScale (a, b);
}

#endif
