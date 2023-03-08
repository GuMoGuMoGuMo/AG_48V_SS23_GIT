#ifndef RTW_HEADER_Erregerstrom_Regelung_h_
#define RTW_HEADER_Erregerstrom_Regelung_h_
#ifndef Erregerstrom_Regelung_COMMON_INCLUDES_
#define Erregerstrom_Regelung_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#include "nesl_rtw.h"
#include "Erregerstrom_Regelung_8db03944_1_gateway.h"
#endif
#include "Erregerstrom_Regelung_types.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME Erregerstrom_Regelung
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (15) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (1)   
#elif NCSTATES != 1
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T l2yxtgd5ue ; real_T an5kgllrrd ; real_T o2elcg3xq5 ;
real_T nas2rebxjp ; real_T g30amokcxz ; real_T pcegtoga1k [ 2 ] ; real_T
bcae5cddmf ; real_T fdx3exdy5g ; real_T otrfhi2jef ; real_T orw15ospbe [ 4 ]
; real_T kmruurvswl [ 9 ] ; real_T nwsf4t2iom ; real_T gncjlmrb1o ; } B ;
typedef struct { real_T ehy1wkofia ; real_T adkeh0nooq ; real_T fwtjvjlo5d ;
real_T eoikp5p4om ; real_T ormsaahnoz [ 2 ] ; real_T bxjovwinxp [ 5 ] ;
real_T nnuqctfxxy ; void * mktnnal2dg ; void * oqc03anz5y ; void * ccsnt40ngz
; void * fuahg5lro5 ; void * mcirybw2xq ; void * e3a1wv3ben ; void *
ivgcjyejwx ; void * osj2f4u0da ; void * bp44salpou ; void * knyviryudv ;
struct { void * LoggedData [ 6 ] ; } nyf0ujggbb ; int_T cm0cbljfgw [ 3 ] ;
int_T lkw4xdculs ; int_T avfzldlkvq ; boolean_T diguumcgnb ; boolean_T
i4btsdgjgc ; boolean_T nsr0cymo53 ; boolean_T ffdrcaowl3 ; } DW ; typedef
struct { real_T k5px2lav4s ; } X ; typedef struct { real_T k5px2lav4s ; }
XDot ; typedef struct { boolean_T k5px2lav4s ; } XDis ; typedef struct {
real_T k5px2lav4s ; } CStateAbsTol ; typedef struct { real_T k5px2lav4s ; }
CXPtMin ; typedef struct { real_T k5px2lav4s ; } CXPtMax ; typedef struct {
real_T ip4nidmzfe ; real_T ovv3yg3gdv ; real_T mz53zgcaby ; real_T jxremjdu1o
; } ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ;
struct P_ { real_T I_Erregung_MAX ; real_T PWM_FREQUENCY ; real_T
Carriercounter_CarrCount ; real_T PIDController_I ; real_T
PIDController_InitialConditionForIntegrator ; real_T PIDController_P ; real_T
Carriercounter_Range ; real_T PWMGenerator_Tdelay ; real_T
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue ;
real_T IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue
; real_T IntegratorwithWrappedStateDiscreteorContinuous_x0 ; real_T
Constant_Value ; real_T Step_Time ; real_T Step_Y0 ; real_T Step_YFinal ;
real_T UnitDelay_InitialCondition ; real_T Integrator_gainval ; real_T
Integrator_gainval_l1xzho0ept ; real_T Constant2_Value ; real_T
Integrator_gainval_fr0wjrfryx ; real_T Constant2_Value_plmatbfhrk ; real_T
Saturation_UpperSat ; real_T Saturation_LowerSat ; real_T Constant3_Value ; }
; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X
rtX ; extern DW rtDW ; extern P rtP ; extern mxArray *
mr_Erregerstrom_Regelung_GetDWork ( ) ; extern void
mr_Erregerstrom_Regelung_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_Erregerstrom_Regelung_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * Erregerstrom_Regelung_GetCAPIStaticMap (
void ) ; extern SimStruct * const rtS ; extern const int_T gblNumToFiles ;
extern const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern const
int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
