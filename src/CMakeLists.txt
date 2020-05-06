# Generic test that uses conan libs
add_library(SpotifyWebApiAdapter detail/SpotifyNetworkManager.hpp
        AuthentificationToken.hpp detail/BaseModel.hpp
        Authentification.hpp detail/HttpHelper.hpp model/accesstoken.hpp detail/SpotifyNetworkManager.cpp model/accesstoken.cpp detail/BaseModel.cpp detail/HttpHelper.cpp AuthentificationToken.cpp Authentification.cpp model/playlistdata.cpp model/playlistdata.hpp model/image.cpp model/image.hpp model/page.cpp model/page.hpp model/followers.cpp model/followers.hpp model/user.cpp model/user.hpp model/artist.cpp model/artist.hpp model/track_album.cpp model/track_album.hpp model/playlisttrack.cpp model/playlisttrack.hpp model/playlist.cpp model/playlist.hpp model/savedtrack.cpp model/savedtrack.hpp)

if ($ENV{CLION_IDE})
    set(CMAKE_PREFIX_PATH /Users/michaelwittmann/Qt/5.14.2/clang_64/lib/cmake/Qt5;/usr/local/include/stlab)
endif ()

find_package(Qt5 COMPONENTS Core Network REQUIRED)

target_compile_definitions(SpotifyWebApiAdapter
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(
        SpotifyWebApiAdapter PRIVATE project_options project_warnings
        CONAN_PKG::catch2
        #CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::openssl
        #CONAN_PKG::boost
        CONAN_PKG::nlohmann_json
        CONAN_PKG::stlab
        Qt5::Core
        Qt5::Network
)
