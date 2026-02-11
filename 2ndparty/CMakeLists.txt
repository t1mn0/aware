include(FetchContent)

FetchContent_Declare(
    eav-lib
    GIT_REPOSITORY https://github.com/t1mn0/eav.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(eav-lib)
