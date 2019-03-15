//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#if _WINDOWS
//void Debug(const char * /*format*/, ...); 
#else

#ifdef __cplusplus
extern "C" {
#endif

void Debug ( const char *format, ... );
void ClearDebugWindow (void);
void DebugTimestamp ( void );

#ifdef __cplusplus
}
#endif
#endif

#endif

