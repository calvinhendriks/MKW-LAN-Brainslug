#include <Kamek/kamek.hpp>
#include <Race/racedata.hpp>
#include <Race/raceinfo.hpp>
#include <Race/kmp.hpp>
#include <Race/playerholder.hpp>
#include <Race/lakitucontroller.hpp>
#include <Race/Item/itemobjproperties.hpp>

#ifdef LAPSPEEDMODIFIER

RaceinfoPlayer *LoadCustomLapCount(RaceinfoPlayer *player, u8 id){
    u8 lapCount = KMP::controller->stageInfo->pointArray[0]->rawData->lapCount;
    raceData->main.scenarios[0].settings.lapCount = lapCount;
    return new(player) RaceinfoPlayer(id, lapCount);
}
kmCall(0x805328d4, &LoadCustomLapCount);

void DisplayCorrectLap(LakituModel *lapModel, u32 maxLap){
    float lap =(float) (maxLap - 2);
    lapModel->DisplayLap(lap);
    return;
}
kmCall(0x80723d70, &DisplayCorrectLap);
kmWrite32(0x80723d64, 0x7FA4EB78);

PlayerStats *ApplySpeedModifier(VehicleId vehicleId, CharacterId characterId){
    SpeedModConv speedModConv;
    speedModConv.kmpValue = (KMP::controller->stageInfo->pointArray[0]->rawData->speedMod << 16);

    if (speedModConv.speedMod == 0.0f) speedModConv.speedMod = 1.0f;

    KartParams *kart = kartParams;
    kart[vehicleId].baseSpeed  *= speedModConv.speedMod;
    kart[vehicleId].standard_acceleration_as[0] *= speedModConv.speedMod;
    kart[vehicleId].standard_acceleration_as[1] *= speedModConv.speedMod;
    kart[vehicleId].standard_acceleration_as[2] *= speedModConv.speedMod;
    kart[vehicleId].standard_acceleration_as[3] *= speedModConv.speedMod;

    greenShellSpeed              = 105.0f    * speedModConv.speedMod;                              
    redShellInitialSpeed         = 75.0f     * speedModConv.speedMod;             
    redShellSpeed                = 130.0f    * speedModConv.speedMod;         
    blueShellSpeed               = 260.0f    * speedModConv.speedMod;      
    blueShellMinimumDiveDistance = 640000.0f * speedModConv.speedMod;
    blueShellHomingSpeed         = 130.0f    * speedModConv.speedMod;       
        
    hardSpeedLimit      = 120.0f * speedModConv.speedMod;
    bulletBillSpeed     = 145.0f * speedModConv.speedMod;
    starSpeed           = 105.0f * speedModConv.speedMod;
    megaMushroomTCSpeed = 95.0f  * speedModConv.speedMod;

    return Compute(vehicleId, characterId);
}
kmCall(0x8058f670, &ApplySpeedModifier);

kmWrite32(0x805336B8, 0x60000000);
kmWrite32(0x80534350, 0x60000000);
kmWrite32(0x80534BBC, 0x60000000);
kmWrite32(0x80723D10, 0x281D0009);
kmWrite32(0x80723D40, 0x3BA00009);

#endif