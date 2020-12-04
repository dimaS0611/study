// Класс поток
#ifndef _STREAM_
#define _STREAM_

struct Stream
{
	long m_size; // размер данных
	long m_capacity; // размер буффера
	unsigned char* m_buffer; // буффер
};

// иницирует поток
void stream_init(struct Stream* self);

// удаляет поток
void stream_free(struct Stream* self);

// возвращает размер потока
long stream_size(struct Stream* self);

// резервирует память
unsigned stream_reserve(struct Stream* self, long size);

// изменяет размер память
unsigned stream_resize(struct Stream* self, long size);

// добавить в конец потока данные
long stream_append(struct Stream* self, const void* data, long length);

// добавить в конец потока строку
long stream_append_str(struct Stream* self, const char* str);

// возвращает указатель на строку при успехе str, иначе null
char* stream_get_str(struct Stream* self, long offset, char* str, long maxSize);

// указатель в буффере по смещению offset
void* stream_ptr(struct Stream* self, long offset);

// тест
void stream_test();

#endif

