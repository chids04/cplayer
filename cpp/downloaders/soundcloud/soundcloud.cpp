#include "soundcloud.h"

#include <iostream>
#include <regex>
#include <QUrlQuery>
#include <filesystem>

SoundcloudWrapper::SoundcloudWrapper(const std::string& repo_path) {
    try {
        // Ensure the interpreter is acquired
        py::gil_scoped_acquire gil;

        // Use site.addsitedir with predefined paths
        py::module_ site = py::module_::import("site");
        site.attr("addsitedir")(SC_LIB_PATH);  // For sclib (extern/sc-lib-fork)
        site.attr("addsitedir")(PY_LIB_PATH);  // For python-libs (extern/python-libs)

        // Debug: Print sys.path to verify
        py::print(py::module_::import("sys").attr("path"));

        // Import sclib.sync and initialize SoundcloudAPI
        py::module_ sclib = py::module_::import("sclib.sync");
        api_instance = sclib.attr("SoundcloudAPI")();

        std::cout << "SoundcloudAPI initialized with SC_LIB_PATH: " << SC_LIB_PATH 
            << " and PY_LIB_PATH: " << PY_LIB_PATH << std::endl;
    }
    catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

SoundcloudWrapper::~SoundcloudWrapper() {
    // Not strictly necessary due to GIL management, but good practice
    py::gil_scoped_acquire gil;
    api_instance = py::none();
}

std::string SoundcloudWrapper::encodeSearchString(const std::string& query) const {
    // Trim whitespace and encode spaces as %20
    std::string trimmed;

    // Trim leading whitespace
    auto start = query.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";  // All whitespace
    }

    // Trim trailing whitespace
    auto end = query.find_last_not_of(" \t\r\n");
    trimmed = query.substr(start, end - start + 1);

    // Replace spaces with %20
    std::string result;
    for (char c : trimmed) {
        if (c == ' ') {
            result += "%20";
        } else {
            result += c;
        }
    }

    return result;
}

