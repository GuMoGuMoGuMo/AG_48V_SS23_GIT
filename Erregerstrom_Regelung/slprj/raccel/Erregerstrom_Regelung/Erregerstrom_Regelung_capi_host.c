#include "Erregerstrom_Regelung_capi_host.h"
static Erregerstrom_Regelung_host_DataMapInfo_T root;
static int initialized = 0;
rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        Erregerstrom_Regelung_host_InitializeDataMapInfo(&(root), "Erregerstrom_Regelung");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}
