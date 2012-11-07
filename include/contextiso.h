
#ifndef CONTEXTISO_H
#define CONTEXTISO_H

// For sizeof()
#include <string.h>

/**
 * Disk size is enough to fit 2KiB of data
 */
static const int CONTEXTISO_CDROM_SIZE = 358400;

/**
 * Create a CD-ROM image that will contain the specified filename with the specified content
 *
 * @param volume        The name of the volume (CD-ROM Label)
 * @param filename      The name fo the file to put in the CD-ROM
 * @param contents      The buffer to copy the file contents from (Maximum 2048 bytes)
 * @param szContents    The size of the buffer
 *
 * @return              Returns the contents of the CD-ROM buffer. The length of the buffer is CONTEXTISO_CDROM_SIZE
 */
char * build_simple_cdrom( const char * volume, const char * filename, const char * contents, int szContents );

/**
 * Generate a contextualization CD-ROM using the specified user_data
 *
 * This function will call build_cd with the appropriate parameters to create a file called CONTEXT.SH with the contents specified
 */
char * build_context_cdrom( const char * user_data ) { return build_simple_cdrom("CONFIGDISK", "CONTEXT.SH", user_data, strlen(user_data)); };

#endif