// ����� �����
#ifndef _STREAM_
#define _STREAM_

struct Stream
{
	long m_size; // ������ ������
	long m_capacity; // ������ �������
	unsigned char* m_buffer; // ������
};

// ��������� �����
void stream_init(struct Stream* self);

// ������� �����
void stream_free(struct Stream* self);

// ���������� ������ ������
long stream_size(struct Stream* self);

// ����������� ������
unsigned stream_reserve(struct Stream* self, long size);

// �������� ������ ������
unsigned stream_resize(struct Stream* self, long size);

// �������� � ����� ������ ������
long stream_append(struct Stream* self, const void* data, long length);

// �������� � ����� ������ ������
long stream_append_str(struct Stream* self, const char* str);

// ���������� ��������� �� ������ ��� ������ str, ����� null
char* stream_get_str(struct Stream* self, long offset, char* str, long maxSize);

// ��������� � ������� �� �������� offset
void* stream_ptr(struct Stream* self, long offset);

// ����
void stream_test();

#endif

