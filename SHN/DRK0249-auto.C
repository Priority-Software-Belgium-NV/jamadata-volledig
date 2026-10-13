/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0249GetD() {return &zzvw;}

#define OVL0249_C
#define ovldat DRK0249dat
#define ovlcod DRK0249cod
#include "DRK0240.c"
