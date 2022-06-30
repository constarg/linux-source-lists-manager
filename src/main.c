#include "io_m.h"

#include <stdio.h>

int main()
{
    char **test = NULL;

    test = open_source_files_d();

    close_source_files_d(test);
}
