#ifndef __BYNARY_H__
#define __BYNARY_H__

typedef unsigned long DWORD;
extern int DEBUG;

/* copy the binary data from *pDin to *pDout.
 * Data isn't aligned up to WORD
 */ 
void BinaryDataTransfer(
     DWORD* pDin,         // pointer to incoming data
     DWORD dInOffset,     // incoming data offset in bits
     DWORD* pDout,        // pointer to outgoing data
     DWORD dOutOffset,    // outgoing data offset in bits
     DWORD dataSizeInBits // length of moved data in bits
);

#endif 
