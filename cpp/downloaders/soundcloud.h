#pragma once

#pragma push_macro("slots")
#undef slots
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#pragma pop_macro("slots")

#include <string>
#include <vector>
#include <optional>
#include <QUrl>
#include <QObject>

namespace py = pybind11;

// Data structures for SoundCloud items
struct SoundcloudItem {
    std::string type;         // "track" or "playlist"
    std::string title;
    std::string artist;       // only valid for tracks
    std::string permalink_url;
    std::string artwork_url;
    int64_t duration = 0;     // in milliseconds

    // For tracks
    bool downloadable = false;

    // For playlists
    int track_count = 0;
};

class SoundcloudWrapper {
private:
    py::object api_instance;

    // URL-encode a search string
    std::string encodeSearchString(const std::string& query) const;

public:
    // Constructor takes the path to the sc-lib-fork directory
    SoundcloudWrapper(const std::string& repo_path);
    ~SoundcloudWrapper();

    // Search API with proper encoding
    std::vector<SoundcloudItem> search(const std::string& search_str, int limit = 10, int offset = 0);

    // Resolve a URL to an item
    std::optional<SoundcloudItem> resolve(const std::string& url);

    // Download a track
    bool downloadTrack(const std::string& track_url, const std::string& filename);

    // Stream URL (for playing without downloading)
    std::string getStreamUrl(const std::string& track_url);
};


