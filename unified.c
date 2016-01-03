#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int fsck_main(int argc, char *argv[]);
extern int mount_main(int argc, char *argv[]);

struct tool {
    const char *name;
    int (*func)(int, char **);
};

struct tool tools[] = {
    { "fsck.exfat", fsck_main },
    { "mount.exfat", mount_main },
    { NULL, NULL }
};

int main(int argc, char *argv[])
{
    const char *basename = argv[0];
    const char *ptr;
    if ((ptr = strrchr(basename, '/'))) {
        basename = ptr + 1;
    }

    struct tool *tool;
    for (tool = tools; tool->name; ++tool) {
        if (strcmp(basename, tool->name) == 0) {
            return tool->func(argc, argv);
        }
    }

    fprintf(stderr, "%s: tool not found\n", basename);
    return EXIT_FAILURE;
}
