#include "io_m.h"
#include "source_m.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct source_list test;
    init_sl(&test);

    if (argv[0] == NULL) return -1;
    if (argv[1] == NULL) return -1; // TODO - print help message.
    if (!strcmp(argv[1], "--show-sources"))
    {
        if (argv[2] == NULL) 
        {
            // TODO - default action of show-sources, print the source.list on /etc/apt/
        } else 
        {
            // TODO - show the sources that described in argv[2].
        }
    } else if (!strcmp(argv[1], "--add-source")) 
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL)
            {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--remove-source"))
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL)
            {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--replace-source"))
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL)
            {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--search-source"))
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL)
            {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--show-source-lists"))
    {
        // TODO - print all source list files. on /etc/apt/source.list and on /etc/apt/source.d/*
    } else if (!strcmp(argv[1], "--create-source-list"))
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - create a new file in /etc/apt/source.d/
        }
    } else if (!strcmp(argv[1], "--remove-source-list"))
    {
        if (argv[2] == NULL) return 0; // TODO - error.
        else
        {
            // TODO - remove the source file.
            // TODO - CAUTION do not allow to remove the /etc/apt/source.list for any reason, or at least give warning message.
        }
    } else
    {
        // TODO - error wrong command.
    }

    open_source_list(&test, "/etc/apt/sources.list");

    close_source_list(&test);
}
