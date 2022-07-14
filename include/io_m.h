#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <malloc.h>
#include <stdlib.h>

static inline void close_source_files_d(char **src)
{
    // O(n) complexity. Where n = the amount of source files.
    for (int f = 0; src[f]; f++)
    {
        free(src[f]);
    }
    free(src);
}

extern char **open_source_files_d();

extern int write_append_line(char *line, const char *path);

extern char **retv_file_lines(const char *path, size_t *lines_s);


#endif
