/* Socket-Based Lexical FSM
 * -----------------------------
 *
 * This application implements a lexical analyzer that directly reads content
 * from a socket connection. For trying, the socket connection may be fed
 * with the 'feed-socket.cpp' application which reads content from a file
 * and passes it trough the socket.
 *
 * As soon as a "bye" lexeme is received, the application terminates.
 *
 *          "feed-socket.cpp"                      "lexer-socket.cpp"
 *          .----------------------.               .-------------------------.
 * .------. |    .--------.        |               |           .----------.  |
 * | file |-+--->| socket |    .--------.      .--------.      | lexical  |  |
 * '------' |    | feeder |--->| socket |----->| socket |----->| analyzer |  |
 *          |    '--------'    '--------'      '--------'      '----------'  |
 *          '----------------------'               '-------------------------'
 *
 *_____________________________________________________________________________
 *
 * EXAMPLE:
 *  
 * Let "[T1]>" denote the command line on a terminal '1' and "[T2]>" denote the
 * command line on a terminal '2'. Then, the socket based lexical analyzer may 
 * be tried out by
 *
 *    [T1]> ./lexer-socket
 *    # (now waiting for incomming connections ...)
 *    
 *    [T2]> ./feed-socket file example-feed.txt 7 1000
 *                         |       |            |   '----- send every second
 *                         |       |            '--------- send chunks of 7 byte
 *                         |       '---------------------- send content of file
 *                         |                               "example-feed.txt"
 *                         |
 *                         '------------------------------ mode: 'read from file'
 *    [T2] starts sending
 *    [T1] starts receiving (watch the drippling tokens!)
 *
 *    [T2]> ./feed-socket string "bye" 1 1
 *    # sends the connection terminating "bye" token.
 *_____________________________________________________________________________
 *
 * (C) Frank-Rene Schaefer                                                   */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#if ! defined(WITH_UTF8)
#   include <lex_ascii/Lexer>
#   include <lex_ascii/lib/quex/byte_loader/ByteLoader_POSIX>
#   include <lex_ascii/lib/quex/byte_loader/ByteLoader_POSIX.i>
#else
#   include <lex_utf8/Lexer>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv.i>
#   include <lex_utf8/lib/quex/byte_loader/ByteLoader_POSIX>
#   include <lex_utf8/lib/quex/byte_loader/ByteLoader_POSIX.i>
#endif

static int  setup_socket_server(void);
static bool accept_and_lex(int listen_fd);
static bool self_on_nothing(quex::ByteLoader*  me, size_t TryN, size_t LoadedN);
 
int main(void)
{
    int listen_fd = setup_socket_server();

    if( listen_fd == - 1) return -1;

    while( accept_and_lex(listen_fd) );

    return 0;
}

static bool
accept_and_lex(int listen_fd)
/* Accept an incoming connection and let a lexical analyser be fed by what 
 * comes through it.
 *
 * RETURNS: True, lexing successful.
 *          False, if an error occured or the 'BYE' token requests to stop.  */
{


    int               connected_fd = accept(listen_fd, (struct sockaddr*)NULL ,NULL); 
    Lexer_Token*      token;
    Lexer*            qlex;
    bool              continue_f;
#if defined(WITH_UTF8)
    quex::Converter*  converter = new quex::Converter_IConv(sizeof(Lexer_lexatom_t)<<3, "UTF8", NULL);
#   else
#   define            converter NULL
#endif

    quex::ByteLoader* loader = quex::ByteLoader_POSIX_new(connected_fd);

    if( connected_fd == -1 ) {
        printf("server: accept() terminates with failure.\n");
        sleep(1);
        return true;
    }

    quex::ByteLoader_seek_disable(loader);

    /* A handler for the case that nothing is received over the line. */
    loader->on_nothing = self_on_nothing; 

    qlex = Lexer::from_ByteLoader(loader, converter);

    continue_f = true;
    do {
        qlex->receive(&token); 
        printf("   Token: %s\n", token->get_string().c_str()); 

        if( token->id == QUEX_TKN_BYE ) {
             continue_f = false;
             break;
        }

    } while( token->id != QUEX_TKN_TERMINATION );
        
    delete qlex;
    printf("<terminated>\n");
    return continue_f;
}


static int 
setup_socket_server(void)
/* Setup a socket server, i.e. something that can listen on incoming 
 * connections. 
 *
 * RETURNS: -1, in case of failure.
 *          file descriptor of a listening socket.                           */
{
    int                 listen_fd = 0;
    struct sockaddr_in  addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( listen_fd == -1 ) {
        printf("server: socket() terminates with failure.\n");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;    
    addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    addr.sin_port        = htons(0x4711);    

    if( bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1 ) {
        printf("server: bind() terminates with failure.\n");
        return -1;
    }

    if( listen(listen_fd, 10) == -1 ) {
        printf("server: listen() terminates with failure.\n");
        return -1;
    }

    return listen_fd;
}

static bool  
self_on_nothing(quex::ByteLoader*  me, size_t TryN, size_t RequiredToLoad)
/* ByteLoader's handler to treat the case that nothing has been received. Note,
 * that with the current setup the socket receiver blocks until something comes
 * in. If nothing is received, the socket is closed.
 *
 * RETURNS: 'false' in any case to mark the end of transmission.
 *                                                                           */
{ 


    int       error  = 0;
    socklen_t len    = sizeof (error);
    int       retval = getsockopt(((quex::ByteLoader_POSIX*)me)->fd, SOL_SOCKET, SO_ERROR, &error, &len);
    (void)TryN; (void)RequiredToLoad;

    if( retval ) {
        /* there was a problem getting the error code */
        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
        return  false;
    }
    else if( error ) {
        /* socket has a non zero error status */
        fprintf(stderr, "socket error: %s\n", strerror(error));
        return false;
    }
    else {
        return false;
    }
}


