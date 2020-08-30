#include <stdlib.h>
#include <stdio.h>
#include "datatransfer.h"

static void BinPrintf(DWORD v)
{
    unsigned long i;
    for (i = 1UL << (sizeof(DWORD)*8 - 1); i > 0; i >>= 1ULL) {
        printf("%d", (v & i)? 1 : 0);
    }
}

/* unset bits in mask.
     set mask as 0, if offset is zero or sizeof(DWORD)
*/
static void UnsetBits(DWORD *mask, DWORD offset)
{
    if (!offset || offset == sizeof(DWORD)*8) { *mask = 0UL; return; }
    DWORD i;
    for (i = sizeof(DWORD)*8 - 1; i >= sizeof(DWORD)*8 - offset; --i) {
        *mask ^= 1ULL << i;
    }
}

// 00000011 -> 11000000
static void TurnBits(DWORD *v)
{
    static unsigned long k;
    k = 0;
    while (*v) {
        *v >>= 1ULL;
        ++k;
    }
    *v = 0ULL;
    UnsetBits(v, k);
}

void BinaryDataTransfer(
     DWORD* pDin,
     DWORD dInOffset,
     DWORD* pDout,
     DWORD dOutOffset,
     DWORD dataSizeInBits)
{
    if (!dataSizeInBits ||
            dInOffset >= sizeof(DWORD) || dOutOffset >= sizeof(DWORD)) { return; }

    /* initialize different masks */
    DWORD inMask = -1,
                oMask  = -1;
    if (dInOffset) { UnsetBits(&inMask, dInOffset); }
    if (dOutOffset) { UnsetBits(&oMask, dOutOffset); }
    if (DEBUG) {
        printf("inMask:   "); BinPrintf(inMask); printf("\n");
        printf("oMask:    "); BinPrintf(oMask); printf("\n");
    }

    DWORD maxOffset = dInOffset > dOutOffset? dInOffset : dOutOffset;
    DWORD diffOffset = abs(dInOffset - dOutOffset);
    DWORD diffMask = -1;
    UnsetBits(&diffMask, sizeof(DWORD)*8 - diffOffset);
    if (DEBUG) { printf("diffMask: "); BinPrintf(diffMask); printf("\n"); }


    register int i;
    // loopIters= 3 means, that we'll walkthrough [0,3] indexes in given arrays
    DWORD loopIters = (dataSizeInBits  + dInOffset) / (sizeof(DWORD)*8);
    DWORD remainBits = dataSizeInBits;

    DWORD val = 0UL, // pDin[i] & 'some mask'
          vals = 0UL, // this will be placed in pDout[i]
          remainder = 0UL; // if anything was cut in some iteration,
                           // it should be added in the next iteration

    if (DEBUG) {
        printf("\nmain cycle from %d to %lu\n", 0, loopIters);
        printf("remainBits: %lu\n", remainBits);
    }
    /* Copy occurs in 3 stages:
         1) copy of the fist dword with applying some masks.
         2) copy of the middle of the given array. maybe skipped
         3) copy of the last dword with applying remainder and some masks
    */
    for (i = 0; i < loopIters; ++i) {
        if (DEBUG) { printf("\titer %d\n", i); }
        if (i == 0) { /* 1 */
            val = pDin[i] & inMask;
            if (diffOffset) {
                vals = val >> dOutOffset;
                if (!dInOffset || !dOutOffset) { remainder = diffMask; }
            } else {
                vals = val;
                if (maxOffset) { remainder = val; }
            }
            pDout[i] |= vals;
            if (dInOffset + dOutOffset < sizeof(DWORD)*8) {
                remainBits -= sizeof(DWORD)*8 - dInOffset;
            }
        } else { /* 2 */
            val = pDin[i];
            vals = val >> diffOffset;
            pDout[i] |= vals;
            pDout[i] |= remainder;
            remainder = val & diffMask;
            remainBits -= sizeof(DWORD)*8;
        }

        if (DEBUG) {printf("unturn rem."); BinPrintf(remainder); printf("\n");}
        TurnBits(&remainder);
        if (DEBUG) {
            printf("pDin[%d] = ", i); BinPrintf(pDin[i]); printf("\n");
            printf("val =     "); BinPrintf(val); printf("\n");
            printf("vals =    "); BinPrintf(vals); printf("\n");
            printf("remaind.= "); BinPrintf(remainder); printf("\n");
            printf("pDout[%d]= ", i); BinPrintf(pDout[i]); printf("\n");
            printf("remainBits = %lu\n", remainBits);
        }
    }

    /* 3 */
    if (!remainder && !remainBits) {
        if (DEBUG) { printf("\nremainder and remBits are zeroes\n"); }
        return;
    }

    if (remainder) {
        if (DEBUG) { printf("\nrem.: "); BinPrintf(remainder); printf("\n"); }
        pDout[i] |= remainder;
    }
    if (remainBits) {
       if (DEBUG) { printf("\nremainBits is %lu\n", remainBits); }
       inMask = -1;
       inMask >>= sizeof(DWORD)*8 - remainBits;

       TurnBits(&inMask);
       val = pDin[i] & inMask;
       vals = val;
       if (!i) { vals = val << dOutOffset; }
       pDout[i] |= vals;

       if (DEBUG) {
           printf("pDin[%d] = ", i); BinPrintf(pDin[i]); printf("\n");
           printf("inMask:   "); BinPrintf(inMask); printf("\n");
           printf("val =     "); BinPrintf(val); printf("\n");
           printf("vals =    "); BinPrintf(vals); printf("\n");
           printf("pDout[%d]= ", i); BinPrintf(pDout[i]); printf("\n");
       }
    }
}

