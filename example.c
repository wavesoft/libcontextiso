
#include <string.h>
#include <iostream>
using namespace std;

// Include the contextiso header
#include "include/contextiso.h"

// Usage example of libcontextiso
int main() {

    // The contents of the contextualization file
    const char * data = "EC2_USER_DATA=\"W2FtaWNvbmZpZ10KcGx1Z2lucyA9IGNlcm52bQoKW2Nlcm52bV0KY29udGV4dHVhbGl6YXRpb25fa2V5PWM3ZGUzNmIyOTUwZTQzYThhOGExZWMxNmJjMDRhZWU4CmVudmlyb25tZW50PVVTRVIyPXRlc3QyCgo=\"\nONE_CONTEXT_PATH=\"/var/lib/amiconfig\"\n";

    // Build a CD-ROM image with the given context.sh
    char * cdrom = build_simple_cdrom(
        "CONFIGDISK", 
        "CONTEXT.SH",
        data,
        strlen(data)
        );
    
    // Dump the results to stdout
    cout.write(cdrom, CONTEXTISO_CDROM_SIZE);
    
    // Success
    return 0;
}
