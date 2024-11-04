//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// Forward declaration of HandleWrapper.
template <typename T>
class HandleWrapper;


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

template<class NodeType, class ValueType>
class TStateGetSet {
	// Getter methods for fields that are not simple fields return the value as a const reference. 
	// Using a const ref as the return value in this typedef didn't work when we had getters for simple fields that
	// returned a value.
	typedef std::function<const ValueType(const NodeType&)> GetterFunction;
	typedef std::function<void(NodeType&, const ValueType&)> SetterFunction;

public:
	explicit TStateGetSet(NodeType** handle, const GetterFunction& g, const SetterFunction& s) :
		fHandle(handle),
		fWrapper(nullptr),
		fGetter(g),
		fSetter(s)
	{
		if (fHandle != nullptr) {
			fSaveState = g(**handle);
		}
	}

	explicit TStateGetSet(HandleWrapper<NodeType> wt, const GetterFunction& g, const SetterFunction& s) :
		fHandle(nullptr),
		fWrapper(wt),
		fGetter(g),
		fSetter(s)
	{
		if (fWrapper != nullptr) {
			fSaveState = g(**wt);
		}
	}

	explicit TStateGetSet(NodeType** handle, const GetterFunction& g, const SetterFunction& s, const ValueType& newValue) :
		fHandle(handle),
		fWrapper(nullptr),
		fGetter(g),
		fSetter(s)
	{
		if (fHandle != nullptr) {
			fSaveState = g(**handle);
			bool needsFlagChange = ! (*fHandle)->IsTransientChangeObject();
			(*fHandle)->MarkAsTransientChangeObject();
			fSetter(**fHandle, newValue);
			if (needsFlagChange)
				(*fHandle)->MarkAsNonTransientChangeObject();
		}
	}

	explicit TStateGetSet(HandleWrapper<NodeType> wt, const GetterFunction& g, const SetterFunction& s, const ValueType& newValue) :
		fHandle(nullptr),
		fWrapper(wt),
		fGetter(g),
		fSetter(s)
	{
		if (fWrapper != nullptr) {
			fSaveState = g(**wt);
			bool needsFlagChange = !(*wt)->IsTransientChangeObject();
			(*wt)->MarkAsTransientChangeObject();
			fSetter(**wt, newValue);
			if (needsFlagChange)
				(*wt)->MarkAsNonTransientChangeObject();
		}
	}

	virtual ~TStateGetSet() {
		if (fHandle != nullptr) {
			bool needsFlagChange = !(*fHandle)->IsTransientChangeObject();
			(*fHandle)->MarkAsTransientChangeObject();
			fSetter(**fHandle, fSaveState);
			if (needsFlagChange)
				(*fHandle)->MarkAsNonTransientChangeObject();
		}
		else if (fWrapper != nullptr) {
			bool needsFlagChange = !(*fWrapper)->IsTransientChangeObject();
			(*fWrapper)->MarkAsTransientChangeObject();
			fSetter(**fWrapper, fSaveState);
			if (needsFlagChange)
				(*fWrapper)->MarkAsNonTransientChangeObject();
		}
	}

private:
	const GetterFunction fGetter;
	const SetterFunction fSetter;

	ValueType fSaveState;
	NodeType** fHandle;
	HandleWrapper<NodeType> fWrapper;

	DISALLOW_DUPLICATES(TStateGetSet);
};

