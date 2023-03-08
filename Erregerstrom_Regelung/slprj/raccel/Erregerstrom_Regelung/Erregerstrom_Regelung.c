#include "Erregerstrom_Regelung.h"
#include "rtwtypes.h"
#include "mwmathutil.h"
#include <string.h>
#include <stddef.h>
#include "Erregerstrom_Regelung_private.h"
#include "rt_logging_mmi.h"
#include "Erregerstrom_Regelung_capi.h"
#include "Erregerstrom_Regelung_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "10.6 (R2022b) 13-May-2022" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 } ; const char * raccelLoadInputsAndAperiodicHitTimes (
SimStruct * S , const char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ; void MdlInitialize ( void ) { rtDW . ehy1wkofia = rtP .
UnitDelay_InitialCondition ; rtDW . adkeh0nooq = rtP .
PIDController_InitialConditionForIntegrator ; rtDW . fwtjvjlo5d = rtB .
bcae5cddmf ; rtDW . eoikp5p4om = rtB . fdx3exdy5g ; } void MdlStart ( void )
{ CXPtMax * _rtXPerturbMax ; CXPtMin * _rtXPerturbMin ; NeModelParameters
modelParameters ; NeModelParameters modelParameters_p ; NeslSimulationData *
simulationData ; NeslSimulator * tmp ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; NeuDiagnosticTree *
diagnosticTree_e ; NeuDiagnosticTree * diagnosticTree_p ; char * msg ; char *
msg_e ; char * msg_p ; real_T tmp_m [ 4 ] ; real_T time ; real_T tmp_e ;
int32_T tmp_i ; int_T tmp_g [ 2 ] ; boolean_T tmp_p ; boolean_T val ; { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} _rtXPerturbMax = ( ( CXPtMax * ) ssGetJacobianPerturbationBoundsMaxVec (
rtS ) ) ; _rtXPerturbMin = ( ( CXPtMin * )
ssGetJacobianPerturbationBoundsMinVec ( rtS ) ) ; rtB . pcegtoga1k [ 0 ] =
5.0E-5 ; rtB . pcegtoga1k [ 1 ] = 0.0 ; rtB . bcae5cddmf = rtP .
IntegratorwithWrappedStateDiscreteorContinuous_x0 ; rtDW . diguumcgnb = true
; rtB . fdx3exdy5g = rtP . PWMGenerator_Tdelay ; rtDW . i4btsdgjgc = true ;
tmp = nesl_lease_simulator ( "Erregerstrom_Regelung/Solver Configuration_1" ,
0 , 0 ) ; rtDW . mktnnal2dg = ( void * ) tmp ; tmp_p = pointer_is_null ( rtDW
. mktnnal2dg ) ; if ( tmp_p ) { Erregerstrom_Regelung_8db03944_1_gateway ( )
; tmp = nesl_lease_simulator ( "Erregerstrom_Regelung/Solver Configuration_1"
, 0 , 0 ) ; rtDW . mktnnal2dg = ( void * ) tmp ; }
slsaSaveRawMemoryForSimTargetOP ( rtS ,
"Erregerstrom_Regelung/Solver Configuration_100" , ( void * * ) ( & rtDW .
mktnnal2dg ) , 0U * sizeof ( real_T ) , nesl_save_simdata ,
nesl_restore_simdata ) ; simulationData = nesl_create_simulation_data ( ) ;
rtDW . oqc03anz5y = ( void * ) simulationData ; diagnosticManager =
rtw_create_diagnostics ( ) ; rtDW . ccsnt40ngz = ( void * ) diagnosticManager
; modelParameters . mSolverType = NE_SOLVER_TYPE_DAE ; modelParameters .
mSolverAbsTol = 0.001 ; modelParameters . mSolverRelTol = 0.001 ;
modelParameters . mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ;
modelParameters . mStartTime = 0.0 ; modelParameters . mLoadInitialState =
false ; modelParameters . mUseSimState = false ; modelParameters .
mLinTrimCompile = false ; modelParameters . mLoggingMode = SSC_LOGGING_NONE ;
modelParameters . mRTWModifiedTimeStamp = 5.9967475E+8 ; modelParameters .
mZcDisabled = false ; tmp_e = 0.001 ; modelParameters . mSolverTolerance =
tmp_e ; tmp_e = 0.0 ; modelParameters . mFixedStepSize = tmp_e ; tmp_p = true
; modelParameters . mVariableStepSolver = tmp_p ; tmp_p = false ;
modelParameters . mIsUsingODEN = tmp_p ; tmp_p =
slIsRapidAcceleratorSimulating ( ) ; val = ssGetGlobalInitialStatesAvailable
( rtS ) ; if ( tmp_p ) { val = ( val && ssIsFirstInitCond ( rtS ) ) ; }
modelParameters . mLoadInitialState = val ; modelParameters . mZcDisabled =
false ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . ccsnt40ngz ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = nesl_initialize_simulator ( ( NeslSimulator * ) rtDW . mktnnal2dg
, & modelParameters , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp_p =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
simulationData = ( NeslSimulationData * ) rtDW . oqc03anz5y ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 1 ;
simulationData -> mData -> mContStates . mX = & rtX . k5px2lav4s ;
simulationData -> mData -> mDiscStates . mN = 5 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . bxjovwinxp [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
cm0cbljfgw [ 0 ] ; tmp_p = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo
( rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp_p ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS
) ; tmp_p = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U )
; simulationData -> mData -> mIsSolverAssertCheck = tmp_p ; tmp_p =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp_p ; tmp_p = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp_p ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp_p = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp_p ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_g [ 0 ] = 0 ;
tmp_m [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_m [ 1 ] = rtB . orw15ospbe [ 1 ] ;
tmp_m [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_m [ 3 ] = rtB . orw15ospbe [ 3 ] ;
tmp_g [ 1 ] = 4 ; simulationData -> mData -> mInputValues . mN = 4 ;
simulationData -> mData -> mInputValues . mX = & tmp_m [ 0 ] ; simulationData
-> mData -> mInputOffsets . mN = 2 ; simulationData -> mData -> mInputOffsets
. mX = & tmp_g [ 0 ] ; simulationData -> mData -> mNumjacDxLo . mN = 1 ;
simulationData -> mData -> mNumjacDxLo . mX = & _rtXPerturbMin -> k5px2lav4s
; simulationData -> mData -> mNumjacDxHi . mN = 1 ; simulationData -> mData
-> mNumjacDxHi . mX = & _rtXPerturbMax -> k5px2lav4s ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . ccsnt40ngz ; diagnosticTree_p =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
ne_simulator_method ( ( NeslSimulator * ) rtDW . mktnnal2dg ,
NESL_SIM_NUMJAC_DX_BOUNDS , simulationData , diagnosticManager ) ; if ( tmp_i
!= 0 ) { tmp_p = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if (
tmp_p ) { msg_p = rtw_diagnostics_msg ( diagnosticTree_p ) ; ssSetErrorStatus
( rtS , msg_p ) ; } } tmp = nesl_lease_simulator (
"Erregerstrom_Regelung/Solver Configuration_1" , 1 , 0 ) ; rtDW . e3a1wv3ben
= ( void * ) tmp ; tmp_p = pointer_is_null ( rtDW . e3a1wv3ben ) ; if ( tmp_p
) { Erregerstrom_Regelung_8db03944_1_gateway ( ) ; tmp = nesl_lease_simulator
( "Erregerstrom_Regelung/Solver Configuration_1" , 1 , 0 ) ; rtDW .
e3a1wv3ben = ( void * ) tmp ; } slsaSaveRawMemoryForSimTargetOP ( rtS ,
"Erregerstrom_Regelung/Solver Configuration_110" , ( void * * ) ( & rtDW .
e3a1wv3ben ) , 0U * sizeof ( real_T ) , nesl_save_simdata ,
nesl_restore_simdata ) ; simulationData = nesl_create_simulation_data ( ) ;
rtDW . ivgcjyejwx = ( void * ) simulationData ; diagnosticManager =
rtw_create_diagnostics ( ) ; rtDW . osj2f4u0da = ( void * ) diagnosticManager
; modelParameters_p . mSolverType = NE_SOLVER_TYPE_DAE ; modelParameters_p .
mSolverAbsTol = 0.001 ; modelParameters_p . mSolverRelTol = 0.001 ;
modelParameters_p . mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ;
modelParameters_p . mStartTime = 0.0 ; modelParameters_p . mLoadInitialState
= false ; modelParameters_p . mUseSimState = false ; modelParameters_p .
mLinTrimCompile = false ; modelParameters_p . mLoggingMode = SSC_LOGGING_NONE
; modelParameters_p . mRTWModifiedTimeStamp = 5.9967475E+8 ;
modelParameters_p . mZcDisabled = false ; tmp_e = 0.001 ; modelParameters_p .
mSolverTolerance = tmp_e ; tmp_e = 0.0 ; modelParameters_p . mFixedStepSize =
tmp_e ; tmp_p = true ; modelParameters_p . mVariableStepSolver = tmp_p ;
tmp_p = false ; modelParameters_p . mIsUsingODEN = tmp_p ; tmp_p =
slIsRapidAcceleratorSimulating ( ) ; val = ssGetGlobalInitialStatesAvailable
( rtS ) ; if ( tmp_p ) { val = ( val && ssIsFirstInitCond ( rtS ) ) ; }
modelParameters_p . mLoadInitialState = val ; modelParameters_p . mZcDisabled
= false ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . osj2f4u0da ;
diagnosticTree_e = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_i = nesl_initialize_simulator ( ( NeslSimulator * )
rtDW . e3a1wv3ben , & modelParameters_p , diagnosticManager ) ; if ( tmp_i !=
0 ) { tmp_p = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p
) { msg_e = rtw_diagnostics_msg ( diagnosticTree_e ) ; ssSetErrorStatus ( rtS
, msg_e ) ; } } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T
p0lbcytzy3 ; NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; NeuDiagnosticTree *
diagnosticTree_p ; char * msg ; char * msg_p ; real_T tmp_m [ 13 ] ; real_T
tmp_p [ 4 ] ; real_T cji3wpa32t ; real_T dyj34onvff ; real_T hbomglvb20 ;
real_T time ; real_T time_e ; real_T time_i ; real_T time_p ; int32_T tmp_i ;
int_T tmp_g [ 3 ] ; int_T tmp_e [ 2 ] ; boolean_T tmp ; if ( ssIsSampleHit (
rtS , 2 , 0 ) ) { rtB . an5kgllrrd = rtDW . ehy1wkofia ; } if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { rtDW . avfzldlkvq = ( ssGetTaskTime ( rtS , 1 ) >= rtP .
Step_Time ) ; if ( rtDW . avfzldlkvq == 1 ) { rtB . l2yxtgd5ue = rtP .
Step_YFinal ; } else { rtB . l2yxtgd5ue = rtP . Step_Y0 ; } rtB . o2elcg3xq5
= rtB . l2yxtgd5ue - rtB . an5kgllrrd ; } if ( ssIsSampleHit ( rtS , 2 , 0 )
) { rtB . nas2rebxjp = rtP . PIDController_P * rtB . o2elcg3xq5 + rtDW .
adkeh0nooq ; rtB . g30amokcxz = 1.0 / rtP . I_Erregung_MAX * rtB . nas2rebxjp
; if ( rtDW . diguumcgnb ) { rtDW . diguumcgnb = false ; rtB . bcae5cddmf =
rtP . IntegratorwithWrappedStateDiscreteorContinuous_x0 ; } else { rtB .
bcae5cddmf = rtDW . fwtjvjlo5d - muDoubleScalarFloor ( 1.0 / ( 1.0 / rtP .
PWM_FREQUENCY - rtP .
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue ) * (
rtDW . fwtjvjlo5d - rtP .
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue ) ) * (
1.0 / rtP . PWM_FREQUENCY - rtP .
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue ) ; }
if ( ( rtDW . fwtjvjlo5d < rtP .
IntegratorwithWrappedStateDiscreteorContinuous_WrappedStateLowerValue ) || (
rtDW . fwtjvjlo5d >= 1.0 / rtP . PWM_FREQUENCY ) ) { rtDW . fwtjvjlo5d = rtB
. bcae5cddmf ; } p0lbcytzy3 = rtDW . fwtjvjlo5d ; hbomglvb20 = 1.0 / rtP .
PWM_FREQUENCY / ( 1.0 / rtP . PWM_FREQUENCY - rtB . pcegtoga1k [ 0 ] ) *
p0lbcytzy3 ; cji3wpa32t = 1.0 / rtP . PWM_FREQUENCY + rtB . pcegtoga1k [ 0 ]
; if ( rtDW . i4btsdgjgc ) { rtDW . i4btsdgjgc = false ; rtB . fdx3exdy5g =
rtP . PWMGenerator_Tdelay ; } else { rtB . fdx3exdy5g = rtDW . eoikp5p4om -
muDoubleScalarFloor ( 1.0 / ( 1.0 / rtP . PWM_FREQUENCY * 2.0 - rtP .
IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue ) * (
rtDW . eoikp5p4om - rtP .
IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue ) ) *
( 1.0 / rtP . PWM_FREQUENCY * 2.0 - rtP .
IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue ) ; }
if ( ( rtDW . eoikp5p4om < rtP .
IntegratorwithWrappedStateDiscreteorContinuous1_WrappedStateLowerValue ) || (
rtDW . eoikp5p4om >= 1.0 / rtP . PWM_FREQUENCY * 2.0 ) ) { rtDW . eoikp5p4om
= rtB . fdx3exdy5g ; } switch ( ( int32_T ) rtP . Carriercounter_CarrCount )
{ case 1 : hbomglvb20 -= muDoubleScalarFloor ( hbomglvb20 / cji3wpa32t ) *
cji3wpa32t ; break ; case 2 : hbomglvb20 = 1.0 / rtP . PWM_FREQUENCY - (
hbomglvb20 - muDoubleScalarFloor ( hbomglvb20 / cji3wpa32t ) * cji3wpa32t ) ;
break ; default : hbomglvb20 = 1.0 / rtP . PWM_FREQUENCY * 2.0 - rtDW .
eoikp5p4om ; if ( rtDW . eoikp5p4om > 1.0 / rtP . PWM_FREQUENCY ) {
cji3wpa32t = rtP . Constant2_Value ; } else { cji3wpa32t = rtDW . eoikp5p4om
; } if ( hbomglvb20 > 1.0 / rtP . PWM_FREQUENCY ) { hbomglvb20 = rtP .
Constant2_Value_plmatbfhrk ; } hbomglvb20 += cji3wpa32t ; break ; }
hbomglvb20 *= 1.0 / ( 1.0 / rtP . PWM_FREQUENCY ) ; if ( hbomglvb20 > rtP .
Saturation_UpperSat ) { hbomglvb20 = rtP . Saturation_UpperSat ; } else if (
hbomglvb20 < rtP . Saturation_LowerSat ) { hbomglvb20 = rtP .
Saturation_LowerSat ; } rtB . otrfhi2jef = ( ( rtB . g30amokcxz != rtP .
Constant_Value ) && ( rtB . g30amokcxz >= rtP . Carriercounter_Range *
hbomglvb20 + ( - rtP . Carriercounter_Range + 1.0 ) ) ) ; } rtB . orw15ospbe
[ 0 ] = rtB . otrfhi2jef ; rtB . orw15ospbe [ 1 ] = 0.0 ; rtB . orw15ospbe [
2 ] = 0.0 ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . ormsaahnoz [ 0 ] = ! (
rtB . orw15ospbe [ 0 ] == rtDW . ormsaahnoz [ 1 ] ) ; rtDW . ormsaahnoz [ 1 ]
= rtB . orw15ospbe [ 0 ] ; } rtB . orw15ospbe [ 0 ] = rtDW . ormsaahnoz [ 1 ]
; rtB . orw15ospbe [ 3 ] = rtDW . ormsaahnoz [ 0 ] ; simulationData = (
NeslSimulationData * ) rtDW . oqc03anz5y ; time = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time ; simulationData -> mData -> mContStates . mN = 1 ;
simulationData -> mData -> mContStates . mX = & rtX . k5px2lav4s ;
simulationData -> mData -> mDiscStates . mN = 5 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . bxjovwinxp [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
cm0cbljfgw [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS )
; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_p [ 1 ] = rtB . orw15ospbe [ 1 ] ;
tmp_p [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_p [ 3 ] = rtB . orw15ospbe [ 3 ] ;
tmp_e [ 1 ] = 4 ; simulationData -> mData -> mInputValues . mN = 4 ;
simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData
-> mData -> mInputOffsets . mN = 2 ; simulationData -> mData -> mInputOffsets
. mX = & tmp_e [ 0 ] ; simulationData -> mData -> mOutputs . mN = 9 ;
simulationData -> mData -> mOutputs . mX = & rtB . kmruurvswl [ 0 ] ;
simulationData -> mData -> mTolerances . mN = 0 ; simulationData -> mData ->
mTolerances . mX = NULL ; simulationData -> mData -> mCstateHasChanged =
false ; time_p = ssGetTaskTime ( rtS , 0 ) ; simulationData -> mData -> mTime
. mN = 1 ; simulationData -> mData -> mTime . mX = & time_p ; simulationData
-> mData -> mSampleHits . mN = 0 ; simulationData -> mData -> mSampleHits .
mX = NULL ; simulationData -> mData -> mIsFundamentalSampleHit = false ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . ccsnt40ngz ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW . mktnnal2dg ,
NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if ( tmp_i != 0 ) {
tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
if ( ssIsMajorTimeStep ( rtS ) && simulationData -> mData ->
mCstateHasChanged ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
simulationData = ( NeslSimulationData * ) rtDW . ivgcjyejwx ; time_e = ssGetT
( rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time_e ; simulationData -> mData -> mContStates . mN = 0 ;
simulationData -> mData -> mContStates . mX = NULL ; simulationData -> mData
-> mDiscStates . mN = 0 ; simulationData -> mData -> mDiscStates . mX = &
rtDW . nnuqctfxxy ; simulationData -> mData -> mModeVector . mN = 0 ;
simulationData -> mData -> mModeVector . mX = & rtDW . lkw4xdculs ; tmp = (
ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents
) ; simulationData -> mData -> mFoundZcEvents = tmp ; simulationData -> mData
-> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr (
rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ;
simulationData -> mData -> mIsSolverCheckingCIC = tmp ; simulationData ->
mData -> mIsComputingJacobian = false ; simulationData -> mData ->
mIsEvaluatingF0 = false ; tmp = ssIsSolverRequestingReset ( rtS ) ;
simulationData -> mData -> mIsSolverRequestingReset = tmp ; simulationData ->
mData -> mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_g [ 0 ]
= 0 ; tmp_m [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_m [ 1 ] = rtB . orw15ospbe [
1 ] ; tmp_m [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_m [ 3 ] = rtB . orw15ospbe [
3 ] ; tmp_g [ 1 ] = 4 ; memcpy ( & tmp_m [ 4 ] , & rtB . kmruurvswl [ 0 ] ,
9U * sizeof ( real_T ) ) ; tmp_g [ 2 ] = 13 ; simulationData -> mData ->
mInputValues . mN = 13 ; simulationData -> mData -> mInputValues . mX = &
tmp_m [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 3 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_g [ 0 ] ;
simulationData -> mData -> mOutputs . mN = 1 ; simulationData -> mData ->
mOutputs . mX = & dyj34onvff ; simulationData -> mData -> mTolerances . mN =
0 ; simulationData -> mData -> mTolerances . mX = NULL ; simulationData ->
mData -> mCstateHasChanged = false ; time_i = ssGetTaskTime ( rtS , 0 ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time_i ; simulationData -> mData -> mSampleHits . mN = 0 ;
simulationData -> mData -> mSampleHits . mX = NULL ; simulationData -> mData
-> mIsFundamentalSampleHit = false ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . osj2f4u0da ; diagnosticTree_p =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
ne_simulator_method ( ( NeslSimulator * ) rtDW . e3a1wv3ben ,
NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if ( tmp_i != 0 ) {
tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg_p
= rtw_diagnostics_msg ( diagnosticTree_p ) ; ssSetErrorStatus ( rtS , msg_p )
; } } if ( ssIsMajorTimeStep ( rtS ) && simulationData -> mData ->
mCstateHasChanged ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
rtB . nwsf4t2iom = dyj34onvff ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB .
gncjlmrb1o = rtP . PIDController_I * rtB . o2elcg3xq5 ; } UNUSED_PARAMETER (
tid ) ; } void MdlOutputsTID3 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
void MdlUpdate ( int_T tid ) { NeslSimulationData * simulationData ;
NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree * diagnosticTree
; char * msg ; real_T tmp_p [ 4 ] ; real_T time ; int32_T tmp_i ; int_T tmp_e
[ 2 ] ; boolean_T tmp ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
ehy1wkofia = rtB . nwsf4t2iom ; rtDW . adkeh0nooq += rtP . Integrator_gainval
* rtB . gncjlmrb1o ; rtDW . fwtjvjlo5d += rtP . Integrator_gainval_l1xzho0ept
* rtP . Constant3_Value ; rtDW . eoikp5p4om += rtP .
Integrator_gainval_fr0wjrfryx * rtP . Constant3_Value ; } simulationData = (
NeslSimulationData * ) rtDW . oqc03anz5y ; time = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time ; simulationData -> mData -> mContStates . mN = 1 ;
simulationData -> mData -> mContStates . mX = & rtX . k5px2lav4s ;
simulationData -> mData -> mDiscStates . mN = 5 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . bxjovwinxp [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
cm0cbljfgw [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS )
; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_p [ 1 ] = rtB . orw15ospbe [ 1 ] ;
tmp_p [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_p [ 3 ] = rtB . orw15ospbe [ 3 ] ;
tmp_e [ 1 ] = 4 ; simulationData -> mData -> mInputValues . mN = 4 ;
simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData
-> mData -> mInputOffsets . mN = 2 ; simulationData -> mData -> mInputOffsets
. mX = & tmp_e [ 0 ] ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW .
ccsnt40ngz ; diagnosticTree = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW
. mktnnal2dg , NESL_SIM_UPDATE , simulationData , diagnosticManager ) ; if (
tmp_i != 0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if
( tmp ) { msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus (
rtS , msg ) ; } } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID3 ( int_T tid
) { UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) {
NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; XDot * _rtXdot ;
char * msg ; real_T tmp_p [ 4 ] ; real_T time ; int32_T tmp_i ; int_T tmp_e [
2 ] ; boolean_T tmp ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ;
simulationData = ( NeslSimulationData * ) rtDW . oqc03anz5y ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 1 ;
simulationData -> mData -> mContStates . mX = & rtX . k5px2lav4s ;
simulationData -> mData -> mDiscStates . mN = 5 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . bxjovwinxp [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
cm0cbljfgw [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS )
; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_p [ 1 ] = rtB . orw15ospbe [ 1 ] ;
tmp_p [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_p [ 3 ] = rtB . orw15ospbe [ 3 ] ;
tmp_e [ 1 ] = 4 ; simulationData -> mData -> mInputValues . mN = 4 ;
simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData
-> mData -> mInputOffsets . mN = 2 ; simulationData -> mData -> mInputOffsets
. mX = & tmp_e [ 0 ] ; simulationData -> mData -> mDx . mN = 1 ;
simulationData -> mData -> mDx . mX = & _rtXdot -> k5px2lav4s ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . ccsnt40ngz ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW . mktnnal2dg ,
NESL_SIM_DERIVATIVES , simulationData , diagnosticManager ) ; if ( tmp_i != 0
) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) {
msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg )
; } } } void MdlProjection ( void ) { } void MdlZeroCrossings ( void ) {
NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; ZCV * _rtZCSV ; char
* msg ; real_T tmp_p [ 4 ] ; real_T time ; int32_T tmp_i ; int_T tmp_e [ 2 ]
; boolean_T tmp ; _rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ;
_rtZCSV -> ip4nidmzfe = ssGetT ( rtS ) - rtP . Step_Time ; simulationData = (
NeslSimulationData * ) rtDW . oqc03anz5y ; time = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time ; simulationData -> mData -> mContStates . mN = 1 ;
simulationData -> mData -> mContStates . mX = & rtX . k5px2lav4s ;
simulationData -> mData -> mDiscStates . mN = 5 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . bxjovwinxp [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 3 ; simulationData -> mData -> mModeVector . mX = & rtDW .
cm0cbljfgw [ 0 ] ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo (
rtS ) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents =
tmp ; simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS )
; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . orw15ospbe [ 0 ] ; tmp_p [ 1 ] = rtB . orw15ospbe [ 1 ] ;
tmp_p [ 2 ] = rtB . orw15ospbe [ 2 ] ; tmp_p [ 3 ] = rtB . orw15ospbe [ 3 ] ;
tmp_e [ 1 ] = 4 ; simulationData -> mData -> mInputValues . mN = 4 ;
simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ; simulationData
-> mData -> mInputOffsets . mN = 2 ; simulationData -> mData -> mInputOffsets
. mX = & tmp_e [ 0 ] ; simulationData -> mData -> mNonSampledZCs . mN = 3 ;
simulationData -> mData -> mNonSampledZCs . mX = & _rtZCSV -> ovv3yg3gdv ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . ccsnt40ngz ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW . mktnnal2dg ,
NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager ) ; if ( tmp_i !=
0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) {
msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg )
; } } } void MdlTerminate ( void ) { neu_destroy_diagnostic_manager ( (
NeuDiagnosticManager * ) rtDW . ccsnt40ngz ) ; nesl_destroy_simulation_data (
( NeslSimulationData * ) rtDW . oqc03anz5y ) ; nesl_erase_simulator (
"Erregerstrom_Regelung/Solver Configuration_1" ) ; nesl_destroy_registry ( )
; neu_destroy_diagnostic_manager ( ( NeuDiagnosticManager * ) rtDW .
osj2f4u0da ) ; nesl_destroy_simulation_data ( ( NeslSimulationData * ) rtDW .
ivgcjyejwx ) ; nesl_erase_simulator (
"Erregerstrom_Regelung/Solver Configuration_1" ) ; nesl_destroy_registry ( )
; } static void mr_Erregerstrom_Regelung_cacheDataAsMxArray ( mxArray *
destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) ;
static void mr_Erregerstrom_Regelung_cacheDataAsMxArray ( mxArray * destArray
, mwIndex i , int j , const void * srcData , size_t numBytes ) { mxArray *
newArray = mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes ,
mxUINT8_CLASS , mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , (
const uint8_T * ) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i ,
j , newArray ) ; } static void
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static void
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_Erregerstrom_Regelung_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) ; static void
mr_Erregerstrom_Regelung_cacheBitFieldToMxArray ( mxArray * destArray ,
mwIndex i , int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j
, mxCreateDoubleScalar ( ( double ) bitVal ) ) ; } static uint_T
mr_Erregerstrom_Regelung_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_Erregerstrom_Regelung_extractBitFieldFromMxArray ( const mxArray *
srcArray , mwIndex i , int j , uint_T numBits ) { const uint_T varVal = (
uint_T ) mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return
varVal & ( ( 1u << numBits ) - 1u ) ; } static void
mr_Erregerstrom_Regelung_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_Erregerstrom_Regelung_cacheDataToMxArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_Erregerstrom_Regelung_restoreDataFromMxArrayWithOffset ( void *
destData , const mxArray * srcArray , mwIndex i , int j , mwIndex offset ,
size_t numBytes ) ; static void
mr_Erregerstrom_Regelung_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_Erregerstrom_Regelung_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static
void mr_Erregerstrom_Regelung_cacheBitFieldToCellArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( double ) fieldVal ) ) ; } static uint_T
mr_Erregerstrom_Regelung_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ;
static uint_T mr_Erregerstrom_Regelung_extractBitFieldFromCellArrayWithOffset
( const mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T
numBits ) { const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_Erregerstrom_Regelung_GetDWork ( ) {
static const char * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "NULL_PrevZCX"
, } ; mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * )
& ( rtB ) , sizeof ( rtB ) ) ; { static const char * rtdwDataFieldNames [ 14
] = { "rtDW.ehy1wkofia" , "rtDW.adkeh0nooq" , "rtDW.fwtjvjlo5d" ,
"rtDW.eoikp5p4om" , "rtDW.ormsaahnoz" , "rtDW.bxjovwinxp" , "rtDW.nnuqctfxxy"
, "rtDW.cm0cbljfgw" , "rtDW.lkw4xdculs" , "rtDW.avfzldlkvq" ,
"rtDW.diguumcgnb" , "rtDW.i4btsdgjgc" , "rtDW.nsr0cymo53" , "rtDW.ffdrcaowl3"
, } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 , 14 ,
rtdwDataFieldNames ) ; mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData
, 0 , 0 , ( const void * ) & ( rtDW . ehy1wkofia ) , sizeof ( rtDW .
ehy1wkofia ) ) ; mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 ,
1 , ( const void * ) & ( rtDW . adkeh0nooq ) , sizeof ( rtDW . adkeh0nooq ) )
; mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const
void * ) & ( rtDW . fwtjvjlo5d ) , sizeof ( rtDW . fwtjvjlo5d ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void
* ) & ( rtDW . eoikp5p4om ) , sizeof ( rtDW . eoikp5p4om ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void
* ) & ( rtDW . ormsaahnoz ) , sizeof ( rtDW . ormsaahnoz ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void
* ) & ( rtDW . bxjovwinxp ) , sizeof ( rtDW . bxjovwinxp ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void
* ) & ( rtDW . nnuqctfxxy ) , sizeof ( rtDW . nnuqctfxxy ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void
* ) & ( rtDW . cm0cbljfgw ) , sizeof ( rtDW . cm0cbljfgw ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void
* ) & ( rtDW . lkw4xdculs ) , sizeof ( rtDW . lkw4xdculs ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void
* ) & ( rtDW . avfzldlkvq ) , sizeof ( rtDW . avfzldlkvq ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const
void * ) & ( rtDW . diguumcgnb ) , sizeof ( rtDW . diguumcgnb ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const
void * ) & ( rtDW . i4btsdgjgc ) , sizeof ( rtDW . i4btsdgjgc ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const
void * ) & ( rtDW . nsr0cymo53 ) , sizeof ( rtDW . nsr0cymo53 ) ) ;
mr_Erregerstrom_Regelung_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const
void * ) & ( rtDW . ffdrcaowl3 ) , sizeof ( rtDW . ffdrcaowl3 ) ) ;
mxSetFieldByNumber ( ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void
mr_Erregerstrom_Regelung_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW
, 0 , 0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber
( ssDW , 0 , 1 ) ; mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void *
) & ( rtDW . ehy1wkofia ) , rtdwData , 0 , 0 , sizeof ( rtDW . ehy1wkofia ) )
; mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
adkeh0nooq ) , rtdwData , 0 , 1 , sizeof ( rtDW . adkeh0nooq ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
fwtjvjlo5d ) , rtdwData , 0 , 2 , sizeof ( rtDW . fwtjvjlo5d ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
eoikp5p4om ) , rtdwData , 0 , 3 , sizeof ( rtDW . eoikp5p4om ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
ormsaahnoz ) , rtdwData , 0 , 4 , sizeof ( rtDW . ormsaahnoz ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
bxjovwinxp ) , rtdwData , 0 , 5 , sizeof ( rtDW . bxjovwinxp ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
nnuqctfxxy ) , rtdwData , 0 , 6 , sizeof ( rtDW . nnuqctfxxy ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
cm0cbljfgw ) , rtdwData , 0 , 7 , sizeof ( rtDW . cm0cbljfgw ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
lkw4xdculs ) , rtdwData , 0 , 8 , sizeof ( rtDW . lkw4xdculs ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
avfzldlkvq ) , rtdwData , 0 , 9 , sizeof ( rtDW . avfzldlkvq ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
diguumcgnb ) , rtdwData , 0 , 10 , sizeof ( rtDW . diguumcgnb ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
i4btsdgjgc ) , rtdwData , 0 , 11 , sizeof ( rtDW . i4btsdgjgc ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
nsr0cymo53 ) , rtdwData , 0 , 12 , sizeof ( rtDW . nsr0cymo53 ) ) ;
mr_Erregerstrom_Regelung_restoreDataFromMxArray ( ( void * ) & ( rtDW .
ffdrcaowl3 ) , rtdwData , 0 , 13 , sizeof ( rtDW . ffdrcaowl3 ) ) ; } }
mxArray * mr_Erregerstrom_Regelung_GetSimStateDisallowedBlocks ( ) { mxArray
* data = mxCreateCellMatrix ( 3 , 3 ) ; mwIndex subs [ 2 ] , offset ; {
static const char * blockType [ 3 ] = { "SimscapeExecutionBlock" ,
"SimscapeExecutionBlock" , "Scope" , } ; static const char * blockPath [ 3 ]
= { "Erregerstrom_Regelung/Solver Configuration/EVAL_KEY/STATE_1" ,
"Erregerstrom_Regelung/Solver Configuration/EVAL_KEY/OUTPUT_1_0" ,
"Erregerstrom_Regelung/Scope" , } ; static const int reason [ 3 ] = { 0 , 0 ,
0 , } ; for ( subs [ 0 ] = 0 ; subs [ 0 ] < 3 ; ++ ( subs [ 0 ] ) ) { subs [
1 ] = 0 ; offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell (
data , offset , mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] =
1 ; offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateDoubleScalar ( ( double ) reason [ subs [ 0 ] ] ) ) ; } }
return data ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
1 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ;
ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 3 ) ; ssSetNumBlocks ( rtS , 80 ) ;
ssSetNumBlockIO ( rtS , 15 ) ; ssSetNumBlockParams ( rtS , 24 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetSampleTime ( rtS , 2 , 5.0E-5 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 3851719436U ) ; ssSetChecksumVal ( rtS , 1 ,
2861185918U ) ; ssSetChecksumVal ( rtS , 2 , 367813115U ) ; ssSetChecksumVal
( rtS , 3 , 687899069U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; ( void ) memset ( ( char * )
rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char * ) & mdlInfo , 0
, sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 23 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
Erregerstrom_Regelung_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"Erregerstrom_Regelung" ) ; ssSetPath ( rtS , "Erregerstrom_Regelung" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 10.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = ( NULL ) ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 1 , 1 , 2 , 5 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static
int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 2 , 5 } ; static
boolean_T rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE
, SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) } ; static
const char_T * rt_LoggedStateLabels [ ] = { "CSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "Discrete" , "Discrete" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = { "Erregerstrom_Regelung/L_rotor" ,
"Erregerstrom_Regelung/Unit Delay" ,
"Erregerstrom_Regelung/PID Controller/Integrator/Discrete/Integrator" ,
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with\nWrapped State\n(Discrete or Continuous)/Discrete/Integrator"
,
 "Erregerstrom_Regelung/PWM Generator/Carrier counter/Integrator with\nWrapped State\n(Discrete or Continuous)1/Discrete/Integrator"
, "Erregerstrom_Regelung/Solver\nConfiguration/EVAL_KEY/INPUT_1_1_1" ,
"Erregerstrom_Regelung/Solver\nConfiguration/EVAL_KEY/STATE_1" } ; static
const char_T * rt_LoggedStateNames [ ] = {
"Erregerstrom_Regelung.L_rotor.i_L" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "Discrete" , "Discrete" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 0 ,
1 , 2 , 3 , 4 , 5 } ; static RTWLogSignalInfo rt_LoggedStateSignalInfo = { 7
, rt_LoggedStateWidths , rt_LoggedStateNumDimensions ,
rt_LoggedStateDimensions , rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) ,
rt_LoggedStateDataTypeIds , rt_LoggedStateComplexSignals , ( NULL ) ,
rt_LoggingStatePreprocessingFcnPtrs , { rt_LoggedStateLabels } , ( NULL ) , (
NULL ) , ( NULL ) , { rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 7 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . k5px2lav4s ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtDW . ehy1wkofia ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . adkeh0nooq ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtDW . fwtjvjlo5d ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtDW . eoikp5p4om ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) rtDW . ormsaahnoz ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) rtDW . bxjovwinxp ; } rtliSetLogT
( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS )
, "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) , "xFinal" ) ;
rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 1 ] ;
static real_T absTol [ 1 ] = { 1.0E-6 } ; static uint8_T absTolControl [ 1 ]
= { 0U } ; static real_T contStateJacPerturbBoundMinVec [ 1 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 1 ] ; static uint8_T zcAttributes [ 4 ] = {
( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_P2Z | ZC_EVENT_P2N | ZC_EVENT_Z2P |
ZC_EVENT_N2P ) , ( ZC_EVENT_P2Z | ZC_EVENT_P2N | ZC_EVENT_Z2P | ZC_EVENT_N2P
) , ( ZC_EVENT_Z2N | ZC_EVENT_P2N | ZC_EVENT_N2Z | ZC_EVENT_N2P ) } ; static
ssNonContDerivSigInfo nonContDerivSigInfo [ 1 ] = { { 1 * sizeof ( real_T ) ,
( char * ) ( & rtB . otrfhi2jef ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i
< 1 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] = 0 ;
contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } } ssSetSolverRelTol (
rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 )
; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 5.0E-5 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
1 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS ,
"VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ;
_ssSetSolverUpdateJacobianAtReset ( rtS , true ) ; ssSetAbsTolVector ( rtS ,
absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 4 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 4 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 3851719436U ) ; ssSetChecksumVal ( rtS , 1 ,
2861185918U ) ; ssSetChecksumVal ( rtS , 2 , 367813115U ) ; ssSetChecksumVal
( rtS , 3 , 687899069U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 3 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = & rtAlwaysEnabled ;
systemRan [ 2 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_Erregerstrom_Regelung_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_Erregerstrom_Regelung_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_Erregerstrom_Regelung_SetDWork ) ;
rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if ( ssGetErrorStatus ( rtS ) )
{ return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID3 ( tid ) ; }
