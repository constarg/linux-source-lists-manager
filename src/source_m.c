#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "source_m.h"
#include "config.h"


static struct source **parse_contents(const char *sl_content, size_t *s_size,
                                     size_t *c_size)
{
    struct source *s_tmp = NULL;
    struct source *c_tmp = NULL;
    struct source **contents;
    size_t s_sources = 10;
    size_t s_comments = 10;
    size_t s_lines = 0;
    char **lines = retv_file_lines(sl_content, &s_lines);

    // no lines has been found.
    if (lines == NULL) return NULL;

    contents = (struct source **)
                malloc(sizeof(struct source *) * 2);

    // allocate space for sources.
    s_tmp = (struct source *) 
            malloc(sizeof(struct source) * s_sources);

    // allocate space for comments.
    c_tmp = (struct source *)
            malloc(sizeof(struct source) * s_comments);

    int s_curr = 0;
    int c_curr = 0;
    for (int l = 0; l < s_lines; l++) {
        // TODO - maybe cleanup a little this for.
        if (lines[l][0] == '#') {
            c_tmp[c_curr].s_content = (char *) malloc(sizeof(char) *
                                                      strlen(lines[l]) + 1);
            if (c_tmp[c_curr].s_content == NULL) return NULL;
            strcpy(c_tmp[c_curr].s_content, lines[l]);

            ++c_curr;
            if (c_curr == s_comments) {
                s_comments += 10;
                c_tmp = (struct source *) realloc(c_tmp, sizeof(struct source) *
                                                  s_comments);
                if (c_tmp == NULL) return NULL;
            }
        } else if (lines[l][0] != '\0' && lines[l][0] != ' ' 
            && lines[l][0] != '\n') {
            s_tmp[s_curr].s_content = (char *) malloc(sizeof(char) * 
                                                      strlen(lines[l]) + 1);
            if (s_tmp[s_curr].s_content == NULL) return NULL;
            strcpy(s_tmp[s_curr].s_content, lines[l]);

            ++s_curr;
            if (s_curr == s_sources) {
                s_sources += 10;
                s_tmp = (struct source *) realloc(s_tmp, sizeof(struct source) * 
                                                  s_sources);
                if (s_tmp == NULL) return NULL;
            }
        }
    }
    
    *s_size = s_curr;
    *c_size = c_curr;
    free_file_lines(lines, s_lines);
 
    contents[0] = (struct source *) realloc(s_tmp, sizeof(struct source) * (s_curr));
    contents[1] = (struct source *) realloc(c_tmp, sizeof(struct source) * (c_curr));
    return contents;
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
    size_t s_sources  = 0;
    size_t s_comments = 0;
    struct source **contents = parse_contents(sl_path, &s_sources,
                                             &s_comments);
    char *sl_name = retv_sl_name(sl_path);
    if (contents == NULL) return -1;

    sl_dst->sl_name       = sl_name;
    sl_dst->sl_loc        = (char *) sl_path;
    sl_dst->sl_s_sources  = s_sources;
    sl_dst->sl_s_comments = s_comments;
    sl_dst->sl_sources    = contents[0];
    sl_dst->sl_comments   = contents[1];

    free(contents);
    return 0;
}

int ct_source_list(const char *sl_name)
{
    if (geteuid() != 0) return ACCESS_DENIED;
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
    if (geteuid() != 0) return ACCESS_DENIED;
    char *sl_path = (char *) malloc(sizeof(char) *
                                    strlen(SOURCE_LIST_D) +
                                    strlen(sl_name) + 1);

    strcpy(sl_path, SOURCE_LIST_D);
    strcat(sl_path, sl_name);

    if (remove(sl_path) == -1) return -1;
    free(sl_path);
    return 0;
}

static void save_changes(const struct source_list *sl_src,
                         size_t size)
{

    // TODO - keep a backup.
    // TODO - save each line in a new file.
    // TODO - move the file with the changes in the right location.

    // TODO - need test.
    int fd = open(sl_src->sl_loc, O_TRUNC); // clear the previous contents.
    close(fd);

    // rewrite the file.
    // rewrite sources.
    // TODO - make a more efficient method. Do not use append, make another function.
    // problem: with the use of append_line function i use to many times the open() sys call.
    // Make a function that takes an array and appened it in a file in one open() call.
    for (int s = 0; s < sl_src->sl_s_sources;
         s++) {
        append_line(sl_src->sl_sources[s].s_content, sl_src->sl_loc);
        append_line("\n", sl_src->sl_loc);
    }
    // rewrite comment.
    for (int c = 0; c < sl_src->sl_s_comments;
         c++) {
        append_line(sl_src->sl_comments[c].s_content, sl_src->sl_loc);
        append_line("\n", sl_src->sl_loc);
    }
}

int rm_source(struct source_list *sl_src, int s_num)
{
    // TODO - need test.
    if (geteuid() != 0) return ACCESS_DENIED;
    if (s_num > sl_src->sl_s_sources) return -1; // No source exists.

    char *rmvd = sl_src->sl_sources[s_num].s_content; // removed source.
    // remove the source.
    for (int i = s_num; 
         i < (sl_src->sl_s_sources - 1); i++) {
        sl_src->sl_sources[i] = sl_src->sl_sources[i + 1];
    }
    --sl_src->sl_s_sources;
    free(rmvd);

    save_changes(sl_src, sl_src->sl_s_sources);
    return 0;
}

int cm_source(struct source_list *sl_src, int s_num)
{
    // TODO - need test.
    if (geteuid() != 0) return ACCESS_DENIED;
    if (s_num > sl_src->sl_s_sources) return -1;

    char *old = sl_src->sl_sources[s_num].s_content;
    char *new = (char *) malloc(sizeof(char) * strlen(old) + 2);

    strcpy(new, "#"); // add the comment symbol.
    strcat(new, old);

    // replace.
    sl_src->sl_sources[s_num].s_content = new;
    free(old);

    /*for (int i = 0; i < sl_src->sl_s_sources; i++)
    {
        printf("%s\n", sl_src->sl_sources[i].s_content);
    }*/
    // make the chagnes absolute.
    save_changes(sl_src, sl_src->sl_s_sources);
    return 0;
}

int ucm_source(struct source_list *sl_src, int s_num)
{
    // TODO - need test.
    if (geteuid() != 0) return ACCESS_DENIED;
    if (s_num > sl_src->sl_s_comments) return -1;

    char *old = sl_src->sl_comments[s_num].s_content;
    char *new = (char *) malloc(sizeof(char) * strlen(old));

    strcpy(new, (++old));

    // replace.
    sl_src->sl_comments[s_num].s_content = new;
    free(old);

    // make the chagnes absolute.
    save_changes(sl_src, sl_src->sl_s_comments);
    return 0;
}
