/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0252GetD() {return &zzvw;}

#define OVL0252_C
#define ovldat DRK0252dat
#define ovlcod DRK0252cod
#include "DRK0240.c"
