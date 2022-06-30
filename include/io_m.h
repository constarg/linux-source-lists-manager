#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <malloc.h>


extern char **open_source_files_d();

static inline void close_source_files_d(char **src)
{
    // O(n) complexity. Where n = the amount of source files.
    for (int f = 0; src[f]; f++)
    {
        free(src[f]);
    }
    free(src);
}

/**
 * Read the content of a source file.
 */
extern int read_source_file(char *dst, const char *name);

extern int write_source_file(const char *src, const char *path);



#endif
