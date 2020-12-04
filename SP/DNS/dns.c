
/*************************************************************************
   LAB 1                                                                

    Edit this file ONLY!

*************************************************************************/

#include "dns.h"
#include "Stream.h"
#include "DnsVector.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

// хранилище - DNS
struct DnsImpl
{
    // буффер хранения строк
    struct Stream m_stm;
    // таблица для хранения hash ключа - смещения на строку - ip
    struct DnsVector m_items;
};

// иницирует объект
void dnsImpl_init(struct DnsImpl* self)
{
    stream_init(&self->m_stm);
    dnsVector_init(&self->m_items);
}

// удаляет объект
void dnsImpl_free(struct DnsImpl* self)
{
    dnsVector_free(&self->m_items);
    stream_free(&self->m_stm);
}

// вычисление hash ключа
unsigned int hashName(const char* str)
{
    int result = 0;

    for (const char* pc=str;*pc !=0; ++pc)
    {
        result = (result * 37) ^ *pc;
    }

    return result;
}

// добавление item в хранилище dnsVector
void dnsImpl_append(struct DnsImpl* self, IPADDRESS ip, const char* hostName)
{
    struct DnsItem item;
    item.m_hash = hashName(hostName);
    item.m_offset = stream_append_str(&self->m_stm, hostName);
    item.m_ip = ip;
    dnsVector_insert(&self->m_items, &item);
}

// запрос на  получение ip по hostName
IPADDRESS dnsImpl_lookUp(struct DnsImpl* self, const char* hostName)
{
    HASH hash = hashName(hostName);
    int indx = dnsVector_find(&self->m_items, hash, NULL);
    if (indx < 0)
        return 0;

    for (; indx < self->m_items.m_size; ++indx)
    {
        struct DnsItem* item = dnsVector_at(&self->m_items, indx);
        if (item->m_hash != hash)
            return 0;

        char str[256];
        if (!stream_get_str(&self->m_stm, item->m_offset, str, 255))
            continue;

        if (strcmp(str, hostName) == 0)
            return item->m_ip;
    }

    return 0;
}

DNSHandle InitDNS()
{
    struct DnsImpl* pImpl = (struct DnsImpl*)malloc(sizeof(struct DnsImpl));
    dnsImpl_init(pImpl);
    return (DNSHandle)pImpl;
}

void ShutdownDNS(DNSHandle hDNS)
{
    struct DnsImpl* pImpl = (struct DnsImpl*)hDNS;
    dnsImpl_free(pImpl);
    free(pImpl);
}

void LoadHostsFile(DNSHandle hDNS, const char* hostsFilePath)
{
    struct DnsImpl* pImpl = (struct DnsImpl*)hDNS;

    FILE* fInput = fopen(hostsFilePath, "r");
    if (NULL == fInput)
        return;

    while (!feof(fInput))
    {
        char buffer[201] = { 0 };
        fgets(buffer, 200, fInput);

        unsigned int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;
        if (5 != fscanf_s(fInput, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, buffer, 200))
            continue;

        IPADDRESS ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | (ip4);

        
        dnsImpl_append(pImpl, ip, buffer);
    }

    fclose(fInput);
}

IPADDRESS DnsLookUp(DNSHandle hDNS, const char* hostName)
{
    struct DnsImpl* pImpl = (struct DnsImpl*)hDNS;
    return dnsImpl_lookUp(pImpl, hostName);
}
