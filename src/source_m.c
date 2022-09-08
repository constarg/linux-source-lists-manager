#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "source_m.h"
#include "config.h"


static struct source *retrieve_sources(const char *sl_content, size_t *size)
{
    struct source *s_tmp = NULL;
    size_t s_sources = 10;
    size_t s_lines = 0;
    char **lines = retv_file_lines(sl_content, &s_lines);

    // no lines has been found.
    if (lines == NULL) return NULL;

    // allocate space for sources.
    s_tmp = (struct source *) 
            malloc(sizeof(struct source) * s_sources);

    int s_curr = 0;
    for (int l = 0; l < s_lines; l++) {
        // if line start with #. It's a commnet.
        if (lines[l][0] != '#' && lines[l][0] != '\0'
            && lines[l][0] != ' ' && lines[l][0] != '\n') {
            s_tmp[s_curr].s_content = (char *) malloc(sizeof(char) * 
                                                      strlen(lines[l]) + 1);
            if (s_tmp[s_curr].s_content == NULL) return NULL;
            strcpy(s_tmp[s_curr].s_content, lines[l]);

            if (s_curr == s_sources) {
                s_sources += 10;
                s_tmp = (struct source *) realloc(s_tmp, sizeof(struct source) * 
                                                  s_sources);
                if (s_tmp == NULL) return NULL;
            }
            ++s_curr;
        }
    }
    
    *size = s_curr;
    free_file_lines(lines, s_lines);

    return (struct source *) realloc(s_tmp, sizeof(struct source) * (s_curr));
}

static inline char *retv_sl_name(const char *sl_path)
{
    char *tmp = strstr(sl_path, "/");

    while (strstr((tmp + 1), "/") != NULL) {
        ++tmp;        
    }

    return tmp + 1; // return the name.
}

int open_source_list(struct source_list *sl_dst, const char *sl_path)
{
    size_t s_sources = 0;
    struct source *sources = retrieve_sources(sl_path, &s_sources);
    char *sl_name = retv_sl_name(sl_path);
    if (sources == NULL) return -1;

    sl_dst->sl_name       = sl_name;
    sl_dst->sl_loc        = (char *) sl_path;
    sl_dst->sl_s_sources  = s_sources;
    sl_dst->sl_sources    = sources;

    return 0;
}

int ct_source_list(const char *sl_name)
{
    char *sl_path = (char *) malloc(sizeof(char) *
                                    strlen(SOURCE_LIST_D) +
                                    strlen(sl_name) + 1);

    strcpy(sl_path, SOURCE_LIST_D);
    strcat(sl_path, sl_name);

    // create the new source list.
    int fd = open(sl_path, O_CREAT);
    if (fd == -1) return -1;

    close(fd);
    free(sl_path);
    return 0;
}

int rm_source_list(const char *sl_name)
{
    char *sl_path = (char *) malloc(sizeof(char) *
                                    strlen(SOURCE_LIST_D) +
                                    strlen(sl_name) + 1);

    strcpy(sl_path, SOURCE_LIST_D);
    strcat(sl_path, sl_name);

    if (remove(sl_path) == -1) return -1;
    free(sl_path);
    return 0;
}

int rm_source(struct source_list *sl_src, int s_num)
{
    if (s_num > sl_src->sl_s_sources) return -1; // No source exists.

    char *rmvd = sl_src->sl_sources[s_num].s_content; // removed source.
    // remove the source.
    for (int i = s_num; 
         i < (sl_src->sl_s_sources - 1); i++) {
        sl_src->sl_sources[i] = sl_src->sl_sources[i + 1];
    }
    --sl_src->sl_s_sources;
    free(rmvd);

    // TODO - get the commented section of the source file.

    return 0;
}

int cm_source(struct source_list *sl_src, int s_num)
{
    return 0;
}
