#include "Stream.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void stream_init(struct Stream* self)
{
	self->m_size = 0;
	self->m_capacity = 0;
	self->m_buffer = 0;

	long v = 0;
	stream_append(self, &v, 4);
}

long stream_size(struct Stream* self)
{
	return self->m_size;
}

unsigned stream_reserve(struct Stream* self, long size)
{
	if (self->m_capacity >= size)
		return 1;

	long newSize = (size / 4096 + 1) * 4096;
	unsigned char* newBuf = (unsigned char*)malloc(newSize);

	if (!newBuf)
		return 0;

	if (self->m_size)
		memcpy(newBuf, self->m_buffer, self->m_size);

	if (self->m_buffer)
		free(self->m_buffer);

	self->m_buffer = newBuf;
	self->m_capacity = newSize;

	return 1;		
}

unsigned stream_resize(struct Stream* self, long size)
{
	if (!stream_reserve(self, size))
		return 0;

	self->m_size = size;
	return 1;
}

long stream_append(struct Stream* self, const void* data, long length)
{
	long offset = self->m_size;

	if (!stream_reserve(self, offset + length))
		return 0;
	
	memcpy(&self->m_buffer[offset], data, length);
	self->m_size += length;

	return offset;
}

long stream_append_str(struct Stream* self, const char* str)
{
	long length = strlen(str);
	if (length == 0)
		return 0;

	long offset = self->m_size;

	if (!stream_reserve(self, offset + 4 + length))
		return 0;

	// копируект 4 байта из length в  buffer
	memcpy(&self->m_buffer[offset], &length, 4);
	memcpy(&self->m_buffer[offset + 4], str, length);
	self->m_size += length + 4;

	return offset;
}

char* stream_get_str(struct Stream* self, long offset, char* str, long maxSize)
{
	long length = *(long*)&self->m_buffer[offset];
	offset += 4;

	// копирование в str, размер буффера в символах, строка, размер строки
	strncpy_s(str, maxSize, (const char*)&self->m_buffer[offset], length);
	str[length] = 0;
	return str;
}

void* stream_ptr(struct Stream* self, long offset)
{
	return &self->m_buffer[offset];
}

void stream_free(struct Stream* self)
{
	if (self->m_buffer != 0)
	{
		free(self->m_buffer);
		self->m_buffer = 0;
	}
}

void stream_test()
{
	struct Stream stm;
	stream_init(&stm);

	{
		long offset[10];
		for (int i = 0; i < 10; ++i)
		{
			offset[i] = stream_append(&stm, &i, 4);
		}

		for (int i = 0; i < 10; ++i)
		{
			int* pi = (int*)stream_ptr(&stm, offset[i]);
			printf("[%d] = %d\n", offset[i], *pi);
		}
	}

	{
		long offset[6];
		offset[0] = stream_append_str(&stm, "hi");
		offset[1] = stream_append_str(&stm, "hello");
		offset[2] = stream_append_str(&stm, "how");
		offset[3] = stream_append_str(&stm, "are");
		offset[4] = stream_append_str(&stm, "you");
		offset[5] = stream_append_str(&stm, "?!");

		for (int i = 0; i < 6; ++i)
		{
			char str[256];
			char* ps = stream_get_str(&stm, offset[i], str, 255);	
			printf("%s\n", str);
		}
	}
	

	stream_free(&stm);
}



