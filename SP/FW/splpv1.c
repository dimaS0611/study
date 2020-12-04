/* 
 * SPLPv1.c
 * The file is part of practical task for System programming course. 
 * This file contains validation of SPLPv1 protocol. 
 */


/*
---------------------------------------------------------------------------------------------------------------------------
# |      STATE      |         DESCRIPTION       |           ALLOWED MESSAGES            | NEW STATE | EXAMPLE
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
1 | INIT            | initial state             | A->B     CONNECT                      |     2     |
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
2 | CONNECTING      | client is waiting for con-| A<-B     CONNECT_OK                   |     3     |
  |                 | nection approval from srv |                                       |           |                      
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
3 | CONNECTED       | Connection is established | A->B     GET_VER                      |     4     |                     
  |                 |                           |        -------------------------------+-----------+----------------------
  |                 |                           |          One of the following:        |     5     |                      
  |                 |                           |          - GET_DATA                   |           |                      
  |                 |                           |          - GET_FILE                   |           |                      
  |                 |                           |          - GET_COMMAND                |           |
  |                 |                           |        -------------------------------+-----------+----------------------
  |                 |                           |          GET_B64                      |     6     |                      
  |                 |                           |        ------------------------------------------------------------------
  |                 |                           |          DISCONNECT                   |     7     |                                 
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
4 | WAITING_VER     | Client is waiting for     | A<-B     VERSION ver                  |     3     | VERSION 2                     
  |                 | server to provide version |          Where ver is an integer (>0) |           |                      
  |                 | information               |          value. Only a single space   |           |                      
  |                 |                           |          is allowed in the message    |           |                      
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
5 | WAITING_DATA    | Client is waiting for a   | A<-B     CMD data CMD                 |     3     | GET_DATA a GET_DATA 
  |                 | response from server      |                                       |           |                      
  |                 |                           |          CMD - command sent by the    |           |                      
  |                 |                           |           client in previous message  |           |                      
  |                 |                           |          data - string which contains |           |                      
  |                 |                           |           the following allowed cha-  |           |                      
  |                 |                           |           racters: small latin letter,|           |                     
  |                 |                           |           digits and '.'              |           |                      
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
6 | WAITING_B64_DATA| Client is waiting for a   | A<-B     B64: data                    |     3     | B64: SGVsbG8=                    
  |                 | response from server.     |          where data is a base64 string|           |                      
  |                 |                           |          only 1 space is allowed      |           |                      
--+-----------------+---------------------------+---------------------------------------+-----------+----------------------
7 | DISCONNECTING   | Client is waiting for     | A<-B     DISCONNECT_OK                |     1     |                      
  |                 | server to close the       |                                       |           |                      
  |                 | connection                |                                       |           |                      
---------------------------------------------------------------------------------------------------------------------------

IN CASE OF INVALID MESSAGE THE STATE SHOULD BE RESET TO 1 (INIT)

*/


#include "splpv1.h"
#include "string.h"

enum State stateClient = INIT;
const char base64[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };

// A->B
enum TestStatus process_message_query(enum MessageID msg)
{
    enum State* state = &stateClient;

