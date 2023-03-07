#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "io_m.h"
#include "config.h"


sl_dir open_source_files_d()
{
    size_t s_ini = 5;
    DIR *dir = NULL;
    struct dirent *sources = NULL;

    // open directory.
    dir = opendir(SOURCE_LIST_D);
    if (NULL == dir) return NULL;

    // the files.
    char **files = (char **) malloc(sizeof(char *) * s_ini);
    if (NULL == files) return NULL;

    char **tmp = files;
    (*tmp) = (char *) malloc(sizeof(char) * strlen(SOURCE_LIST) + 1);
    if (NULL == *tmp) return NULL;

    strcpy(*tmp, SOURCE_LIST);

    int index = 1; 
    // try to open directory.
    // O(n) - complexity, where n = amount of source files. TODO - can be better than O(n)?
    while ((sources = readdir(dir)) != NULL) {
        // if it's a file.
        if (DT_REG == sources->d_type)  {

            *(tmp + 1) = (char *) malloc(sizeof(char) * strlen(sources->d_name)
                                                      + strlen(SOURCE_LIST_D) + 1);
            if (NULL == (tmp + 1)) return NULL;

            strcpy(*(tmp + 1), SOURCE_LIST_D);
            strcat(*(++tmp), sources->d_name);
            index += 1;

            if (index == s_ini) {
                s_ini += 5;
                files = (char **) realloc(files, sizeof(char *) * s_ini);
                tmp = files + index - 1; // set the tmp again in the right position.
                if (NULL == files) return NULL;
            }
        }
    }
    *(tmp + 1) = NULL;

    closedir(dir);
    return (char **) realloc(files, sizeof(char *) * (index + 1)); // reduce the memory to the absolute size of the array.
}

int append_line(const char *line, const char *path)
{
    int fd = open(path, O_WRONLY | O_APPEND);
    if (-1 == fd) return -1;

    if (-1 == write(fd, line, strlen(line))) return -1;

    close(fd);
    return 0;
}

static int get_line(char **dst, int fd)
{
    char buff = ' ';

    off_t size = 0;
    off_t begin = lseek(fd, 0, SEEK_CUR);
    if (-1 == begin) return -1;

    off_t dist;
    off_t end;
    off_t curr;

    end  = lseek(fd, 0, SEEK_END);
    curr = lseek(fd, begin, SEEK_SET); 
    if (-1 == end || -1 == curr) return -1;

    while (buff != '\n' && curr != end) 
    {
        curr = lseek(fd, 0, SEEK_CUR);
        if (-1 == curr) return -1;
        if (read(fd, &buff, 1) == -1) return -1;
    }
    
    dist = lseek(fd, 0, SEEK_CUR);
    if (-1 == dist) return -1;

    size = (dist - begin);
    if (-1 == lseek(fd, begin, SEEK_SET)) return -1;

    (*dst) = (char *) malloc(sizeof(char) * size + 1);
    memset(*dst, 0x0, sizeof(char) * size);

    if (NULL == (*dst)) return -1;
    // get the line.
    if (-1 == read(fd, (*dst), (size_t) (size - 1))) return -1;

    (*dst)[size] = '\0';

    if (-1 == lseek(fd, dist, SEEK_SET)) return -1;
    if (dist == end) return -1;
    return 0;
}

char **retv_file_lines(const char *path, size_t *sr_lines)
{
    size_t s_lines = 10;
    char *(*lines) = (char **) malloc(sizeof(char *) * s_lines);
    if (NULL == lines) return NULL;

    int fd = open(path, O_RDONLY);
    if (-1 == fd) return NULL;

    int c_line = 0;
    // get lines.
    while (0 == get_line(&lines[c_line], fd)) {
        ++c_line;
        if (c_line == s_lines) {
            s_lines += 10;
            lines = realloc(lines, sizeof(char *) * s_lines);
        }
    }

    *sr_lines = c_line + 1;

    close(fd);
    return (char **) realloc(lines, sizeof(char *) * (c_line + 1));
}
