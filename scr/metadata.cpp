#include "metadata.h"
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>

void displayAudioMetadata(const std::string& filePath) {
    TagLib::FileRef file(filePath.c_str());

    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();

        std::cout << "Title: " << tag->title() << std::endl;
        std::cout << "Artist: " << tag->artist() << std::endl;
        std::cout << "Album: " << tag->album() << std::endl;
        std::cout << "Genre: " << tag->genre() << std::endl;
        std::cout << "Year: " << tag->year() << std::endl;

        if (file.audioProperties()) {
            TagLib::AudioProperties* properties = file.audioProperties();
            std::cout << "Duration: " << properties->lengthInSeconds() << " seconds" << std::endl;
        }
    } else {
        std::cout << "Could not read metadata from " << filePath << std::endl;
    }
}
