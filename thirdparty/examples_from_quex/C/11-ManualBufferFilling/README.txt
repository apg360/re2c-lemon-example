EXAMPLE: Manual Buffer Filling
-------------------------------
(C) Frank-Rene Schaefer

The engine's buffer can either be filled automatically or manually. Automatic
means that the analyzer calls the loading procedure as soon as the buffer's
end has been reached. In some circumstances, there is not even a file system
where the analyzer runs, so the buffer must be filled manually. The examples
in this directory demonstrate how this is done. 

There are three types of doing so: feeding, gavaging and pointing. The first
two are implemented by lexical analyzer adaptors. Pointing can be done by 
specifying a place for the lexer's buffer.

  Feeding: Here the lexical analyzer's buffer is filled with chunks
           of arbitrary size. In case converters are used, the chunks
           are dropped into the intermediate buffer, i.e. the one before
           conversion takes place.

           This is the most easy to use method and the most flexible. Under
           normal circumstances there is no need, whatsoever, to apply any
           other manual filling method.

           EXAMPLE: lexer-feeder.c

  Gavaging: This method is more intrusive. For gavaging the user gains direct
            access to the lexical analyzer's buffer. When conversion is used
            access to the intermediate buffer is granted. The user can then
            fill content at the buffer directly.

            Pros/Cons:  + spares a copy operation per byte.
                        + receivers do not need to allocate extra space for
                          content to be received.
                        - the content to be received can never exceed the
                          buffer's free space.
                        - only makes sense if the data source can stream into
                          a dedicated place in memory.

           EXAMPLE: lexer-gavager.c

  Pointing: In case of pointing, the lexical analyzer uses a user-specified 
            region in memory in order to run lexical analysis. This is simply
            controlled by the lexer's constructors and reset functions.

            Pointing is only available for setups without converters.

           EXAMPLE: lexer-point.c
 
The examples for without and with converter are 'compile-time' controlled by
the macro 

                  -DQUEX_EXAMPLE_WITH_CONVERTER 
                  
If it is present a converter-based analyzer is compiled, otherwise, a plain 
buffer filler is compiled.

=====================================

COMMENT: Syntactic Chunks vs. Arbitrary Chunks

Earlier versions of this example directory distinguished between syntactic
chunks and arbitrary chunks. The adaptors for feeding and gavaging, though,
provide a high-performance easy-to-use API so that differentiation between
these two concepts is no longer considered advantageous.



