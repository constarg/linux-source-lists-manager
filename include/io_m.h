#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <malloc.h>
#include <stdlib.h>

typedef char** sl_dir;



static inline void close_source_files_d(sl_dir src)
{
    // O(n) complexity. Where n = the amount of source files.
    for (int f = 0; src[f]; f++) {
        free(src[f]);
    }
    free(src);
}

static inline void free_file_lines(char **lines, size_t size)
{
    for (int f = 0; f < size; f++) {
        free(lines[f]);
    }
    free(lines);
}

extern sl_dir open_source_files_d();

extern int append_line(char *line, const char *path);

extern char **retv_file_lines(const char *path, size_t *sr_lines);


#endif
