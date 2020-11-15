#include <stdio.h>
#include <syslog.h>
#include "write_log.h"

void write_log(char* text)
{
        openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        syslog (LOG_INFO, "%s", text);
        closelog();
        return;
}