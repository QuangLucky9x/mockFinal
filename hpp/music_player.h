#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>
#include <playlist.h>

extern std::atomic<bool> playing;
extern std::atomic<bool> stopped;
extern std::atomic<int> volume;
extern std::mutex mtx;
extern std::condition_variable cv;
extern size_t currentTrack;

void playMusic();
void initializeSDL();
void cleanUpSDL();

#endif // MUSIC_PLAYER_H
