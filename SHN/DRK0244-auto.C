/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0244GetD() {return &zzvw;}

#define OVL0244_C
#define ovldat DRK0244dat
#define ovlcod DRK0244cod
#include "DRK0240.c"
