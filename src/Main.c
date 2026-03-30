#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"


RLCamera rlc;

void Setup(AlxWindow* w){
    rlc = RLCamera_New(RLCAMERA_DEVICE,RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);

    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
    //window.Running = 0;
}

void Update(AlxWindow* w){
    
    Sprite sp = Sprite_Null();
    sp.img = RLCamera_Get(&rlc,&sp.w,&sp.h);
    
    Clear(BLACK);

    if(sp.img){
        Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
        Sprite_Free(&sp);
    }

    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
}

void Delete(AlxWindow* w){
    RLCamera_Free(&rlc);
}

int main(){
    if(Create("Camera Test",840,680,1,1,Setup,Update,Delete))
        Start();
    return 0;
}