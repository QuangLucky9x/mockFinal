#include "playlist.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

namespace fs = std::filesystem;

std::vector<std::string> playlist;

void createPlaylist(const std::string& name) {
    std::string playlistFile = "C:/Users/HP/Desktop/Mock/" + name + ".playlist";
    std::ofstream ofs(playlistFile);
    if (ofs) {
        ofs.close();
        std::cout << "Playlist " << name << " created successfully." << std::endl;
    } else {
        std::cout << "Failed to create playlist " << name << "." << std::endl;
    }
}

void updatePlaylist(const std::string& name, const std::string& mediaFile) {
    std::string playlistFile = "C:/Users/HP/Desktop/Mock/" + name + ".playlist";
    std::ofstream ofs(playlistFile, std::ios::app);
    if (ofs) {
        ofs << mediaFile << std::endl;
        ofs.close();
        std::cout << "Updated playlist " << name << " with " << mediaFile << "." << std::endl;
    } else {
        std::cout << "Failed to update playlist " << name << "." << std::endl;
    }
}

void deletePlaylist(const std::string& name) {
    std::string playlistFile = "C:/Users/HP/Desktop/Mock/" + name + ".playlist";
    if (fs::remove(playlistFile)) {
        std::cout << "Playlist " << name << " deleted successfully." << std::endl;
    } else {
        std::cout << "Failed to delete playlist " << name << "." << std::endl;
    }
}

void displayPlaylists() {
    for (const auto& entry : fs::directory_iterator("C:/Users/HP/Desktop/Mock")) {
        if (entry.path().extension() == ".playlist") {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }
}
