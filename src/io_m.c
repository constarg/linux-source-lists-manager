#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "io_m.h"

#define SOURCE_LIST     "/etc/apt/sources.list"
#define SOURCE_LIST_D   "/etc/apt/sources.list.d/"


char **open_source_files_d()
{
    size_t ini_s = 5;
    DIR *dir = NULL;
    struct dirent *sources = NULL;

    // open directory.
    dir = opendir(SOURCE_LIST_D);
    if (dir == NULL) return NULL;

    // the files.
    char **files = (char **) malloc(sizeof(char *) * ini_s);
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
                ini_s += 5;
                files = (char **) realloc(files, sizeof(char *) * ini_s);
                tmp = files + index - 1; // set the tmp again in the right position.
                if (files == NULL) return NULL;
            }
        }
    }
    *(tmp + 1) = NULL;

    closedir(dir);
    return (char **) realloc(files, sizeof(char *) * (index + 1)); // reduce the memory to the absolute size of the array.
}

int read_source_file(char **dst, const char *path)
{
    int fd = open(path, O_RDONLY);
    int stat_err = 0;
    int dst_err = 0;
    int read_err = 0;
    if (fd == -1) return -1;

    // get the size of the file.
    struct stat stat_buff;
    stat_err = lstat(path, &stat_buff);
    // allocate space for the incoming file.
    (*dst) = (char *) malloc(sizeof(char) * stat_buff.st_size);
    dst_err = (dst == NULL)? -1 : 0;

    // read file.
    read_err = read(fd, *dst, stat_buff.st_size);

    if (stat_err == -1 || dst_err == -1 
        || read_err == -1)
    {
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int write_source_file(const char *src, const char *path)
{
    return 0;
}
