#pragma once
#include "Stream.h"

typedef unsigned int HASH;

// ������ ���������
struct DnsItem
{
	HASH m_hash;
	unsigned int m_offset;
	unsigned int m_ip;
};

// �����������
struct DnsItem dnsItem(unsigned int hash, unsigned int offset, unsigned int ip);

struct DnsVector
{
	struct Stream m_buffer;
	int m_size;
};

// ������������� ��������� ��������
void dnsVector_init(struct DnsVector* self);

// ������� ���������
void dnsVector_free(struct DnsVector* self);

// ���������� ������ ��������� (���-�� ��������)
long dnsVector_size(struct DnsVector* self);

// ���������� �� ������ �� �������
struct DnsItem* dnsVector_at(struct DnsVector* self, int indx);

// ���������� �������
int dnsVector_insert(struct DnsVector* self, struct DnsItem* item);

// ����� ������� 
int dnsVector_find(struct DnsVector* self, HASH hash, int* upperIndx);

// �������� ������
void dnsVector_trace(struct DnsVector* self);
