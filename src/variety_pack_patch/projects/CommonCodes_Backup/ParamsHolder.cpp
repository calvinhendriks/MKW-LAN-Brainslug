#include <Kamek/kamek.hpp>
#include <System/system.hpp>
#include <paramsholder.hpp>
#include <project.hpp>

#ifdef PARAMSHOLDER

ParamsHolder *ParamsHolder::sInstance = NULL;

ParamsHolder::ParamsHolder(){
    Settings1 *buffer = (Settings1*) EGG::Heap::alloc(sizeof(Settings1), 0x20, 0);

    char *path = "settings.bin";
    NANDFileInfo info;
    u32 length = 0;

    s32 code = NANDOpen(path, &info, NAND_MODE_READ_WRITE);
    NANDGetLength(&info, &length);
    if (code < NAND_CODE_OK) {
        if (NANDCreate(path, NAND_PERM_READ_WRITE, 0) != NAND_CODE_OK) return; //can't locate or create the file
        code = NANDOpen(path, &info, NAND_MODE_READ_WRITE);
        if (code < NAND_CODE_OK) return;
        NANDGetLength(&info, &length);
    };
    code = NANDRead(&info, buffer, length);
    if (code >= NAND_CODE_OK){
        if(strcmp(buffer->magic, "VP") == 0){
            if (buffer->version == curVersion){
                memcpy(&this->settings, buffer,sizeof(Settings1));
                NANDClose(&info);
                EGG::Heap::free(buffer, 0);
                return;
            }
            else{
                new(&this->settings) Settings1((Settings0*) buffer);
            }
        }
        else{
            new(&this->settings) Settings1();
        }
    }
    memcpy(buffer, &this->settings,sizeof(Settings1));
    NANDSeek(&info, 0, 0);
    NANDWrite(&info, buffer, sizeof(Settings1));
    NANDClose(&info);
    EGG::Heap::free(buffer, 0);
}

void CreateParamsHolder(){
    ParamsHolder::sInstance = new(ParamsHolder);
};
static BootHook CreateParams(CreateParamsHolder);

void ParamsHolder::SaveSettings(){
    char *path = "settings.bin";
    NANDFileInfo info;
    s32 code = NANDOpen(path, &info, NAND_MODE_READ_WRITE);
    if (code == NAND_CODE_OK) {
        RKSystem *system = &rkSystem;
        Settings1 *buffer = (Settings1*) EGG::Heap::alloc(sizeof(Settings1), 0x20, system->EGGSystem);
        memcpy(buffer, &this->settings, sizeof(Settings1));
        NANDSeek(&info, 0, 0);
        NANDWrite(&info, buffer, sizeof(Settings1));
        NANDClose(&info);
    }
    return;
}

#endif