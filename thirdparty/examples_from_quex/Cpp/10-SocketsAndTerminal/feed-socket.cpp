/* Socket Feeder
 * --------------
 *
 * This application shall read content from a file and pass it through a socket
 * so that on the other side a lexical analyzer may listen on the socket and
 * directly examine it.
 *
 *
 *           socket feeder                          lexer-socket
 *          .----------------------.               .-------------------------.
 * .------. |    .--------.        |               |           .----------.  |
 * | file |-+--->| socket |    .--------.      .--------.      | lexical  |  |
 * '------' |    | feeder |--->| socket |----->| socket |----->| analyzer |  |
 *          |    '--------'    '--------'      '--------'      '----------'  |
 *          '----------------------'               '-------------------------'
 *
 *
 * (C) Frank-Rene Schaefer
 *                                                                           */
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

static void feed_file_to_socket(char* FileName, int socket_fd, int ChunkSize, int Delay_ms);
static void feed_string_to_socket(char* String, int socket_fd, int ChunkSize, int Delay_ms);
static int  connect_to_server();

int 
main(int argc, char** argv)
/* Reads a file whose name is given on the command line add flushes it through
 * socket 0x4711 on this host: 
 *
 * USAGE:
 *
 *  (i) $1 == "string":
 *
 *     $2 = string to be sent. 
 *
 *     Send the string given by $2 over the line to the quex analyzer. Use
 *     this to send the "bye" token which terminates the session.
 *
 *  $2 == "file":
 *
 *     $2 = name of file containing the content to be sent. 
 *
 *  $3 Chunk size of chunks fed into socket.                                  
 *  $4 Milliseconds to wait in between sendings.                             
 *
 *  EXAMPLES: 
 *
 *  The 'bye' token is sent by
 *
 *     > feed-socket string bye  
 *
 *  The content of file "example-feed.txt" is sent in chunks of 7 byte every 5 
 *  milliseconds by
 *
 *     > feed-socket file example-feed.txt 7 5
 *
 * The string "hello world" is sent in chunks of 2 bytes every second by
 *
 *     > feed-socket string 'hello world' 2 1000
 *  
 *  (C) Frank-Rene Schaefer                                                  */
{
    enum mode { 
        FEED_STRING, 
        FEED_FILE, 
        FEED_BAD 
    }            mode;
    int          socket_fd = 0;
    char         empty[] = { '\0' };
    char*        specification_str = argc > 2 ? argv[2] : &empty[0];
    const int    ChunkSize         = argc > 3 ? atoi(argv[3]) : 3;
    const int    Delay_ms          = argc > 4 ? atoi(argv[4]) : 1;

    printf("Setup:\n");
    printf("   mode:  %s;\n",        argc > 1 ? argv[1] : "<missing>");
    printf("   spec:  \"%s\";\n",    specification_str);
    printf("   chunk: %i [byte];\n", ChunkSize);
    printf("   freq:  %i [chunks/millisec];\n", Delay_ms);
    printf("\n");

    if( argc < 2 ) {
        printf("command line argument 1: mode 'string' or 'file' not specified.\n");
        exit(-1);
    }
    else {
        if     ( strcmp(argv[1], "string") == 0 ) mode = FEED_STRING;
        else if( strcmp(argv[1], "file") == 0 )   mode = FEED_FILE;
        else {
            printf("command line argument 1: mode 'string' or 'file' not specified.\n");
            exit(-1);
        }
    }
    if( argc < 3 ) {
        printf("command line argument 2: missing specification of file or string.\n");
    }
    else {
    }

    socket_fd = connect_to_server();
    if( socket_fd == -1 ) return -1;

    if( ! ChunkSize ) {
        printf("Chunk size must be > 0!\n");
        return -1;
    }

    switch( mode ) {
    case FEED_STRING:
        feed_string_to_socket(specification_str, socket_fd, ChunkSize, Delay_ms);
        return 0;
    case FEED_FILE:
        feed_file_to_socket(specification_str, socket_fd, ChunkSize, Delay_ms);
        return 0;
    default: 
        return -1;
    }
}

static int
connect_to_server()
{
    struct sockaddr_in  addr;
    int                 socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if( socket_fd == -1 ) {
        printf("client: socket() terminates with failure.\n");
        return -1;
    }

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(0x4711);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if( connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1 ) {
        std::cout << "client: write() terminates with failure." << std::endl;
        return -1;
    }

    return socket_fd;
}

static void
feed_file_to_socket(char* FileName, int socket_fd, int ChunkSize, int Delay_ms)
/* Take the content found in 'fh' and feeds it into socket 'socket_fd' in 
 * chunks of size 'ChunkSize'. When done, this function returns.             */
{
    char   buffer[256];
    size_t read_n; 
    FILE*  fh = fopen(FileName, "rb");

    if( ! fh ) {
        printf("could not open file '%s'.\n", FileName);
        return;
    }
    assert(ChunkSize <= 256);

    while( 1 + 1 == 2 ) {
        /* Read some bytes from the file that contains the source for 
         * feeding.                                                          */
        read_n = fread(&buffer[0], 1, ChunkSize, fh);
        buffer[read_n] = '\0';
        printf("flush: %i: [%s]\n", (int)read_n, &buffer[0]);
        if( ! read_n ) break;

        /* Flush the bytes into the socket.                                  */
        if( write(socket_fd, &buffer[0], read_n) == -1 ) {
            std::cout << "client: write() terminates with failure." << std::endl;
            return;
        }
        usleep((__useconds_t)1000 * Delay_ms);
    }
    std::cout << "<done>" << std::endl;
}

static void
feed_string_to_socket(char* String, int socket_fd, int ChunkSize, int Delay_ms)
/* Take the content found in 'fh' and feeds it into socket 'socket_fd' in 
 * chunks of size 'ChunkSize'. When done, this function returns.             */
{
    char*       p;
    const char* StringEnd = &String[strlen(String)+1];
    ptrdiff_t   chunk_size;
    char        tmp;

    assert(ChunkSize <= 256);

    for(p = &String[0]; p < StringEnd; p += ChunkSize) {

        chunk_size = ChunkSize > StringEnd - p ? StringEnd - p : ChunkSize;

        tmp = p[chunk_size];
        p[chunk_size] = '\0';

        printf("flush: %i: [%s]\n", (int)chunk_size, p);

        p[chunk_size] = tmp;

        /* Flush the bytes into the socket.                                  */
        if( write(socket_fd, p, chunk_size) == -1 ) {
            std::cout << "client: write() terminates with failure." << std::endl;
            return;
        }
        usleep((__useconds_t)1000 * Delay_ms);
    }
    std::cout << "<done>" << std::endl;
}
