#include <stdint.h>

#ifndef STDINT_H
#define STDINT_H

typedef struct {
    uint16_t time;       // Time in seconds
    uint16_t rpm;        // Revolutions per minute (rpm)
    uint16_t torque;     // Torque in Newton-meters (Nm)
    float exitacion_current; // Excitation Current in Ampere (A)
} measuring_cycle_def;

#define MEASURING_CYCLE_TABLE_SIZE 250

const measuring_cycle_def measuring_cycle_table[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 500, 0, 1.00},
    {3, 500, 0, 2.00},
    {6, 500, 0, 3.00},
    {9, 500, 0, 4.00},
    {12, 500, 0, 5.00},
    {15, 500, 10, 1.00},
    {18, 500, 10, 2.00},
    {21, 500, 10, 3.00},
    {24, 500, 10, 4.00},
    {27, 500, 10, 5.00},
    {30, 500, 20, 1.00},
    {33, 500, 20, 2.00},
    {36, 500, 20, 3.00},
    {39, 500, 20, 4.00},
    {42, 500, 20, 5.00},
    {45, 500, 30, 1.00},
    {48, 500, 30, 2.00},
    {51, 500, 30, 3.00},
    {54, 500, 30, 4.00},
    {57, 500, 30, 5.00},
    {60, 500, 40, 1.00},
    {63, 500, 40, 2.00},
    {66, 500, 40, 3.00},
    {69, 500, 40, 4.00},
    {72, 500, 40, 5.00},
    {75, 1000, 0, 1.00},
    {78, 1000, 0, 2.00},
    {81, 1000, 0, 3.00},
    {84, 1000, 0, 4.00},
    {87, 1000, 0, 5.00},
    {90, 1000, 10, 1.00},
    {93, 1000, 10, 2.00},
    {96, 1000, 10, 3.00},
    {99, 1000, 10, 4.00},
    {102, 1000, 10, 5.00},
    {105, 1000, 20, 1.00},
    {108, 1000, 20, 2.00},
    {111, 1000, 20, 3.00},
    {114, 1000, 20, 4.00},
    {117, 1000, 20, 5.00},
    {120, 1000, 30, 1.00},
    {123, 1000, 30, 2.00},
    {126, 1000, 30, 3.00},
    {129, 1000, 30, 4.00},
    {132, 1000, 30, 5.00},
    {135, 1000, 40, 1.00},
    {138, 1000, 40, 2.00},
    {141, 1000, 40, 3.00},
    {144, 1000, 40, 4.00},
    {147, 1000, 40, 5.00},
    {150, 1500, 0, 1.00},
    {153, 1500, 0, 2.00},
    {156, 1500, 0, 3.00},
    {159, 1500, 0, 4.00},
    {162, 1500, 0, 5.00},
    {165, 1500, 10, 1.00},
    {168, 1500, 10, 2.00},
    {171, 1500, 10, 3.00},
    {174, 1500, 10, 4.00},
    {177, 1500, 10, 5.00},
    {180, 1500, 20, 1.00},
    {183, 1500, 20, 2.00},
    {186, 1500, 20, 3.00},
    {189, 1500, 20, 4.00},
    {192, 1500, 20, 5.00},
    {195, 1500, 30, 1.00},
    {198, 1500, 30, 2.00},
    {201, 1500, 30, 3.00},
    {204, 1500, 30, 4.00},
    {207, 1500, 30, 5.00},
    {210, 1500, 40, 1.00},
    {213, 1500, 40, 2.00},
    {216, 1500, 40, 3.00},
    {219, 1500, 40, 4.00},
    {222, 1500, 40, 5.00},
    {225, 2000, 0, 1.00},
    {228, 2000, 0, 2.00},
    {231, 2000, 0, 3.00},
    {234, 2000, 0, 4.00},
    {237, 2000, 0, 5.00},
    {240, 2000, 10, 1.00},
    {243, 2000, 10, 2.00},
    {246, 2000, 10, 3.00},
    {249, 2000, 10, 4.00},
    {252, 2000, 10, 5.00},
    {255, 2000, 20, 1.00},
    {258, 2000, 20, 2.00},
    {261, 2000, 20, 3.00},
    {264, 2000, 20, 4.00},
    {267, 2000, 20, 5.00},
    {270, 2000, 30, 1.00},
    {273, 2000, 30, 2.00},
    {276, 2000, 30, 3.00},
    {279, 2000, 30, 4.00},
    {282, 2000, 30, 5.00},
    {285, 2000, 40, 1.00},
    {288, 2000, 40, 2.00},
    {291, 2000, 40, 3.00},
    {294, 2000, 40, 4.00},
    {297, 2000, 40, 5.00},
    {300, 2500, 0, 1.00},
    {303, 2500, 0, 2.00},
    {306, 2500, 0, 3.00},
    {309, 2500, 0, 4.00},
    {312, 2500, 0, 5.00},
    {315, 2500, 10, 1.00},
    {318, 2500, 10, 2.00},
    {321, 2500, 10, 3.00},
    {324, 2500, 10, 4.00},
    {327, 2500, 10, 5.00},
    {330, 2500, 20, 1.00},
    {333, 2500, 20, 2.00},
    {336, 2500, 20, 3.00},
    {339, 2500, 20, 4.00},
    {342, 2500, 20, 5.00},
    {345, 2500, 30, 1.00},
    {348, 2500, 30, 2.00},
    {351, 2500, 30, 3.00},
    {354, 2500, 30, 4.00},
    {357, 2500, 30, 5.00},
    {360, 2500, 40, 1.00},
    {363, 2500, 40, 2.00},
    {366, 2500, 40, 3.00},
    {369, 2500, 40, 4.00},
    {372, 2500, 40, 5.00},
    {375, 3000, 0, 1.00},
    {378, 3000, 0, 2.00},
    {381, 3000, 0, 3.00},
    {384, 3000, 0, 4.00},
    {387, 3000, 0, 5.00},
    {390, 3000, 10, 1.00},
    {393, 3000, 10, 2.00},
    {396, 3000, 10, 3.00},
    {399, 3000, 10, 4.00},
    {402, 3000, 10, 5.00},
    {405, 3000, 20, 1.00},
    {408, 3000, 20, 2.00},
    {411, 3000, 20, 3.00},
    {414, 3000, 20, 4.00},
    {417, 3000, 20, 5.00},
    {420, 3000, 30, 1.00},
    {423, 3000, 30, 2.00},
    {426, 3000, 30, 3.00},
    {429, 3000, 30, 4.00},
    {432, 3000, 30, 5.00},
    {435, 3000, 40, 1.00},
    {438, 3000, 40, 2.00},
    {441, 3000, 40, 3.00},
    {444, 3000, 40, 4.00},
    {447, 3000, 40, 5.00},
    {450, 3500, 0, 1.00},
    {453, 3500, 0, 2.00},
    {456, 3500, 0, 3.00},
    {459, 3500, 0, 4.00},
    {462, 3500, 0, 5.00},
    {465, 3500, 10, 1.00},
    {468, 3500, 10, 2.00},
    {471, 3500, 10, 3.00},
    {474, 3500, 10, 4.00},
    {477, 3500, 10, 5.00},
    {480, 3500, 20, 1.00},
    {483, 3500, 20, 2.00},
    {486, 3500, 20, 3.00},
    {489, 3500, 20, 4.00},
    {492, 3500, 20, 5.00},
    {495, 3500, 30, 1.00},
    {498, 3500, 30, 2.00},
    {501, 3500, 30, 3.00},
    {504, 3500, 30, 4.00},
    {507, 3500, 30, 5.00},
    {510, 3500, 40, 1.00},
    {513, 3500, 40, 2.00},
    {516, 3500, 40, 3.00},
    {519, 3500, 40, 4.00},
    {522, 3500, 40, 5.00},
    {525, 4000, 0, 1.00},
    {528, 4000, 0, 2.00},
    {531, 4000, 0, 3.00},
    {534, 4000, 0, 4.00},
    {537, 4000, 0, 5.00},
    {540, 4000, 10, 1.00},
    {543, 4000, 10, 2.00},
    {546, 4000, 10, 3.00},
    {549, 4000, 10, 4.00},
    {552, 4000, 10, 5.00},
    {555, 4000, 20, 1.00},
    {558, 4000, 20, 2.00},
    {561, 4000, 20, 3.00},
    {564, 4000, 20, 4.00},
    {567, 4000, 20, 5.00},
    {570, 4000, 30, 1.00},
    {573, 4000, 30, 2.00},
    {576, 4000, 30, 3.00},
    {579, 4000, 30, 4.00},
    {582, 4000, 30, 5.00},
    {585, 4000, 40, 1.00},
    {588, 4000, 40, 2.00},
    {591, 4000, 40, 3.00},
    {594, 4000, 40, 4.00},
    {597, 4000, 40, 5.00},
    {600, 4500, 0, 1.00},
    {603, 4500, 0, 2.00},
    {606, 4500, 0, 3.00},
    {609, 4500, 0, 4.00},
    {612, 4500, 0, 5.00},
    {615, 4500, 10, 1.00},
    {618, 4500, 10, 2.00},
    {621, 4500, 10, 3.00},
    {624, 4500, 10, 4.00},
    {627, 4500, 10, 5.00},
    {630, 4500, 20, 1.00},
    {633, 4500, 20, 2.00},
    {636, 4500, 20, 3.00},
    {639, 4500, 20, 4.00},
    {642, 4500, 20, 5.00},
    {645, 4500, 30, 1.00},
    {648, 4500, 30, 2.00},
    {651, 4500, 30, 3.00},
    {654, 4500, 30, 4.00},
    {657, 4500, 30, 5.00},
    {660, 4500, 40, 1.00},
    {663, 4500, 40, 2.00},
    {666, 4500, 40, 3.00},
    {669, 4500, 40, 4.00},
    {672, 4500, 40, 5.00},
    {675, 5000, 0, 1.00},
    {678, 5000, 0, 2.00},
    {681, 5000, 0, 3.00},
    {684, 5000, 0, 4.00},
    {687, 5000, 0, 5.00},
    {690, 5000, 10, 1.00},
    {693, 5000, 10, 2.00},
    {696, 5000, 10, 3.00},
    {699, 5000, 10, 4.00},
    {702, 5000, 10, 5.00},
    {705, 5000, 20, 1.00},
    {708, 5000, 20, 2.00},
    {711, 5000, 20, 3.00},
    {714, 5000, 20, 4.00},
    {717, 5000, 20, 5.00},
    {720, 5000, 30, 1.00},
    {723, 5000, 30, 2.00},
    {726, 5000, 30, 3.00},
    {729, 5000, 30, 4.00},
    {732, 5000, 30, 5.00},
    {735, 5000, 40, 1.00},
    {738, 5000, 40, 2.00},
    {741, 5000, 40, 3.00},
    {744, 5000, 40, 4.00},
    {747, 5000, 40, 5.00}
};

#endif /* MEASURING_CYCLE_TABLE_H */