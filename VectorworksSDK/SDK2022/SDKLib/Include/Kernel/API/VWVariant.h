//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	This file contains Variant definition.
//

#pragma once

// provide STL memory allocator for VW type memory for the plug-ins
namespace std
{
	// vw memory allocatorfor objects of class _Ty
	template<class _Ty> class vwallocator
	{
	public:
		typedef _Ty 				value_type;


		typedef value_type*			pointer;
		typedef value_type& 		reference;
		typedef const value_type*	const_pointer;
		typedef const value_type& 	const_reference;

		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;

		template<class _Other> struct rebind {	// convert an vwallocator<_Ty> to an vwallocator <_Other>
			typedef vwallocator<_Other> other;
 		};

		pointer address(reference _Val) const {	// return address of mutable _Val
			return (&_Val);
		}

		const_pointer address(const_reference _Val) const {	// return address of nonmutable _Val
			return (&_Val);
		}

		vwallocator() {	// construct default vwallocator (do nothing)
		}

		vwallocator(const vwallocator<_Ty>&) {	// construct by copying (do nothing)
		}

		template<class _Other> vwallocator(const vwallocator<_Other>&) {	// construct from a related vwallocator (do nothing)
		}

		template<class _Other> vwallocator<_Ty>& operator=(const vwallocator<_Other>&) {	// assign from a related vwallocator (do nothing)
			return (*this);
		}
		
		template<class _Other> bool operator==(const vwallocator<_Other>&) {	// assign from a related vwallocator (do nothing)
			return true;
		}

		template<class _Other> bool operator!=(const vwallocator<_Other>&) {	// assign from a related vwallocator (do nothing)
			return false;
		}

		void deallocate(pointer _Ptr, size_type) {	// deallocate object at _Ptr, ignore size
			//operator delete(_Ptr);
#ifndef _WINDOWS
			Mem_DisposePtr( (MemPtr) _Ptr );
#else
			::GS_DisposePtr( gCBP, _Ptr );
#endif
		}

		pointer allocate(size_type _Count) {	// allocate array of _Count elements
			//return (_Allocate(_Count, (pointer)0));
#ifndef _WINDOWS
			pointer ptr =  (pointer) Mem_NewPtr( _Count * sizeof (_Ty) );
#else
			pointer ptr =  (pointer) ::GS_NewPtr( gCBP, _Count * sizeof (_Ty) );
#endif

			if(ptr == NULL)
			{
				std::bad_alloc memException;
				throw memException;
			}
				

			return ptr;
		}

		pointer allocate(size_type _Count, const void*) {	// allocate array of _Count elements, ignore hint
			return (allocate(_Count));
		}

		void construct(pointer _Ptr, const _Ty& _Val) {	// construct object at _Ptr with value _Val
            ::new(static_cast<void*>(_Ptr)) value_type(_Val);
		}

		void destroy(pointer _Ptr)	{	// destroy object at _Ptr
            _Ptr->~value_type();
		}

		size_type max_size() const	{	// estimate maximum array size
			size_type _Count = (size_type)(-1) / sizeof (_Ty);
			return (0 < _Count ? _Count : 1);
		}
	};
}

// ------------------------------------------------
enum EVWVariantType
{
	eVWVariantType_Empty,
	eVWVariantType_SignedInteger,
	eVWVariantType_UnsignedInteger,
	eVWVariantType_Double,
	eVWVariantType_Float,
	eVWVariantType_Bool,
	eVWVariantType_String,
	eVWVariantType_RawBuffer,
	eVWVariantType_Arrary,

	// Vectorworks types
	eVWVariantType_Handle,
	eVWVariantType_InternalNumber,
	eVWVariantType_InternalName,
};

// ------------------------------------------------
class VWVariant
{
public:
					VWVariant();
					VWVariant(EVWVariantType type);
					VWVariant(Sint8 value);
					VWVariant(Uint8 value);
					VWVariant(Sint16 value);
					VWVariant(Uint16 value);
					VWVariant(Sint32 value);
					VWVariant(Uint32 value);
					VWVariant(double value);
					VWVariant(float value);
					VWVariant(bool value);

					VWVariant(const char* szBuffer, size_t size);			// c-style string
					VWVariant(const unsigned char* psBuffer, size_t size);	// pascal-style string
					VWVariant(const TXString& value);
					VWVariant(void* buffer, size_t size, size_t typeID=0);

					VWVariant(MCObjectHandle value);
					//VWVariant(InternalIndex value);	use Sint32
					//VWVariant(InternalName value);
					//VWVariant(ColorRef value);		use Sint16

					VWVariant(const VWVariant& src);

	virtual			~VWVariant();

	VWVariant&		operator=(const VWVariant& value);
	VWVariant&		operator=(Sint8 value);
	VWVariant&		operator=(Uint8 value);
	VWVariant&		operator=(Sint16 value);
	VWVariant&		operator=(Uint16 value);
	VWVariant&		operator=(Sint32 value);
	VWVariant&		operator=(Uint32 value);
	VWVariant&		operator=(double value);
	VWVariant&		operator=(float value);
	VWVariant&		operator=(bool value);
	VWVariant&		operator=(const TXString& value);
	VWVariant&		operator=(const char* szString);
	VWVariant&		operator=(const unsigned char* psString);

