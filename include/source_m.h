#ifndef SOURCE_MANAGER
#define SOURCE_MANAGER

#include <malloc.h>
#include <memory.h>

struct source 
{
    char *s_content;             // The content of a source ( url ).
};

struct source_list
{
    char *sl_name;               // The source list name.
    char *sl_loc;                // The source list location.
    size_t sl_sources_s;         // The sources number.
    struct source *sl_sources;   // The source list sources.
};


static inline void init_sl(struct source_list *sl)
{
    memset(sl, 0x0, sizeof(struct source_list));
}

static inline void close_source_list(struct source_list *sl_src)
{
    //free(sl_src->sl_name); // TODO - if you make it with malloc uncomment this.
    free(sl_src->sl_loc);
    // free the sources.
    for (int s = 0; 
         s < sl_src->sl_sources_s; s++)
    {
        free(sl_src->sl_sources[s].s_content);
    }
    free(sl_src->sl_sources);
}


/*
 * Retrieves all the informations about a source list.
 *
 * @param sl_dst Where all the informations is going to be saved.
 * @param sl_path The path to the source list.
 * @return 0 on success or -1 on error.
 */
extern int open_source_list(struct source_list *sl_dst, const char *sl_path);

/**
 * Creates a new source list with the informations describes in sl_src.
 *
 * @param sl_src The source list to make.
 * @return 0 on success or -1 on error.
 */
extern int ct_source_list(const struct source_list *sl_src);


/**
 * Remove a source list.
 *
 * @param sl_path The path to the source list to be removed.
 * @return 0 on success or -1 on error.
 */
extern int rm_source_list(const char *sl_path);


/**
 * Add a new source in an existing source list.
 *
 * @param sl_dst The source list to add the source.
 * @param s The source to add.
 * @return 0 on success or -1 on error.
 */
extern int add_source(struct source_list *sl_dst, const struct source s);

/**
 * Rmoeve a source from an existing source list.
 *
 * @param sl_dst The source list to change.
 * @param s_num The number of line that describes the source to be removed.
 * @return 0 on success or -1 on error.
 */
extern int rm_source(struct source_list *sl_dst, int s_num);


/**
 * Comments a source from an existing source list.
 *
 * @param sl_dst The source list to change.
 * @param s_num The source to commemet. Based on line number.
 * @return 0 on success or -1 on error.
 */
extern int cm_source(struct source_list *sl_dst, int s_num);


#endif
