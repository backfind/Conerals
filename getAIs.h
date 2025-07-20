// get AIs
#include "humanOptions.h"
#include ".\AI\example1.h"
#include ".\AI\example1_copy1.h"
#include ".\AI\example1_copy2.h"
#include ".\AI\example1_copy3.h"
#include ".\AI\example2.h"
#include ".\AI\PhirainEX.h"
#include ".\AI\feiwu.h"
#include ".\AI\feiwu_copy1.h"
#include ".\AI\OI_minecraft.h"
#include ".\AI\OI_minecraft_copy1.h"
#include ".\AI\OI_minecraft_copy2.h"
#include ".\AI\OI_minecraft_copy3.h"
// initialize
void Initialize(string currentAIname){
    if (currentAIname == "human"){
        humanChooseX = 0;
        humanChooseY = 0;
        return;
    }
    else if (currentAIname == "example1"){
        example1::Init();
        return;
    }
    else if (currentAIname == "example1_copy1"){
        example1_copy1::Init();
        return;
    }
    else if (currentAIname == "example1_copy2"){
        example1_copy2::Init();
        return;
    }
    else if (currentAIname == "example1_copy3"){
        example1_copy3::Init();
        return;
    }
    else if (currentAIname == "example2"){
        example2::Init();
        return;
    }
    else if (currentAIname == "PhirainEX"){
        PhirainEX::Init();
        return;
    }
    else if (currentAIname == "feiwu"){
        feiwu::Init();
        return;
    }
    else if (currentAIname == "feiwu_copy1"){
        feiwu_copy1::Init();
        return;
    }
    else if (currentAIname == "OI_minecraft"){
        OI_minecraft::Init();
        return;
    }
    else if (currentAIname == "OI_minecraft_copy1"){
        OI_minecraft_copy1::Init();
        return;
    }
    else if (currentAIname == "OI_minecraft_copy2"){
        OI_minecraft_copy2::Init();
        return;
    }
    else if (currentAIname == "OI_minecraft_copy3"){
        OI_minecraft_copy3::Init();
        return;
    }
    return;
}
// get moves
movement GetMove(string currentAIname){
    if (currentAIname == "human"){
        humanOptions::GetTheTime(theStartTimeOfTheCurrentTurn);
        return humanOptions::Move();
    }
    else if (currentAIname == "example1"){
        return example1::Move();
    }
    else if (currentAIname == "example1_copy1"){
        return example1_copy1::Move();
    }
    else if (currentAIname == "example1_copy2"){
        return example1_copy2::Move();
    }
    else if (currentAIname == "example1_copy3"){
        return example1_copy3::Move();
    }
    else if (currentAIname == "example2"){
        return example2::Move();
    }
    else if (currentAIname == "PhirainEX"){
        return PhirainEX::Move();
    }
    else if (currentAIname == "feiwu"){
        return feiwu::Move();
    }
    else if (currentAIname == "feiwu_copy1"){
        return feiwu_copy1::Move();
    }
    else if (currentAIname == "OI_minecraft"){
        return OI_minecraft::Move();
    }
    else if (currentAIname == "OI_minecraft_copy1"){
        return OI_minecraft_copy1::Move();
    }
    else if (currentAIname == "OI_minecraft_copy2"){
        return OI_minecraft_copy2::Move();
    }
    else if (currentAIname == "OI_minecraft_copy3"){
        return OI_minecraft_copy3::Move();
    }
    return (movement){-1, -1, 0};
}
