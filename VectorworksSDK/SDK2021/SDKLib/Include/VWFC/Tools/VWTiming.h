//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once


namespace VWFC
{
	namespace Tools
	{
		// ------------------------------------------------------------------------
		// We want __FUNCTION__ to return the decorated function name
		//	so we have to use __PRETTY_FUCNTION__ so the gcc can work ok
		#ifdef _WINDOWS
		# define	__PRETTY_FUNCTION__		__FUNCTION__
		#endif

		// ------------------------------------------------------------------------
		class ITimingSettingsProvider
		{
		public:
			virtual			~ITimingSettingsProvider()	{}
			virtual	bool	IsTiming() = 0;
			virtual	bool	IsTimingShow() = 0;
			virtual void	OnTimingFinished(const TXStringArray& arrLines) = 0;
		};

		// ------------------------------------------------------------------------
		class CTiming;

		// ------------------------------------------------------------------------
		class CTimingEnvironment
		{
		public:
						CTimingEnvironment(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext);
			virtual		~CTimingEnvironment();

		private:
			ITimingSettingsProvider*	fSettingsProvider;
			CTiming*					fTiming;
		};

		// ------------------------------------------------------------------------
		class CTiming
		{
		public:
						CTiming(ITimingSettingsProvider* provider, const char* szFunction);
						CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext);
						CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1);
						CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1, size_t data2, const char* str2);
						CTiming(ITimingSettingsProvider* provider, const char* szFunction, const char* szContext, size_t data1, const char* str1, size_t data2, const char* str2, size_t data3, const char* str3);
			virtual		~CTiming();

			void		AddData(size_t data, const char* str);

		private:
			TXString	Analyse(const char* szFunction);

		private:
			ITimingSettingsProvider*	fSettingsProvider;
			TXString					fTaskInfo;

			size_t						fDataCnt;
			size_t						fData[3];
			TXString					fDataStr[3];
		};

		class CTimingResultsDialog;
		// ---------------------------------------------------------------------------
		class VWTiming
		{
			friend class CTimingResultsDialog;
		protected:
			VWTiming();
			~VWTiming();

		public:
			static VWTiming*	GetInstance();

		public:
			static void			Initialize();
			static void			Deinitilalize();
			void				Start(const TXString& category, const TXString& context, const TXString& callstack);
			void				End(const TXString& taskInfo);
			void				End(const TXString& taskInfo, size_t data1, const TXString& str1);
			void				End(const TXString& taskInfo, size_t data1, const TXString& str1, size_t data2, const TXString& str2);
			void				End(const TXString& taskInfo, size_t data1, const TXString& str1, size_t data2, const TXString& str2, size_t data3, const TXString& str3);
			void				ShowTimingResultDialog(const TXString& description);
			void				GetTimingResult(const TXString& description, TXStringArray& outArrLines);

		protected:
			// -----------------------------
			struct STimerStart {
				Uint32			startTime;
				TXString		category;
				TXString		context;
				TXString		callstack;
				STimerStart();
				~STimerStart();
			};
			typedef std::vector<STimerStart>		TTimersQueue;

			// -----------------------------
			struct SData {
				size_t			data;
				TXString		desc;
				SData();
				SData(size_t dt, const TXString& txt);
				~SData();
			};
			typedef std::vector<SData>				TDataArray;

			// -----------------------------
			struct STimerCollected {
				bool			isValid;
				Uint32			timeEllapsed;
				Uint32			count;
				TXString		context;
				TXString		taskInfo;
				TXString		callstack;
				TDataArray		arrData;
				STimerCollected();
				~STimerCollected();
			};
			typedef std::vector<STimerCollected>	TTimerCollectedArray;

			// -----------------------------
			struct STimerCategory {
				TXString				category;
				TTimerCollectedArray	arrTimerData;
				STimerCategory();
				~STimerCategory();
			};
			typedef std::vector<STimerCategory>		TTimerCategoriesArray;

		protected:
			Uint32				GetTimer();
			void				End(const TXString& taskInfo, STimerCollected& collected);
			void				Compact();

		private:
			static VWTiming*		spInstance;
			TTimersQueue			fTimerStartQueue;
			TTimerCategoriesArray	fTimerCategories;
		};
	}
}
