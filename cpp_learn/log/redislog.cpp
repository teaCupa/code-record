//
// Created by teagm on 2023/4/18.
//

#include <stdio.h>
#include <stdarg.h>
#include<time.h>

struct redisserver{
    char *logfile;
    int verbosity;
};

struct redisserver server;

static void redisLog(int level, const char *fmt, ...) {
    va_list ap;
    FILE *fp;

    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
    if (!fp) return;

    va_start(ap, fmt);
    if (level >= server.verbosity) {
        char *c = ".-*";
        char buf[64];
        time_t now;

        now = time(NULL);
        strftime(buf,64,"%d %b %H:%M:%S",gmtime(&now));
        //首先使用 fprintf() 将一些数据打印到 LogFile 中，然后使用 vfprintf() 在那里打印它自己的可变参数
        fprintf(fp,"%s %c ",buf,c[level]); //fp: 28 Nov 07:31:13 [.-*]
        vfprintf(fp, fmt, ap);      //28 Nov 07:31:13 . hello: 0 redisLog\n
        fprintf(fp,"\n");
        fflush(fp);
    }
    va_end(ap);

    if (server.logfile) fclose(fp);
}

int main()
{
    server.logfile="LOG";
    redisLog(0,"hello: 0 redisLog\n");
    redisLog(1,"hello: 1 redisLog\n");
    redisLog(2,"hello: 2 redisLog\n");

}
