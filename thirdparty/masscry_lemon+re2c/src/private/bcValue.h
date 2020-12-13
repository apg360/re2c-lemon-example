/**
 * @file bcValue.h
 * 
 * BadCode Value Structures.
 * 
 */
#pragma once
#ifndef DECI_SPACE_BADCODE_VALUE_HEADER
#define DECI_SPACE_BADCODE_VALUE_HEADER

/**
 * Available data types to box
 */
typedef enum bcDataType_t
{
  BC_NULL = 0,       /**< Null object */
  BC_INTEGER,        /**< Int64 */
  BC_NUMBER,         /**< Float64 */
  BC_STRING,         /**< Character string */
  BC_LIST,           /**< Linear List */
  BC_DICT,           /**< Key-Value Storage */
  BC_REF,            /**< Reference */
  BC_FUNC,           /**< Interpretable function */
  BC_NATIVE,         /**< Native C-function */
  BC_CODE,           /**< Code block */
  BC_DATA_TYPE_TOTAL
} bcDataType_t;

/**
 * Abstract value type.
 */
typedef struct bcValue_t
{
  bcDataType_t type; /**< Value type */
  int32_t refCount; /**< reference counter */
} bcValue_t;

/**
 * BC_INTEGER.
 */
typedef struct bcInteger_t
{
  bcValue_t head;
  int64_t   data;
} bcInteger_t;

/**
 * BC_NUMBER.
 */
typedef struct bcNumber_t
{
  bcValue_t head;
  double    data;
} bcNumber_t;

/**
 * BC_STRING.
 */
typedef struct bcString_t
{
  bcValue_t head;
  size_t    len;
  char      data[];
} bcString_t;

/**
 * BC_NATIVE.
 */
typedef struct bcNative_t
{
  bcValue_t head;
  void (*func)(BC_CORE);
} bcNative_t;

/**
 * BC_REF.
 */
typedef struct bcRef_t
{
  bcValue_t head;
  BC_VALUE data;
} bcRef_t;

/**
 * BC_DICT.
 */
typedef struct bcNameDict_t
{
  char* name;
  uint32_t index;
} bcNameDict_t;


#endif /* DECI_SPACE_BADCODE_VALUE_HEADER */

