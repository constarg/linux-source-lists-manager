#ifdef linux

#include "io_m.h"
#include "source_m.h"
#include "config.h"

#include <stdio.h>
#include <string.h>

#else

#include <stdio.h>

#endif


int main(int argc, char *argv[])
{
#ifdef linux

    struct source_list list;
    init_sl(&list);

    if (argv[0] == NULL) return -1;
    if (argv[1] == NULL) {
        printf(HELP_MSG);
        return 0;
    }
    if (!strcmp(argv[1], "--show-sources")) {
        /**
         * Display all the sources of one source file.
         * Default action, reads the /etc/apt/sources.list
         * Otherwise reads from the argument argv[2].
         */
        if (argv[2] == NULL) {
            if (open_source_list(&list, SOURCE_LIST) == -1) return -1; // TODO - error.
        } else {
            if (open_source_list(&list, argv[2]) == -1) return -1; // TODO - error and check if the given source is in source.d directory.
        } 
        // Display the sources.
        printf("[*] ---- Sources ---- [*]\n\n");
        for (int i = 0; 
             i < list.sl_s_sources; i++) {
            printf("[%d] -> %s\n", i, list.sl_sources[i].s_content);
        }

        close_source_list(&list);
    } else if (!strcmp(argv[1], "--show-comments")) {
        /**
         * Display all the comments of one source file.
         * Default action, reads the /etc/apt/sources.list
         * Otherwise reads from the argument argv[2].
         */
        if (argv[2] == NULL) {
            if (open_source_list(&list, SOURCE_LIST) == -1) return -1; // TODO - error.
        } else {
            if (open_source_list(&list, argv[2]) == -1) return -1; // TODO - error and check if the given source is in source.d directory.
        } 
        // Display the sources.
        printf("[*] ---- Comments ---- [*]\n\n");
        for (int i = 0; 
             i < list.sl_s_comments; i++) {
            printf("[%d] -> %s\n", i, list.sl_comments[i].s_content);
        }

        close_source_list(&list);

    } else if (!strcmp(argv[1], "--add-source")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL) {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--remove-source")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - add the source in argv[2] to the source list to source list if no other location has been given, otherwise to given location.
            if (argv[3] == NULL) {
                // TODO - default
            } else {
                // TODO - given location.
            }
        }
    } else if (!strcmp(argv[1], "--comment-source")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - comment the source in the specific line.
        }
    } else if (!strcmp(argv[1], "--uncomment-source")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - uncomment the source in the specific line.
        }

    } else if (!strcmp(argv[1], "--show-source-lists")) {
        /**
         * Display all the source lists that
         * exists in the system's two directories
         * 1) /etc/apt/ and 2) /etc/apt/sources.d/
         */
        sl_dir source_lists = open_source_files_d();

        printf("[*] ---- Source Lists ---- [*]\n\n");
        for (int sl = 0; 
             source_lists[sl]; sl++) {
            printf("[%d] -> %s\n", sl, source_lists[sl]);
        }

        close_source_files_d(source_lists);
    
    } else if (!strcmp(argv[1], "--create-source-list")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - create a new file in /etc/apt/source.d/
        }
    } else if (!strcmp(argv[1], "--remove-source-list")) {
        if (argv[2] == NULL) return 0; // TODO - error.
        else {
            // TODO - remove the source file.
            // TODO - CAUTION do not allow to remove the /etc/apt/source.list for any reason, or at least give warning message.
        }
    } else if (!strcmp(argv[1], "--undo")) {
        // TODO - undo the previous action, using an temporary backup.
    } else {
        printf(HELP_MSG);
    }

#else
    printf("The oparating system is not supported.");
#endif
}
