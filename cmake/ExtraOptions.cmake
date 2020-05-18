function(set_project_extra_options project_name)
    option(EXTRA_OPTION_ENABLE "Enable the extra options" TRUE)
    option(TIME_TRACE_ENABLE "Enable the -ftime-trace option" FALSE)

    if (EXTRA_OPTION_ENABLE)
        if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
            if (CMAKE_BUILD_TYPE MATCHES "Release")
                set(EXTRA_OPTIONS -flto=thin)
            endif ()
            if (TIME_TRACE_ENABLE)
                set(EXTRA_OPTIONS ${EXTRA_OPTIONS} -ftime-trace)
            endif ()
        endif ()
    endif ()

    target_compile_options(${project_name} INTERFACE ${EXTRA_OPTIONS})

endfunction()