	VWVariant&		operator=(MCObjectHandle value);
	//VWVariant&	operator=(InternalIndex value);		// use Sint32
	//VWVariant&	operator=(InternalName value);
	//VWVariant&	operator=(ColorRef value);		// use Sint16

	bool			operator==(const VWVariant& v);
	
	EVWVariantType	GetType() const;
	bool			IsEmpty() const;
	size_t			GetBytesCount() const;

	// values
	Sint8			GetSint8() const;
	void			SetSint8(Sint8 value);
	Uint8	 		GetUint8() const;
	void			SetUint8(Uint8 value);
	Sint16			GetSint16() const;
	void			SetSint16(Sint16 value);
	Uint16			GetUint16() const;
	void			SetUint16(Uint16 value);
	Sint32			GetSint32() const;
	void			SetSint32(Sint32 value);
	Uint32			GetUint32() const;
	void			SetUint32(Uint32 value);
	double			GetDouble() const;
	void			SetDouble(double value);
	float			GetFloat() const;
	void			SetFloat(float value);
	bool			GetBool() const;
	void			SetBool(bool value);

	TXString		GetTXString() const;
	void			SetTXString(const TXString& value);

	// pass in buffer=NULL to check the size
	// return bytes copied to the buffer (or buffer size of buffer=NULL)
	size_t			GetBuffer(void* buffer, size_t bufferSize) const;
	size_t			GetBuffer(void* buffer, size_t bufferSize, size_t& outTypeID) const;

	MCObjectHandle	GetHandle() const;
	InternalIndex	GetInternalIndex() const;
	bool			GetInternalName(InternalName& outName) const;

	// array support
	size_t						GetElementCount() const;
	void						AddElement(const VWVariant& value);
	VWVariant&					GetElement(size_t at);
	const VWVariant&			GetElement(size_t at) const;
	void						RemoveElement(size_t at);
	void						ClearElements();

	void						Clear();

public:
	static VWVariant			sEmpty;

protected:
	void						Init();
	void						Free(bool complete);
	template<class TYPE> void	InitForSimpleType(const TYPE& value);
	template<class TYPE> void	SetForSimpleType(EVWVariantType type, const TYPE& value);
	template<class TYPE> TYPE	GetIntegerSimpleType(bool signd) const;
	void						EnsureBuffeSize(size_t size, size_t extraChunksCnt=0);

private:
	EVWVariantType		fType;
	size_t				fBytesCnt;
	Uint8*				fBuffer;
	size_t				fBufferSize;
};


// ------------------------------------------------------------------------------------------------
template<class TYPE> void VWVariant::InitForSimpleType(const TYPE& value)
{
	fBytesCnt	= sizeof(TYPE);
	this->EnsureBuffeSize( fBytesCnt );
	memcpy( fBuffer, & value, fBytesCnt );
}

// ------------------------------------------------------------------------------------------------
template<class TYPE> void VWVariant::SetForSimpleType(EVWVariantType type, const TYPE& value)
{
	if ( fType == eVWVariantType_Empty ) {
		fType	= type;
		this->InitForSimpleType( value );
	}
	else if ( fType == type && VERIFYN( kVStanev, sizeof(TYPE) >= fBytesCnt ) ) {
		this->EnsureBuffeSize( fBytesCnt );
		memcpy( fBuffer, & value, fBytesCnt );
	}
	else {
		VWVariant	inValue( value );
		this->SetTXString( inValue.GetTXString() );
	}
}

// ------------------------------------------------------------------------------------------------
template<class TYPE> TYPE VWVariant::GetIntegerSimpleType(bool signd) const
{
	TYPE	result		= 0;
	bool	resultOk	= false;
			
	if ( VERIFYN( kVStanev, sizeof(TYPE) >= fBytesCnt ) )
	{
		if (	(   signd && fType == eVWVariantType_SignedInteger )
			||	( ! signd && fType == eVWVariantType_UnsignedInteger )
			)
		{
			memcpy( & result, fBuffer, fBytesCnt );
			resultOk	= true;
		}
		else if (	(   signd && fType == eVWVariantType_UnsignedInteger )
				||	( ! signd && fType == eVWVariantType_SignedInteger )
				)
		{
			memcpy( & result, fBuffer, sizeof(TYPE) );
			if ( fType == eVWVariantType_SignedInteger && DemoteTo<Sint32>( kVStanev, result ) < 0 ) {
				// we're dealing with integer
				// clean up the right-most flat that carries the sign
				Uint8*	valueBuff	= (Uint8*) & result;
				valueBuff			+= sizeof(TYPE);
				*valueBuff			= (*valueBuff & 0x80) ^ 0x7F;
			}
			resultOk	= true;
		}
	}

	if ( ! resultOk ) {
		TXString	strRes	= this->GetTXString();
		result				= strRes.atoi();
	}

	return result;
}

