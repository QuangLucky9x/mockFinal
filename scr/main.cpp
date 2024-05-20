#include "playlist.h"
#include "metadata.h"
#include "music_player.h"
#include <iostream>
#include <thread>
#include <algorithm>

void showMenu() {
    std::cout << "Menu Options:" << std::endl;
    std::cout << "1. Create Playlist" << std::endl;
    std::cout << "2. Update Playlist" << std::endl;
    std::cout << "3. Delete Playlist" << std::endl;
    std::cout << "4. View Playlists" << std::endl;
    std::cout << "5. Display Metadata" << std::endl;
    std::cout << "6. Play Music" << std::endl;
    std::cout << "7. Pause Music" << std::endl;
    std::cout << "8. Next Track" << std::endl;
    std::cout << "9. Previous Track" << std::endl;
    std::cout << "10. Set Volume" << std::endl;
    std::cout << "11. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main(int argc, char* argv[]) {
    std::string directoryPath = "C:/Users/HP/Desktop/Mock";
    if (argc > 1) {
        directoryPath = argv[1];
    }

    std::thread musicThread(playMusic);

    int choice = 0;
    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string playlistName;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;
                createPlaylist(playlistName);
                break;
            }
            case 2: {
                std::string playlistName, mediaFile;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;
                std::cout << "Enter media file path: ";
                std::cin >> mediaFile;
                updatePlaylist(playlistName, mediaFile);
                break;
            }
            case 3: {
                std::string playlistName;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;
                deletePlaylist(playlistName);
                break;
            }
            case 4: {
                displayPlaylists();
                break;
            }
            case 5: {
                std::string filePath;
                std::cout << "Enter media file path: ";
                std::cin >> filePath;
                displayAudioMetadata(filePath);
                break;
            }
            case 6: {
                playing = true;
                cv.notify_all();
                break;
            }
            case 7: {
                playing = false;
                break;
            }
            case 8: {
                playing = false;
                currentTrack = (currentTrack + 1) % playlist.size();
                playing = true;
                cv.notify_all();
                break;
            }
            case 9: {
                playing = false;
                if (currentTrack == 0) {
                    currentTrack = playlist.size() - 1;
                } else {
                    currentTrack--;
                }
                playing = true;
                cv.notify_all();
                break;
            }
            case 10: {
                int vol;
                std::cout << "Enter volume (0-128): ";
                std::cin >> vol;
                volume = std::clamp(vol, 0, 128); // Ensure volume is within valid range
                break;
            }
            case 11: {
                stopped = true;
                playing = false;
                cv.notify_all();
                musicThread.join();
                cleanUpSDL();
                return 0;
            }
            default: {
                std::cout << "Unknown choice. Please try again." << std::endl;
                break;
            }
        }
    }

    return 0;
}
