macro(enable_cppcheck)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
        # Enable all warnings that are actionable by the user of this toolset style should enable the other 3, but we'll be explicit just in case
        set(CMAKE_CXX_CPPCHECK
            ${CPPCHECK}
            --enable=style,performance,warning,portability
            --inline-suppr
            # We cannot act on a bug/missing feature of cppcheck
            --suppress=internalAstError
            # if a file does not have an internalAstError, we get an unmatchedSuppression error
            --suppress=unmatchedSuppression
            --inconclusive)
        if(NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
            set(CMAKE_CXX_CPPCHECK ${CMAKE_CXX_CPPCHECK} --std=c++${CMAKE_CXX_STANDARD})
        endif()
        if(WARNINGS_AS_ERRORS)
            list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
        endif()
    else()
        message(${WARNING_MESSAGE} "cppcheck requested but executable not found")
    endif()
endmacro()

macro(enable_clang_tidy)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        # construct the clang-tidy command line
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
        # set standard
        if(NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
            if("${CMAKE_CXX_CLANG_TIDY_DRIVER_MODE}" STREQUAL "cl")
                set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
            else()
                set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
            endif()
        endif()
        # set warnings as errors
        if(WARNINGS_AS_ERRORS)
            list(APPEND CMAKE_CXX_CLANG_TIDY -warnings-as-errors=*)
        endif()
    else()
        message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
    endif()
endmacro()

macro(enable_include_what_you_use)
    find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
    if(INCLUDE_WHAT_YOU_USE)
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
    else()
        message(${WARNING_MESSAGE} "include-what-you-use requested but executable not found")
    endif()
endmacro()
