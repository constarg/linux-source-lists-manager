#ifndef SOURCE_INFO
#define SOURCE_INFO

#define SOURCE_LIST     "/etc/apt/sources.list"
#define SOURCE_LIST_D   "/etc/apt/sources.list.d/"

#define HELP_MSG "Usage: source-manager [OPTION]...\n\n"                                                                                                                                    \
                 "\t--show-sources [source file], Display all the sources of one souce file. If no file specified, /etc/apt/sources.list sources will be displayed.\n"                 \
                 "\t--show-comments [source file], Display all the comments of one source file. If no file specified, /etc/apt/sources.list comments will be displayed.\n"              \
                 "\t--add-source [source file] [new source], Add a new source in a specific source file. If no file specified, the new source stored at the end of /etc/apt/sources.list\n"  \
                 "\t--remove-source [source file] [row], Remove a source,in [row], from a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be removed.\n"  \
                 "\t--comment-source [source file] [row], Comments the source, in [row], of a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be commented.\n" \
                 "\t--uncomment-source [source file] [row], Uncomments the source, in [row], of a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be uncommentd.\n" \
                 "\t--show-source-lists, Display all the source lists that exists in the system's two directories 1) /etc/apt 2) /etc/apt/sources.d.\n" \
                 "\t--create-source-list [source list], Create a new source list inside the /etc/apt/sources.d folder.\n" \
                 "\t--remove-source-list [source list], Remove a source list from the /etc/apt/sources.d\n\n" 
#endif
