cmake_minimum_required(VERSION 3.13)

project(cmaketest2 VERSION 1.0)

option(USE_MATH "Math library" ON)

configure_file(cmaketest2Config.h.in cmaketest2Config.h)

if(USE_MATH)
    message(STATUS "USE_MATH is ON")
    add_subdirectory(Math)
    list(APPEND EXTRA_LIB_DIRS ${PROJECT_BINARY_DIR}/Math)
    list(APPEND EXTRA_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Math)
    list(APPEND EXTRA_LIBS Math)
endif()

if(NOT USE_MATH)
    message(STATUS "USE_MATH is OFF")
endif()


#dependent libraries 
find_library(myglewlib glew NAMES glew2 GLEW GLEW2 DOC "glew library")
if(${myglewlib} STREQUAL "myglewlib-NOTFOUND")
    message(FATAL_ERROR "${myglewlib} no glew found. please install.")
else()
    message(STATUS "glew found! as ${myglewlib}")
endif()

find_library(myglulib glu NAMES GLU DOC "glu library")
if(${myglulib} STREQUAL "myglulib-NOTFOUND")
    message(FATAL_ERROR "${myglulib} no glu found. please install.")
else()
    message(STATUS "glu found! as ${myglulib}")
endif()

find_library(mygllib gl NAMES GL DOC "gl library")
if(${mygllib} STREQUAL "mygllib-NOTFOUND")
    message(FATAL_ERROR "${mygllib} no gl found. please install.")
else()
    message(STATUS "gl found! as ${mygllib}")
endif()



find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please check.")
        endif()
    endif()
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please check")
endif()

add_subdirectory(external/glfw)

add_executable(cmaketest2 main.cpp)

target_include_directories(cmaketest2 
    PUBLIC external/glfw/include
    PUBLIC ${PROJECT_BINARY_DIR}
    PUBLIC ${EXTRA_INCLUDE_DIRS}
)
target_link_directories(cmaketest2 
    PUBLIC external/glfw/src
    PUBLIC ${EXTRA_LIB_DIRS}
)

target_link_libraries(cmaketest2 glfw ${EXTRA_LIBS} ${myglewlib} ${myglulib} ${mygllib})


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/cmaketest2Config.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${cmaketest2_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${cmaketest2_VERSION_MINOR}")
include(CPack)