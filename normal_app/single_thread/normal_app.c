#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//#include <assert.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int g_log_fno;
char bin2asc[] = "0123456789ABCDEF";

static void e_signal_handler(int signo) {
    char buf[4];
    write(g_log_fno, "signo: ", 8);
    if (signo < 0) {
        write(g_log_fno, "neg\n", 5);
    } else if (signo < 256) {
        buf[0] = bin2asc[signo / 16];
        buf[1] = bin2asc[signo % 16];
        buf[2] = '\n';
        buf[3] = '\0';
        write(g_log_fno, buf, 4);
    } else {
        write(g_log_fno, "big(>256)\n", 11);
    }
    close(g_log_fno);
    _exit(1);
}

static int e_signals[] = {SIGBUS,  // 7
                          10,      // SIGBUS
                          SIGILL,  // 4
                          SIGSEGV, // 11
                          SIGABRT, // 6
                          SIGFPE}; // 8

static void set_signal_handler(void) {
    int i;
    struct sigaction act;
    act.sa_handler = e_signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    for (i = 0; i < ARRAY_SIZE(e_signals); i++) {
        printf("register the signal handler for %d\n", e_signals[i]);
        sigaction(e_signals[i], &act, NULL);
    }
}

int prepare_logfile(int fd) {
    int stdout_fd = fileno(stdout);
    if (fd == stdout_fd) {
        return fd;
    } else {
        return open("log.txt", O_CREAT | O_APPEND | O_SYNC);
    }
}

void cleanup_logfile(int fd) {
    int stdout_fd = fileno(stdout);
    if (fd == stdout_fd) {
        return;
    } else {
        close(fd);
        return;
    }
}

int main() {
    g_log_fno = prepare_logfile(fileno(stdout));
    // g_log_fno = prepare_logfile(-1);
    printf("g_log_fno: %d\n", g_log_fno);
    write(g_log_fno, "hi\n", 4);
    set_signal_handler();
    while (true) {
        printf(".");
        sleep(1);
        fflush(stdout);
    }
    close(g_log_fno);
}
