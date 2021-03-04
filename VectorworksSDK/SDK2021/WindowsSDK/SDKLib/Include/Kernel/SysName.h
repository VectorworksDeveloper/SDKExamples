//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Definitions needed for SysName.
//

#ifndef _SYSNAME_H_
#define _SYSNAME_H_ 1

#pragma once

#include "GSString.h"
#include "GSString.X.h"

//=======================================================================================
// typedef of RefName
typedef TXString RefName;			// RefName is TXString!


/////////////////////////////////////////////////////////////////////////////////////////

// You might think we could allow LONG_MAX (about 2 billion SysNames).  But
// the RefListType node will have 4 bytes for every SysName, and we were
// concerned that it would be a problem if its size was greater than a
// Sint32, since most of our handle functions have Sint32 parameters, assuming
// the size of the handle will not be greater than a Sint32.  We allow more
// total SysNames than named SysNames (has a string, not just an id), because
// the RefNameNode has about 68 bytes for every named SysName.  If you divide
// 2 billion by 100, you get 20 million, but we decided to be a little
// conservative and set a limit of 10 million named SysNames.  [BF 6/16/00]


const Sint32 refNumberListMax	= 100000000L;
const Sint32 refNameListMax		= 10000000L;

typedef Sint32 RefNumber;

typedef RefNumber ClassRefNumber;
typedef RefNumber HatchRefNumber;
typedef RefNumber MaterialRefNumber;
typedef RefNumber FillRefNumber;

/////////////////////////////////////////////////////////////////////////////////////////


#endif // _SYSNAME_H_
