# Generic test that uses conan libs
add_library(SpotifyWebApiAdapter SpotifyWebApiAdapter.cpp SpotifyWebApiAdapter.h SpotifyNetworkManager.cpp SpotifyNetworkManager.h
        AuthentificationToken.cpp AuthentificationToken.h)

if ($ENV{CLION_IDE})
    set(CMAKE_PREFIX_PATH /Users/michaelwittmann/Qt/5.14.2/clang_64/lib/cmake/Qt5;/usr/local/include/stlab)
endif ()

find_package(Qt5 COMPONENTS Core Network REQUIRED)

target_compile_definitions(SpotifyWebApiAdapter
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(
        SpotifyWebApiAdapter PRIVATE project_options project_warnings
        CONAN_PKG::catch2
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::openssl
        #CONAN_PKG::boost
        CONAN_PKG::nlohmann_json
        CONAN_PKG::stlab
        Qt5::Core
        Qt5::Network
)
