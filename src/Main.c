#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"
#include "/home/codeleaded/System/Static/Library/BarCode.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/ImageFilter.h"


BarCode_Selection bcs;
RLCamera rlc;
BarCode_Analyser bca;

void Setup(AlxWindow* w){
    bcs = BarCode_Selection_Make((BarCode[]){
        0x3bcd11bbf0744cffULL,  // 0
        0x1326e53172768b23ULL,  // 1
        0x2286fa3ff80dd449ULL,  // 2
        0x4ca194b3a8a30925ULL,  // 3
        0x659638ab7f8cf8a3ULL,  // 4
        0x578fad6f6d6712f7ULL,  // 5
        0x4ead5338661be08dULL,  // 6
        0x1c73a8bd4cc4ed18ULL,  // 7
        0x5338c014469c1687ULL,  // 8
        0x64ac5f5b0097700aULL,  // 9
        0x6b8410ae0c454e6cULL,  // 10
        0x1d352e5ecd16d49fULL,  // 11
        BARCODE_ERROR
    });
    rlc = RLCamera_New(RLCAMERA_DEVICE,RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);
    bca = BarCode_Analyser_New(3.0f);

    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
    //window.Running = 0;
}

void Update(AlxWindow* w){
    Sprite sp = Sprite_Null();
    sp.img = RLCamera_Get(&rlc,&sp.w,&sp.h);

    Sprite trans = ImageFilter_BW_LN(&sp,0.65f);
    //Sprite trans = ImageFilter_G(&sp);
    //Sprite trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sobel_V());
    //Sprite trans = ImageFilter_C_Motion(&sp,&now,0.65f);

    const float bc_sp_w = (float)trans.w * 0.3f;
    const float bc_sp_h = (float)trans.w * 0.3f;
    const float bc_sp_x = ((float)trans.w - bc_sp_w) * 0.5f;
    const float bc_sp_y = ((float)trans.h - bc_sp_w) * 0.5f;

    const float bc_w = (float)GetWidth() * 0.3f;
    const float bc_h = (float)GetWidth() * 0.3f;
    const float bc_x = ((float)GetWidth() - bc_w) * 0.5f;
    const float bc_y = ((float)GetHeight() - bc_w) * 0.5f;

    if(Stroke(ALX_KEY_1).PRESSED){
        Sprite bc_sp = Sprite_Null();

        Sprite_AppendHSub(&bc_sp,SubSprite_New(&trans,bc_sp_x,bc_sp_y,bc_sp_w,bc_sp_h));

        Sprite_Save(&bc_sp,"./data/BarCode.png");
        Sprite_Free(&bc_sp);
    }
    if(Stroke(ALX_KEY_2).PRESSED){
        BarCode bc = Random_u64_MinMax(0,RANDOM_MAX >> 1);
        printf("Make: Bar-Code: %llu | %llx\n",bc,bc);

        Sprite bc_sp = BarCode_Generate(bc,400,200);
        Sprite_Save(&bc_sp,"./data/BarCodeR.png");
        Sprite_Free(&bc_sp);
    }
    if(Stroke(ALX_KEY_3).PRESSED){
        BarCode bc = BarCode_Scan_Path(&bcs,"./data/BarCode.png");
        printf("Scan: Bar-Code: %llu | %llx\n",bc,bc);
    }
    if(Stroke(ALX_KEY_4).PRESSED){
        BarCode bc = BarCode_Scan_Path(&bcs,"./data/BarCodeR.png");
        printf("Scan: Bar-Code: %llu | %llx\n",bc,bc);
    }

    if(Stroke(ALX_KEY_W).PRESSED){
        for(int i = 0;i<2;i++){
            LCG_Seed_Set(Time_Nano());

            BarCode bc = Random_u64_MinMax(0,RANDOM_MAX >> 1);
            printf("Make: Bar-Code: %llx\n",bc);

            Sprite bc_sp = BarCode_Generate(bc,200,200);
            CStr path = CStr_Format("./data/BarCode%d.png",i);
            Sprite_Save(&bc_sp,path);
            CStr_Free(&path);
            Sprite_Free(&bc_sp);
        }
    }

    Sprite bc_sp = Sprite_Null();
    Sprite_AppendHSub(&bc_sp,SubSprite_New(&trans,bc_sp_x,bc_sp_y,bc_sp_w,bc_sp_h));
    BarCode_Analyser_Update(&bca,&bcs,&bc_sp);

    if(!BarCode_Analyser_Scanning(&bca) && bca.start != 0UL){
        BarCode bc = BarCode_Analyser_Output(&bca,&bcs);
        int i = BarCode_Selection_Find(&bcs,bc);

        if(bc == BARCODE_ERROR) printf("Error, not found!\n");
        else                    printf("Output: %llx (%d)\n",bc,i);
    }

    if(Stroke(ALX_KEY_SPACE).PRESSED){
        BarCode_Analyser_Start(&bca,bcs.size);
    }
    if(Stroke(ALX_KEY_BACKSPACE).DOWN){
        BarCode bc = BarCode_Scan(&bcs,&bc_sp);
        int i = BarCode_Selection_Find(&bcs,bc);

        if(bc == BARCODE_ERROR) printf("Error, not found!\n");
        else                    printf("Output: %llx (%d)\n",bc,i);
    }

    Clear(BLACK);

    if(trans.img){
        //Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
	    Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
    }

    Sprite_Free(&bc_sp);
    Sprite_Free(&trans);
    Sprite_Free(&sp);

    Rect_RenderXXAlpha(WINDOW_STD_ARGS,bc_x,bc_y,bc_w,bc_h,BarCode_Analyser_Scanning(&bca) ? 0xAA773300 : 0x77773300);
    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
}

void Delete(AlxWindow* w){
    RLCamera_Free(&rlc);
    BarCode_Analyser_Free(&bca);
}

int main(){
    if(Create("Bar Code Camera",RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
