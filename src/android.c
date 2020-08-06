// See: http://www.50ply.com/blog/2013/01/19/loading-compressed-android-assets-with-file-pointer/
// See: https://github.com/android/ndk/issues/562

#include "android.h"
#include "nanovg.h"

#if defined(__ANDROID__)

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <android/log.h>
#include <android/asset_manager.h>

#define LOGV(...) (__android_log_print(ANDROID_LOG_VERBOSE, "NanoVG Demo", __VA_ARGS__))
#define LOGI(...) (__android_log_print(ANDROID_LOG_INFO,    "NanoVG Demo", __VA_ARGS__))
#define LOGW(...) (__android_log_print(ANDROID_LOG_WARN,    "NanoVG Demo", __VA_ARGS__))
#define LOGE(...) (__android_log_print(ANDROID_LOG_ERROR,   "NanoVG Demo", __VA_ARGS__))
#define LOGF(...) (__android_log_print(ANDROID_LOG_FATAL,   "NanoVG Demo", __VA_ARGS__))

static int android_read(void * cookie, char * buf, int size) {
  return AAsset_read((AAsset*)cookie, buf, size);
}

static int android_write(void * cookie, const char * buf, int size) {
  (void)cookie; (void)buf; (void)size; // unused
  return EACCES; // can't provide write access to the apk
}

static fpos_t android_seek(void * cookie, fpos_t offset, int whence) {
  return AAsset_seek((AAsset*)cookie, offset, whence);
}

static int android_close(void * cookie) {
  AAsset_close((AAsset*)cookie);
  return 0;
}

AAssetManager * android_asset_manager = NULL;
void nvgSetAndroidAssetManager(AAssetManager * manager) {
  android_asset_manager = manager;
}

FILE * android_fopen(const char * fname, const char * mode) {
  if (mode[0] == '/') { // absolute path
  }

  if (strchr(mode, 'w')) { // for writing
    LOGE("Unable to open asset (trying to write): '%s' ('%s')", fname, mode);
    return NULL;
  }

  if (!android_asset_manager) {
    LOGE("Unable to open asset (unknown asset manager): '%s' ('%s')", fname, mode);
    return NULL;
  }

  AAsset* asset = AAssetManager_open(android_asset_manager, fname, 0);
  if (!asset) {
    LOGW("Unable to open asset: '%s' ('%s')", fname, mode);
    return NULL;
  }

  LOGV("Opening asset: '%s' ('%s')", fname, mode);
  return funopen(asset, android_read, android_write, android_seek, android_close);
}

#endif
