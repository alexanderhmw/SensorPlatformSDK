#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include "XWGPS.h"

#define HeaderGLL "$GPGLL" 
#define HeaderZDA "$GPZDA"
#define HeaderFPD "$GPFPD"
#define EndGLL "\r\n"
#define Invalid ",,,"

Q_DECL_EXPORT void dataTransfer(int startid, int endid, XWGPSCOMMUNICATORRECEIVEDATA * XWGPSreceivedata);


#endif