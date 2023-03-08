#ifndef RTW_HEADER_Erregerstrom_Regelung_acc_h_
#define RTW_HEADER_Erregerstrom_Regelung_acc_h_
#ifndef Erregerstrom_Regelung_acc_COMMON_INCLUDES_
#define Erregerstrom_Regelung_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "Erregerstrom_Regelung_acc_types.h"
#include "rt_defines.h"
#include <stddef.h>
typedef struct { real_T B_2_0_0 ; real_T B_2_1_0 ; real_T B_2_2_0 ; real_T
B_2_4_0 ; real_T B_2_6_0 ; real_T B_2_7_0 ; real_T B_2_11_0 [ 2 ] ; real_T
B_2_22_0 ; real_T B_2_40_0 ; real_T B_2_53_0 ; real_T B_2_54_0 [ 4 ] ; real_T
B_2_55_0 [ 9 ] ; real_T B_2_56_0 ; real_T B_2_59_0 ; real_T B_2_61_0 ; real_T
B_2_0_0_m ; real_T B_2_1_0_c ; real_T B_2_2_0_k ; real_T B_2_3_0 ; boolean_T
B_2_16_0 ; boolean_T B_2_34_0 ; char_T pad_B_2_34_0 [ 6 ] ; }
B_Erregerstrom_Regelung_T ; typedef struct { real_T UnitDelay_DSTATE ; real_T
Integrator_DSTATE ; real_T Integrator_DSTATE_h ; real_T Integrator_DSTATE_f ;
real_T INPUT_1_1_1_Discrete [ 2 ] ; real_T STATE_1_Discrete [ 5 ] ; real_T
OUTPUT_1_0_Discrete ; void * STATE_1_Simulator ; void * STATE_1_SimData ;
void * STATE_1_DiagMgr ; void * STATE_1_ZcLogger ; void * STATE_1_TsInfo ;
void * OUTPUT_1_0_Simulator ; void * OUTPUT_1_0_SimData ; void *
OUTPUT_1_0_DiagMgr ; void * OUTPUT_1_0_ZcLogger ; void * OUTPUT_1_0_TsInfo ;
void * Scope_PWORK [ 7 ] ; int32_T
TmpAtomicSubsysAtMultiportSwitchInport4_sysIdxToRun ; int32_T
TmpAtomicSubsysAtMultiportSwitchInport3_sysIdxToRun ; int_T STATE_1_Modes [ 3
] ; int_T OUTPUT_1_0_Modes ; int_T Step_MODE ; boolean_T
Initial_FirstOutputTime ; boolean_T Initial_FirstOutputTime_b ; boolean_T
STATE_1_FirstOutput ; boolean_T OUTPUT_1_0_FirstOutput ; }
DW_Erregerstrom_Regelung_T ; typedef struct { real_T
Erregerstrom_RegelungL_rotori_L ; real_T integrator_CSTATE ; }
X_Erregerstrom_Regelung_T ; typedef struct { real_T
Erregerstrom_RegelungL_rotori_L ; real_T integrator_CSTATE ; }
XDot_Erregerstrom_Regelung_T ; typedef struct { boolean_T
Erregerstrom_RegelungL_rotori_L ; boolean_T integrator_CSTATE ; }
XDis_Erregerstrom_Regelung_T ; typedef struct { real_T
Erregerstrom_RegelungL_rotori_L ; real_T integrator_CSTATE ; }
CStateAbsTol_Erregerstrom_Regelung_T ; typedef struct { real_T
Erregerstrom_RegelungL_rotori_L ; real_T integrator_CSTATE ; }
CXPtMin_Erregerstrom_Regelung_T ; typedef struct { real_T
Erregerstrom_RegelungL_rotori_L ; real_T integrator_CSTATE ; }
CXPtMax_Erregerstrom_Regelung_T ; typedef struct { real_T Step_StepTime_ZC ;
real_T STATE_1_Diodezc_1_ZC ; real_T
STATE_1_IGBT_Ideal_Switchingideal_switchzc_1_ZC ; real_T
STATE_1_IGBT_Ideal_Switchingideal_switchzc_2_ZC ; }
ZCV_Erregerstrom_Regelung_T ; typedef struct { ZCSigState Step_StepTime_ZCE ;
ZCSigState STATE_1_Diodezc_1_ZCE ; ZCSigState
STATE_1_IGBT_Ideal_Switchingideal_switchzc_1_ZCE ; ZCSigState
STATE_1_IGBT_Ideal_Switchingideal_switchzc_2_ZCE ; }
PrevZCX_Erregerstrom_Regelung_T ; typedef struct { const real_T B_2_0_0 ; }
ConstB_Erregerstrom_Regelung_T ;
#define Erregerstrom_Regelung_rtC(S) ((ConstB_Erregerstrom_Regelung_T *) _ssGetConstBlockIO(S))
struct P_Erregerstrom_Regelung_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ;
real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T
P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ;
real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T
P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ;
real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T
P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ;
} ; extern P_Erregerstrom_Regelung_T Erregerstrom_Regelung_rtDefaultP ;
extern const ConstB_Erregerstrom_Regelung_T Erregerstrom_Regelung_rtInvariant
;
#endif
