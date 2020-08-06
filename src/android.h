// See: http://www.50ply.com/blog/2013/01/19/loading-compressed-android-assets-with-file-pointer/

#ifndef NANOVG_ANDROID_H_04F2956C_D65D_11EA_852A_07298A1173F1
#define NANOVG_ANDROID_H_04F2956C_D65D_11EA_852A_07298A1173F1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ANDROID__)

#include <stdio.h>
#include <android/asset_manager.h>

void android_fopen_set_asset_manager(AAssetManager* manager);
FILE* android_fopen(const char* fname, const char* mode);

#define fopen(name, mode) android_fopen(name, mode)

#endif

#ifdef __cplusplus
}
#endif

#endif // NANOVG_ANDROID_H_04F2956C_D65D_11EA_852A_07298A1173F1
