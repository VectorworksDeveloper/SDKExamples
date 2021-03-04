//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// Generic State Saver
// -------------------

template <class T> class TState {
private:
	T		fSaveState;
	T&		fStateVariable;
	
	DISALLOW_DUPLICATES(TState);
	
public:
	TState(T& stateVariable) : fStateVariable(stateVariable)
	{ fSaveState = fStateVariable; }
	TState(T& stateVariable, const T& newValue) : fStateVariable(stateVariable)
	{ fSaveState = fStateVariable; fStateVariable = newValue; }
	~TState()
	{ fStateVariable = fSaveState; }
};


//////////////////////////////////////////////////////////////////////////////
template <class T> class TConditionalState
//////////////////////////////////////////////////////////////////////////////
{
private:
	T		fSaveState;
	T&		fStateVariable;
	bool	fbCondition;

	DISALLOW_DUPLICATES(TConditionalState);
	
public:
	TConditionalState(bool inbCondition, T& stateVariable)
		: fStateVariable(stateVariable), fbCondition(inbCondition)
	{
		if (fbCondition)
			fSaveState = fStateVariable;
	}

	TConditionalState(bool inbCondition, T& stateVariable, const T& newValue)
		: fStateVariable(stateVariable), fbCondition(inbCondition)
	{
		if (fbCondition) {
			fSaveState = fStateVariable;
			fStateVariable = newValue;
		}
	}

	~TConditionalState()
	{
		if (fbCondition) {
			fStateVariable = fSaveState;
		}
	}
};

// this macro avoids evaluation of the other parameters when the condition is false
#define VW_CONDITIONAL_TSTATE(condition, variableTypeName, variable)					TState<variableTypeName>* pState##variable = NULL;\
																						if (condition) {\
																							try {\
																								pState##variable = new TState<variableTypeName>(variable);\
																							} catch(std::bad_alloc) {\
																								pState##variable = NULL;\
																							}\
																						}\
																						auto_ptr<TState<variableTypeName>> apState##variable(pState##variable)

#define VW_CONDITIONAL_TSTATE_VALUE(condition, variableTypeName, variable, newValue)	TState<variableTypeName>* pState##variable = NULL;\
																						if (condition) {\
																							try {\
																								pState##variable = new TState<variableTypeName>(variable, newValue);\
																							} catch(std::bad_alloc) {\
																								pState##variable = NULL;\
																							}\
																						}\
																						auto_ptr<TState<variableTypeName>> apState##variable(pState##variable)


//////////////////////////////////////////////////////////////////////////////
template <class T> class TAutoClean_ContainerOfPtr
//////////////////////////////////////////////////////////////////////////////
{
public:
	TAutoClean_ContainerOfPtr(T& inContainerToClean)
		: fContainerToClean(inContainerToClean)
	{ }

	~TAutoClean_ContainerOfPtr()
	{
		for (auto riter = fContainerToClean.rbegin(); riter != fContainerToClean.rend(); ++riter) 
		{
			if (*riter)
				delete *riter;
        }
	}

private:
	T&	fContainerToClean;
	
	DISALLOW_DUPLICATES(TAutoClean_ContainerOfPtr);
};
