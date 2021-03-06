#include <ultra64.h>
#include <global.h>

void func_800E8EA0(GlobalContext* ctxt, Actor* actor, u16 param_3) {
    func_80151938(ctxt, param_3);
    actor->textId = param_3;
}

s32 nop_800E8ED0(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EE0(UNK_TYPE4 param_1) {}

s32 nop_800E8EEC(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EFC(UNK_TYPE4 param_1) {}

s32 func_800E8F08(Vec3s* param_1, Vec3s* param_2) {
  Math_SmoothScaleMaxMinS(&param_1->y, 0, 6, 6200, 100);
  Math_SmoothScaleMaxMinS(&param_1->x, 0, 6, 6200, 100);
  Math_SmoothScaleMaxMinS(&param_2->y, 0, 6, 6200, 100);
  Math_SmoothScaleMaxMinS(&param_2->x, 0, 6, 6200, 100);
  return 1;
}

s32 func_800E8FA4(Actor* actor, Vec3f* param_2, Vec3s* param_3, Vec3s* param_4) {
    s16 targetPitch;
    s16 targetYaw;
    s16 yawDiffFromTarget;

    targetPitch = Math_Vec3f_Pitch(&actor->focus.pos,param_2);
    targetYaw = Math_Vec3f_Yaw(&actor->focus.pos,param_2) - actor->world.rot.y;

    Math_SmoothScaleMaxMinS(&param_3->x, targetPitch, 6, 2000, 1);
    param_3->x = (param_3->x < -6000)? -6000 : ((6000 < param_3->x)? 6000 : param_3->x);

    yawDiffFromTarget = Math_SmoothScaleMaxMinS(&param_3->y, targetYaw, 6, 2000, 1);
    param_3->y = (param_3->y < -8000)? -8000 : ((8000 < param_3->y)? 8000 : param_3->y);

    if (yawDiffFromTarget != 0) {
        if ((param_3->y < 0? -param_3->y : param_3->y) < 8000) {
            return 0;
        }
    }

    Math_SmoothScaleMaxMinS(&param_4->y, targetYaw - param_3->y, 4, 2000, 1);
    param_4->y = (param_4->y < -12000)? -12000 : ((12000 < param_4->y)? 12000 : param_4->y);

    return 1;
}

s32 func_800E9138(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, f32 param_5) {
    s16 sVar3;
    Actor *player;
    Vec3f local_14;

    player = (ctxt->actorCtx).actorList[2].first;
    actor->focus.pos = actor->world.pos;
    actor->focus.pos.y += param_5;

    if (((ctxt->csCtx).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = actor->yawTowardsPlayer - actor->shape.rot.y;
        // TODO is this shifting because of a missing cast?
        if (0x42ff < (sVar3 < 0? ((-sVar3 << 0x10) >> 0x10) : ((sVar3 << 0x10) >> 0x10))) {
            func_800E8F08(param_3,param_4);
            return 0;
        }
    }

    if (((ctxt->csCtx).state != 0) || (D_801D0D50 != 0)) {
        local_14 = ctxt->view.eye;
    } else {
        local_14 = player->focus.pos;
    }

    func_800E8FA4(actor,&local_14,param_3,param_4);

    return 1;
}
s32 func_800E9250(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, Vec3f param_5) {
    s16 sVar3;
    Actor *player;
    Vec3f local_14;

    player = (ctxt->actorCtx).actorList[2].first;
    actor->focus.pos = param_5;

    if (((ctxt->csCtx).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = actor->yawTowardsPlayer - actor->shape.rot.y;
        // TODO is this shifting because of a missing cast?
        if (0x42ff < (sVar3 < 0? ((-sVar3 << 0x10) >> 0x10) : ((sVar3 << 0x10) >> 0x10))) {
            func_800E8F08(param_3,param_4);
            return 0;
        }
    }

    if (((ctxt->csCtx).state != 0) || (D_801D0D50 != 0)) {
        local_14 = ctxt->view.eye;
    } else {
        local_14 = player->focus.pos;
    }

    func_800E8FA4(actor,&local_14,param_3,param_4);

    return 1;
}

