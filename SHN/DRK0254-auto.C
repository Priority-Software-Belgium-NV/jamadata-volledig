/*32-01*/
#pragma pack(1)
#pragma data_seg(".dsovl")
#pragma const_seg(".dsovl")
#pragma bss_seg(".dsovl")
static char zzvw;
char* DRK0254GetD() {return &zzvw;}

#define OVL0254_C
#define ovldat DRK0254dat
#define ovlcod DRK0254cod
#include "DRK0240.c"
