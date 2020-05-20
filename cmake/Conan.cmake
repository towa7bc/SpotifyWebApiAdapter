macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(
                STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD
                "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME bincrafters URL
            https://api.bintray.com/conan/bincrafters/public-conan)

    conan_add_remote(NAME manu343726 URL
            https://api.bintray.com/conan/manu343726/conan-packages)

    conan_cmake_run(
            REQUIRES
            ${CONAN_EXTRA_REQUIRES}
            stlab/1.5.2
            catch2/2.12.0
            # fmt/6.1.2
            spdlog/1.5.0
            #openssl/1.1.1f
            # boost/1.69.0
            nlohmann_json/3.7.3
            OPTIONS
            boost:shared=True
            boost:without_chrono=False
            boost:without_system=False
            boost:without_timer=False
            boost:without_test=False
            boost:without_iostreams=True
            boost:without_log=True
            boost:without_regex=True
            boost:without_locale=True
            boost:without_exception=True
            boost:without_filesystem=True
            boost:without_container=True
            boost:without_program_options=True
            boost:without_wave=True
            boost:without_thread=True
            boost:without_graph_parallel=True
            boost:without_context=True
            boost:without_random=True
            boost:without_graph=True
            boost:without_serialization=True
            boost:without_date_time=False
            boost:without_fiber=True
            boost:without_coroutine=True
            boost:without_mpi=True
            boost:without_type_erasure=True
            boost:without_math=True
            boost:without_container=True
            boost:without_log=True
            boost:without_exception=True
            boost:without_python=True
            boost:without_stacktrace=True
            boost:without_atomic=True
            ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
            CMAKE_TARGETS # individual targets to link to
            BUILD
            missing)
endmacro()
