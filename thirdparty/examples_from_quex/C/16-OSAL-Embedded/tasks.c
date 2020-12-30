#include "tiny/tiny.h"
#include "tiny/lib/quex/byte_loader/ByteLoader_OSAL"
#include "tiny/lib/quex/byte_loader/ByteLoader_OSAL.i"

#include "auxiliary.h"

void 
task_lexer(void)
/* TASK: Implementing the lexical analyzer which analyzes a file.
 *       Sends tokens to task 'task_token_receiver'.
 *
 * EXIT: Either if the token queue is full and not emptied after a
 *       couple of retries, or the token TERMINATION is found.                */
{

    const char* file_name = "/myDrive/example.txt"; /* '/myDrive' -> './ram0' */
    /* The path is relative to the executable path of 'lexer'.                */

    OS_TaskRegister();
    OS_printf("[START] 'task_lexer'\n");

    tiny_Token*       token_p = 0x0;
    uint8             buffer[128];
    size_t            size;
    int32             status;
    int               retry_n;
    quex_ByteLoader*  byte_loader = quex_ByteLoader_OSAL_new_from_file_name(file_name);
    tiny              tlex;

    if( ! byte_loader ) {
        OS_printf("[FAIL ] task_lexer: failed to open file './ram0/example.txt'\n");
        OS_printf("[FAIL ] task_lexer: program must be called from inside directory '16-OSALEmbedded'.\n");
        aux_send_token_termination_forced();
        OS_TaskExit();
        return;
    }

    tiny_from_ByteLoader(&tlex, byte_loader, /* Converter */NULL);

    while( tlex.error_code == E_Error_None ) {
        tlex.receive(&tlex, &token_p);

        CALL((OS_MutSemTake(aux_mutex_id)));

        /* Serialize token an send it to 'task_token_receiver'                */
        size = aux_token_serialize(token_p, &buffer[0], 128);
        for(retry_n=0, status=OS_QUEUE_FULL; status == OS_QUEUE_FULL ; ++retry_n) {
            status = OS_QueuePut(aux_msgq_id, (void*)&buffer[0], size, 0);
            OS_TaskDelay(5);
        }

        CALL((OS_MutSemGive(aux_mutex_id))) 

        if( retry_n > 50 ) {
            /* For propper termination 'task_token_receiver' needs to be 
             * triggered to terminate via a TERMINATION token.                */
            aux_send_token_termination_forced();
            break;
        } 
        else if( token_p->id == QUEX_TKN_TERMINATION) {
            break;
        }
    } 
    tiny_destruct(&tlex);
    OS_printf("[EXIT ] task_lexer\n");
    OS_TaskExit();
}

void 
task_token_receiver(void)
/* TASK: Receives a token from 'task_lexer'.
 *       Prints token and lexeme via 'OS_printf()'.
 *
 * EXIT: Receiption of token 'TERMINATION'.                                   */
{

    uint8          buffer[128];
    tiny_Token     token;
    int32          status = 0;
    uint32         size;
    
    OS_TaskRegister();
    OS_printf("[START] 'task_token_receiver'\n");

    token.id   = QUEX_TKN_SPACE;
    token.text = (tiny_lexatom_t*)quex_MemoryManager_allocate(64, E_MemoryObjectType_TEXT);

    while(token.id != QUEX_TKN_TERMINATION)
    {
        CALL((OS_QueueGet(aux_msgq_id, (void*)&buffer[0], 128, &size, OS_PEND))) 

        aux_token_deserialize(buffer, sizeof(buffer), &token, 64);
        OS_printf("[OK   ] received: '%s %s'\n", tiny_map_token_id_to_name(token.id), (const char*)token.text);
        OS_TaskDelay(2);
    }  

    /* Inform 'task_system_monitor' about termination, so it may leave. */
    CALL((OS_QueuePut(aux_msgq_termination_id, (void*)&token.text[0], 1, 0)));

    tiny_Token_destruct(&token);
    OS_printf("[EXIT ] task_token_receiver\n");
    OS_TaskExit();
}

void 
task_system_monitor(void)
{   
    uint8  tmp; 
    uint32 size;

    OS_TaskRegister();
    OS_printf("[START] 'task_system_monitor'\n");

    /* Iterate until a termination signal arrives.                            */
    while( OS_SUCCESS != OS_QueueGet(aux_msgq_termination_id, (void*)&tmp, 1, &size, OS_CHECK) )
    {
        OS_TaskDelay(50);
    }
    aux_memory_statistic();
    OS_printf("[EXIT ] task_system_monitor\n");
    main_shutdown();
}

