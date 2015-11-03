#include "MutableBuffer.h"
#include <string.h>
#include <stdlib.h>

MutableBuffer* MutableBuffer_New(size_t InitialCapacity) {
	MutableBuffer* NewBuffer = malloc(sizeof(MutableBuffer));
	NewBuffer->Size = 0;
	NewBuffer->Capacity = InitialCapacity;
	NewBuffer->Data = malloc(NewBuffer->Capacity * sizeof(char));
	return NewBuffer;
}

void MutableBuffer_Init(MutableBuffer* Buffer, size_t InitialCapacity) {
	Buffer->Size = 0;
	Buffer->Capacity = InitialCapacity;
	Buffer->Data = malloc(Buffer->Capacity * sizeof(char));
}

size_t MutableBuffer_FixIndex(MutableBuffer* Buffer, size_t Index) {
	if (Index < 0) return 0;
	if (Index > Buffer->Size) return Buffer->Size;
	return Index;
}

bool MutableBuffer_Grow(MutableBuffer* Buffer, size_t Atleast) {
	size_t NewCapacity = Buffer->Capacity + (Atleast * 2);
	char* ReallocatedData = realloc(Buffer->Data,NewCapacity * sizeof(char));
	if (ReallocatedData == 0) {
		return false;
	} else {
		Buffer->Data = ReallocatedData;
		Buffer->Capacity = NewCapacity;
		return true;
	}
}

bool MutableBuffer_Write(MutableBuffer* Buffer, size_t* Position, const char* SourceBuffer, size_t Size) {
	*Position = MutableBuffer_FixIndex(Buffer,*Position);
	
	size_t End = *Position + (Size - 1);
	if (Buffer->Capacity == 0) {
		bool Reallocated = MutableBuffer_Grow(Buffer,Size);
		if (!Reallocated) {
			return false;
		}
	} else {
		size_t CapacityEnd = Buffer->Capacity - 1;
		if (End > CapacityEnd) {
			size_t Remaining = End - CapacityEnd;
			bool Reallocated = MutableBuffer_Grow(Buffer,Remaining);
			if (!Reallocated) {
				return false;
			}
		}
	}
	
	if (Buffer->Size == 0) {
		Buffer->Size = Size;
	} else {
		size_t SizeEnd = Buffer->Size - 1;
		if (End > SizeEnd) {
			size_t SizeIncrease = End - SizeEnd;
			Buffer->Size += SizeIncrease;
		}
	}

	memcpy(Buffer->Data + *Position, SourceBuffer, Size);

	return true;
}

char* MutableBuffer_Read(MutableBuffer* Buffer, size_t* From, size_t* To, bool Copy) {
	*From = MutableBuffer_FixIndex(Buffer,*From);
	*To = MutableBuffer_FixIndex(Buffer,*To);
	if (*From > *To) *From = *To;
	size_t Length = *To - *From;
	if (Copy == true) {
		char* DataCopy = malloc(Length * sizeof(char));
		memcpy(DataCopy,Buffer->Data,Length);
		return DataCopy;
	} else {
		return Buffer->Data + *From;
	}
}
