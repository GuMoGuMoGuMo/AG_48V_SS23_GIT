#include "Erregerstrom_Regelung_acc.h"
#include "mwmathutil.h"
#include "rtwtypes.h"
#include "Erregerstrom_Regelung_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T
* * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( void * S , void * diag ) { SimStruct * castedS = (
SimStruct * ) S ; if ( ! _ssIsErrorStatusAslErrMsg ( castedS ) ) {
_ssSet_slErrMsg ( castedS , diag ) ; } else { _ssDiscardDiagnostic ( castedS
, diag ) ; } } void rt_ssReportDiagnosticAsWarning ( void * S , void * diag )
{ _ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_2_23_0 ;
B_Erregerstrom_Regelung_T * _rtB ; DW_Erregerstrom_Regelung_T * _rtDW ;
P_Erregerstrom_Regelung_T * _rtP ; real_T rtb_B_2_25_0 ; real_T rtb_B_2_3_0 ;
int32_T isHit ; _rtDW = ( ( DW_Erregerstrom_Regelung_T * ) ssGetRootDWork ( S
) ) ; _rtP = ( ( P_Erregerstrom_Regelung_T * ) ssGetModelRtp ( S ) ) ; _rtB =
( ( B_Erregerstrom_Regelung_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step_MODE = (
ssGetTaskTime ( S , 1 ) >= _rtP -> P_3 ) ; if ( _rtDW -> Step_MODE == 1 ) {
_rtB -> B_2_0_0 = _rtP -> P_5 ; } else { _rtB -> B_2_0_0 = _rtP -> P_4 ; } }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_2_1_0 =
_rtDW -> UnitDelay_DSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_2_2_0 = _rtB -> B_2_0_0 - _rtB -> B_2_1_0 ;
rtb_B_2_3_0 = _rtP -> P_7 * _rtB -> B_2_2_0 ; } isHit = ssIsSampleHit ( S , 2
, 0 ) ; if ( isHit != 0 ) { _rtB -> B_2_4_0 = _rtDW -> Integrator_DSTATE ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_2_3_0 += _rtB
-> B_2_4_0 ; if ( rtb_B_2_3_0 > _rtP -> P_10 ) { _rtB -> B_2_6_0 = _rtP ->
P_10 ; } else if ( rtb_B_2_3_0 < _rtP -> P_11 ) { _rtB -> B_2_6_0 = _rtP ->
P_11 ; } else { _rtB -> B_2_6_0 = rtb_B_2_3_0 ; } _rtB -> B_2_7_0 = _rtP ->
P_12 * _rtB -> B_2_6_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_2_16_0 = ( ( _rtDW -> Integrator_DSTATE_h < _rtB ->
B_2_0_0_m ) || ( _rtDW -> Integrator_DSTATE_h >= _rtB -> B_2_1_0_c ) ) ; if (
_rtDW -> Initial_FirstOutputTime ) { _rtDW -> Initial_FirstOutputTime = false
; _rtB -> B_2_22_0 = _rtP -> P_18 ; } else { _rtB -> B_2_22_0 = _rtDW ->
Integrator_DSTATE_h - muDoubleScalarFloor ( ( _rtDW -> Integrator_DSTATE_h +
_rtP -> P_15 ) * _rtP -> P_16 ) * _rtP -> P_17 ; } if ( _rtB -> B_2_16_0 ) {
_rtDW -> Integrator_DSTATE_h = _rtB -> B_2_22_0 ; } B_2_23_0 = _rtDW ->
Integrator_DSTATE_h ; rtb_B_2_3_0 = _rtP -> P_14 / ( _rtP -> P_14 - _rtB ->
B_2_11_0 [ 0 ] ) * B_2_23_0 ; rtb_B_2_25_0 = _rtB -> B_2_11_0 [ 0 ] + _rtP ->
P_20 ; _rtB -> B_2_34_0 = ( ( _rtDW -> Integrator_DSTATE_f < _rtB ->
B_2_2_0_k ) || ( _rtDW -> Integrator_DSTATE_f >= _rtB -> B_2_3_0 ) ) ; if (
_rtDW -> Initial_FirstOutputTime_b ) { _rtDW -> Initial_FirstOutputTime_b =
false ; _rtB -> B_2_40_0 = _rtP -> P_26 ; } else { _rtB -> B_2_40_0 = _rtDW
-> Integrator_DSTATE_f - muDoubleScalarFloor ( ( _rtDW -> Integrator_DSTATE_f
+ _rtP -> P_23 ) * _rtP -> P_24 ) * _rtP -> P_25 ; } if ( _rtB -> B_2_34_0 )
{ _rtDW -> Integrator_DSTATE_f = _rtB -> B_2_40_0 ; } switch ( ( int32_T )
_rtP -> P_13 ) { case 1 : rtb_B_2_3_0 -= muDoubleScalarFloor ( rtb_B_2_3_0 /
rtb_B_2_25_0 ) * rtb_B_2_25_0 ; break ; case 2 : rtb_B_2_3_0 = _rtP -> P_21 -
( rtb_B_2_3_0 - muDoubleScalarFloor ( rtb_B_2_3_0 / rtb_B_2_25_0 ) *
rtb_B_2_25_0 ) ; break ; default : rtb_B_2_3_0 = _rtP -> P_29 - _rtDW ->
Integrator_DSTATE_f ; if ( _rtDW -> Integrator_DSTATE_f > _rtP -> P_1 ) {
rtb_B_2_25_0 = _rtP -> P_22 ; } else { rtb_B_2_25_0 = _rtDW ->
Integrator_DSTATE_f ; } if ( rtb_B_2_3_0 > _rtP -> P_0 ) { rtb_B_2_3_0 = _rtP
-> P_28 ; } rtb_B_2_3_0 += rtb_B_2_25_0 ; break ; } rtb_B_2_3_0 *= _rtP ->
P_30 ; if ( rtb_B_2_3_0 > _rtP -> P_31 ) { rtb_B_2_3_0 = _rtP -> P_31 ; }
else if ( rtb_B_2_3_0 < _rtP -> P_32 ) { rtb_B_2_3_0 = _rtP -> P_32 ; } _rtB
-> B_2_53_0 = ( ( _rtB -> B_2_7_0 != Erregerstrom_Regelung_rtC ( S ) ->
B_2_0_0 ) && ( _rtB -> B_2_7_0 >= _rtP -> P_33 * rtb_B_2_3_0 + _rtP -> P_34 )
) ; } _rtB -> B_2_54_0 [ 0 ] = _rtB -> B_2_53_0 ; _rtB -> B_2_54_0 [ 1 ] =
0.0 ; _rtB -> B_2_54_0 [ 2 ] = 0.0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> INPUT_1_1_1_Discrete [ 0 ] = ! ( _rtB -> B_2_54_0 [ 0 ] == _rtDW ->
INPUT_1_1_1_Discrete [ 1 ] ) ; _rtDW -> INPUT_1_1_1_Discrete [ 1 ] = _rtB ->
B_2_54_0 [ 0 ] ; } _rtB -> B_2_54_0 [ 0 ] = _rtDW -> INPUT_1_1_1_Discrete [ 1
] ; _rtB -> B_2_54_0 [ 3 ] = _rtDW -> INPUT_1_1_1_Discrete [ 0 ] ;
ssCallAccelRunBlock ( S , 2 , 55 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 2 , 56 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 2 , 57 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_2_59_0 = _rtP ->
P_35 * _rtB -> B_2_2_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_2_61_0 = _rtP -> P_36 ; } UNUSED_PARAMETER ( tid ) ; }
static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) {
B_Erregerstrom_Regelung_T * _rtB ; P_Erregerstrom_Regelung_T * _rtP ; _rtP =
( ( P_Erregerstrom_Regelung_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Erregerstrom_Regelung_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_2_0_0_m
= _rtP -> P_38 ; _rtB -> B_2_1_0_c = _rtP -> P_39 ; _rtB -> B_2_2_0_k = _rtP
-> P_40 ; _rtB -> B_2_3_0 = _rtP -> P_41 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_Erregerstrom_Regelung_T * _rtB ; DW_Erregerstrom_Regelung_T * _rtDW ;
P_Erregerstrom_Regelung_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_Erregerstrom_Regelung_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_Erregerstrom_Regelung_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Erregerstrom_Regelung_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> UnitDelay_DSTATE =
_rtB -> B_2_56_0 ; _rtDW -> Integrator_DSTATE += _rtP -> P_8 * _rtB ->
B_2_59_0 ; _rtDW -> Integrator_DSTATE_h += _rtP -> P_19 * _rtB -> B_2_61_0 ;
_rtDW -> Integrator_DSTATE_f += _rtP -> P_27 * _rtB -> B_2_61_0 ; }
ssCallAccelRunBlock ( S , 2 , 55 , SS_CALL_MDL_UPDATE ) ; UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { XDot_Erregerstrom_Regelung_T *
_rtXdot ; _rtXdot = ( ( XDot_Erregerstrom_Regelung_T * ) ssGetdX ( S ) ) ;
ssCallAccelRunBlock ( S , 2 , 55 , SS_CALL_MDL_DERIVATIVES ) ; _rtXdot ->
integrator_CSTATE = 0.0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { P_Erregerstrom_Regelung_T *
_rtP ; ZCV_Erregerstrom_Regelung_T * _rtZCSV ; _rtZCSV = ( (
ZCV_Erregerstrom_Regelung_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = (
( P_Erregerstrom_Regelung_T * ) ssGetModelRtp ( S ) ) ; _rtZCSV ->
Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_3 ; ssCallAccelRunBlock ( S , 2 ,
55 , SS_CALL_MDL_ZERO_CROSSINGS ) ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 4085283748U ) ; ssSetChecksumVal
( S , 1 , 3932217331U ) ; ssSetChecksumVal ( S , 2 , 42061960U ) ;
ssSetChecksumVal ( S , 3 , 841562997U ) ; { mxArray * slVerStructMat = ( NULL
) ; mxArray * slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10
] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat ,
"ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField (
slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) { status = 1 ;
} else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.6" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_Erregerstrom_Regelung_T ) ) { static char msg [
256 ] ; sprintf ( msg , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof (
DW_Erregerstrom_Regelung_T ) ) ; ssSetErrorStatus ( S , msg ) ; } if (
ssGetSizeofGlobalBlockIO ( S ) != ( SLSize ) sizeof (
B_Erregerstrom_Regelung_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_Erregerstrom_Regelung_T ) ) ; ssSetErrorStatus ( S , msg ) ; } { int
ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_Erregerstrom_Regelung_T ) ) { static char msg [
256 ] ; sprintf ( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_Erregerstrom_Regelung_T ) ) ; ssSetErrorStatus ( S
, msg ) ; } } _ssSetModelRtp ( S , ( real_T * ) &
Erregerstrom_Regelung_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
Erregerstrom_Regelung_rtInvariant ) ; } static void mdlInitializeSampleTimes
( SimStruct * S ) { slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static
void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
