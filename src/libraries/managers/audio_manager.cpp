#include "audio_manager.h"

namespace ts
{

    void AudioManager::init()
    {
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            throw std::runtime_error("Failed to initialize SDL Audio: " + std::string(SDL_GetError()));
        }

        if (MIX_Init() == false)
        {
            throw std::runtime_error("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(SDL_GetError()));
        }

        if (mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); mixer == nullptr)
        {
            throw std::runtime_error("Failed to create mixer device: " + std::string(SDL_GetError()));
        }

        addTrack("music");
    }

    void AudioManager::destroy()
    {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    void AudioManager::clear()
    {

        for(auto& [name, track] : soundTracks) {
            MIX_StopTrack(track, 0);
        }
        for(auto& [name, audio] : soundCache) {
            MIX_DestroyAudio(audio);
        }
    }

    void AudioManager::loadAudio(const std::string name, const std::string &filePath, bool predecode)
    {
        if (soundCache.find(name) != soundCache.end())
        {
            return; // Already loaded
        }

        MIX_Audio *audio = MIX_LoadAudio(mixer, filePath.c_str(), predecode);
        if (audio == nullptr)
        {
            throw std::runtime_error("Failed to load audio file: " + filePath + " Error: " + std::string(SDL_GetError()));
        }

        soundCache[name] = audio;
    }

    void AudioManager::startTrack(const std::string &trackName, const std::string &clipName, bool loop)
    {

        if (soundCache.find(clipName) == soundCache.end())
        {
            throw std::runtime_error("Audio clip not found: " + clipName);
        }

        TrackStatus status = getTrackStatus(trackName);
        if (status == NONE)
        {
            addTrack(trackName);
        }
        else if (status == PLAYING or status == PAUSED)
        {
            stopTrack(trackName, 0);
        }

        MIX_Track *track = soundTracks[trackName];
        MIX_Audio *audio = soundCache[clipName];

        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loop ? -1 : 0);
        MIX_SetTrackAudio(track, audio);
        if (MIX_PlayTrack(track, props) == false)
        {
            throw std::runtime_error("Failed to play track: " + trackName + " Error: " + std::string(SDL_GetError()));
        }

        SDL_DestroyProperties(props);
    }

    void AudioManager::resumeTrack(const std::string &trackName)
    {
        TrackStatus status = getTrackStatus(trackName);
        if (status == PAUSED)
        {
            MIX_Track *track = soundTracks[trackName];
            MIX_ResumeTrack(track);
        }
    }

    void AudioManager::pauseTrack(const std::string &trackName)
    {
        TrackStatus status = getTrackStatus(trackName);
        if (status == PLAYING)
        {
            MIX_Track *track = soundTracks[trackName];
            MIX_PauseTrack(track);
        }
    }
    void AudioManager::playSound(const std::string &name)
    {
        if (soundCache.find(name) == soundCache.end())
        {
            throw std::runtime_error("Sound not found: " + name);
        }

        MIX_Audio *audio = soundCache[name];
        MIX_PlayAudio(mixer, audio);
    }
    void AudioManager::stopTrack(const std::string &trackName, int fadeOutFrame)
    {
        TrackStatus status = getTrackStatus(trackName);

        if (status == PLAYING || status == PAUSED)
        {
            MIX_Track *track = soundTracks[trackName];
            MIX_StopTrack(track, fadeOutFrame);
        }
    }
    TrackStatus AudioManager::getTrackStatus(const std::string &trackName)
    {
        if (soundTracks.find(trackName) == soundTracks.end())
        {
            return NONE;
        }

        MIX_Track *track = soundTracks[trackName];
        if (MIX_TrackPlaying(track))
        {
            return PLAYING;
        }
        else if (MIX_TrackPaused(track))
        {
            return PAUSED;
        }
        else
        {
            return STOPPED;
        }
    }

    void AudioManager::addTrack(const std::string &name)
    {
        MIX_Track *track;
        if (track = MIX_CreateTrack(mixer); track == nullptr)
        {
            throw std::runtime_error("Failed to create music track! SDL_mixer Error: " + std::string(SDL_GetError()));
        }
        soundTracks[name] = track;
    }
}