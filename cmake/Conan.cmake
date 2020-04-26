macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(
                STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME bincrafters URL
            https://api.bintray.com/conan/bincrafters/public-conan)

    conan_cmake_run(
            REQUIRES
            ${CONAN_EXTRA_REQUIRES}
            catch2/2.12.0
            fmt/6.1.2
            spdlog/1.5.0
            openssl/1.1.1f
            boost/1.72.0
            nlohmann_json/3.7.3
            OPTIONS
            ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
            CMAKE_TARGETS # individual targets to link to
            BUILD
            missing)
endmacro()
