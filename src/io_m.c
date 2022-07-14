#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "io_m.h"
#include "config.h"


char **open_source_files_d()
{
    size_t s_ini = 5;
    DIR *dir = NULL;
    struct dirent *sources = NULL;

    // open directory.
    dir = opendir(SOURCE_LIST_D);
    if (dir == NULL) return NULL;

    // the files.
    char **files = (char **) malloc(sizeof(char *) * s_ini);
    if (files == NULL) return NULL;

    char **tmp = files;
    (*tmp) = (char *) malloc(sizeof(char) * strlen(SOURCE_LIST) + 1);
    if (*tmp == NULL) return NULL;

    strcpy(*tmp, SOURCE_LIST);

    int index = 1; 
    // try to open directory.
    // O(n) - complexity, where n = amount of source files. TODO - can be better than O(n)?
    while ((sources = readdir(dir)) != NULL)
    {
        // if it's a file.
        if (sources->d_type == DT_REG)
        {

            *(tmp + 1) = (char *) malloc(sizeof(char) * strlen(sources->d_name)
                                                      + strlen(SOURCE_LIST_D) + 1);
            if ((tmp + 1) == NULL) return NULL;

            strcpy(*(tmp + 1), SOURCE_LIST_D);
            strcat(*(++tmp), sources->d_name);
            index += 1;

            if (index == ini_s)
            {
                s_ini += 5;
                files = (char **) realloc(files, sizeof(char *) * s_ini);
                tmp = files + index - 1; // set the tmp again in the right position.
                if (files == NULL) return NULL;
            }
        }
    }
    *(tmp + 1) = NULL;

    closedir(dir);
    return (char **) realloc(files, sizeof(char *) * (index + 1)); // reduce the memory to the absolute size of the array.
}

int write_append_line(char *line, const char *path)
{
    return 0;
}


static int get_line(char *dst, int fd)
{
    char buff = '\0';
    size_t size = 0;
    off_t begin = lseek(fd, 0, SEEK_CUR);
    if (begin == -1) return -1;

    off_t dist;

    while (buff != '\n' && buff != '\0')
    {
        if (read(fd, &buff, 1) == -1) return -1;
        dist = lseek(fd, 1, SEEK_CUR);
        if (dist == -1) return -1;
        ++size;
    }
    if (buff == '\0' && size == 1) return 1;

    size = (dist - begin);
    if (lseek(fd, begin, SEEK_SET) == -1) return -1;

    dst = malloc(sizeof(char) * size + 1);
    if (dst == NULL) return -1;
    // get the line.
    if (read(fd, line, size) == -1) return -1;
    dst[size] = '\0';

    return 0;
}

char **retv_file_lines(const char *path, size_t *lines_s)
{
    size_t s_lines = 10;
    char *(*lines) = (char *) malloc(sizeof(char *) * s_lines); 
    if (lines == NULL) return NULL;

    int c_line = 0;
    // get lines.
    while (get_line(lines[c_line], fd) == 0)
    {
        ++c_line;
        if (c_line == s_lines)
        {
            s_lines += 10;
            lines = realloc(lines, sizeof(char *) * s_lines);
        }
    }
    // TODO - Test this function.
    return realloc(lines, sizeof(char *) * (c_line + 1));
}
