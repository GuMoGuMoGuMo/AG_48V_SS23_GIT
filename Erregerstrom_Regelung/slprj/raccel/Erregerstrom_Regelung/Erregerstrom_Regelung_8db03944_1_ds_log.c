#include "ne_ds.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_sys_struct.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_log.h"
#include "Erregerstrom_Regelung_8db03944_1_ds.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_externals.h"
#include "Erregerstrom_Regelung_8db03944_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T Erregerstrom_Regelung_8db03944_1_ds_log ( const NeDynamicSystem * sys
, const NeDynamicSystemInput * t5 , NeDsMethodOutput * t6 ) { PmRealVector
out ; real_T Current_Sensor_I ; real_T Diode_i ; real_T U_idx_0 ; real_T
X_idx_0 ; real_T X_idx_1 ; real_T X_idx_2 ; real_T X_idx_3 ; real_T t0 ;
int32_T M_idx_0 ; M_idx_0 = t5 -> mM . mX [ 0 ] ; U_idx_0 = t5 -> mU . mX [ 0
] ; X_idx_0 = t5 -> mX . mX [ 0 ] ; X_idx_1 = t5 -> mX . mX [ 1 ] ; X_idx_2 =
t5 -> mX . mX [ 2 ] ; X_idx_3 = t5 -> mX . mX [ 3 ] ; out = t6 -> mLOG ;
Current_Sensor_I = X_idx_1 * 1.0E-9 + X_idx_0 ; Diode_i = ( - X_idx_0 +
X_idx_1 * - 1.0E-9 ) + X_idx_2 ; if ( M_idx_0 != 0 ) { t0 = ( - X_idx_3 +
48.0 ) - 0.8 ; } else { t0 = U_idx_0 - 0.5 ; } out . mX [ 0 ] =
Current_Sensor_I ; out . mX [ 1 ] = Current_Sensor_I ; out . mX [ 2 ] =
Current_Sensor_I ; out . mX [ 3 ] = Diode_i ; out . mX [ 4 ] = X_idx_3 ; out
. mX [ 5 ] = X_idx_3 - 48.0 ; out . mX [ 6 ] = Diode_i * ( X_idx_3 - 48.0 ) ;
out . mX [ 7 ] = X_idx_3 ; out . mX [ 8 ] = U_idx_0 ; out . mX [ 9 ] =
X_idx_2 ; out . mX [ 10 ] = U_idx_0 ; out . mX [ 11 ] = X_idx_2 ; out . mX [
12 ] = t0 ; out . mX [ 13 ] = X_idx_3 ; out . mX [ 14 ] = X_idx_2 * ( -
X_idx_3 + 48.0 ) * 0.001 * 1000.0 ; out . mX [ 15 ] = - X_idx_3 + 48.0 ; out
. mX [ 16 ] = U_idx_0 ; out . mX [ 17 ] = 48.0 - X_idx_3 ; out . mX [ 18 ] =
Current_Sensor_I ; out . mX [ 19 ] = X_idx_1 ; out . mX [ 20 ] = X_idx_1 ;
out . mX [ 21 ] = X_idx_0 ; out . mX [ 22 ] = X_idx_1 * X_idx_1 *
1.0000000000000002E-12 ; out . mX [ 23 ] = Current_Sensor_I ; out . mX [ 24 ]
= X_idx_1 ; out . mX [ 25 ] = X_idx_3 ; out . mX [ 26 ] = Current_Sensor_I *
8.0 ; out . mX [ 27 ] = Current_Sensor_I * Current_Sensor_I * 8.0 ; out . mX
[ 28 ] = U_idx_0 ; out . mX [ 29 ] = - Current_Sensor_I ; ( void ) sys ; (
void ) t6 ; return 0 ; }
