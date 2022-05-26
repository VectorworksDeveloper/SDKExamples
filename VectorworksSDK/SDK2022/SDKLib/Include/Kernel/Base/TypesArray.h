//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

/* 
	Static Array Macro Templates
	----------------------------

    The standard static array macro is passed a type, length, and class name.
	This class always pins the index value to the array extents and breaks
	into the debugger when BUG is turned on if an out of range value is passed.
	IndexInRange allows you to check if an index is in range while looping
	through the array.
*/

//---------------------------------------------------------------------------------------
template <class T, ptrdiff_t elems> class StaticArray
{
	public:
		StaticArray()				{ }

		T& operator[](ptrdiff_t i)		{ 
			#if BUG
				DSTOPIF(!IndexInRange(i), (kStaticArrayToWhom | kNoNetDebug, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#else
				DSTOPIF(!IndexInRange(i), (kEveryone, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#endif
			return fBuf[PIN(i, 0, elems-1)]; 
		}

		const T& operator[](ptrdiff_t i) const { 
			#if BUG
				DSTOPIF(!IndexInRange(i), (kStaticArrayToWhom | kNoNetDebug, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#else
				DSTOPIF(!IndexInRange(i), (kEveryone, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#endif
			return fBuf[PIN(i, 0, elems-1)]; 
		}

		bool IndexInRange(ptrdiff_t i) const { return i >= 0 && i < elems; }

	private:
		T			fBuf[elems];
};

#define STATIC_ARRAY(DataType, elems, ClassName) \
	typedef StaticArray<DataType, elems>  ClassName

#define STATIC_ARRAY_DEBUGONLY(DataType, elems, ClassName) \
	typedef StaticArray<DataType, elems>  ClassName

//---------------------------------------------------------------------------------------
template <class T> struct List
{
	T v;
	T& operator[](ptrdiff_t i)				{ return (&v)[i]; }
	const T& operator[](ptrdiff_t i) const	{ return (&v)[i]; }
};

#define DEFINE_LISTSTRUCT(T)  typedef List<T> T##List


/////////////////////////////////////////////////////////////////////////////////////////
//
// TLargeArray
//
//	This object can index an array of up to MAX_LONG elements
//
/////////////////////////////////////////////////////////////////////////////////////////


/**************************************************************************
						Warning for TSmallArray Users
**************************************************************************
Data placed in a TSmallArray is stored in an unlocked handle. Therefore, you 
must be careful to never rely on a pointer to TSmallArray data, because the 
data handle could move during a Mac system call and leave your pointer in 
the dust.  

The easiest way to make this mistake is to pass TSmallArray data to a function 
as a reference parameter. 


	TSmallArray<PStr31>	fViewName;
			
	for(Sint32 i=0; i<fViewName.NumItems(); i++){
	
		// The wrong way
		SomeFunction(theThing, fViewName[i]);
		
		// The safe way
		PStr31 toolName = fViewName[i]; // PString class makes a copy of the data
		SomeFunction(theThing, toolName);
	}


Normally you dont have to worry about unlocked handles because almost 
all handles in MiniCAD, including object handles, are locked.

Darick W. DeHart 2/12/98
**************************************************************************/

extern "C" {
	typedef Sint32 (*QSortCompareFunc)(const void*, const void*);
}


/*
	   There are two ways to construct TSmallArrayRawMemorys, one by passing an existing handle and one without a handle,
	all other fields are the same InclusiveBetween the two.  When you pass an existing handle, such as when modifying 
	a PolyTDHandle, you need to specify the byte offset to the count word and to the beginning of the data.  In
	the case of PolyTDHandles, for instance, the count word is located at offsetof(TDPolyType, vertices), and the
	first data byte at offsetof(TDPolyType, vertexList[0]).  If one cell has a count of 1, then the count
	is NOT zero-based.
	
	   If you do not have an existing handle, the easiest way to construct a dynamic array is without passing any
	parameters.  In this case, TSmallArrayRawMemory sets up everything and does automatic buffering (every 10 cells).
	
	   Use DEFINE_TARRAY to define type specific dynamic array classes.  For example, DEFINE_TARRAY(WorldRect) would
	define a dynamic array type TLongRectArray.  This allows use of the [] operator and returns a reference to
	the proper data type.
*/


enum EArrayGrowthMethod { eOneAtATimeGrowth,   // 1, 2, 3, 4, ... (for when have existing data handle)
						 eArithmeticGrowth,    // 10, 20, 30, 40...
					     eGeometricGrowth,     // 10, 20, 40, 80...
						 eExponentialGrowth};  // 10, 100, 1000, 10000...


template <class T, typename TIndexType> class TXMemoryArray;

// ------------------------------------------------------------------------------------------------------------------------
template <typename TIndexType>
class TXMemoryRawArray : public TDebugObject
{
	template <class T1, typename T2>
	friend class TXMemoryArray;
	public:
		TXMemoryRawArray(size_t dataSz, size_t dataOff = sizeof(TIndexType), size_t countOff = 0L, Bool8 zeroBasedCount = false, short numCells = 0, Bool8 growGeometrically = false);
		TXMemoryRawArray(size_t dataSz, EArrayGrowthMethod growthMethod);
		TXMemoryRawArray(GSHandle dataH, size_t dataSz, size_t dataOff, size_t countOff, Bool8 zeroBasedCount);
		~TXMemoryRawArray();
		
		TIndexType NumItems() const				{ return fNumUsedItems; }		
		void Empty()							{ DeleteCells(0, this->NumItems()); }		

		Boolean AppendCells(TIndexType numCells);
		Boolean AppendCellAndData(const void* cellData);
		Boolean InsertCells(TIndexType beforeWhere, TIndexType numCells);
		Boolean InsertCellAndData(TIndexType beforeWhere, const void* cellData);
		void DeleteCells(TIndexType firstCellToDelete, TIndexType numCells);

		void SortArray(QSortCompareFunc CompFunc);

		GSHandle GetDataHandle()
		// this must be used very carefully!!!
		// if this handle is locked - it must be unlocked!!
		{
			ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
			return (GSHandle) fDataHandle;
		}

		size_t SizeOf() const { return fNumAllocItems * fDataSize; } //-V104
		
		#ifdef BUG
		void CheckArrayValues(bool bcheckExtraSpace = false) const;
		void WriteArray() const;
		#endif

	protected:
		GSHandle		    fDataHandle;			// Handle to the data
		size_t		        fDataSize;				// Size of each cell’s data in bytes
		size_t				fDataOffset;			// Byte offset from beginning of handle to first data item
		size_t				fCountOffset;			// Byte offset from beginning of handle to count item (a TIndexType)
		Bool8				fCountZeroBased;		// Is the count 0 or 1 based?
		EArrayGrowthMethod  fGrowthMethod;
		
		void SetCount(TIndexType numDataItems);
		
		
		#if BUG
		void* GetCellPtr(TIndexType cellNum) const;
		#else
		void* GetCellPtr(TIndexType cellNum) const		{ TIndexType i = PIN(cellNum, (TIndexType)0, fNumUsedItems - 1); return (void*) (*this->fDataHandle + fDataOffset + i*fDataSize); }
		#endif

	private:
							TXMemoryRawArray(const TXMemoryRawArray&) {}			// make this private so it can't be actually called
		TXMemoryRawArray&	operator=(const TXMemoryRawArray&) { return *this; }	// make this private so it can't be actually called
		void				operator=(void *) {}									// make this private so it can't be actually called

	protected:
		enum {
			kBuffSize = 10						// Number of cells buffered when growing the handle
		};
		
		Bool8		fFreeMemWhenDone;		// Dispose of fDataHandle when done
		TIndexType	fNumAllocItems;			// Number of cells actually allocated
		TIndexType	fNumUsedItems;			// Number of items the client is using
};

// ------------------------------------------------------------------------------------------------------------------------
template <class T, typename TIndexType>
class TXMemoryArray 
{
	public:		
		TXMemoryArray(size_t dataOff = sizeof(TIndexType), size_t countOff = 0L, Bool8 zeroBasedCount = false, short numCells = 0, Bool8 growGeometrically = false)
			: fData(sizeof(T), dataOff, countOff, zeroBasedCount, numCells, growGeometrically)	{ }

		TXMemoryArray(EArrayGrowthMethod growthMethod)
			: fData(sizeof(T), growthMethod)													{ }

		TXMemoryArray(GSHandle dataH, size_t dataOff, size_t countOff, Bool8 zeroBasedCount)
			: fData(dataH, sizeof(T), dataOff, countOff, zeroBasedCount)						{ }

		~TXMemoryArray()									{ if (fData.fFreeMemWhenDone) this->Empty(); }

		size_t		SizeOf() const							{ return fData.SizeOf(); }
		GSHandle	GetDataHandle()							{ return fData.GetDataHandle(); }

		TIndexType	NumItems() const						{ return fData.NumItems(); }		
		void		Empty()									{ this->DeleteCells(0, this->NumItems()); }		

		T&			operator[](size_t cellNum)				{ return *((T*) fData.GetCellPtr((TIndexType)cellNum)); } 
		const T&	operator[](size_t cellNum) const		{ return *((T*) fData.GetCellPtr((TIndexType)cellNum)); } 

		T*			GetAt(size_t cellNum)					{ return (T*) fData.GetCellPtr((TIndexType)cellNum); }

		Boolean		AppendCells(TIndexType numCells);
		Boolean		PushData(const T& cellData);
		Boolean		InsertData(TIndexType beforeWhere, const T& cellData);
		Boolean		InsertData(TIndexType where, TIndexType count, const T* arrCellData);
		void		DeleteCells(TIndexType firstCellToDelete, TIndexType numCells);
		T			PopData();

		void SortArray(QSortCompareFunc CompFunc)			{ fData.SortArray( CompFunc ); }

#ifdef BUG
		void WriteArray() const								{ fData.WriteArray(); }
#endif

	private:
						TXMemoryArray(const TXMemoryArray&) {}				// make this private so it can't be actually called
		TXMemoryArray&	operator=(const TXMemoryArray&) { return *this; }	// make this private so it can't be actually called
		void			operator=(void *) {}								// make this private so it can't be actually called

		Boolean			AppendCellsRaw(TIndexType numCells);
		Boolean			InsertCellsRaw(TIndexType beforeWhere, TIndexType numCells);
		void			DeleteCellsRaw(TIndexType firstCellToDelete, TIndexType numCells);

	private:
		TXMemoryRawArray<TIndexType>	fData;
};

/////////////////////////////////////////////////////////////////////////////////////////
typedef Uint32			LargeArrayIndex;

// ------------------------------------------------------------------------------------------------------------------------
class TSmallArrayHandler : public TXMemoryRawArray<short>
{
	public:
		TSmallArrayHandler(size_t dataSz, size_t dataOff = sizeof(short), size_t countOff = 0L, Bool8 zeroBasedCount = false, short numCells = 0, Bool8 growGeometrically = true)
			: TXMemoryRawArray<short>(dataSz, dataOff, countOff, zeroBasedCount, numCells, growGeometrically)	{ }

		TSmallArrayHandler(GSHandle dataH, size_t dataSz, size_t dataOff, size_t countOff, Bool8 zeroBasedCount)
			: TXMemoryRawArray<short>(dataH, dataSz, dataOff, countOff, zeroBasedCount)	{ }
};

// ------------------------------------------------------------------------------------------------------------------------
template<typename T>
class TSmallArray : public TXMemoryArray<T, short>
{
	public:
		TSmallArray(size_t dataOff = sizeof(short), size_t countOff = 0L, Bool8 zeroBasedCount = false, short numCells = 0, Bool8 growGeometrically = true)
			: TXMemoryArray<T, short>(dataOff, countOff, zeroBasedCount, numCells, growGeometrically)	{ }

		TSmallArray(EArrayGrowthMethod growthMethod)
			: TXMemoryArray<T, short>(growthMethod)		{ }

		TSmallArray(GSHandle dataH, size_t dataOff, size_t countOff, Bool8 zeroBasedCount)
			: TXMemoryArray<T, short>(dataH, dataOff, countOff, zeroBasedCount)	{ }

};

// ------------------------------------------------------------------------------------------------------------------------
template<typename T>
class TLargeArray : public TXMemoryArray<T, LargeArrayIndex>
{
	public:
		TLargeArray(size_t dataOff = sizeof(LargeArrayIndex), size_t countOff = 0L, Bool8 zeroBasedCount = false, short numCells = 0, Bool8 growGeometrically = true)
			: TXMemoryArray<T, LargeArrayIndex>(dataOff, countOff, zeroBasedCount, numCells, growGeometrically)	{ }

		TLargeArray(EArrayGrowthMethod growthMethod )
			: TXMemoryArray<T, LargeArrayIndex>(growthMethod)		{ }

		TLargeArray(GSHandle dataH, size_t dataOff, size_t countOff, Bool8 zeroBasedCount)
			: TXMemoryArray<T, LargeArrayIndex>(dataH, dataOff, countOff, zeroBasedCount)	{ }
};

// C++11 "alias template" equivalent of the above
//template<typename T> using TSmallArray = TXMemoryArray<T, short>;
//template<typename T> using TLargeArray = TXMemoryArray<T, LargeArrayIndex>;

/////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_TARRAY(DataType)				typedef TSmallArray<DataType> T##DataType##Array
#define DEFINE_NOPOP_TARRAY(DataType)		typedef TSmallArray<DataType> T##DataType##Array

#define DEFINE_TLARGEARRAY(DataType)		typedef TLargeArray<DataType> TLarge##DataType##Array
#define DEFINE_NOPOP_TLARGEARRAY(DataType)	typedef TLargeArray<DataType> TLarge##DataType##Array


/////////////////////////////////////////////////////////////////////////////////////////
// Implementation TXMemoryRawArray
/////////////////////////////////////////////////////////////////////////////////////////

GSHandle	TXMemoryRawArray_ctor(size_t size);
void		TXMemoryRawArray_dtor(GSHandle h);
void		TXMemoryRawArray_GetSize(GSHandle h, size_t& size);
Boolean		TXMemoryRawArray_SetSize(GSHandle h, size_t size, std::function<void(void* oldMem, size_t oldSize, void* newMem, size_t newSize)> copyCallback=nullptr);
void		TXMemoryRawArray_HUnlock(GSHandle h);
void		TXMemoryRawArray_HLock(GSHandle h);
void		TXMemoryRawArray_DMSG(const char* str, Sint32 p1);
void		TXMemoryRawArray_DMSG(const char* str, Sint32 p1, Sint32 p2);
GSHandle	TXMemoryRawArray_FixHandle(GSHandle h);

template <typename TIndexType>
TXMemoryRawArray<TIndexType>::TXMemoryRawArray(size_t dataSz, size_t dataOff, size_t countOff, Bool8 zeroBasedCount, short numCells, Bool8 growGeometrically)
{
	fDataSize			= dataSz;
	fGrowthMethod		= growGeometrically ? eGeometricGrowth : eArithmeticGrowth;
	fCountOffset		= countOff;
	fDataOffset			= dataOff;
	fFreeMemWhenDone	= true;
	fCountZeroBased		= zeroBasedCount;

	this->fDataHandle	= TXMemoryRawArray_ctor(kBuffSize * fDataSize + fDataOffset);

	this->fNumAllocItems = this->fDataHandle ? kBuffSize : numCells;
	this->SetCount(0);
	
	#ifdef BUG
		this->CheckArrayValues();
	#endif
}

template <typename TIndexType>
TXMemoryRawArray<TIndexType>::TXMemoryRawArray(size_t dataSz, EArrayGrowthMethod growthMethod)
{
	fDataSize			= dataSz;
	fGrowthMethod		= growthMethod;
	fCountOffset		= 0L;
	fDataOffset			= sizeof(TIndexType);
	fFreeMemWhenDone	= true;
	fCountZeroBased		= true;

	this->fDataHandle	= TXMemoryRawArray_ctor(kBuffSize * fDataSize + fDataOffset);

	this->fNumAllocItems = this->fDataHandle ? kBuffSize : 0;
	this->SetCount(0);
	
	#ifdef BUG
		this->CheckArrayValues();
	#endif
}

template <typename TIndexType>
TXMemoryRawArray<TIndexType>::TXMemoryRawArray(GSHandle dataH, size_t dataSz, size_t dataOff, size_t countOff, Bool8 zeroBasedCount)
{
	fDataSize     = dataSz;
	fGrowthMethod = eOneAtATimeGrowth;
	fDataOffset = dataOff;
	fCountOffset = countOff;
	fCountZeroBased = zeroBasedCount;
	fFreeMemWhenDone = false;

	// In case the incoming 'handle' was just &ptr, fix it to a real handle
	fDataHandle = TXMemoryRawArray_FixHandle(dataH);

	TIndexType numCells = *((TIndexType*) (*fDataHandle + fCountOffset));
	fNumUsedItems = (fCountZeroBased) ? numCells+1 : numCells;
	fNumAllocItems = fNumUsedItems;

	ASSERTHANDLE(kBruce, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
	
	#ifdef BUG
		this->CheckArrayValues();
	#endif
}

template <typename TIndexType>
TXMemoryRawArray<TIndexType>::~TXMemoryRawArray()
{
	if (this->fDataHandle && fFreeMemWhenDone)
		TXMemoryRawArray_dtor( this->fDataHandle );
}

#if BUG
template <typename TIndexType>
void* TXMemoryRawArray<TIndexType>::GetCellPtr(TIndexType cellNum) const
/*
	Returns a pointer to the beginning of the data at cellNum
*/
{
	if (fDataHandle) {
		ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
	
		#ifdef BUG
		if ((cellNum >= this->NumItems()) && cellNum != std::numeric_limits<TIndexType>::max()) {
			DSTOP((kSean, brief, "cellNum out of range! (cellNum = %i, cellMax = %i)\n", cellNum, this->NumItems() - 1));
		}
		if (this->NumItems() == 0) {
			DSTOP((kSean, "There are no items to access!\n"));
		}
		#endif

		if (cellNum >= this->NumItems())
			cellNum = this->NumItems()-1;

		Ptr result = (Ptr) (*this->fDataHandle + fDataOffset + cellNum*fDataSize); //-V104
		
		ASSERTPOINTER(kSean, result, fDataSize);
		return result;
	}
	
	return nullptr;
}
#endif

#ifdef BUG

template <typename TIndexType>
void TXMemoryRawArray<TIndexType>::WriteArray() const
{
	DMSG((kEveryone, "dataSize = %" PRIuPTR "\n", fDataSize));
	DMSG((kEveryone, "dataOff = %" PRIuPTR "\n", fDataOffset));
	DMSG((kEveryone, "countOff = %" PRIuPTR "\n", fCountOffset));
	DMSG((kEveryone, "NumItems = %i\n", this->NumItems()));
}
#endif

#ifdef BUG
template <typename TIndexType>
void TXMemoryRawArray<TIndexType>::CheckArrayValues(bool bcheckExtraSpace) const
{
		if (!this->fDataHandle)
			DSTOP((kSean, "TXMemoryRawArray::CheckArrayValues - No data handle!\n"));
		else {
			ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
				
			size_t hSz;
			TXMemoryRawArray_GetSize(this->fDataHandle, hSz);

			if (this->fDataOffset < sizeof(TIndexType) || (size_t)this->fDataOffset > hSz){
				DMSG((kEveryone, "Illegal dataOff: %" PRIuPTR "\n", this->fDataOffset));
			}
 			if (this->fCountOffset > (hSz - sizeof(TIndexType))){
				DMSG((kEveryone, "Illegal countOff: %" PRIuPTR "\n", this->fCountOffset));
			}

			size_t spaceNeeded = this->NumItems() * this->fDataSize; //-V104
			if (spaceNeeded > (hSz - fDataOffset))
				DSTOP((kSean, "Handle is not large enough to hold %i items(items stored = %i)\n", this->NumItems(), spaceNeeded / this->fDataSize));
			
			if (bcheckExtraSpace && (hSz > (fNumUsedItems * fDataSize + fDataOffset))) { //-V104

				#if !DaveD && !AndrewB
					// XXX: not sure if these should be a DSTOP or a DMSG
					DMSG((kSean, "SpaceNeeded: %" PRIuPTR ", hSize: %" PRIuPTR ", space available: %" PRIuPTR "\n", spaceNeeded, hSz, hSz));
					DMSG((kSean, "Handle is larger than necessary to hold %" PRIuPTR " items(items stored = %" PRIuPTR ")\n", this->NumItems(), spaceNeeded / this->fDataSize));
				#endif	// !DaveD
			}
		}
}
#endif

template <typename TIndexType>
Boolean TXMemoryRawArray<TIndexType>::AppendCells(TIndexType numCells)
/*
	Adds numCells with no data to end of array
*/
{ 
	#if BUG && !_MINICAD_EXTERNAL_
	if (GSDebug::DebugLevel() > verbose) {
		DMSG((kMark, " --- Adding %i cells.\n", numCells));
		this->WriteArray();
	}
	#endif
	
	size_t dataSize;
	Boolean validResize;
	
	if (this->fDataHandle) {

		#ifdef _MINICAD_
		ASSERTUNLOCKED(kPaul, this->fDataHandle);
		#endif
	
		ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
	
		TIndexType nItems = this->NumItems();
		
		// will numCells growth fit without overflowing index type?
		if (std::numeric_limits<TIndexType>::max() - nItems >= numCells) {
			if (nItems + numCells > this->fNumAllocItems) {

				size_t neededSize = 0;

				DMSG((kMark, "Expanding TLargeArray from %d items to... ", this->fNumAllocItems)); 

				switch (this->fGrowthMethod) {

					case eArithmeticGrowth:
					{
						size_t itemsCnt = (nItems + numCells + (kBuffSize - (nItems + numCells) % kBuffSize));
						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = this->fDataSize * itemsCnt;
						break;				
					}

					case eGeometricGrowth:
					{
						// 20% with 10 minimum [MAF 10/20/00] //-V201
						size_t itemsCnt	= DemoteTo<size_t>(kRBerge, ceil((float)this->fNumAllocItems * 1.2f));
						if ( itemsCnt < (size_t)(nItems + 10) )
						{
							itemsCnt = (size_t)(nItems + 10);
						}

						// If 20%/#10 is not enough for requested numCells.
						if ( itemsCnt < nItems + numCells )
						{
							itemsCnt = nItems + numCells;
						}

						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = this->fDataSize * itemsCnt;
						break;
					}

					case eExponentialGrowth:
					{
						size_t itemsCnt	= DemoteTo<size_t>(kRBerge, ceil((float)this->fNumAllocItems * this->fNumAllocItems));
						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = this->fDataSize * itemsCnt;
						break;
					}

					case eOneAtATimeGrowth:
					{
						size_t itemsCnt	= (nItems + numCells);
						// overflow already handled at very top
						neededSize = fDataSize * itemsCnt;
						break;
					}

					default:
						DSTOP((kMark, "Invalid TLargeArray growth method: %d\n", this->fGrowthMethod));
						neededSize = 0;
						break;				
				}
				
				dataSize = neededSize + fDataOffset;
				ASSERTN(kSean, dataSize >= (fDataSize * numCells + fDataOffset)); //-V104
			}
			else
				dataSize = 0;
			
			if (dataSize <= 0L) {
				this->SetCount(nItems + numCells);
				return true;
			}
			else {
				#ifdef _MINICAD_
				ASSERTUNLOCKED(kPaul, this->fDataHandle);
				
				TXMemoryRawArray_HUnlock(this->fDataHandle);
		
				validResize = TXMemoryRawArray_SetSize(this->fDataHandle, dataSize);
				#else

				TXMemoryRawArray_SetSize(this->fDataHandle, dataSize);

				size_t	dataHandleSize = 0;
				TXMemoryRawArray_GetSize(this->fDataHandle, dataHandleSize);
				validResize = (dataHandleSize == dataSize);
				#endif

				if (validResize) {
					this->SetCount(nItems + numCells);
					this->fNumAllocItems = (TIndexType) ((dataSize - fDataOffset) / fDataSize); //-V202
					DMSG((kMark, "%d items\n", this->fNumAllocItems)); 
					ASSERTN(kSean, fNumUsedItems <= fNumAllocItems);
					return true;
				}
				else {
					DSTOP((kSean, "Could not increase array size.\n"));
					return false;
				}
			}
		}
		else {
			DSTOP((kSean, "TXMemoryRawArray::AppendCellsAndData - ran out of index space (>UINT32_MAX cells)\n"));
			return false;
		}
	}
	else
		return false;
}

template <typename TIndexType>
Boolean TXMemoryRawArray<TIndexType>::AppendCellAndData(const void* cellData)
/*
	Adds one cell and data in cellData to end of array
*/
{

	if (this->AppendCells(1)) {
		memcpy(this->GetCellPtr(this->NumItems()-1), cellData, (size_t) this->fDataSize);
		return true;
	}
	else
		return false;
}

template <typename TIndexType>
Boolean TXMemoryRawArray<TIndexType>::InsertCells(TIndexType beforeWhere, TIndexType numCells)
/*
	Inserts numCells cells into the array (0 inserts at front)
*/
{
	TIndexType prevSize;
	
	if (beforeWhere > this->NumItems()) {
		DSTOP((kSean, "Trying to insert cells at illegal point (beforeWhere: %i)\n", beforeWhere));
		return false;
	}
	
	if (numCells <= 0) {
		DSTOP((kSean, "numCells is <= 0 in InsertCells! (numCells: %i)\n", numCells));
		return false;
	}

	if (std::numeric_limits<TIndexType>::is_signed && beforeWhere < 0) {
		DSTOP((kRBerge, "beforeWhere is < 0 in InsertCells! (beforeWhere: %i)\n", beforeWhere));
		return false;
	}

	prevSize = this->NumItems();
	
	#ifdef _MINICAD_
	ASSERTUNLOCKED(kPaul, this->fDataHandle);
	#endif
	
	if (this->AppendCells(numCells)) {
		// Slide all the past beforeWhere-1 up by fDataSize
		Ptr beforeWherePtr = (Ptr) this->GetCellPtr(beforeWhere);

		#if _MINICAD_
			Mem_Move(beforeWherePtr+(this->fDataSize*numCells), beforeWherePtr, (prevSize-beforeWhere)*this->fDataSize);
		#else
			//The memmove call replaces the ::VWMM::NNABlockMoveData(...) call - required for Altura removal changes. [AAO, 1-29-03]
			memmove(beforeWherePtr+(this->fDataSize*numCells), beforeWherePtr, (prevSize-beforeWhere)*this->fDataSize); //-V104
			//::VWMM::NNABlockMoveData(beforeWherePtr, beforeWherePtr+(this->fDataSize*numCells), (prevSize-beforeWhere)*this->fDataSize);
		#endif
		return true;
	}
	else	
		return false;
}

template <typename TIndexType>
Boolean TXMemoryRawArray<TIndexType>::InsertCellAndData(TIndexType beforeWhere, const void* cellData)
/*
	Inserts one cell anywhere in the array (0 inserts at front), and sets it to data in cellData
*/
{
	if (this->InsertCells(beforeWhere, 1)) {
		memcpy(this->GetCellPtr(beforeWhere), cellData, (size_t) this->fDataSize);
		return true;
	}
	else	
		return false;
}

template <typename TIndexType>
void TXMemoryRawArray<TIndexType>::DeleteCells(TIndexType firstCell, TIndexType numCells)
//
//	Deletes numCell cells starting at firstCell
//
{
	if ((numCells ==  0) && (this->NumItems() == 0))
		return;

	if (numCells > (this->NumItems()-firstCell)) {
		DSTOP((kSean, "numCells is out of bounds in DeleteCells (numCells: %i)", numCells));
		return;
	}
	
	if (firstCell >= this->NumItems()) {
		DSTOP((kSean, "firstCell is out of bounds in DeleteCells (firstCell: %i)", firstCell));
		return;
	}
	
	if (this->fDataHandle) {
		ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);

		TIndexType numItems = this->NumItems();
		Ptr firstCellPtr = (Ptr) this->GetCellPtr(firstCell);
		ASSERTPOINTER(kSean, firstCellPtr, fDataSize*numCells);
		size_t numMoveBytes = (numItems-(firstCell+numCells))*this->fDataSize; //-V104
		if (numMoveBytes > 0)
		{
		#if _MINICAD_
			Mem_Move(firstCellPtr, firstCellPtr + numCells*this->fDataSize, numMoveBytes);
		#else
			memmove(firstCellPtr, firstCellPtr + numCells*this->fDataSize, numMoveBytes); //-V104
		#endif			
		}
			
		if (! fFreeMemWhenDone ||
			((numItems / kBuffSize) != (numItems - numCells) / kBuffSize)) 
		{
			TIndexType numAllocCells;
			
			if (fFreeMemWhenDone)
				numAllocCells = ((numItems - numCells) / kBuffSize + 1) * kBuffSize;
			else
				numAllocCells = numItems - numCells;

			size_t newHandleSize = fDataOffset + fDataSize * numAllocCells; //-V104
			TXMemoryRawArray_SetSize(fDataHandle, newHandleSize); // Handle ALWAYS gets smaller //-V107
			
			ASSERTN(kSean, numAllocCells >= (numItems - numCells));
			ASSERTN(kSean, numAllocCells == (newHandleSize - fDataOffset) / this->fDataSize); //-V104
			fNumAllocItems = numAllocCells;
		}
		
		ASSERTHANDLE(kSean, fDataHandle, fDataOffset + fNumAllocItems * fDataSize);
		this->SetCount(numItems-numCells);
	}
}

template <typename TIndexType>
void TXMemoryRawArray<TIndexType>::SetCount(TIndexType numDataItems)
{
	if (fDataHandle) {
		*((TIndexType *) (*fDataHandle + fCountOffset)) = fCountZeroBased ? 
					numDataItems-1 : numDataItems;
		fNumUsedItems = numDataItems;
	}
}

template <typename TIndexType>
void TXMemoryRawArray<TIndexType>::SortArray(QSortCompareFunc CompFunc)
{
	TXMemoryRawArray_HLock(this->GetDataHandle());
	TIndexType numItems =  this->NumItems();
	if (numItems >0) qsort(this->GetCellPtr(0), numItems, (size_t) fDataSize, CompFunc); //-V106

#if !GS_INTERFACE_FACTORING && defined(_MINICAD_)
	ASSERTN(kSean, !HandleIsPurgeable(this->GetDataHandle()));
#endif

	TXMemoryRawArray_HUnlock(this->GetDataHandle());
}


/////////////////////////////////////////////////////////////////////////////////////////
// Implementation TXMemoryArray
/////////////////////////////////////////////////////////////////////////////////////////


template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::AppendCellsRaw(TIndexType numCells)
/*
	Adds numCells with no data to end of array
*/
{ 
	#if BUG && !_MINICAD_EXTERNAL_
	if (GSDebug::DebugLevel() > verbose) {
		DMSG((kMark, " --- Adding %i cells.\n", numCells));
		fData.WriteArray();
	}
	#endif
	
	size_t dataSize;
	Boolean validResize;
	
	if (fData.fDataHandle) {

		#ifdef _MINICAD_
		ASSERTUNLOCKED(kPaul, fData.fDataHandle);
		#endif
	
		ASSERTHANDLE(kSean, fData.fDataHandle, fData.fDataOffset + fData.fNumAllocItems * fData.fDataSize);
	
		TIndexType nItems = fData.NumItems();
		
		// will numCells growth fit without overflowing index type?
		if (std::numeric_limits<TIndexType>::max() - nItems >= numCells) {
			if (nItems + numCells > fData.fNumAllocItems) {

				size_t neededSize = 0;

				DMSG((kMark, "Expanding TLargeArray from %d items to... ", fData.fNumAllocItems)); 

				switch (fData.fGrowthMethod) {

					case eArithmeticGrowth:
					{
						size_t itemsCnt	= (nItems + numCells + (TXMemoryRawArray<TIndexType>::kBuffSize - (nItems + numCells) % TXMemoryRawArray<TIndexType>::kBuffSize));
						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = fData.fDataSize * itemsCnt;
						break;
					}
						
					case eGeometricGrowth:
					{
						// 20% with 10 minimum [MAF 10/20/00] //-V201
						size_t itemsCnt	= DemoteTo<size_t>(kRBerge, ceil((float)fData.fNumAllocItems * 1.2f));
						if ( itemsCnt < (size_t)(nItems + 10) )
						{
							itemsCnt = (size_t)(nItems + 10);
						}

						// If 20%/#10 is not enough for requested numCells.
						if ( itemsCnt < size_t(nItems + numCells) )
						{
							itemsCnt = nItems + numCells;
						}

						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = fData.fDataSize * itemsCnt;
						break;
					}

					case eExponentialGrowth:
					{
						size_t itemsCnt	= DemoteTo<size_t>(kRBerge, ceil((float)fData.fNumAllocItems * fData.fNumAllocItems));
						// extra growth might overflow index type
						if (itemsCnt > std::numeric_limits<TIndexType>::max())
						{
							itemsCnt = std::numeric_limits<TIndexType>::max();
						}
						neededSize = fData.fDataSize * itemsCnt;
						break;
					}
						
					case eOneAtATimeGrowth:
					{
						size_t itemsCnt	= (nItems + numCells);
						// overflow already handled at very top
						neededSize = fData.fDataSize * itemsCnt;
						break;
					}

					default:
						DSTOP((kMark, "Invalid TLargeArray growth method: %d\n", fData.fGrowthMethod));
						neededSize = 0;
						break;				
				}
				
				dataSize = neededSize + fData.fDataOffset;
				ASSERTN(kSean, dataSize >= (fData.fDataSize * numCells + fData.fDataOffset)); //-V104
			}
			else
				dataSize = 0;
			
			if (dataSize <= 0L) {
				fData.SetCount(nItems + numCells);
				return true;
			}
			else {
				auto copyCallback = [&](void* oldMem, size_t oldSize, void* newMem, size_t newSize)
				{
					memcpy( newMem, oldMem, fData.fDataOffset );
					Ptr oldPtr = ((Ptr)oldMem) + fData.fDataOffset;
					Ptr newPtr = ((Ptr)newMem) + fData.fDataOffset;
					for(TIndexType i=0; i<fData.fNumUsedItems; i++)
					{
						T* oldObj = (T*) oldPtr;
						new ( newPtr ) T( *oldObj );
						oldObj->~T();

						oldPtr += sizeof(T);
						newPtr += sizeof(T);
					}
				};

				#ifdef _MINICAD_
				ASSERTUNLOCKED(kPaul, fData.fDataHandle);
				
				TXMemoryRawArray_HUnlock(fData.fDataHandle);
		
				validResize = TXMemoryRawArray_SetSize(fData.fDataHandle, dataSize, copyCallback);
				#else

				TXMemoryRawArray_SetSize(fData.fDataHandle, dataSize, copyCallback);

				size_t	dataHandleSize = 0;
				TXMemoryRawArray_GetSize(fData.fDataHandle, dataHandleSize);
				validResize = (dataHandleSize == dataSize);
				#endif

				if (validResize) {
					fData.SetCount(nItems + numCells);
					fData.fNumAllocItems = (TIndexType) ((dataSize - fData.fDataOffset) / fData.fDataSize); //-V202
					DMSG((kMark, "%d items\n", fData.fNumAllocItems)); 
					ASSERTN(kSean, fData.fNumUsedItems <= fData.fNumAllocItems);
					return true;
				}
				else {
					DSTOP((kSean, "Could not increase array size.\n"));
					return false;
				}
			}
		}
		else {
			DSTOP((kSean, "TXMemoryRawArray::AppendCellsAndData - ran out of index space (>UINT32_MAX cells)\n"));
			return false;
		}
	}
	else
		return false;
}

template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::InsertCellsRaw(TIndexType beforeWhere, TIndexType numCells)
/*
	Inserts numCells cells into the array (0 inserts at front)
*/
{
	TIndexType prevSize;
	
	if (beforeWhere > this->NumItems()) {
		DSTOP((kSean, "Trying to insert cells at illegal point (beforeWhere: %i)\n", beforeWhere));
		return false;
	}
	
	if (numCells <= 0) {
		DSTOP((kSean, "numCells is <= 0 in InsertCellsRaw! (numCells: %i)\n", numCells));
		return false;
	}
	if (std::numeric_limits<TIndexType>::is_signed && beforeWhere < 0) {
		DSTOP((kRBerge, "beforeWhere is < 0 in InsertCellsRaw! (beforeWhere: %i)\n", beforeWhere));
		return false;
	}
	
	prevSize = fData.NumItems();
	
	#ifdef _MINICAD_
	ASSERTUNLOCKED(kPaul, this->fDataHandle);
	#endif
	
	if (this->AppendCellsRaw(numCells))
	{
		if ( beforeWhere < prevSize ) // move only if not added at the end
		{
			// Slide all the past beforeWhere-1 up by fDataSize
			Ptr beforeWherePtr = (Ptr) fData.GetCellPtr(beforeWhere);
			Ptr newWherePtr = beforeWherePtr + sizeof(T) * numCells;

			TIndexType	cnt	= prevSize - beforeWhere;
			beforeWherePtr	+= cnt * sizeof(T);
			newWherePtr		+= cnt * sizeof(T);

			for(TIndexType i=0; i<cnt; i++)
			{
				beforeWherePtr	-= sizeof(T);
				newWherePtr		-= sizeof(T);

				T* oldPtr = (T*) beforeWherePtr;
				new ( newWherePtr ) T( *oldPtr );
				oldPtr->~T();
			}
		}

		return true;
	}
	else
		return false;
}

template <class T, typename TIndexType>
void TXMemoryArray<T, TIndexType>::DeleteCellsRaw(TIndexType firstCell, TIndexType numCells)
//
//	Deletes numCell cells starting at firstCell
//
{
	if ((numCells ==  0) && (fData.NumItems() == 0))
		return;

	if (numCells > (fData.NumItems()-firstCell)) {
		DSTOP((kSean, "numCells is out of bounds in DeleteCells (numCells: %i)", numCells));
		return;
	}
	
	if (firstCell >= fData.NumItems()) {
		DSTOP((kSean, "firstCell is out of bounds in DeleteCells (firstCell: %i)", firstCell));
		return;
	}
	
	if (fData.fDataHandle) {
		ASSERTHANDLE(kSean, fData.fDataHandle, fData.fDataOffset + fData.fNumAllocItems * fData.fDataSize);

		TIndexType numItems = fData.NumItems();
		Ptr firstCellPtr = (Ptr) fData.GetCellPtr(firstCell);
		ASSERTPOINTER(kSean, firstCellPtr, fData.fDataSize*numCells);
		if (numItems-(firstCell+numCells) > 0)
		{
			Ptr oldWherePtr = firstCellPtr + sizeof(T) * numCells;

			TIndexType	cnt	= numItems-(firstCell+numCells);
			for(TIndexType i=0; i<cnt; i++)
			{
				T* oldPtr = (T*) oldWherePtr;
				new ( firstCellPtr ) T( *oldPtr );
				oldPtr->~T();

				firstCellPtr	+= sizeof(T);
				oldWherePtr		+= sizeof(T);
			}
		}
			
		if (! fData.fFreeMemWhenDone ||
			((numItems / TXMemoryRawArray<TIndexType>::kBuffSize) != (numItems - numCells) / TXMemoryRawArray<TIndexType>::kBuffSize)) 
		{
			TIndexType numAllocCells;
			
			if (fData.fFreeMemWhenDone)
				numAllocCells = ((numItems - numCells) / TXMemoryRawArray<TIndexType>::kBuffSize + 1) * TXMemoryRawArray<TIndexType>::kBuffSize;
			else
				numAllocCells = numItems - numCells;

			auto copyCallback = [&](void* oldMem, size_t oldSize, void* newMem, size_t newSize)
			{
				memcpy( newMem, oldMem, fData.fDataOffset );
				Ptr oldPtr = ((Ptr)oldMem) + fData.fDataOffset;
				Ptr newPtr = ((Ptr)newMem) + fData.fDataOffset;
				for(TIndexType i=0; i<(numItems-numCells); i++)
				{
					T* oldObj = (T*) oldPtr;
					new ( newPtr ) T( *oldObj );
					oldObj->~T();

					oldPtr += sizeof(T);
					newPtr += sizeof(T);
				}
			};

			size_t newHandleSize = fData.fDataOffset + fData.fDataSize * numAllocCells; //-V104
			TXMemoryRawArray_SetSize(fData.fDataHandle, newHandleSize, copyCallback); // Handle ALWAYS gets smaller //-V107
			
			ASSERTN(kSean, numAllocCells >= (numItems - numCells));
			ASSERTN(kSean, (size_t)numAllocCells == (newHandleSize - fData.fDataOffset) / fData.fDataSize); //-V104
			fData.fNumAllocItems = numAllocCells;
		}
		
		ASSERTHANDLE(kSean, fData.fDataHandle, fData.fDataOffset + fData.fNumAllocItems * fData.fDataSize);
		fData.SetCount(numItems-numCells);
	}
}

template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::AppendCells(TIndexType numCells)
{
	TIndexType	orgLen = this->NumItems();

	bool result = false;
	if ( this->AppendCellsRaw(numCells) )
	{
		for(TIndexType i=orgLen; i<numCells; ++i)
		{
			void* newItem = fData.GetCellPtr( this->NumItems() - 1 );
			new ( newItem ) T();
		}
		result = true;
	}

	return result;
}

template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::PushData(const T& cellData)
{
	bool result = false;
	if ( this->AppendCellsRaw(1) )
	{
		void* newItem = fData.GetCellPtr( this->NumItems() - 1 );
		new ( newItem ) T( cellData );
		result = true;
	}

	return result;
}

template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::InsertData(TIndexType beforeWhere, const T& cellData)
{
	bool result = false;
	if ( this->InsertCellsRaw( beforeWhere, 1 ) )
	{
		void* newItem = fData.GetCellPtr( beforeWhere );
		new ( newItem ) T( cellData );
		result = true;
	}

	return result;
}

template <class T, typename TIndexType>
Boolean TXMemoryArray<T, TIndexType>::InsertData(TIndexType where, TIndexType count, const T* arrCellData)
{
	bool result = false;
	if ( this->InsertCellsRaw( where, count ) )
	{
		for(TIndexType i=0; i<count; ++i)
		{
			void* newItem = fData.GetCellPtr( where + i );
			new ( newItem ) T( arrCellData[i] );
		}
		result = true;
	}

	return result;
}

template <class T, typename TIndexType>
void TXMemoryArray<T, TIndexType>::DeleteCells(TIndexType firstCellToDelete, TIndexType numCells)
{
	for(TIndexType i=0; i<numCells; ++i)
	{
		T* theItem = this->GetAt( firstCellToDelete + i );
		//theItem;
		theItem->~T();
	}

	this->DeleteCellsRaw( firstCellToDelete, numCells );
}

template <class T, typename TIndexType>
T TXMemoryArray<T, TIndexType>::PopData()
{
	T tmp;
	
	if ( this->NumItems() > 0 )
	{
		tmp = (*this)[std::numeric_limits<TIndexType>::max()];
		this->DeleteCells( this->NumItems() - 1, 1 );
	}
	return tmp; 
}


/////////////////////////////////////////////////////////////////////////////////////////
// TXGenericArray //
/////////////////////////////////////////////////////////////////////////////////////////

template<class T> class TXGenericArray
{
public:
					TXGenericArray(size_t nInitialSize=0, size_t nGrowBy=10);
					TXGenericArray(const TXGenericArray &src);
	virtual			~TXGenericArray();

	TXGenericArray&	operator=(const TXGenericArray &src);

	size_t			GetSize() const;
	bool			SetSize(size_t size);

	bool			IsEmpty() const;

	const T&		GetAt(size_t nIndex) const;
	T&				GetAt(size_t nIndex);
	const T&		operator[](size_t nIndex) const;
	T&				operator[](size_t nIndex);

	void 			SetAt(size_t nIndex, const T & value);

	bool 			Append(const T & value);
	bool 			Append(const TXGenericArray & src);

	void 			Erase(size_t nIndex, size_t nCount = 1);
	void 			Clear();

	// return size_t(-1) if not found
	size_t			Find(const T& value);

private:
	void 			Init(size_t nInitialSize, size_t nGrowBy);
	bool 			EnsureArraySize(size_t nSize);

	size_t		fGrowBy;
	size_t		fNumStringsStored;
	size_t		fMaxStringsStored;
	T*			fValuesPtr;
};


/////////////////////////////////////////////////////////////////////////////////////////
// TXGenericArray Routines //
/////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::TXGenericArray(size_t nInitialSize, size_t nGrowBy)
{
	this->Init(nInitialSize, nGrowBy);
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::TXGenericArray(const TXGenericArray<T> & src)
{
	this->Init(src.GetSize(), src.fGrowBy);
	this->Append(src);
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>::~TXGenericArray()
{
	this->Clear();
}

//---------------------------------------------------------------------------------------
template<class T> TXGenericArray<T>& TXGenericArray<T>::operator=(const TXGenericArray<T> & src)
{
	this->Init(src.GetSize(), src.fGrowBy);
	this->Append(src);
	return *this;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::SetSize(size_t nSize)
{
	if (nSize < fNumStringsStored) {
		this->RemoveAt(nSize, fNumStringsStored - nSize);
	}
	else if (nSize > fNumStringsStored) {
		if (this->EnsureArraySize(nSize)) {
			fNumStringsStored = nSize;
		}
		else
			return false;
	}
	return true;
}

//---------------------------------------------------------------------------------------
template<class T> size_t TXGenericArray<T>::GetSize() const
{
	return fNumStringsStored;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::IsEmpty() const
{
	return fNumStringsStored == 0;
}

//---------------------------------------------------------------------------------------
template<class T> const T& TXGenericArray<T>::GetAt(size_t nIndex) const
{
	ASSERTN(kDave, nIndex < fNumStringsStored);
	return fValuesPtr[nIndex];
}

//---------------------------------------------------------------------------------------
template<class T> T& TXGenericArray<T>::GetAt(size_t nIndex)
{
	ASSERTN(kDave, nIndex < fNumStringsStored);
	return fValuesPtr[nIndex];
}

//---------------------------------------------------------------------------------------
template<class T> const T& TXGenericArray<T>::operator[](size_t nIndex) const
{
	return GetAt(nIndex);
}

//---------------------------------------------------------------------------------------
template<class T> T& TXGenericArray<T>::operator[](size_t nIndex)
{
	return GetAt(nIndex);
}

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::SetAt(size_t nIndex, const T & value)
{
	if (this->EnsureArraySize(nIndex+1)) {
		fValuesPtr[nIndex] = value;
		if (nIndex+1 > fNumStringsStored) {
			fNumStringsStored = nIndex+1;
		}
	}
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::Append(const T & value)
{
	if (EnsureArraySize(fNumStringsStored+1)) {
		fValuesPtr[fNumStringsStored] = value;
		++fNumStringsStored;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::Append(const TXGenericArray<T> & src)
{
	const size_t nNumToAppend = src.GetSize();

	if (this->EnsureArraySize(fNumStringsStored + nNumToAppend)) {

		for (size_t i=0; i<nNumToAppend; ++i) {
			this->Append(src[i]);
		}
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Erase(size_t nIndex, size_t nCount)
{
	// The method used here may seem weird, but it doesn't require
	// any new memory to be allocated, so it can't fail.

	// Check and correct parameters.
	if (nIndex < fNumStringsStored && nCount > 0) {
	
		// for the starting index specified, determine the maximum legal count
		size_t maxCount = fNumStringsStored - nIndex;
	
		// pin count to the max legal range
		if (nCount > maxCount)
			nCount = maxCount;

		// slide the remaining strings down one by one
		for (size_t i = nIndex; i + nCount < fNumStringsStored; i++) {
			fValuesPtr[i] = fValuesPtr[i + nCount];
		}
		
		fNumStringsStored -= nCount;		
	}
}


// this is the source of a gargantuan memory leak. TXGenericArray is defined to grow in chunks of 10 or more strings.
// so the maximum size is usually greater than the occupied size. When we were disposing of these arrays (which are used
// all over the place) we were only disposing of the strings being used and leaking the unused strings at the end of the array. - PCP

//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Clear()
{
	// Delete each value in the array.
	for (size_t i=0; i<fMaxStringsStored; ++i) {
		fValuesPtr[i].~T();
	}

	char*		pBuffer		= (char*) fValuesPtr;
	if ( pBuffer ) {
		char*	pTheData		= pBuffer - 1;
		char	memoryCode		= *pTheData;

		void TXGenericArray_Dispose(char memoryCode, char* pTheData);
		TXGenericArray_Dispose( memoryCode, pTheData );
	}

	fValuesPtr = NULL;

	fNumStringsStored = fMaxStringsStored = 0;
}


//---------------------------------------------------------------------------------------
template<class T> void TXGenericArray<T>::Init(size_t nInitialSize, size_t nGrowBy)
{
	fGrowBy = nGrowBy;
	fNumStringsStored = fMaxStringsStored = 0;
	fValuesPtr = NULL;
	
	this->EnsureArraySize(nInitialSize);
}

//---------------------------------------------------------------------------------------
template<class T> bool TXGenericArray<T>::EnsureArraySize(size_t nSize)
{
	if (fMaxStringsStored < nSize) {

		size_t nRoundedSize = (nSize / fGrowBy) * fGrowBy;
		if (nSize % fGrowBy) nRoundedSize += fGrowBy;

		char	memoryCode		= 0;

		// Allocate new, larger buffer for all of the value pointers.
		char* TXGenericArray_Allocate(char& memoryCode, size_t sz);
		char*	newBuf		= TXGenericArray_Allocate( memoryCode, 1 + sizeof(T) * nRoundedSize );

		if ( newBuf == NULL )
			return false;

		*newBuf			= memoryCode;

		T*	pNewArray = (T*) (newBuf + 1);
		if (pNewArray) {
			for(size_t i=0; i<nRoundedSize; i++) {
				if ( i < fNumStringsStored ) {
					new (&pNewArray[i]) T( fValuesPtr[i] );
				}
				else {
					new (&pNewArray[i]) T();
				}
			}

			size_t	numStringsStored = fNumStringsStored;
			for(size_t i=0; i<numStringsStored; i++) {
				pNewArray[i]	= fValuesPtr[i];
			}

			this->Clear();

			fValuesPtr			= pNewArray;
			fMaxStringsStored	= nRoundedSize;
			fNumStringsStored	= numStringsStored;

			return true;
		}
		return false;
	}
	return true;
}

template<class T> size_t TXGenericArray<T>::Find(const T& value)
{
	for (size_t i = 0; i < fNumStringsStored; i++) {
		if ( this->GetAt (i) == value ) {
			return i;
		}
	}

	return size_t(-1);
}


