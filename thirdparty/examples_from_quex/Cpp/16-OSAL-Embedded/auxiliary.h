#ifndef  QUEX_EXAMPLE_OSAL_AUXILIARY_H
#define  QUEX_EXAMPLE_OSAL_AUXILIARY_H

#include "tiny/tiny"
#include "common_types.h"
#include "osapi.h"

#ifdef __cplusplus
extern "C" {
#endif

void        task_lexer(void);
void        task_token_receiver(void);
void        task_system_monitor(void);

void        main_startup(void);
void        main_shutdown(void);

extern uint32 aux_mutex_id;
extern uint32 aux_msgq_id;
extern uint32 aux_msgq_termination_id;

#ifdef __cplusplus
}
#endif

void        aux_send_token_termination_forced(void);
void        aux_memory_statistic();
size_t      aux_token_serialize(const tiny_Token* token_p, uint8* buffer, size_t size);
bool        aux_token_deserialize(uint8* buffer, size_t size, tiny_Token* token_p, size_t max_lexeme_length);
const char* aux_error_string(int ErrorCode);

#define CALL(F) status = F; \
                if( OS_SUCCESS != status ) \
                { OS_printf("[FAIL ] %s: %s -> %s\n", #F, __FUNCTION__, aux_error_string(status)); }

#endif /*  QUEX_EXAMPLE_OSAL_AUXILIARY_H */
