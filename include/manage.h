#ifndef MANAGE_H
# define MANAGE_H

# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

// Maximum number of tracked daemons.
# define DAEMONS_SIZE 4096

// Global array mapping daemon index to PID.
extern pid_t daemons[DAEMONS_SIZE];

// Returns the command line of a process by reading /proc/<pid>/cmdline.
char *get_process_cmd(pid_t pid);

// Populates the daemons array by scanning /proc for processes with PPID == 1.
void get_daemons(void);

// Displays the list of daemons with their index, PID, and command line.
void display_daemons(void);

#endif /* !MANAGE_H */
