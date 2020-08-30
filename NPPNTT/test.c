#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "datatransfer.h"

#define ARR_IN_SIZE 3
#define ARR_OUT_SIZE 4
DWORD* pDin;
DWORD* pDout;
int DEBUG = 0;

void hexDump (const void * addr, const int len);
int testCase(const char *, DWORD inOffset, DWORD outOffset, DWORD dataSize);

int main(void)
{
    pDin = (DWORD*)calloc(ARR_IN_SIZE, sizeof(DWORD));
    pDout = (DWORD*)calloc(ARR_OUT_SIZE, sizeof(DWORD));
    
    int rc = 1;

    printf("\nRun tests...\n");
    rc &= testCase("case 1: inOffset = 0, outOffset = 0, size = 128 bits",
                   0, 0, 128);

    rc &= testCase("case 2: inOffset = 1, outOffset = 1, size = 128 bits",
                   1, 1, 128);

    rc &= testCase("case 3: inOffset = 0, outOffset = 1, size = 128 bits",
                   0, 1, 128);

    rc &= testCase("case 4: inOffset = 1, outOffset = 0, size = 128 bits",
                   1, 0, 128);
   
    printf("All tests are done. ");
    if (rc) { printf("\033[0;32m [OK] \033[0m\n\n"); }
    else { printf("\033[0;31m [FAIL] \033[0m\n\n"); }

    free(pDin);
    free(pDout);
    assert(rc);

    return 0;
}

int testCase(const char *info, DWORD inOffset, DWORD outOffset, DWORD dataSize)
{
    int rc = 0;
    /* initialize pDin with -1, because it sets all bits as '1' */
    int i = 0;
    for (i = 0; i < ARR_IN_SIZE; ++i) {
        pDin[i] = -1;
    }
    for (i = 0; i < ARR_OUT_SIZE; ++i) {
        pDout[i] = 0;
    }

    if (DEBUG) { // dump arrays before BinaryDataTransfer() will be used
        hexDump((void*)pDin, ARR_IN_SIZE * sizeof(DWORD));
        printf("\n");
        hexDump((void*)pDout, ARR_OUT_SIZE * sizeof(DWORD));
    }

    // call of the tested function
        BinaryDataTransfer(pDin, inOffset, pDout, outOffset, dataSize);

    // make pDin comparable with pDout. Warning! it will change pDin
    if (inOffset == outOffset) {
        pDin[0] >>= inOffset;
    } else {
        if (outOffset > inOffset) {
            for (i = 0; i < outOffset; ++i) {
                pDin[0] >>= 1;
            }
        } else if (inOffset > outOffset) {
            for (i = 0; i < inOffset; ++i) {
                pDin[0] >>= 1;
            }
        }
    }

    // Compare of the two first elements in arrays
    if (pDin[0] == pDout[0] && pDin[1] == pDout[1]) { rc = 1; }
    else {
        printf("pDin[0]= %lu, pDout[0]= %lu\n", pDin[0], pDout[0]);
        printf("pDin[1]= %lu, pDout[1]= %lu\n", pDin[1], pDout[1]);
    }

    if (DEBUG) {
       printf("Result:\nWarning! pDin may be different than it was\n");
       hexDump((void*)pDin, ARR_IN_SIZE * sizeof(DWORD));
       printf("\n");
       hexDump((void*)pDout, ARR_OUT_SIZE * sizeof(DWORD));
    }

    // say a result of the current test-case
    if (rc) { printf("%s \033[0;32m [SUCCESS] \033[0m\n", info); }
    else { printf("%s \033[0;31m [FAIL] \033[0m\n", info); }

    return rc;
}

/* this function from stackoverflow :) */
void hexDump (const void * addr, const int len)
{
    int i;
    unsigned char buff[17];
    const unsigned char * pc = (const unsigned char *)addr;

    // Length checks.
    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0) { printf("  %s\n", buff); }

            // Output the offset.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And buffer a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) { // isprint() may be better.
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII buffer.
    printf("  %s\n", buff);
}

