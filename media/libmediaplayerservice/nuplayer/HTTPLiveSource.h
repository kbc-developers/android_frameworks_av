/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HTTP_LIVE_SOURCE_H_

#define HTTP_LIVE_SOURCE_H_

#include "NuPlayer.h"
#include "NuPlayerSource.h"

namespace android {

struct ATSParser;
struct LiveSession;

struct NuPlayer::HTTPLiveSource : public NuPlayer::Source {
    HTTPLiveSource(
            const sp<AMessage> &notify,
            const char *url,
            const KeyedVector<String8, String8> *headers,
            bool uidValid = false,
            uid_t uid = 0);

    virtual void prepareAsync();
    virtual void start();

    virtual status_t feedMoreTSData();

    virtual status_t dequeueAccessUnit(bool audio, sp<ABuffer> *accessUnit);

    virtual status_t getDuration(int64_t *durationUs);
    virtual status_t seekTo(int64_t seekTimeUs);

protected:
    virtual ~HTTPLiveSource();

    virtual sp<MetaData> getFormatMeta(bool audio);

    virtual void onMessageReceived(const sp<AMessage> &msg);

private:
    enum Flags {
        // Don't log any URLs.
        kFlagIncognito = 1,
    };

    enum {
        kWhatSessionNotify,
    };

    AString mURL;
    KeyedVector<String8, String8> mExtraHeaders;
    bool mUIDValid;
    uid_t mUID;
    uint32_t mFlags;
    status_t mFinalResult;
    off64_t mOffset;
    sp<ALooper> mLiveLooper;
    sp<LiveSession> mLiveSession;
    sp<ATSParser> mTSParser;

    void onSessionNotify(const sp<AMessage> &msg);

    DISALLOW_EVIL_CONSTRUCTORS(HTTPLiveSource);
};

}  // namespace android

#endif  // HTTP_LIVE_SOURCE_H_
