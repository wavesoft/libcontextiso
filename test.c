
#include <string.h>
#include <iostream>
#include "include/contextiso.h"
using namespace std;

int main() {

    const char * data = "EC2_USER_DATA=\"W2FtaWNvbmZpZ10KcGx1Z2lucyA9IGNlcm52bQoKW2Nlcm52bV0KY29udGV4dHVhbGl6YXRpb25fa2V5PWM3ZGUzNmIyOTUwZTQzYThhOGExZWMxNmJjMDRhZWU4CmVudmlyb25tZW50PVVTRVIyPXRlc3QyCgo=\"\nONE_CONTEXT_PATH=\"/var/lib/amiconfig\"\n";

    // Build a CD-ROM image with the given context.sh
    char * cdrom = build_simple_cdrom(
        "CONFIGDISK", 
        "cONtExtInfO.CONF",
        data,
        strlen(data)
        );
    
    cout.write(cdrom, CONTEXTISO_CDROM_SIZE);
    return 0;
}