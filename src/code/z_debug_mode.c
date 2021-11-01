#include "global.h"

typedef struct {
    u8 x;
    u8 y;
    u8 colorId;
    char text[41];
} PrintTextInfo;

typedef struct {
    u16 push;
    u16 held;
} InputCombo;

typedef struct {
    u8 y;
    char text[0xB];
} PrintTextInfo2;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_mode/func_800E9C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_mode/func_800E9CA0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_mode/func_800E9CFC.s")
extern PrintTextInfo2 D_801BB094[];
extern Color_RGBA8 D_801BB0DC[];

void func_800E9CFC(GfxPrint* printer) {
    Color_RGBA8* color;
    s32 i;
    PrintTextInfo2* phi_s0;
    for(i = 0x14 ; i < 0x1A ; i++){
        phi_s0 = &D_801BB094[i];
        GfxPrint_SetPos(printer, 0x1A, i);
        color = &D_801BB0DC[phi_s0->y];
        GfxPrint_SetColor(printer, color->r, color->g, color->b, color->a);
        GfxPrint_Printf(printer, "%s", phi_s0->text);
        phi_s0->text[0] = 0;
    }

}



#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_mode/func_800E9DBC.s")

extern Color_RGBA8 D_801BB100[];
extern PrintTextInfo D_801F3F80[];
extern s32 D_801BB090;
extern s16 D_801BB0FC;

void func_800E9E94(GfxPrint* printer) {
    s32 i;
    Color_RGBA8* color;
    PrintTextInfo* buf;
    char* text;

    for (i = 0; i < D_801BB0FC; i++) {
        buf = &D_801F3F80[i];
        text = buf->text;

        color = &D_801BB100[buf->colorId];
        GfxPrint_SetColor(printer, color->r, color->g, color->b, color->a);
        GfxPrint_SetPos(printer, buf->x, buf->y);
        GfxPrint_Printf(printer, "%s", text);
    }
}

void func_800E9F78(GraphicsContext* gfxCtx) {
    Gfx* temp2;
    Gfx* dListHead;
    GfxPrint printer;
    Gfx* temp;

    if (THGA_GetSize(&gfxCtx->polyOpa) >= 0x2800) {
        OPEN_DISPS(gfxCtx);
        GfxPrint_Init(&printer);
        dListHead = POLY_OPA_DISP;

        temp = Graph_GfxPlusOne(POLY_OPA_DISP);
        gSPDisplayList(DEBUG_DISP++, temp);

        GfxPrint_Open(&printer, temp);

        if ((D_801BB090 & 2) != 0) {
            func_800E9E94(&printer);
        }

        D_801BB0FC = 0;
        if ((D_801BB090 & 1) != 0) {
            func_800E9CFC(&printer);
        }

        temp2 = GfxPrint_Close(&printer);
        gSPEndDisplayList(temp2++);

        Graph_BranchDlist(dListHead, temp2);
        gfxCtx->polyOpa.p = temp2;
        CLOSE_DISPS(gfxCtx);
        GfxPrint_Destroy(&printer);
    }
}
