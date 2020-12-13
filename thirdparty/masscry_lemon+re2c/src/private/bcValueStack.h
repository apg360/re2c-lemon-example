#pragma once
#ifndef DECI_SPACE_BADCODE_VALUE_STACK_HEADER
#define DECI_SPACE_BADCODE_VALUE_STACK_HEADER

/**
 * Simple stack for BC_VALUE.
 */
typedef struct bcValueStack_t
{
  size_t total;     /**< Maximum stack size */
  BC_VALUE* bottom; /**< First element in stack */
  BC_VALUE* top;    /**< Stack top */
} bcValueStack_t;

/**
 * Initialize stack with of given size.
 * 
 * @param[in] pStack pointer to stack structure to initialize
 * @param[in] total total size of stack
 * 
 * @return
 *    BC_INVALID_ARG - (pStack == NULL) or (total == NULL)
 *    BC_NO_MEMORY - if memory allocation failed
 *    BC_OK - stack allocated.
 */
bcStatus_t bcValueStackInit(bcValueStack_t* pStack, size_t total);

/**
 * Cleanup given stack.
 * 
 * @param[in] pStack pointer to stack to cleanup.
 * 
 * @return 
 *    BC_INVALID_ARG - if (pStack == NULL)
 *    BC_OK - stack memory cleaned.
 */
bcStatus_t bcValueStackCleanup(bcValueStack_t* pStack);

/**
 * Push value on stack.
 * 
 * If function completed successfully, memory of pushed value is now owned by stack.
 * 
 * @param[in] pStack pointer to valid stack
 * @param[in] value value to push on stack
 * 
 * @return
 *    BC_INVALID_ARG - if (pStack == NULL) || (value == NULL)
 *    BC_OVERFLOW - if total stack size exceeded.
 *    BC_OK - new value added to stack
 */
bcStatus_t bcValueStackPush(bcValueStack_t* pStack, const BC_VALUE value);

/**
 * Pop value from stack.
 * 
 * @param[in] pStack pointer to valid stack
 * 
 * @return BC_OK if no erros, error code otherwise
 */
bcStatus_t bcValueStackPop(bcValueStack_t* pStack);


#endif /* DECI_SPACE_BADCODE_VALUE_STACK_HEADER */
