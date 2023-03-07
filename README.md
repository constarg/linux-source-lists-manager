# linux-source-lists-manager

The source list manager is a powerful terminal-based tool that manages the source files that are located in /etc/apt/sources.list and any other source list that may exist in /etc/apt/sources.d. 


# Download & Build

First download the program from GitHub and go to the simple-reverse-shell folder.

```
% git clone https://github.com/EmbeddedCat/linux-source-lists-manager.git
% cd linux-source-lists-manager/
```

After installation the program must be built. In order to build the program, the following instruction must be
followed.<br>

```
% make
```

# Usage
```
Usage: source-manager [OPTION]...

	--show-sources [source file],             Display all the sources of one souce file. If no file specified, /etc/apt/sources.list sources will be displayed.
	--show-coments [source file],             Display all the comments of one source file. If no file specified, /etc/apt/sources.list comments will be displayed.
	--add-source [source file] [new source],  Add a new source in a specific source file. If no file specified, the new source stored at the end of /etc/apt/sources.list
	--remove-source [source file] [row],      Remove a source,in [row], from a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be removed.
	--comment-source [source file] [row],     Commants the source, in [row], of a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be commented.
	--uncomment-source [source file] [row],   Uncomments the source, in [row], of a specific source file. If no file specified the source in the [row] of /etc/apt/sources.list will be uncommentd.
	--show-source-lists,                      Display all the source lists that exists in the system's two directories 1) /etc/apt 2) /etc/apt/sources.d.
	--create-source-list,                     Create a new source list inside the /etc/apt/sources.d folder.
	--remove-source-list,                     Remove a source list from the /etc/apt/sources.d```
