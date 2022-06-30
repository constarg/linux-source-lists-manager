#include "io_m.h"

#include <stdio.h>

int main()
{
    char **test = NULL;

    test = open_source_files_d();

    char *file_c = NULL;
    int error = read_source_file(&file_c, test[0]);

    free(file_c);

    // TODO - Make a parser to recognize comments # in source files.
    // TODO - Append or comment or delete a source.

    close_source_files_d(test);
}
