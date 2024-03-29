#include <stdint.h> //include for usage of uint16_t in struct def
// Data structure for a table entry
struct measuring_cycle_def {
    uint16_t time;       // Time in seconds
    uint16_t rpm;        // Revolutions per minute (rpm)
    uint16_t torque;     // Torque in Newton-meters (Nm)
    float exitacion_current; // exitacion Current in Ampere (A) 
};

#define MEASURING_CYCLE_TABLE_SIZE 9 //set number of table entries here
// example table
/*
struct measuring_cycle_def measuring_cycle_1[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 0, 0, 0},
    {5, 1000, 0, 0},
    {10, 1000, 0, 0},
    {15, 1000, 0, 0},
    {20, 0, 0, 0}
};
*/
// active table
struct measuring_cycle_def measuring_cycle_table[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 0, 0, 0},
    {5, 0, 0, 5},
    {10, 1000, 0, 5,},
    {15, 1000, 5, 5},
    {20, 1000, 5, 5},
    {25, 1000, 0, 5},
    {30, 0, 0, 5},
    {35, 0, 0, 0} 
};
