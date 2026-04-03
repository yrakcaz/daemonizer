#include <manage.h>

pid_t daemons[DAEMONS_SIZE];

char *get_process_cmd(pid_t pid)
{
    char name[64];
    snprintf(name, sizeof(name), "/proc/%d/cmdline", pid);
    int fd = open(name, O_RDONLY);
    char *ret = malloc(128 * sizeof (char));
    int nbbytes = read(fd, ret, 128);
    int i;
    for (i = 0; i < nbbytes; i++)
        ret[i] = ret[i] == '\0' ? ' ' : ret[i];
    ret[i] = '\0';
    close(fd);
    return ret;
}

static int is_a_number(char *s)
{
    for (size_t i = 0; i < strlen(s); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

static int is_a_dir(char *file)
{
    char path[64];
    snprintf(path, sizeof(path), "/proc/%s", file);
    struct stat st;
    stat(path, &st);
    if (S_ISDIR(st.st_mode))
        return 1;
    return 0;
}

static int is_a_daemon(char *dir)
{
    char name[64];
    snprintf(name, sizeof(name), "/proc/%s/stat", dir);
    int fd = open(name, O_RDONLY);
    char buf[256];
    int n = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (n <= 0)
        return 0;
    buf[n] = '\0';
    char *p = strrchr(buf, ')');
    if (!p)
        return 0;
    int ppid;
    if (sscanf(p + 1, " %*c %d", &ppid) != 1)
        return 0;
    return ppid == 1;
}

void get_daemons(void)
{
    for (int i = 0; i < DAEMONS_SIZE; i++)
        daemons[i] = 0;
    DIR *rep = opendir("/proc");
    struct dirent *file;
    int i = 0;
    while ((file = readdir(rep)))
    {
        if (is_a_number(file->d_name) && is_a_dir(file->d_name))
            if (is_a_daemon(file->d_name))
                daemons[i++] = atoi(file->d_name);
    }
    closedir(rep);
}

void display_daemons(void)
{
    printf("id\tpid\tcmdline\n");
    get_daemons();
    for (int i = 0; daemons[i] != 0; i++)
    {
        char *cmdline = get_process_cmd(daemons[i]);
        printf("[%d]\t%d\t%s\n", i, daemons[i], cmdline);
        free(cmdline);
    }
    exit(0);
}
