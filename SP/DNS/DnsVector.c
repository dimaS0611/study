#include "DnsVector.h"
#include "Stream.h"
#include <stdio.h>

struct DnsItem dnsItem(unsigned int hash, unsigned int offset, unsigned int ip)
{
	struct DnsItem result;
	result.m_hash = hash;
	result.m_offset = offset;
	result.m_ip = ip;
	return result;
}

void dnsVector_init(struct DnsVector* self)
{
	stream_init(&self->m_buffer);
	self->m_size = 0;
}

void dnsVector_free(struct DnsVector* self)
{
	stream_free(&self->m_buffer);
}

long dnsVector_size(struct DnsVector* self)
{
	return self->m_size;
}

struct DnsItem* dnsVector_at(struct DnsVector* self, int indx)
{
	return (struct DnsItem*)stream_ptr(&self->m_buffer, indx * sizeof(struct DnsItem));
}

int dnsVector_insert(struct DnsVector* self, struct DnsItem* item)
{
	struct Stream* buf = &self->m_buffer;
	int size = self->m_size;

	if (!stream_resize(buf, (size + 1) * sizeof(struct DnsItem)))
		return -1;

	int upperIndx = 0;
	int indx = dnsVector_find(self, item->m_hash, &upperIndx);
	indx = (indx >= 0) ? indx + 1 : upperIndx;

	if (indx < size) {
		for (int i = size; i > indx; --i) {
			struct DnsItem* item1 = dnsVector_at(self, i - 1);
			struct DnsItem* item2 = dnsVector_at(self, i);
			*item2 = *item1;
		}
	}

	*dnsVector_at(self, indx) = *item;
	self->m_size++;

	return indx;
}

int dnsVector_find(struct DnsVector* self, HASH hash, int* upperIndx)
{
	int i1 = 0;
	int i2 = self->m_size - 1;

	while (i1 <= i2)
	{
		int ii = (i1 + i2) / 2;
		HASH itHash = dnsVector_at(self, ii)->m_hash;
		if (hash < itHash)
			i2 = ii - 1;
		else if (hash > itHash)
			i1 = ii + 1;
		else {
			for (; ii > 0; --ii) {
				if (hash != dnsVector_at(self, ii - 1)->m_hash)
					break;
			}

			return ii;
		}
	}

	if (upperIndx)
		*upperIndx = i1;

	return -1;
}

void dnsVector_trace(struct DnsVector* self)
{
	printf("================\n");
	for (int i = 0; i < self->m_size; ++i) {
		struct DnsItem* item = dnsVector_at(self, i);
		printf("%u %d %u\n", item->m_hash, item->m_offset, item->m_ip);
	}
	printf("================\n");
}

