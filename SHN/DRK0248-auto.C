/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0248GetD() {return &zzvw;}

#define OVL0248_C
#define ovldat DRK0248dat
#define ovlcod DRK0248cod
#include "DRK0240.c"