std::vector<SoundcloudItem> SoundcloudWrapper::search(const std::string& search_str, int limit, int offset) {
    py::gil_scoped_acquire gil;
    std::vector<SoundcloudItem> results;

    std::string query = encodeSearchString(search_str);

    try {
        // Search using the API
        py::list py_results = api_instance.attr("search")(query, limit, offset);

        // Convert Python results to C++ objects
        for (const auto& py_item : py_results) {
            SoundcloudItem item;

            // Get the kind (track or playlist)
            std::string kind = py::str(py_item.attr("kind"));
            item.type = kind;

            // Common attributes
            item.title = py::str(py_item.attr("title"));
            item.permalink_url = py::str(py_item.attr("permalink_url"));

            // Get the artwork URL if available
            if (py::hasattr(py_item, "artwork_url") && !py_item.attr("artwork_url").is_none()) {
                item.artwork_url = py::str(py_item.attr("artwork_url"));
            }

            // Get duration
            if (py::hasattr(py_item, "duration") && !py_item.attr("duration").is_none()) {
                item.duration = py::int_(py_item.attr("duration"));
            }

            // Track-specific attributes
            if (kind == "track") {
                if (py::hasattr(py_item, "artist") && !py_item.attr("artist").is_none()) {
                    item.artist = py::str(py_item.attr("artist"));
                }
                else if(kind == "playlist" || "system-playlist"){
                    if(py::hasattr(py_item, "label_name") && !py_item.attr("label_name").is_none()){
                        item.artist = py::str(py_item.attr("label_name"));
                    }
                }

                // Check if downloadable
                if (py::hasattr(py_item, "downloadable") && !py_item.attr("downloadable").is_none()) {
                    item.downloadable = py::bool_(py_item.attr("downloadable"));
                }
            }
            // Playlist-specific attributes
            else if (kind == "playlist" || kind == "system-playlist") {
                // Get track count
                if (py::hasattr(py_item, "track_count") && !py_item.attr("track_count").is_none()) {
                    item.track_count = py::int_(py_item.attr("track_count"));
                }

                if(py::hasattr(py_item, "is_album") && !py_item.attr("is_album").is_none()){
                    item.isAlbum  = py::bool_(py_item.attr("is_album"));
                }

                //now need to get all the songs in the album
                
                std::vector<SoundcloudItem> tracks;
                py_item.attr("clean_attributes")();

                // Get the list of tracks from the playlist/album
                py::list py_tracks = py_item.attr("tracks");
                for (const auto& py_track : py_tracks) {
                    SoundcloudItem item;

                    // Fill in common track attributes
                    if (py::hasattr(py_track, "title"))
                        item.title = py::str(py_track.attr("title"));
                    if (py::hasattr(py_track, "permalink_url"))
                        item.permalink_url = py::str(py_track.attr("permalink_url"));
                    if (py::hasattr(py_track, "artist") && !py_track.attr("artist").is_none())
                        item.artist = py::str(py_track.attr("artist"));
                    if (py::hasattr(py_item, "artwork_url") && !py_item.attr("artwork_url").is_none()) {
                        item.artwork_url = py::str(py_item.attr("artwork_url"));
                    }
                    // You can also extract additional fields as needed

                    tracks.push_back(item);
                }

                item.playlist_tracks = tracks;
            }

            results.push_back(item);
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error in search: " << ex.what() << std::endl;
    }

    return results;
}

std::optional<SoundcloudItem> SoundcloudWrapper::resolve(const std::string& url) {
    py::gil_scoped_acquire gil;

    try {
        py::object item = api_instance.attr("resolve")(url);

        // Create a SoundcloudItem from the Python object
        SoundcloudItem result;

        // Get the kind (track or playlist)
        std::string kind = py::str(item.attr("kind"));
        result.type = kind;

        // Common attributes
        result.title = py::str(item.attr("title"));
        result.permalink_url = py::str(item.attr("permalink_url"));

        // Get the artwork URL if available
        if (py::hasattr(item, "artwork_url") && !item.attr("artwork_url").is_none()) {
            result.artwork_url = py::str(item.attr("artwork_url"));
        }

        // Get duration
        if (py::hasattr(item, "duration") && !item.attr("duration").is_none()) {
            result.duration = py::int_(item.attr("duration"));
        }

        // Track-specific attributes
        if (kind == "track") {
            if (py::hasattr(item, "artist") && !item.attr("artist").is_none()) {
                result.artist = py::str(item.attr("artist"));
            }

            // Check if downloadable
            if (py::hasattr(item, "downloadable") && !item.attr("downloadable").is_none()) {
                result.downloadable = py::bool_(item.attr("downloadable"));
            }
        }
        // Playlist-specific attributes
        else if (kind == "playlist" || kind == "system-playlist") {
            // Get track count
            if (py::hasattr(item, "track_count") && !item.attr("track_count").is_none()) {
                result.track_count = py::int_(item.attr("track_count"));
            }
        }

        return result;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error in resolve: " << ex.what() << std::endl;
        return std::nullopt;
    }
}

bool SoundcloudWrapper::downloadTrack(const std::string& track_url, const std::string& filename) {
    py::gil_scoped_acquire gil;
    try {
        py::object track_obj = api_instance.attr("resolve")(track_url);

        // Validate that the item is a track
        if (!py::hasattr(track_obj, "artist") || track_obj.attr("artist").is_none()) {
            throw std::runtime_error("The resolved URL is not a track.");
        }

        // Use Python's built-in open() to create a file object in binary mode
        py::object builtins = py::module::import("builtins");
        py::object file = builtins.attr("open")(filename, "wb+");

        // Debug output
        std::cout << "Downloading track: " << py::str(track_obj.attr("title")) << std::endl;

        // Call the track's write_mp3_to(file) method
        track_obj.attr("write_mp3_to")(file);

        // Close the file
        file.attr("close")();

        std::cout << "Download completed: " << filename << std::endl;
        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error in downloadTrack: " << ex.what() << std::endl;
        return false;
    }
}

std::string SoundcloudWrapper::getStreamUrl(const std::string& track_url) {
    py::gil_scoped_acquire gil;
    try {
        py::object track_obj = api_instance.attr("resolve")(track_url);

        // Validate that the item is a track
        if (!py::hasattr(track_obj, "artist") || track_obj.attr("artist").is_none()) {
            throw std::runtime_error("The resolved URL is not a track.");
        }

        // Get the stream URL
        return py::str(track_obj.attr("get_stream_url")());
    }
    catch (const std::exception& ex) {
        std::cerr << "Error getting stream URL: " << ex.what() << std::endl;
        return "";
    }
}
