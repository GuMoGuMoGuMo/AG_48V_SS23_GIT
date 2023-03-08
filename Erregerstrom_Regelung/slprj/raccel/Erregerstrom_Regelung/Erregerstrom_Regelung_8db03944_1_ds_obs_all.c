#include "ne_ds.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_sys_struct.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_obs_all.h"
#include "Erregerstrom_Regelung_8db03944_1_ds.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_externals.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T Erregerstrom_Regelung_8db03944_1_ds_obs_all ( const NeDynamicSystem *
sys , const NeDynamicSystemInput * t5 , NeDsMethodOutput * t6 ) {
PmRealVector out ; real_T Current_Sensor_I ; real_T U_idx_0 ; real_T X_idx_0
; real_T X_idx_1 ; real_T X_idx_2 ; real_T X_idx_3 ; real_T t0 ; int32_T
M_idx_0 ; M_idx_0 = t5 -> mM . mX [ 0 ] ; U_idx_0 = t5 -> mU . mX [ 0 ] ;
X_idx_0 = t5 -> mX . mX [ 0 ] ; X_idx_1 = t5 -> mX . mX [ 1 ] ; X_idx_2 = t5
-> mX . mX [ 2 ] ; X_idx_3 = t5 -> mX . mX [ 3 ] ; out = t6 -> mOBS_ALL ;
Current_Sensor_I = X_idx_1 * 1.0E-9 + X_idx_0 ; if ( M_idx_0 != 0 ) { t0 = (
- X_idx_3 + 48.0 ) - 0.8 ; } else { t0 = U_idx_0 - 0.5 ; } out . mX [ 0 ] =
Current_Sensor_I ; out . mX [ 1 ] = Current_Sensor_I ; out . mX [ 2 ] = 48.0
; out . mX [ 3 ] = 48.0 ; out . mX [ 4 ] = Current_Sensor_I ; out . mX [ 5 ]
= ( - X_idx_0 + X_idx_1 * - 1.0E-9 ) + X_idx_2 ; out . mX [ 6 ] = 48.0 ; out
. mX [ 7 ] = X_idx_3 ; out . mX [ 8 ] = X_idx_3 - 48.0 ; out . mX [ 9 ] = 0.0
; out . mX [ 10 ] = 48.0 ; out . mX [ 11 ] = X_idx_3 ; out . mX [ 12 ] =
U_idx_0 ; out . mX [ 13 ] = 0.0 ; out . mX [ 14 ] = X_idx_2 ; out . mX [ 15 ]
= U_idx_0 ; out . mX [ 16 ] = X_idx_2 ; out . mX [ 17 ] = t0 ; out . mX [ 18
] = X_idx_3 ; out . mX [ 19 ] = 48.0 ; out . mX [ 20 ] = X_idx_2 * ( -
X_idx_3 + 48.0 ) * 0.001 * 1000.0 ; out . mX [ 21 ] = - X_idx_3 + 48.0 ; out
. mX [ 22 ] = U_idx_0 ; out . mX [ 23 ] = 48.0 - X_idx_3 ; out . mX [ 24 ] =
0.0 ; out . mX [ 25 ] = Current_Sensor_I ; out . mX [ 26 ] = 0.0 ; out . mX [
27 ] = X_idx_1 ; out . mX [ 28 ] = X_idx_1 ; out . mX [ 29 ] = X_idx_0 ; out
. mX [ 30 ] = Current_Sensor_I ; out . mX [ 31 ] = X_idx_1 ; out . mX [ 32 ]
= X_idx_3 ; out . mX [ 33 ] = Current_Sensor_I * 8.0 ; out . mX [ 34 ] =
U_idx_0 ; out . mX [ 35 ] = - Current_Sensor_I ; out . mX [ 36 ] = 0.0 ; out
. mX [ 37 ] = 48.0 ; out . mX [ 38 ] = 48.0 ; ( void ) sys ; ( void ) t6 ;
return 0 ; }
