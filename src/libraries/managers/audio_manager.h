#pragma once

#include "pch.h"

namespace ts
{

    enum TrackStatus{
        NONE,
        PLAYING,
        PAUSED,
        STOPPED
    };
    class AudioManager
    {
    public:
        void init();
        void destroy();

        void clear();

        void loadAudio(const std::string name,const std::string &filePath, bool predecode = true);
 
        void startTrack(const std::string& trackName,const std::string &clipName, bool loop = true);
        void resumeTrack(const std::string &trackName);
        void stopTrack(const std::string &trackName, int fadeOutFrame = 0);
        void pauseTrack(const std::string &trackName);
        void playSound(const std::string &name);


        static AudioManager *getInstance()
        {
            static AudioManager *instance = new AudioManager();
            return instance;
        }

        TrackStatus getTrackStatus(const std::string& trackName);

    private:
        static AudioManager *instance;
        AudioManager() = default;
        ~AudioManager() = default;
        AudioManager(const AudioManager &) = delete;
        AudioManager &operator=(const AudioManager &) = delete;


        void addTrack(const std::string& name);

        MIX_Mixer *mixer = nullptr;

        std::unordered_map<std::string, MIX_Audio*> soundCache;
        std::unordered_map<std::string, MIX_Track*> soundTracks;
    };
}