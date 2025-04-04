#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#include "../util/defines.h"

#include "builtin.h"

char *builtin_list[] = {
    "cd",
    "echo",
    "exit",
    "help",
    "sinfo"
};

int (*builtin_func[]) (char **) = {
    &cd,
    &echo,
    &osh_exit,
    &help,
    &sinfo
};

int num_builtin() {
    return sizeof(builtin_list) / sizeof(char *);
}

int cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "osh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("osh");
        }
    }
    return 1;
}

int echo(char **args) {
    int newline = 1;
    int idx = 1;
    
    // Checking for no newline flag
    if (args[1] && strcmp(args[1], "-n") == 0) {
        newline = 0;
        idx++;
    }

    // Iterate through string arg to echo
    for (; args[idx] != NULL; ++idx) {
        printf("%s", args[idx]);
        if (args[idx + 1] != NULL) {
            printf(" ");
        }
    }

    if (newline) {
        printf("\n");
    }

    return 1;
}

int help(char **args) {
    printf("osh: The Open Shell\n");
    printf("The following commands are currently supported:\n");

    for (int i = 0; i < num_builtin(); ++i) {
        printf("  %s\n", builtin_list[i]);
    }

    return 1;
}

int osh_exit(char **args) {
    return 0;
}

int sinfo(char **args) {
    struct sysinfo info;
    FILE *fp;
    char buffer[256];
    
    // Read current memory and system uptime info from sysinfo() call
    if (sysinfo(&info) == 0) {
        long uptime = info.uptime;
        int uptime_hours = uptime / 3600;
        int uptime_minutes = (uptime % 3600) / 60;

        printf("Uptime: %dh %dm\n", uptime_hours, uptime_minutes);

        long total_ram = info.totalram / 1024 / 1024;
        long free_ram = info.freeram / 1024 / 1024;
        long total_gb = total_ram / 1024;
        long free_gb = free_ram / 1024;

        printf("Memory: %ldMB (%ldGB) total, %ldMB (%ldGB) free\n", total_ram, total_gb, free_ram, free_gb);
    } else {
        perror("sinfo error");
    }

    // Read kernel info
    fp = fopen("/proc/version", "r");
    if (fp != NULL) {
        fgets(buffer, sizeof(buffer), fp);
        printf("Kernel: %s", buffer);
        fclose(fp);
    }

    // Read CPU info
    fp = fopen("/proc/cpuinfo", "r");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "model name", 10) == 0) {
                char *model = strchr(buffer, ':') + 2;
                printf("CPU: %s", model);
                break;
            }
        }
        fclose(fp);
    }
    
    return 1;
}