// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define _USE_INLINING //handling the _TCHAR types
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>



// TODO: reference additional headers your program requires here
#include "time64.h"
#include "ArchImporter.h"
#include "ArchReader.h"
#include "ArchWriter.h"

// print additional debug output
#define DEBUG
// inform about errors
#define VALIDATE_RESULT if(result!=0){printf("%s\n",strerror(errno));return false;};
