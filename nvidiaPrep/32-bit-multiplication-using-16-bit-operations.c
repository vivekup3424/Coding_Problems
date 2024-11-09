#include <stdint.h>;
#include <stdio.h>

typedef struct{
	uint16_t high;
	uint16_t low;
} uint32_split_t;

//function to split a 32-number into two 16-bit parts
uint32_split_t split32(uint32_t num){
	uint16_t low = num & 0xFFFF;
	uint16_t high = num >> 16;
	uint32_split_t result;
	result.low = low;
	result.high = high;
	return result;
}

//function to combine the left and right 16 bits part to create 32 bit
uint32_t combine32(uint32_split_t result){
	uint32_t ans = 0;
	ans |= (uint32_t)result.low;
	ans |= (uint32_t)result.high <<16;
	return ans;
}

uint32_t product(uint32_t x, uint32_t y){
	uint16_t rx = x & 0xFFFF;
	uint16_t lx = x >> 16;
	printf("%d,%d",rx,lx);
	uint16_t ry = y & 0xFFFF;
	uint16_t ly = y >> 16;
	
}
