/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0944GetD() {return &zzvw;}

#define OVL0944_C
#define ovldat DRK0944dat
#define ovlcod DRK0944cod
#include "DRK0240.c"
