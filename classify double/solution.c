#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    uint64_t mask = (uint64_t)1 << index;
	uint64_t temp = mask & number;
	temp >>= index;
	return temp;
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7FF0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xFFF0000000000000;
}

bool checkForPlusNormal (uint64_t number) {
    uint64_t PlusZero = 0x0000000000000000;
    uint64_t PlusInf = 0x7FF0000000000000;
    
    return (get_bit(number, 63) == 0) 
        && ((number & PlusInf) != PlusZero) 
        && ((number & PlusInf) != PlusInf);
}

bool checkForMinusNormal (uint64_t number) {
    uint64_t MinusZero = 0x8000000000000000;
    uint64_t MinusInf = 0xFFF0000000000000;
    
    return (get_bit(number, 63) == 1)
        && ((number & MinusInf) != MinusZero)
        && ((number & MinusInf) != MinusInf);
}

bool checkForPlusDenormal (uint64_t number) {
    uint64_t PlusZero = 0x0000000000000000;
    uint64_t MinusInf = 0xFFF0000000000000;

    return (number != PlusZero) && ((number & MinusInf) == PlusZero);
}

bool checkForMinusDenormal (uint64_t number) {
    uint64_t MinusZero = 0x8000000000000000;
    uint64_t MinusInf = 0xFFF0000000000000;

    return (number != MinusZero) && ((number & MinusInf) == MinusZero);
}

bool checkForSignalingNan (uint64_t number) {
    uint64_t PlusInf = 0x7FF0000000000000;
    uint64_t PlusQNun1 = 0x7FF8000000000000;
    uint64_t PlusQNun2 = 0x7FFFFFFFFFFFFFFF;

    return ((number & PlusQNun1) == PlusInf) && ((number & PlusQNun2) != PlusInf);
}

bool checkForQuietNan (uint64_t number) {
    uint64_t PlusQNun = 0x7FF8000000000000;

    return (number & PlusQNun) == PlusQNun;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
