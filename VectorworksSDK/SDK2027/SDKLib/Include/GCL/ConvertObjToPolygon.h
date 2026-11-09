//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef _OBJ2POLY_
#define _OBJ2POLY_

Handle GS_API ConvertObjToPolygon(CallBackPtr cbp, Handle h, Boolean preserveOriginal);
Handle GS_API ConvertObjToPolygonN(CallBackPtr cbp, Handle h, Boolean preserveOriginal, short in2DConversionRes);


#endif
