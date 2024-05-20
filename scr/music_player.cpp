#include "music_player.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <thread>

std::atomic<bool> playing(false);
std::atomic<bool> stopped(false);
std::atomic<int> volume(128);
std::mutex mtx;
std::condition_variable cv;
size_t currentTrack = 0;

void playMusic() {
    while (!stopped) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return playing || stopped; });

        if (stopped) break;

        if (!playlist.empty()) {
            std::string currentFile = playlist[currentTrack];

            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_AudioSpec wavSpec;
            Uint32 wavLength;
            Uint8 *wavBuffer;
            if (SDL_LoadWAV(currentFile.c_str(), &wavSpec, &wavBuffer, &wavLength) == nullptr) {
                std::cerr << "Failed to load WAV file! SDL_Error: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
            if (deviceId == 0) {
                std::cerr << "Failed to open audio device! SDL_Error: " << SDL_GetError() << std::endl;
                SDL_FreeWAV(wavBuffer);
                return;
            }

            SDL_PauseAudioDevice(deviceId, 0);

            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            if (success < 0) {
                std::cerr << "Failed to queue audio! SDL_Error: " << SDL_GetError() << std::endl;
            }

            while (SDL_GetQueuedAudioSize(deviceId) > 0 && playing) {
                SDL_Delay(100);
                SDL_MixAudioFormat(wavBuffer, wavBuffer, wavSpec.format, wavLength, volume);
            }

            SDL_CloseAudioDevice(deviceId);
            SDL_FreeWAV(wavBuffer);

            currentTrack = (currentTrack + 1) % playlist.size();
        }
    }
}

void initializeSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

void cleanUpSDL() {
    SDL_Quit();
}
