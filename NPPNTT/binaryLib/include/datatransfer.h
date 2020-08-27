#ifndef __BYNARY_H__
#define __BYNARY_H__

typedef unsigned long DWORD;

/* Moves the binary data from *pDin to *pDout.
 * Data isn't aligned up to WORD
 */ 
void BinaryDataTransfer(
     DWORD* pDin,
     DWORD dInOffset,
     DWORD* pDout,
     DWORD dOutOffset,
     DWORD dataSizeInBits
);

#endif 
