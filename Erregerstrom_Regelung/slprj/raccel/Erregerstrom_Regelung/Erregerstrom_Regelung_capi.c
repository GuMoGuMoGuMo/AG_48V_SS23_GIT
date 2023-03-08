#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "Erregerstrom_Regelung_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "Erregerstrom_Regelung.h"
#include "Erregerstrom_Regelung_capi.h"
#include "Erregerstrom_Regelung_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/Gain" ) , TARGET_STRING ( "DC" ) , 0 , 0 , 0 , 0 , 0 }
, { 1 , 0 , TARGET_STRING ( "Erregerstrom_Regelung/Step" ) , TARGET_STRING (
"i_soll_erregung" ) , 0 , 0 , 0 , 0 , 1 } , { 2 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/Sum" ) , TARGET_STRING ( "i_error_erregung" ) , 0 , 0
, 0 , 0 , 1 } , { 3 , 0 , TARGET_STRING ( "Erregerstrom_Regelung/Unit Delay"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 4 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Data Type Conversion2" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 5 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/PS-Simulink Converter/EVAL_KEY/RESHAPE" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 6 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/Solver Configuration/EVAL_KEY/INPUT_1_1_1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 1 , 0 , 2 } , { 7 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/Solver Configuration/EVAL_KEY/STATE_1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 2 , 0 , 2 } , { 8 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/PID Controller/I Gain/Internal Parameters/Integral Gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 9 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/PID Controller/Sum/Sum_PI/Sum" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 10 , 0 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/scale/Probe" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 3 , 0 , 0 } , { 11 , 0 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)/Discrete/Initial"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 12 , 0 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)1/Discrete/Initial"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL
) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 13 , TARGET_STRING (
"Erregerstrom_Regelung/PID Controller" ) , TARGET_STRING ( "P" ) , 0 , 0 , 0
} , { 14 , TARGET_STRING ( "Erregerstrom_Regelung/PID Controller" ) ,
TARGET_STRING ( "I" ) , 0 , 0 , 0 } , { 15 , TARGET_STRING (
"Erregerstrom_Regelung/PID Controller" ) , TARGET_STRING (
"InitialConditionForIntegrator" ) , 0 , 0 , 0 } , { 16 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator" ) , TARGET_STRING ( "Tdelay" ) , 0 , 0
, 0 } , { 17 , TARGET_STRING ( "Erregerstrom_Regelung/Step" ) , TARGET_STRING
( "Time" ) , 0 , 0 , 0 } , { 18 , TARGET_STRING (
"Erregerstrom_Regelung/Step" ) , TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , {
19 , TARGET_STRING ( "Erregerstrom_Regelung/Step" ) , TARGET_STRING ( "After"
) , 0 , 0 , 0 } , { 20 , TARGET_STRING ( "Erregerstrom_Regelung/Unit Delay" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 21 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter" ) , TARGET_STRING (
"CarrCount" ) , 0 , 0 , 0 } , { 22 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter" ) , TARGET_STRING (
"Range" ) , 0 , 0 , 0 } , { 23 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 24 ,
TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)"
) , TARGET_STRING ( "x0" ) , 0 , 0 , 0 } , { 25 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)1"
) , TARGET_STRING ( "WrappedStateLowerValue" ) , 0 , 0 , 0 } , { 26 ,
TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/Constant3" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/Saturation" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 29 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Compare To Zero/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 30 , TARGET_STRING (
"Erregerstrom_Regelung/PID Controller/Integrator/Discrete/Integrator" ) ,
TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 31 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/Limitation/Constant2" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING (
"Erregerstrom_Regelung/PWM Generator/Carrier counter/Limitation1/Constant2" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 33 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)/Discrete/Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 34 , TARGET_STRING (
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with Wrapped State (Discrete or Continuous)1/Discrete/Integrator"
) , TARGET_STRING ( "gainval" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0
, 0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 35 , TARGET_STRING (
"I_Erregung_MAX" ) , 0 , 0 , 0 } , { 36 , TARGET_STRING ( "PWM_FREQUENCY" ) ,
0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . g30amokcxz , & rtB . l2yxtgd5ue ,
& rtB . o2elcg3xq5 , & rtB . an5kgllrrd , & rtB . otrfhi2jef , & rtB .
nwsf4t2iom , & rtB . orw15ospbe [ 0 ] , & rtB . kmruurvswl [ 0 ] , & rtB .
gncjlmrb1o , & rtB . nas2rebxjp , & rtB . pcegtoga1k [ 0 ] , & rtB .
bcae5cddmf , & rtB . fdx3exdy5g , & rtP . PIDController_P , & rtP .
PIDController_I , & rtP . PIDController_InitialConditionForIntegrator , & rtP
. PWMGenerator_Tdelay , & rtP . Step_Time , & rtP . Step_Y0 , & rtP .
Step_YFinal , & rtP . UnitDelay_InitialCondition , & rtP .
Carriercounter_CarrCount , & rtP . Carriercounter_Range , & rtP .
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue , & rtP
. IntegratorwithWrappedStateDiscreteorContinuous_x0 , & rtP .
IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue , &
rtP . Constant3_Value , & rtP . Saturation_UpperSat , & rtP .
Saturation_LowerSat , & rtP . Constant_Value , & rtP . Integrator_gainval , &
rtP . Constant2_Value , & rtP . Constant2_Value_plmatbfhrk , & rtP .
Integrator_gainval_l1xzho0ept , & rtP . Integrator_gainval_fr0wjrfryx , & rtP
. I_Erregung_MAX , & rtP . PWM_FREQUENCY , } ; static int32_T *
rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } }
;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 4 , 1 , 9 , 1 , 2 , 1 } ;
static const real_T rtcapiStoredFloats [ ] = { 5.0E-5 , 0.0 , 1.0 } ; static
const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , (
int8_T ) 2 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ]
, ( const void * ) & rtcapiStoredFloats [ 2 ] , ( int8_T ) 1 , ( uint8_T ) 0
} , { ( const void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( int8_T ) 0 , ( uint8_T ) 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 13 ,
rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 22 ,
rtModelParameters , 2 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 3851719436U , 2861185918U , 367813115U , 687899069U } , ( NULL ) , 0 , (
boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * Erregerstrom_Regelung_GetCAPIStaticMap (
void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void Erregerstrom_Regelung_InitializeDataMapInfo ( void ) {
rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ;
rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi ,
rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr )
. mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi
, ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi ,
0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void Erregerstrom_Regelung_host_InitializeDataMapInfo (
Erregerstrom_Regelung_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
