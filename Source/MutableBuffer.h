#pragma once
#include <stdbool.h>
#include <stddef.h>
typedef struct {
	char* Data;
	size_t Size;
	size_t Capacity;
} MutableBuffer;

size_t MutableBuffer_FixIndex(MutableBuffer* Buffer, size_t Index);
void MutableBuffer_Init(MutableBuffer* Buffer, size_t InitialCapacity);
bool MutableBuffer_Grow(MutableBuffer* Buffer, size_t Atleast);
bool MutableBuffer_Write(MutableBuffer* Buffer, size_t* Position, const char* SourceBuffer, size_t Size);
char* MutableBuffer_Read(MutableBuffer* Buffer, size_t* From, size_t* To, bool Copy);
