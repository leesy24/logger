#include <stdio.h>
#include <string.h>

typedef const char* c_str;
FILE* log_fp = NULL;
int max_log_size = 1 * 1024 * 1024;
int max_no = 1000;
c_str prefix = "logs_";
c_str postfix = "";
c_str ext = "txt";

void logger_init(c_str prefix_i, c_str postfix_i, c_str ext_i, int limit, int count)
{
    prefix = prefix_i;
    postfix = postfix_i;
    ext = ext_i;
    max_log_size = limit;
    max_no = count;
}

void logger_out( c_str str )
{
    char file1[100], file2[100];

    if( log_fp == NULL )
    {
        sprintf( file1, "%s%d%s.%s", prefix, 0, postfix, ext );
        log_fp = fopen( file1, "a" );
    }

    if( log_fp != NULL )
    {
        if( ftell( log_fp ) + strlen(str) > max_log_size )
        {
            fclose( log_fp );
            log_fp = 0;

            int i;
            for( i = (max_no - 1); i >= 0; i-- )
            {
                sprintf( file1, "%s%d%s.%s", prefix, i, postfix, ext );
                sprintf( file2, "%s%d%s.%s", prefix, i+1, postfix, ext );
                rename( file1, file2 );
            }

            sprintf( file1, "%s%d%s.%s", prefix, 0, postfix, ext );
            log_fp = fopen( file1, "a" );
        }

        fputs( str, log_fp );
        fflush( log_fp );
    }
}

main()
{
    char msg[100];

    logger_init("/tmp/log_", "", "log", 1024*1024, 1000);

    int i;
    for(i = 0; i < 10000000; i ++)
    {
        sprintf(msg, "abcdefghijk%dlmnopqrstuvwxyz\n", i);
        logger_out(msg);
    }
}

