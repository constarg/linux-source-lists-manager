#ifdef linux

#include "io_m.h"
#include "source_m.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

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
        if (NULL == argv[2]) {
            if (-1 == open_source_list(&list, SOURCE_LIST)) return -1; // TODO - error.
        } else {
            if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
            if (-1 == open_source_list(&list, argv[2])) return -1; // TODO - error and check if the given source is in source.d directory.
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
        if (NULL == argv[2]) {
            if (-1 == open_source_list(&list, SOURCE_LIST)) return -1; // TODO - error.
        } else {
            if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
            if (-1 == open_source_list(&list, argv[2])) return -1; // TODO - error and check if the given source is in source.d directory.
        } 
        // Display the sources.
        printf("[*] ---- Comments ---- [*]\n\n");
        for (int i = 0; 
             i < list.sl_s_comments; i++) {
            printf("[%d] -> %s\n", i, list.sl_comments[i].s_content);
        }
        close_source_list(&list);

    } else if (!strcmp(argv[1], "--add-source")) {
        /**
         * Add a new source in a specific source file.
         * Default action, add the given source in /etc/apt/sources.list
         * Otherwise add the new source in the given path.
         */
        struct source new_source;
        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            if (NULL == argv[3]) {
                if (-1 == open_source_list(&list, SOURCE_LIST)) return -1; // TODO - error.
                new_source.s_content = (char *) malloc(sizeof(char) *
                                                       strlen(argv[2]) + 2);
                if (NULL == new_source.s_content) return -1;

                strcpy(new_source.s_content, argv[2]);
            } else {
                if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
                if (-1 == open_source_list(&list, argv[2])) return -1;
                new_source.s_content = (char *) malloc(sizeof(char) *
                                                       strlen(argv[3]) + 2);
                if (NULL == new_source.s_content) return -1;

                strcpy(new_source.s_content, argv[3]);
            }
        }
        strcat(new_source.s_content, "\n"); // ensure that the new source let one or more lines.

        int err = add_source(&list, new_source);
        if (err == ACCESS_DENIED) printf("[*] This action require root access.");
        else if (err == -1) return -1;

        free(new_source.s_content);
        close_source_list(&list);
    
    } else if (!strcmp(argv[1], "--remove-source")) {
        /**
         * Remove a source from a specific source file.
         * Default action, remove the source in the specific number in /etc/apt/sources.list
         * Otherwise remove the the source in given path.
         */

        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            int num = 0;
            errno = 0;
            if (NULL == argv[3]) {
                if (-1 == open_source_list(&list, SOURCE_LIST)) return -1;
                num = atoi(argv[2]);
            } else {
                if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
                if (-1 == open_source_list(&list, argv[2])) return -1;
                num = atoi(argv[3]);
            }
            if (errno != 0) return -1;

            int err = rm_source(&list, num);
            if (ACCESS_DENIED == err) printf("[*] This action require root access.");
            else if (err == -1) return -1;
            close_source_list(&list);
        }
    } else if (!strcmp(argv[1], "--comment-source")) {
        /**
         * comment a source from a specific source file.
         * Default action, comment the source in the specific number in /etc/apt/sources.list
         * Otherwise comment the the source in given path.
         */
        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            int num = 0;
            errno = 0;
            if (NULL == argv[3]) {
                if (-1 == open_source_list(&list, SOURCE_LIST)) return -1;
                num = atoi(argv[2]);
            } else {
                if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
                if (-1 == open_source_list(&list, argv[2])) return -1;
                num = atoi(argv[3]);
            }
            if (errno != 0) return -1;

            int err = cm_source(&list, num);
            if (ACCESS_DENIED == err) printf("[*] This action require root access.");
            else if (-1 == err) return -1;
            close_source_list(&list);
        }
    } else if (!strcmp(argv[1], "--uncomment-source")) {
        /**
         * uncomment a source from a specific source file.
         * Default action, uncomment the source in the specific number in /etc/apt/sources.list
         * Otherwise uncomment the the source in given path.
         */
        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            int num = 0;
            errno = 0;
            if (NULL == argv[3]) {
                if (-1 == open_source_list(&list, SOURCE_LIST)) return -1;
                num = atoi(argv[2]);
            } else {
                if (NULL == strstr(argv[2], SOURCE_LIST_D)) return -1;
                if (-1 == open_source_list(&list, argv[2])) return -1;
                num = atoi(argv[3]);
            }
            if (errno != 0) return -1;

            int err = ucm_source(&list, num);
            if (ACCESS_DENIED == err) printf("[*] This action require root access.");
            else if (-1 == err) return -1;
            close_source_list(&list);
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
        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            if (-1 == create_source_file(argv[2])) return -1;
        }
    } else if (!strcmp(argv[1], "--remove-source-list")) {
        if (NULL == argv[2]) return 0; // TODO - error.
        else {
            if (-1 == remove_source_file(argv[2])) return -1;
        }
    /*} else if (!strcmp(argv[1], "--undo")) {
        // TODO - undo the previous action, using an temporary backup. TODO - maybe add this feature later.*/
    } else {
        printf(HELP_MSG);
    }

#else
    printf("The oparating system is not supported.");
#endif

    return 0;
}
