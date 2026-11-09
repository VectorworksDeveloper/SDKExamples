#pragma once
#include <vector>

namespace handle {
struct Handle {
	std::size_t index = 0;
	std::size_t generation = 0;
	bool operator ==(const Handle& h) const { return std::tie(index, generation) == std::tie(h.index, h.generation); }
	bool operator !=(const Handle& h) const { return !(*this == h); }
	bool operator <(const Handle& h) const { return std::tie(index, generation) < std::tie(h.index, h.generation); }
};

template<typename T>
class HandleTable {
private:
	using valueType = T;
	struct Slot {
		T data;
		size_t generation = 1;
		size_t freeSlotIndex = size_t(-1); // -1 means alive; table wide leak detection
	};
	std::vector<Slot> slots;
	std::vector<size_t> freeSlots;	
	T dataOnResize; // protect creating new handle when reallocating vector
	size_t size = 0; // number of valid entries

public:
	~HandleTable() {
#if HandleTable_CHECK_FOR_LEAKS
		assert(size == 0);
		assert(freeSlots.empty());
		for( size_t i = 0; i < slots.size(); i++ )
			assert(slots[i].freeSlotIndex != size_t(-1));
		ForEachHandle([](Handle h) {
			assert(false);
		});
#endif
	}

	T& operator[](Handle h) {
		static T invalid;
		return IsValid(h) ? slots[h.index].data : invalid;
	}

	void Clear() {
		*this = HandleTable<T>();
	}

	template<typename CB>
	void ForEachHandle(CB cb) {
		for( size_t i = 0; i != size; ++i ) {
			Slot& s = slots[i];
			if( !cb(Handle({.index = i, .generation=s.generation})) )
				break;
		}
	}

	size_t Size() {
		return size;
	}

	Handle NewHandle(const T& data = T()) {
		Handle h;
		const T* newData = &data;
		
		if( freeSlots.empty() ) {
			h.index = slots.size();
			
			if( slots.size() == slots.capacity() ) {
				// if 'data' lives in this handle table, prevent bad things from happen on realloc
				dataOnResize = data;
				newData = &dataOnResize;
				slots.reserve((slots.size() + 1) * 2);
			}
			
			slots.resize(slots.size() + 1);
		}
		else {
			h.index = freeSlots.back();
			
			freeSlots.pop_back();
			// trim freeSlots
			if( freeSlots.size() > MinReservation() && freeSlots.size() <= freeSlots.capacity() / 2 )
				slots.shrink_to_fit();
		}
		
		size++;

		size_t gen = slots[h.index].generation;
		slots[h.index] = Slot{*newData, gen};
		
		h.generation = gen;
		return h;
	}

	bool IsValid(Handle h) {
		return h.index < slots.size() && slots[h.index].generation == h.generation;
	}

	void DeleteHandle(Handle h) {
		if( !IsValid(h) ) return;

		Slot& slot = slots[h.index];
		slot.generation++;		
		slot.freeSlotIndex = freeSlots.size();
		freeSlots.push_back(h.index);
		
		size--;

		size_t prevSize = slots.size();
		// trim slots
		for( size_t i = slots.size() - 1; i != size_t(-1) && slots[i].freeSlotIndex != size_t(-1); i-- ) {
			slots[freeSlots.back()].freeSlotIndex = slots[i].freeSlotIndex;
			freeSlots[slots[i].freeSlotIndex] = freeSlots.back();
			freeSlots.pop_back();
			slots.pop_back();
		}
		
		if( slots.size() > MinReservation() && slots.size()*2 < slots.capacity() )
			slots.shrink_to_fit();
		
		if( freeSlots.size() > MinReservation() && freeSlots.size() * 2 < freeSlots.capacity() )
			freeSlots.shrink_to_fit();
		
	}

	constexpr size_t MinReservation() { return 10; }
};
}
