/**
 * @file bcPrivate.h
 * 
 * Private definitions for Bad Code Programming Language.
 * 
 */
#pragma once
#ifndef DECI_SPACE_BADCODE_PRIVATE_HEADER
#define DECI_SPACE_BADCODE_PRIVATE_HEADER

#include <badcode.h>
#include "bcValue.h"
#include "bcValueStack.h"
#include "bcParseTree.h"

/**
 * Maximum stack size. Interpreter exits with BC_OVERFLOW if stack exceed this 
 * size.
 */
#define BC_CORE_VALUE_STACK_SIZE (4096)

/**
 * Initial code stream opcode capacity. It increases using CAP1 = CAP*3/2
 * formula when actual size exceeds current capacity, where CAP1 - new capacity,
 * CAP - old capacity.
 */
#define BC_CODE_STREAM_INITIAL_OPCODE_CAP (16)

/**
 * Initial code stream constants capacity. It increases using CAP1 = CAP*3/2 
 * formula when actual size exceeds current capacity, where CAP1 - new capacity,
 * CAP - old capacity
 */
#define BC_CODE_STREAM_INITIAL_CONST_CAP (2)

/**
 * Initial capacity of global variables. It increases using CAP1 = CAP*3/2 
 * formula when actual size exceeds current capacity, where CAP1 - new capacity,
 * CAP - old capacity
 */
#define BC_CORE_GLOBAL_INITIAL_CAP (2)

/**
 * Interpreter bytecodes.
 * 
 * Only few bytecodes has additional arguments passed after it.
 * 
 * As an example: after BC_PSH follows byte encoding constant ID to push.
 */
typedef enum bcOp_t
{
  BC_HALT = 0x00, /**< Halt VM Execution */
  BC_PSH, /**< push(A) */
  BC_POP, /**< pop() */
  BC_ADD, /**< A + B */
  BC_SUB, /**< A - B */
  BC_MUL, /**< A * B */
  BC_DIV, /**< A / B */
  BC_MOD, /**< A % B */
  BC_EQ,  /**< A = B */
  BC_NEQ, /**< A != B */
  BC_GR,  /**< A > B */
  BC_LS,  /**< A < B */
  BC_GRE, /**< A >= B */
  BC_LSE, /**< A <= B */
  BC_LND, /**< A && B */
  BC_LOR, /**< A || B */
  BC_BND, /**< A & B */
  BC_BOR, /**< A | B */ 
  BC_XOR, /**< A ^ B */
  BC_BLS, /**< A << B */
  BC_BRS, /**< A >> B */
  BC_SET, /**< A <- B */
  BC_NEG, /**< -A */
  BC_LNT, /**< !A */
  BC_BNT, /**< ~A */
  BC_INT, /**< (int) A */
  BC_NUM, /**< (num) A */
  BC_STR, /**< (str) A */
  BC_VAL, /**< ValueOf(A) */
  BC_IFS, /**< Check call */
  BC_RET, /**< Set result value */
  BC_CPY, /**< Copy value on stack to top */
  BC_IND, /**< A[B] */
  BC_ADR, /**< &A */
  BC_ITM, /**< A.B */
  BC_CLL, /**< A() */
  BC_LST, /**< toList(A) */
  BC_DCT, /**< toDict(A) */
  BC_OP_LAST, /**< Last valid opcode */
  BC_OP_TOTAL = 0xFF
} bcOp_t;

/**
 * Abstraction for chunk of compiled code without branches.
 */
typedef struct bcCodeStream_t
{
  size_t opCap;     /**< Total opcode capacity */
  size_t opSize;    /**< Total opcode size     */
  uint8_t* opcodes; /**< opcodes               */

  size_t    conCap;  /**< Total consts capacity */
  size_t    conSize; /**< Total consts size     */
  BC_VALUE* cons;    /**< Constants             */

} bcCodeStream_t;

typedef struct bcGlobalVar_t
{
  BC_VALUE value;
  char name[];
} bcGlobalVar_t ,*BC_GLOBAL;

typedef struct bcParseContext_t
{
  void* context;
  int newline;

  uint8_t indentStack[64];
  uint8_t* indentTop;
} bcParseContext_t;

typedef struct bcCode_t
{
  bcValue_t head;
  bcCodeStream_t code;
} bcCode_t;

/**
 * Interprerer evaluation core.
 */
struct bcCore_t
{
  bcValueStack_t stack;

  size_t globalCap;
  size_t globalSize;
  BC_GLOBAL* globals;

  bcParseContext_t parseContext;
  BC_VALUE result;
};

bcStatus_t bcCoreSetGlobal(
  BC_CORE core,
  const char* name,
  const BC_VALUE value
);