//////////////////////////////////////////////////////////////////////////////
template <class NodeType, class ValueType> class TConditionalStateGetSet
//////////////////////////////////////////////////////////////////////////////
{
	typedef std::function<const ValueType(const NodeType&)> GetterFunction;
	typedef std::function<void(NodeType&, const ValueType&)> SetterFunction;

private:
	const GetterFunction fGetter;
	const SetterFunction fSetter;

	ValueType		fSaveState;
	bool			fbCondition;
	NodeType**		fHandle;
	HandleWrapper<NodeType> fWrapper;

	DISALLOW_DUPLICATES(TConditionalStateGetSet);

public:
	explicit TConditionalStateGetSet(bool inbCondition, NodeType** handle, const GetterFunction& g, const SetterFunction& s)
		: fHandle(handle), fWrapper(nullptr), fGetter(g), fSetter(s), fbCondition(inbCondition)
	{
		if (fbCondition && (fHandle != nullptr))
			fSaveState = g(**handle);
	}

	explicit TConditionalStateGetSet(bool inbCondition, HandleWrapper<NodeType> wt, const GetterFunction& g, const SetterFunction& s)
		: fHandle(nullptr), fWrapper(wt), fGetter(g), fSetter(s), fbCondition(inbCondition)
	{
		if (fbCondition && (fWrapper != nullptr))
			fSaveState = g(**wt);
	}

	explicit TConditionalStateGetSet(bool inbCondition, NodeType** handle, const GetterFunction& g, const SetterFunction& s, const ValueType& newValue)
		: fHandle(handle), fWrapper(nullptr), fGetter(g), fSetter(s), fbCondition(inbCondition)
	{
		if (fbCondition && (fHandle != nullptr)) {
			fSaveState = g(**handle);
			bool needsFlagChange = !(*fHandle)->IsTransientChangeObject();
			(*fHandle)->MarkAsTransientChangeObject();
			fSetter(**fHandle, newValue);
			if (needsFlagChange) {
				(*fHandle)->MarkAsNonTransientChangeObject();
			}
		}
	}

	explicit TConditionalStateGetSet(bool inbCondition, HandleWrapper<NodeType> wt, const GetterFunction& g, const SetterFunction& s, const ValueType& newValue)
		: fHandle(nullptr), fWrapper(wt), fGetter(g), fSetter(s), fbCondition(inbCondition)
	{
		if (fbCondition && (fWrapper != nullptr)) {
			fSaveState = g(**wt);
			bool needsFlagChange = !(*fWrapper)->IsTransientChangeObject();
			(*fWrapper)->MarkAsTransientChangeObject();
			fSetter(**fWrapper, newValue);
			if (needsFlagChange) {
				(*fWrapper)->MarkAsNonTransientChangeObject();
			}
		}
	}

	virtual ~TConditionalStateGetSet()
	{
		if (fbCondition) {
			if (fHandle != nullptr) {
				bool needsFlagChange = !(*fHandle)->IsTransientChangeObject();
				(*fHandle)->MarkAsTransientChangeObject();
				fSetter(**fHandle, fSaveState);
				if (needsFlagChange) {
					(*fHandle)->MarkAsNonTransientChangeObject();
				}
			}
			else if (fWrapper != nullptr) {
				bool needsFlagChange = !(*fWrapper)->IsTransientChangeObject();
				(*fWrapper)->MarkAsTransientChangeObject();
				fSetter(**fWrapper, fSaveState);
				if (needsFlagChange) {
					(*fWrapper)->MarkAsNonTransientChangeObject();
				}
			}
		}
	}
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
#define VW_CONDITIONAL_TSTATE(condition, variableTypeName, variable)					TState<variableTypeName>* pState##variable = nullptr;\
																						if (condition) {\
																							try {\
																								pState##variable = new TState<variableTypeName>(variable);\
																							} catch(std::bad_alloc) {\
																								pState##variable = nullptr;\
																							}\
																						}\
																						unique_ptr<TState<variableTypeName>> apState##variable(pState##variable)

#define VW_CONDITIONAL_TSTATE_VALUE(condition, variableTypeName, variable, newValue)	TState<variableTypeName>* pState##variable = nullptr;\
																						if (condition) {\
																							try {\
																								pState##variable = new TState<variableTypeName>(variable, newValue);\
																							} catch(std::bad_alloc) {\
																								pState##variable = nullptr;\
																							}\
																						}\
																						unique_ptr<TState<variableTypeName>> apState##variable(pState##variable)


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
