
#include <ctype.h>
#include <string.h>
#include "iso9660.h"

// CD-ROM size for 2KiB of data
static const int CONTEXTISO_CDROM_SIZE = 358400;

/**
 * Hard-coded offsets
 */
static const int PRIMARY_DESCRIPTOR_OFFSET          = 0x8000;
static const int SECONDARY_DESCRIPTOR_OFFSET        = 0x8800;
static const int SECONDARY_DIRECTORY_RECORD_OFFSET  = 0xB800;
static const int CONTENTS_OFFSET                    = 0xC000;

/**
 * Update a long in ISO9660 pivot-endian representation
 */
void isosetl( int x, unsigned char buffer[]) {
    buffer[0] =  x        & 0xFF;
    buffer[1] = (x >>  8) & 0xFF;
    buffer[2] = (x >> 16) & 0xFF;
    buffer[3] = (x >> 24) & 0xFF;
    buffer[4] = (x >> 24) & 0xFF;
    buffer[5] = (x >> 16) & 0xFF;
    buffer[6] = (x >>  8) & 0xFF;
    buffer[7] =  x        & 0xFF;
}

/**
 * Generate a CD-ROM ISO buffer compatible with the ISO9660 (CDFS) filesystem
 * (Using reference from: http://users.telenet.be/it3.consultants.bvba/handouts/ISO9960.html)
 */
char * build_simple_cdrom( const char * volume_id, const char * filename, const char * buffer, int size ) {
    
    // Local variables
    static char bytes[CONTEXTISO_CDROM_SIZE];
    iso_primary_descriptor  descPrimary;
    iso_directory_record    descFile;
    int i;
    
    // Copy defaults to the primary sector descriptor
    memcpy(&descPrimary, &ISO9660_PRIMARY_DESCRIPTOR, sizeof(descPrimary));
    
    // Update volume_id on the primary sector
    int lVol = strlen(volume_id);
    if (lVol > 31) lVol=31;
    memset(&descPrimary.volume_id, 0x20, 31);
    memcpy(&descPrimary.volume_id, volume_id, lVol);
    
    // Calculate the volume size
    // (For now just limit to 2048)
    int lDataSize = size;
    if (lDataSize>2048) lDataSize=2048;
    //We should actually do something like:
    //int lVolSize = 1 + ((lDataSize - 1) / 2048);
    //isosetl(lVolSize, descPrimary.volume_space_size);
    
    // Copy defaults to CONTEXT.SH record
    memcpy(&descFile, &ISO9660_CONTEXT_SH_STRUCT[0x44], sizeof(descFile));
    
    // Update CONTEXT.SH record
    isosetl(lDataSize, descFile.size);      // <-- File size
    i=0; for (;i<strlen(filename);i++) {    // <-- File name
        if (i>=12) break;
        char c = toupper(filename[i]);
        if (c==' ') c='_';
        descFile.name[i]=c;
    }
    descFile.name[i]=';';  // Add file revision (;1)
    descFile.name[i+1]='1';
    
    // Compose the CD-ROM Disk buffer
    memset(&bytes,0,CONTEXTISO_CDROM_SIZE);
    memcpy(&bytes[PRIMARY_DESCRIPTOR_OFFSET],           &descPrimary,               sizeof(descPrimary));
    memcpy(&bytes[SECONDARY_DESCRIPTOR_OFFSET],         &ISO9660_SECONDARY,         sizeof(ISO9660_SECONDARY));
    memcpy(&bytes[SECONDARY_DIRECTORY_RECORD_OFFSET],   &ISO9660_CONTEXT_SH_STRUCT, sizeof(ISO9660_CONTEXT_SH_STRUCT));
    memcpy(&bytes[SECONDARY_DIRECTORY_RECORD_OFFSET+68],&descFile,                  sizeof(descFile));
    memcpy(&bytes[CONTENTS_OFFSET],                     buffer,                     lDataSize);
    
    // Return the built buffer
    return bytes;
}
