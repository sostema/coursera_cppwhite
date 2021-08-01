get_filename_component(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" CurrentDir ${CurrentDir})
set(ParentProject ${ParentProject}_${CurrentDir})

FILE(GLOB subdirectories "./*")

foreach (subdirectory IN ITEMS ${subdirectories})
    IF (IS_DIRECTORY ${subdirectory} AND EXISTS ${subdirectory}/CMakeLists.txt)
        add_subdirectory(${subdirectory})
    endif ()
endforeach ()