/**
 * Initialize code stream in-place.
 * 
 * Function allocates space for bcCodeStream_t. Structure must not be previosly
 * initialized, or memory leak happens.
 * 
 * If function failed, no changes to data passed in argument are applied.
 * 
 * @param cs[in] pointer to uninitialized code stream
 * 
 * @return 
 *  BC_OK - if code stream initialized successfully
 *  BC_NO_MEMORY - if some data allocation failed.
 */
bcStatus_t bcCodeStreamInit(bcCodeStream_t* cs);

/**
 * Cleanup valid code stream.
 * 
 * Function cleanup memory for valid code stream, frees all stored inside BC_VALUEs.
 * 
 * @param cs[in] pointer to valid code stream
 * 
 * @return
 *   BC_OK - always, may change later
 */
bcStatus_t bcCodeStreamCleanup(bcCodeStream_t* cs);

/**
 * Appends new opcode at end of opcode list.
 * 
 * When opcode capacity is reached, allocates new opcode array of bigger size
 * copy all opcodes from old array to new and frees old array.
 * 
 * No checks for opcode validity are made in this function.
 * 
 * @param cs[in] - valid code stream
 * @param opcode[in] - opcode to append
 * 
 * @return
 *    BC_INVALID_ARG - if passed cs == NULL
 *    BC_NO_MEMORY - when capacity reached and no memory can't be allocated
 *    BC_OK - opcode appended successfully
 */
bcStatus_t bcCodeStreamAppendOpcode(bcCodeStream_t* cs, uint8_t opcode);

/**
 * Appends new constant at end of constant list and returns it's ID.
 * 
 * When constant capacity is reached, allocates new constant array of bigger size
 * copy all constants from old array to new and frees old array.
 * 
 * Function check constant pointer equality to NULL. Code stream owns passed
 * constant's BC_VALUE if function call completed successfully.
 * 
 * @param cs[in] - valid code stream
 * @param con[in] - constant to add
 * @param pCon[out] - pointer to store new constant ID.
 * 
 * @return 
 *    BC_INVALID_ARG - if cs == NULL, or pCon == NULL, or con == NULL
 *    BC_TOO_MANY_CONSTANTS - total count of constants can't exceeds UINT8_MAX+1
 *    BC_NO_MEMORY - when capactity reached and no memory can't be allocated
 *    BC_OK - constant appened successfully
 */
bcStatus_t bcCodeStreamAppendConstant(bcCodeStream_t* cs, const BC_VALUE con, uint8_t* pCon);

bcStatus_t bcCodeStreamCompile(bcCodeStream_t* cs, const bcTree_t* tree);

/**
 * Interface function to re2c generated lexer.
 * 
 * Split input character stream into tokens.
 * 
 * @param[in] head - first character in stream
 * @param[out] tail - pointer is set to character after last processed
 * @param[out] pData - pointer is set to new allocated BC_VALUE, if any.
 * @param[in,out] parseContext - pointer to parsing context
 * 
 * @return 0 if string ended and no tokens are found, one of TOK_ constants otherwise
 */
int bcGetToken(const char* head, const char** tail, BC_VALUE* pData, bcParseContext_t* parseContext);

/**
 * Interface function to LEMON generated parser.
 * 
 * Generate code stream from given character string.
 * 
 * Code stream is initialized inside function, so only uninitialized streams must
 * be passed, or memory leak happens.
 * 
 * @param[in] str - string to parse into code stream
 * @param[out] parseTree - pointer to parse tree fill, if function fails, no changes to parseTree are made.
 * @param[out] endp - pointer in str to last processed character without error.
 * @param[out] context - pointer to memory to store parsing context, if BC_PARSE_NOT_FINISHED is returned
 * 
 * @return 
 *    BC_PARSE_NOT_FINISHED - more data expected, 
 *    BC_INVALID_ARG - when str or codeStream equals to NULL
 *    BC_NO_MEMORY - when code stream allocation fails, or parser failed to get memory
 *    BC_OK - if parsing completed successfully
 */
bcStatus_t bcParseString(const char* str, bcTree_t** parseTree, char** endp, bcParseContext_t* parseContext);

/**
 * Compile code stream to value.
 */
BC_VALUE bcValueCode(const bcTree_t* parseTree);

BC_GLOBAL bcGlobalNew(const char* name, const BC_VALUE value);

void bcGlobalDelete(BC_GLOBAL global);

bcStatus_t bcCoreSetGlobal(BC_CORE core, const char* name, const BC_VALUE value);

BC_VALUE bcCoreGetGlobal(BC_CORE core, const char* name);

bcStatus_t bcValueBinaryOperatorAlgebra(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result);

bcStatus_t bcValueBinaryOperatorCompare(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result);

bcStatus_t bcValueBinaryOperatorLogicBitwise(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result);

bcStatus_t bcValueBinaryOperator(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result);

bcStatus_t bcValueUnaryOperator(const BC_VALUE a, uint8_t unop, BC_VALUE* result);

const char* bcOpcodeString(uint8_t opcode);

#endif /* DECI_SPACE_BADCODE_PRIVATE_HEADER */
