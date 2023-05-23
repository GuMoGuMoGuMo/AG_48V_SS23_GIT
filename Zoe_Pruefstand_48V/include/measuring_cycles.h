#include <stdint.h>
// Data structure for a table entry
struct measuring_cycle_def {
    uint16_t time;       // Time in seconds
    uint16_t rpm;        // Revolutions per minute (rpm)
    uint16_t torque;     // Torque in Newton-meters (Nm)
    float exitacion_current; // exitacion Current in Ampere (A) 
};

#define MEASURING_CYCLE_TABLE_SIZE 5 //37

struct measuring_cycle_def measuring_cycle_1[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 0, 0, 0},
    {5, 1000, 0, 0},
    {10, 1000, 0, 0},
    {15, 1000, 0, 0},
    {20, 0, 0, 0}
};

/*
struct measuring_cycle_def measuring_cycle_1[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 0, 0, 2.0},
    {5, 0, 2, 2.0},
    {10, 0, 4, 2.0},
    {15, 0, 6, 2.0},
    {20, 0, 8, 2.0},
    {25, 0, 10, 2.0},
    {30, 100, 0, 2.0},
    {35, 100, 2, 2.0},
    {40, 100, 4, 2.0},
    {45, 100, 6, 2.0},
    {50, 100, 8, 2.0},
    {55, 100, 10, 2.0},
    {60, 200, 0, 2.0},
    {65, 200, 2, 2.0},
    {70, 200, 4, 2.0},
    {75, 200, 6, 2.0},
    {80, 200, 8, 2.0},
    {85, 200, 10, 2.0},
    {90, 300, 0, 2.0},
    {95, 300, 2, 2.0},
    {100, 300, 4, 2.0},
    {105, 300, 6, 2.0},
    {110, 300, 8, 2.0},
    {115, 300, 10, 2.0},
    {120, 400, 0, 2.0},
    {125, 400, 2, 2.0},
    {130, 400, 4, 2.0},
    {135, 400, 6, 2.0},
    {140, 400, 8, 2.0},
    {145, 400, 10, 2.0},
    {150, 500, 0, 2.0},
    {155, 500, 2, 2.0},
    {160, 500, 4, 2.0},
    {165, 500, 6, 2.0},
    {170, 500, 8, 2.0},
    {175, 500, 10, 2.0},
    {0, 0, 0, 2.0} 
};
*/

