#ifndef DAEMONIZE_H
# define DAEMONIZE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include "manage.h"
# include "helper.h"

// glibc kill prototype to make it compile.
int kill(pid_t pid, int sig);

// Main entry point: parses arguments and dispatches to the appropriate handler.
void handle_options(int argc, char **argv);

#endif /* !DAEMONIZE_H */
