/* 
 * SPLPv1.c
 * The file is part of practical task for System programming course. 
 * This file contains definitions of the data structures and forward
 * declaration of handle_message() function
 */



enum TestStatus 
{ 
    MESSAGE_INVALID, 
    MESSAGE_VALID 
};

// состояния
enum State {
    INIT = 1,
    CONNECTING = 2,
    CONNECTED = 3,
    WAITING_VER = 4,
    WAITING_DATA = 5,
    WAITING_B64_DATA = 6,
    DISCONNECTING = 7
};

// сообщения
enum MessageID {
    CONNECT,
    CONNECT_OK,
    GET_DATA,
    GET_VER,
    GET_FILE,
    GET_COMMAND,
    GET_B64,
    DISCONNECT,
    VERSION,
    CMD,
    B64,
    DISCONNECT_OK,
    UNKNOWN_MSG
};

enum Direction 
{ 
    A_TO_B, 
    B_TO_A 
};


struct Message /* message */
{
	enum Direction	direction;        
	char			*text_message;
};

extern enum TestStatus validate_message( struct Message* pMessage ); 
