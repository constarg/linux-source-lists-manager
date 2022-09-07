#include <stdlib.h>
#include <string.h>

#include "source_m.h"
#include "config.h"
#include "io_m.h"

static struct source *retrieve_sources(const char *sl_content, size_t *size)
{
    struct source *s_tmp = NULL;
    size_t sources_s = 10;
    size_t lines_s = 0;
    char **lines = retv_file_lines(sl_content, &lines_s);

    // no lines has been found.
    if (lines == NULL) return NULL;

    // allocate space for sources.
    s_tmp = (struct source *) 
            malloc(sizeof(struct source) * sources_s);

    int s_curr = 0;
    for (int l = 0; l < lines_s; l++)
    {
        // if line start with #. It's a commnet.
        if (lines[l][0] != '#')
        {
            (s_tmp + s_curr)->s_content = malloc(sizeof(char) * 
                                                   strlen(lines[l]) + 1);
            if ((s_tmp + s_curr)->s_content == NULL) return NULL;
            strcpy((s_tmp + s_curr++)->s_content, lines[l]);

            if (s_curr == sources_s)
            {
                sources_s += 10;
                s_tmp = realloc(s_tmp, sizeof(struct source) * 
                                              sources_s);
                if (s_tmp == NULL) return NULL;
            }
        }
        free(lines[l]);
    }
    

    free(lines);
    return realloc(s_tmp, sizeof(struct source) * s_curr);
}

static inline char *retv_sl_name(const char *sl_path)
{
    char *tmp = strstr(sl_path, "/");

    while (strstr((tmp + 1), "/") != NULL) 
    {
        ++tmp;        
    }

    return tmp + 1; // return the name.
}

int open_source_list(struct source_list *sl_dst, const char *sl_path)
{
    size_t sources_s = 0;
    struct source *sources = retrieve_sources(sl_path, &sources_s);
    char *sl_name = retv_sl_name(sl_path);
    if (sources == NULL) return -1;

    // TODO - must do sl_name with malloc? check 
    // again when you define from where you get the sl_path
    
    sl_dst->sl_name       = sl_name;
    sl_dst->sl_loc        = (char *) sl_path;
    sl_dst->sl_sources_s  = sources_s;
    sl_dst->sl_sources    = sources;

    return 0;
}

int ct_source_list(const struct source_list *sl_src)
{
    return 0;
}

int rm_source_list(const char *sl_path)
{
    return 0;
}

int add_source(struct source_list *sl_dst, const struct source s)
{
    return 0;
}

int rm_source(struct source_list *sl_dst, int s_num)
{
    return 0;
}

int cm_source(struct source_list *sl_dst, int s_num)
{
    return 0;
}
