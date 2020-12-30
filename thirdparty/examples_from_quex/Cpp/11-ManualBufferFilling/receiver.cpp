#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "receiver.h"

#ifdef QUEX_DEMO_WITH_CONVERTER
#   include "converter/Lexer"
    static ELEMENT_TYPE receiver_data[] = 
       "Ελληνικά • Euskara • فارسی • Frysk • Galego • 한국어 • हिन्दी bye";
#else
#   include "plain/Lexer"
    static Lexer_lexatom_t   receiver_data[] = 
       "A little nonsense now and then is cherished by the wisest men bye";
#endif

/* Content size without the implicit terminating zero.                       */
static const ptrdiff_t CONTENT_SIZE = ((sizeof(receiver_data)/sizeof(receiver_data[0]))-1);

size_t 
receiver_get_pointer_to_received(ELEMENT_TYPE** rx_buffer)
/* Simulate the reception into a place that is defined by the low level driver.
 * The low level driver reports the address of that place and the size.
 *                                                                           */
{
    static ELEMENT_TYPE*  iterator       = &receiver_data[0];
    const size_t          remainder_size =   CONTENT_SIZE  
                                           - (iterator - &receiver_data[0]);
    size_t                size = (size_t)((float)(rand()) / (float)(RAND_MAX) * 10.0) + 1;

    if( size >= remainder_size ) size = remainder_size; 

    *rx_buffer = iterator; 
    iterator += size;

    if( size != 0 ) {
        __quex_assert(iterator <= receiver_data + CONTENT_SIZE);
    } else {
        __quex_assert(iterator == receiver_data + CONTENT_SIZE);
    }

    return size;
}


size_t 
receiver_receive_in_this_place(ELEMENT_TYPE* BeginP, const ELEMENT_TYPE* EndP)
/* Simulate a low lever driver that is able to fill a specified position in 
 * memory.                                                                   */
{
    static ELEMENT_TYPE*  iterator   = receiver_data;
    const size_t          BufferSize = EndP - BeginP;
    size_t                size = (size_t)((float)(rand()) / (float)(RAND_MAX) * 10.0) + 1;

    assert(iterator <= receiver_data + CONTENT_SIZE);
    if( iterator + size >= receiver_data + CONTENT_SIZE ) 
        size = CONTENT_SIZE - (iterator - receiver_data); 
    if( size > BufferSize ) size = BufferSize;

    memcpy(BeginP, iterator, size);
    iterator += size;

    return size;
}

