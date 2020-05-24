# Generic test that uses conan libs
add_library(
        SpotifyWebApiAdapter
        detail/SpotifyNetworkManager.hpp
        detail/SpotifyNetworkManager.cpp
        detail/BaseModel.hpp
        detail/BaseModel.cpp
        detail/HttpHelper.hpp
        detail/HttpHelper.cpp
        model/modeldata.hpp
        model/modeldata.cpp
        AuthenticationToken.hpp
        AuthenticationToken.cpp
        Authentication.hpp
        Authentication.cpp
        User.hpp
        User.cpp
        PlaylistTrack.hpp
        PlaylistTrack.cpp
        Image.hpp
        Image.cpp
        Artist.hpp
        Artist.cpp
        Track.hpp
        Track.cpp
        Album.hpp
        Album.cpp
        Page.hpp
        Page.cpp
        Playlist.hpp
        Playlist.cpp
        Browse.cpp
        Browse.hpp
        Followers.hpp
        Followers.cpp
        detail/Core.hpp
        detail/Log.cpp
        detail/Log.hpp)

set(CMAKE_PREFIX_PATH
        /usr/local/Cellar/qt/5.14.2;C:\\Qt\\5.14.2\\msvc2017_64\\;/usr/local/include/stlab
        )

find_package(
        Qt5
        COMPONENTS Core Network
        REQUIRED)

target_compile_definitions(
        SpotifyWebApiAdapter
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(
        SpotifyWebApiAdapter
        PRIVATE project_options
        project_warnings
        CONAN_PKG::catch2
        # CONAN_PKG::fmt
        CONAN_PKG::spdlog
        # CONAN_PKG::openssl
        # CONAN_PKG::boost
        CONAN_PKG::nlohmann_json
        CONAN_PKG::stlab
        Qt5::Core
        Qt5::Network)