    switch (msg)
    {
    case CONNECT:
        if (*state == INIT) {
            *state = CONNECTING;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case GET_VER:
        if (*state == CONNECTED) {
            *state = WAITING_VER;
            return  MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case GET_DATA:
    case GET_FILE:
    case GET_COMMAND:
        if (*state == CONNECTED) {
            *state = WAITING_DATA;
            return  MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case GET_B64:
        if (*state == CONNECTED)
        {
            *state = WAITING_B64_DATA;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;
    
    case DISCONNECT:
        if (*state == CONNECTED)
        {
            *state = DISCONNECTING;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;
    }

    return MESSAGE_INVALID;
}

// B->A
enum TestStatus process_message_ack(enum Messages msg)
{
    enum State* state = &stateClient;

    switch (msg)
    {
    case CONNECT_OK:
        if (*state == CONNECTING) {
            *state = CONNECTED;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case VERSION:
        if (*state == WAITING_VER)
        {
            *state = CONNECTED;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case GET_DATA:
    case GET_FILE:
    case GET_COMMAND:
        if (*state == WAITING_DATA) {
            *state = CONNECTED;
            return  MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case B64:
        if (*state == WAITING_B64_DATA)
        {
            *state = CONNECTED;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;

    case DISCONNECT_OK:
        if (*state == DISCONNECTING)
        {
            *state = INIT;
            return MESSAGE_VALID;
        }
        else
            *state = INIT;
        break;
    }

    return MESSAGE_INVALID;
}

// проверка B64
unsigned verifyB64(const char* str)
{
    unsigned result = 0;

    const char* p = str;
    for (; base64[*p + 128]; ++p);

    char check = 0;
    for (; (check < 2) && (p[check] == '='); ++check);

    if ((p - str + check) % 4 == 0 && !p[check]) 
        return 1;

    return 0;
}

unsigned verifyData(const char* str)
{
    for (const char* p = str; *p != 0; ++p)
    {
        char ch = *p;
        if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch == '.')
            continue;

        if (ch == ' ')
            return 1;

        return 0;
    }

    return 0;
}

// проверка строки 
unsigned verifyFile(const char* str)
{
    unsigned result = 0;

    for (const char* p = str; *p != 0; ++p)
    {
        char ch = *p;
        if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch == '.')
            result = 1;
        else if (ch == ' ')
            return result;
        else
            return 0;
    }

    return 0;
}

// convert to int
unsigned toUInt(const char* ver, unsigned* pOk)
{
    unsigned ok = 0;
    unsigned result = 0;

    for (const char* p = ver; *p != 0; ++p)
    {
        char ch = *p;
        if (ch > '0' && ch <= '9') {
            result = result * 10 + ch - '0';
            ok = 1;
        }
        else {
            ok = 0;
            break;
        }
    }

    if (pOk)
        *pOk = ok;

    return result;
}

// проверяем что команда в начале совпадает с концом
unsigned verifySuffix(const char* msg, const char* end)
{
    const char* p = msg + strlen(msg) - strlen(end);
    return strcmp(p, end);
}

// переводит строковую команду в перечислимый тип
enum MessageID decode_message(const char* msg)
{
    if (strcmp(msg, "CONNECT") == 0)
        return CONNECT;

    if (strcmp(msg, "CONNECT_OK") == 0)
        return CONNECT_OK;

    if (strcmp(msg, "GET_VER") == 0)
         return GET_VER;

    if (strcmp(msg, "GET_DATA") == 0)
        return GET_DATA;

    if (strncmp(msg, "GET_DATA ", 9) == 0)
    {
        unsigned res = verifyData(&msg[9]);
        int resCmp = verifySuffix(msg, "GET_DATA");
        if (res == 1 && resCmp == 0)    
            return GET_DATA;
        else
            return UNKNOWN_MSG;
    }
    if (strcmp(msg, "GET_FILE") == 0)
        return GET_FILE;
   
    if (strncmp(msg, "GET_FILE ", 9) == 0)
    {
        unsigned res = verifyFile(&msg[9]);
        int resCmp = verifySuffix(msg, "GET_FILE");
        if (res == 1 && resCmp == 0)
            return GET_FILE;
        else
            return UNKNOWN_MSG;
    }
    if (strcmp(msg, "GET_COMMAND") == 0)
        return GET_COMMAND;
     
    if (strncmp(msg, "GET_COMMAND ", 12) == 0)
    {
        unsigned res = verifyData(&msg[12]);
        int resCmp = verifySuffix(msg, "GET_COMMAND");
        if (res == 1 && resCmp == 0)
            return GET_COMMAND;
        else
            return UNKNOWN_MSG;
    }
    if (strcmp(msg, "GET_B64") == 0)
        return GET_B64;

    if (strcmp(msg, "DISCONNECT") == 0)
        return DISCONNECT;

    if (strncmp(msg, "VERSION ", 8) == 0)
    {
        unsigned ok = 0;
        unsigned ver = toUInt(&msg[8], &ok);
        if (ver > 0 && ok)
            return VERSION;
        else
            return UNKNOWN_MSG;
    }
    if (strncmp(msg, "B64: ", 5) == 0)
    {
        unsigned res = verifyB64(&msg[5]);
        if (res == 1)
            return B64;
        else
            return UNKNOWN_MSG;
    }
    if (strcmp(msg, "DISCONNECT_OK") == 0)
        return DISCONNECT_OK;

    return UNKNOWN_MSG;
}

/* FUNCTION:  validate_message
 * 
 * PURPOSE:  
 *    This function is called for each SPLPv1 message between client 
 *    and server
 * 
 * PARAMETERS:
 *    msg - pointer to a structure which stores information about 
 *    message
 * 
 * RETURN VALUE:
 *    MESSAGE_VALID if the message is correct 
 *    MESSAGE_INVALID if the message is incorrect or out of protocol 
 *    state
 */
enum TestStatus validate_message( struct Message *msg )
{
    enum MessageID message = decode_message(msg->text_message);
    enum Direction direction = msg->direction;
    enum TestStatus testStatus;
    if (message == UNKNOWN_MSG) {
        if (stateClient == DISCONNECTING)
            stateClient = INIT;
        return MESSAGE_INVALID;
    }

    if (direction == A_TO_B) {
        testStatus = process_message_query(message);
    }
    else if (direction == B_TO_A)
    {
        testStatus = process_message_ack(message);
    }

    if (testStatus == MESSAGE_INVALID)
        stateClient = INIT;

    return testStatus;     
}




