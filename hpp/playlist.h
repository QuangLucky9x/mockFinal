#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>

void createPlaylist(const std::string& name);
void updatePlaylist(const std::string& name, const std::string& mediaFile);
void deletePlaylist(const std::string& name);
void displayPlaylists();
extern std::vector<std::string> playlist;

#endif // PLAYLIST_H
