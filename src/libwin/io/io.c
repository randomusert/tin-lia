#include "io.h"
#include <stdio.h>
#include <windows.h>

void fileOpen(char file[], LPOFSTRUCT lpReopenBuff, UINT uStyle) {
    LPCSTR lpFileName = file; 
    OpenFile(lpFileName, lpReopenBuff, uStyle); 
}