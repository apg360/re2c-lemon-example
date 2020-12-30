#include "auxiliary.h"

#define STACK_SIZE_IN_4BYTE 1024
#define HEAP_MEMORY_SIZE    1047576

uint32 aux_mutex_id = (uint32)-1;
uint32 aux_msgq_id = (uint32)-1;
uint32 aux_msgq_termination_id = (uint32)-1;

static uint8  heap_memory[HEAP_MEMORY_SIZE];
static uint32 stack_task_lexer[STACK_SIZE_IN_4BYTE];
static uint32 stack_task_token_receiver[STACK_SIZE_IN_4BYTE];
static uint32 stack_task_system_monitor[STACK_SIZE_IN_4BYTE];

typedef struct {
    uint32          id;    /* Id is assigned by 'OS_TaskCreate()' */
    const char*     name;
    osal_task_entry function_p;
    uint32*         stack_p;
    uint32          stack_size; 
    uint32          priority;
} TaskTableEntry;

TaskTableEntry task_table[] = {
    { (uint32)-1, "task_lexer",          task_lexer,          &stack_task_lexer[0],          STACK_SIZE_IN_4BYTE, 101 },
    { (uint32)-1, "task_token_receiver", task_token_receiver, &stack_task_token_receiver[0], STACK_SIZE_IN_4BYTE, 101 },
    { (uint32)-1, "task_system_monitor", task_system_monitor, &stack_task_system_monitor[0], STACK_SIZE_IN_4BYTE, 101 }
};

#define foreach_task(T) for((T)=&task_table[0]; (T)!=&task_table[3]; ++(T))

extern "C" void OS_Application_Startup(void)
{ main_startup(); }

void main_startup(void)
{
    uint32 status = 0;
    TaskTableEntry* task;

    /* Quex's tiny Standard Library implementation cannot be self-initializing
     * due to potential racing conditions. To be independent of scheduler and 
     * mutex implementations, initialization needs to be called explicitly
     * BEFORE ANYTHING ELSE which might call a stdlib function.               */
    quex::stdlib_init(&heap_memory[0], HEAP_MEMORY_SIZE); 
    aux_memory_statistic();

    OS_API_Init();
    OS_printf("[START] OS_Application_Startup()\n");

    /* File system _____________________________________________________________
     *                                                                        */
    char device[] = "/ramdev0";
    char device_name[] = "RAM";
    char virtual_device[] = "/myDrive";
    CALL((OS_mkfs(0, &device[0], &device_name[0], 512, 200)));
    CALL((OS_mount(&device[0], &virtual_device[0])))
    /* bsp_voltab.c: '/ramdev0' --> './ram0'                                  */


    /* Communication infrastructure ____________________________________________
     *                                                                        */
    CALL(OS_QueueCreate(&aux_msgq_id, "token queue", 
                        /* max. number of elements in queue */10, 
                        /* max. sizes of element in queue   */64, 
                        /* flags (ignored)                  */0));
    CALL(OS_QueueCreate(&aux_msgq_termination_id, "termination queue", 
                        /* max. number of elements in queue */1, 
                        /* max. sizes of element in queue   */1, 
                        /* flags (ignored)                  */0));

    CALL(OS_MutSemCreate( &aux_mutex_id, "Mutex", 0))
    OS_printf("[%s] mutex (id=%d)\n", status == OS_SUCCESS ? "OK   " : "FAIL ", (int)aux_mutex_id);

    /* Tasks ___________________________________________________________________
     *                                                                        */
    foreach_task(task) {
        status = OS_TaskCreate(&task->id, task->name, task->function_p, task->stack_p, task->stack_size, task->priority, 0);
        OS_printf("[%s] initiated '%s'\n", status == OS_SUCCESS ? "OK   " : "FAIL ", task->name);
    }

    OS_printf("[DONE ] OS_Application_Startup()\n");
}

void 
main_shutdown(void)
{
    uint32          thisId = (uint32)OS_TaskGetId();
    OS_task_prop_t  dummy;
    bool            done_f = true;
    TaskTableEntry* task;

    /* All tasks received a termination signal. Wait until other tasks exited.*/
    while( 1 + 1 == 2 ) {
        done_f = true;
        foreach_task(task) {
            if( thisId != task->id && OS_TaskGetInfo(task->id, &dummy) == OS_SUCCESS) { 
                done_f = false; break; 
            }
        }
        if( done_f ) break;
        OS_TaskDelay(10);
    }

    OS_QueueDelete(aux_msgq_id);
    OS_QueueDelete(aux_msgq_termination_id);

    OS_MutSemDelete(aux_mutex_id);
    OS_printf("[OK   ] Tasks, message queues, mutex deleted; OS_ApplicationShutdown() initiated.\n");

    OS_TaskExitAndShutdown();
}
