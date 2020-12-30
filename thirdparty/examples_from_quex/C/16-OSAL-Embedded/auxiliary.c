#include "auxiliary.h"

size_t aux_token_serialize(const tiny_Token* token_p, uint8* buffer, size_t size)
/* Transform: 'tiny_Token' --> byte stream.              
 * 
 * RETURNS: Number of occupied bytes.                                         */
{
    const uint8* r;
    uint8*       w;
    if( size < 5 ) return 0;
    buffer[0] = (token_p->id      ) & 0xFF;
    buffer[1] = (token_p->id >>  8) & 0xFF;
    buffer[2] = (token_p->id >> 16) & 0xFF;
    buffer[3] = (token_p->id >> 24) & 0xFF;

    for(r=&token_p->text[0], w=&buffer[4]; *r && w - buffer != (ptrdiff_t)size-1 ; ++r, ++w) *w = *r;

    *w = 0; /* Ensure terminating zero */

    return (size_t)(w - buffer + 1);
}

bool aux_token_deserialize(uint8* buffer, size_t size, tiny_Token* token_p, size_t max_lexeme_length)
/* Transform: byte stream --> 'tiny_Token'
 * 
 * RETURNS: true, in case of success; false, else.                            */
{
    const uint8* r;
    ptrdiff_t    copy_size;
    const uint8* message_end = buffer + size;

    if( size < 5 ) return false;
    token_p->id = buffer[0] + (buffer[1] << 8) + (buffer[2] << 16) + (buffer[3] << 24);

    for(r=&buffer[4]; *r && r != message_end ; ++r);
    copy_size  = r - &buffer[4] + 1;
    copy_size  = size < max_lexeme_length ? size : max_lexeme_length;
    quex_memcpy((void*)token_p->text, &buffer[4], copy_size);
    ((tiny_lexatom_t*)token_p->text)[copy_size-1] = 0; /* Ensure terminating zero */
    return true;
}

void aux_memory_statistic()
/* Print a short statistic on memory management.
 *                                                                            */
{
    quex_MallocStatistic  s;

    quex_MallocStatistic_get(&s);
    OS_printf("[     ] memory: { free: %i [byte]; allocated: %i [byte]; watermark: %i [byte]; malloc_call_n: %i; free_call_n: %i; }\n", 
              (int)s.free_byte_n, (int)s.allocated_byte_n, (int)s.allocated_byte_n_watermark, (int)s.calls.malloc_n, (int)s.calls.free_n);
    (void)aux_error_string;
}

void aux_send_token_termination_forced(void)
/* Force a token 'TERMINATION' to be sent. The token message queue is first 
 * completely emptied, then the token is sent. This is used to force the 
 * 'task_token_receiver' to quit as quickly as possible.                      */
{
    uint8          buffer[16];
    uint32         size;
    int32          status = 0;
    tiny_Token     token;

    /* Safety time delay: ensure all task are started.                        */
    OS_TaskDelay(100);

    /* Empty the queue                                                        */
    while( OS_SUCCESS == OS_QueueGet(aux_msgq_id, (void*)&buffer[0], 128, &size, OS_CHECK) );

    token.id = QUEX_TKN_TERMINATION;
    ((tiny_lexatom_t*)(token.text))[0] = (tiny_lexatom_t)0;
    size = aux_token_serialize(&token, &buffer[0], 128);

    OS_printf("[     ] premature 'TERMINATION' to terminate all processes.\n");
    CALL((OS_QueuePut(aux_msgq_id, (void*)&buffer[0], size, 0)));
}

const char* aux_error_string(int ErrorCode)
/* Provide a human-readable string for an OSAL error code.    
 *
 * RETURNS: (const char*) pointer.                                            */
{
    switch( ErrorCode ) {
    case OS_SUCCESS: return "OS_SUCCESS";
    case OS_ERROR: return "OS_ERROR";
    case OS_INVALID_POINTER: return "OS_INVALID_POINTER";
    case OS_ERROR_ADDRESS_MISALIGNED: return "OS_ERROR_ADDRESS_MISALIGNED";
    case OS_ERROR_TIMEOUT: return "OS_ERROR_TIMEOUT";
    case OS_INVALID_INT_NUM: return "OS_INVALID_INT_NUM";
    case OS_SEM_FAILURE: return "OS_SEM_FAILURE";
    case OS_SEM_TIMEOUT: return "OS_SEM_TIMEOUT";
    case OS_QUEUE_EMPTY: return "OS_QUEUE_EMPTY";
    case OS_QUEUE_FULL: return "OS_QUEUE_FULL";
    case OS_QUEUE_TIMEOUT: return "OS_QUEUE_TIMEOUT";
    case OS_QUEUE_INVALID_SIZE: return "OS_QUEUE_INVALID_SIZE";
    case OS_QUEUE_ID_ERROR: return "OS_QUEUE_ID_ERROR";
    case OS_ERR_NAME_TOO_LONG: return "OS_ERR_NAME_TOO_LONG";
    case OS_ERR_NO_FREE_IDS: return "OS_ERR_NO_FREE_IDS";
    case OS_ERR_NAME_TAKEN: return "OS_ERR_NAME_TAKEN";
    case OS_ERR_INVALID_ID: return "OS_ERR_INVALID_ID";
    case OS_ERR_NAME_NOT_FOUND: return "OS_ERR_NAME_NOT_FOUND";
    case OS_ERR_SEM_NOT_FULL: return "OS_ERR_SEM_NOT_FULL";
    case OS_ERR_INVALID_PRIORITY: return "OS_ERR_INVALID_PRIORITY";
    case OS_INVALID_SEM_VALUE: return "OS_INVALID_SEM_VALUE";
    case OS_ERR_FILE: return "OS_ERR_FILE";
    case OS_ERR_NOT_IMPLEMENTED: return "OS_ERR_NOT_IMPLEMENTED";
    case OS_TIMER_ERR_INVALID_ARGS: return "OS_TIMER_ERR_INVALID_ARGS";
    case OS_TIMER_ERR_TIMER_ID: return "OS_TIMER_ERR_TIMER_ID";
    case OS_TIMER_ERR_UNAVAILABLE: return "OS_TIMER_ERR_UNAVAILABLE";
    case OS_TIMER_ERR_INTERNAL: return "OS_TIMER_ERR_INTERNAL";
    default: return "<unknown code>";
    }
}

