#pragma once
#include "Stream.h"

typedef unsigned int HASH;

// объект хранилища
struct DnsItem
{
	HASH m_hash;
	unsigned int m_offset;
	unsigned int m_ip;
};

// конструктор
struct DnsItem dnsItem(unsigned int hash, unsigned int offset, unsigned int ip);

struct DnsVector
{
	struct Stream m_buffer;
	int m_size;
};

// иницилизирует хранилище объектов
void dnsVector_init(struct DnsVector* self);

// удаляет хранилище
void dnsVector_free(struct DnsVector* self);

// возвращает размер хранилища (кол-во объектов)
long dnsVector_size(struct DnsVector* self);

// возвращает на объект по индексу
struct DnsItem* dnsVector_at(struct DnsVector* self, int indx);

// добавление объекта
int dnsVector_insert(struct DnsVector* self, struct DnsItem* item);

// поиск объекта 
int dnsVector_find(struct DnsVector* self, HASH hash, int* upperIndx);

// тестовая печать
void dnsVector_trace(struct DnsVector* self);
