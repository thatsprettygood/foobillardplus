cmake_minimum_required(VERSION 3.16)
project(foobillardplus VERSION 3.43 LANGUAGES C)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)

option(FOOBILLARDPLUS_MATH_SINGLE "Use single-precision vector math" ON)
option(FOOBILLARDPLUS_NETWORK "Build network play support" ON)
option(FOOBILLARDPLUS_SOUND "Build sound and music support" ON)
option(FOOBILLARDPLUS_TOUCH "Build generic touch-device support" OFF)
option(FOOBILLARDPLUS_WETAB "Build for the WeTab tablet (also enables touch support)" OFF)
option(FOOBILLARDPLUS_SSE "Use SSE intrinsics (x86 only; forces single precision)" OFF)
option(FOOBILLARDPLUS_FAST_MATH "Use the game's approximate fast-math routines" OFF)
option(FOOBILLARDPLUS_NVIDIA "Enable NVIDIA-specific extensions" OFF)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
if(FOOBILLARDPLUS_NETWORK)
    pkg_check_modules(SDL2_NET REQUIRED IMPORTED_TARGET SDL2_net)
endif()
if(FOOBILLARDPLUS_SOUND)
    pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
endif()

set(FOOBILLARDPLUS_SOURCES
    src/aiplayer.c
    src/ball.c
    src/billard.c
    src/billard3d.c
    src/billmove.c
    src/bottle.c
    src/bumpref.c
    src/cartoonguy.c
    src/ceilinglamp_high.c
    src/chess.c
    src/evaluate_move.c
    src/fire.c
    src/fireplace_high.c
    src/flower.c
    src/font.c
    src/getopt_long.c
    src/helpscreen.c
    src/history.c
    src/language.c
    src/menu.c
    src/mesh.c
    src/net_socket.c
    src/options.c
    src/png_loader.c
    src/queue.c
    src/room.c
    src/sittingboy.c
    src/sound_stuff.c
    src/sys_stuff.c
    src/table.c
    src/textobj.c
    src/vmath.c
)

add_executable(foobillardplus ${FOOBILLARDPLUS_SOURCES})
target_include_directories(foobillardplus PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_compile_features(foobillardplus PRIVATE c_std_99)
set_target_properties(foobillardplus PROPERTIES C_EXTENSIONS ON)
target_compile_options(foobillardplus PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall>
)
target_link_libraries(foobillardplus PRIVATE
    PkgConfig::SDL2
    OpenGL::GL
    OpenGL::GLU
    PNG::PNG
    Freetype::Freetype
    m
)

if(FOOBILLARDPLUS_MATH_SINGLE OR FOOBILLARDPLUS_SSE)
    target_compile_definitions(foobillardplus PRIVATE VMATH_SINGLE_PRECISION)
endif()
if(FOOBILLARDPLUS_NETWORK)
    target_compile_definitions(foobillardplus PRIVATE NETWORKING)
    target_link_libraries(foobillardplus PRIVATE PkgConfig::SDL2_NET)
endif()
if(FOOBILLARDPLUS_SOUND)
    target_compile_definitions(foobillardplus PRIVATE USE_SOUND)
    target_link_libraries(foobillardplus PRIVATE PkgConfig::SDL2_MIXER)
endif()
if(FOOBILLARDPLUS_TOUCH OR FOOBILLARDPLUS_WETAB)
    target_compile_definitions(foobillardplus PRIVATE TOUCH)
endif()
if(FOOBILLARDPLUS_WETAB)
    target_compile_definitions(foobillardplus PRIVATE WETAB)
endif()
if(FOOBILLARDPLUS_SSE)
    if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64|i.86)$")
        message(FATAL_ERROR "FOOBILLARDPLUS_SSE is supported only on x86 processors")
    endif()
    target_compile_definitions(foobillardplus PRIVATE USE_SSE)
    target_compile_options(foobillardplus PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-msse>
    )
endif()
if(FOOBILLARDPLUS_FAST_MATH)
    target_compile_definitions(foobillardplus PRIVATE FAST_MATH)
endif()
if(NOT FOOBILLARDPLUS_NVIDIA)
    target_compile_definitions(foobillardplus PRIVATE NO_NV_BUMPREF NO_NV_FRESNEL)
endif()

# The game locates its assets in ../data relative to the installed executable.
install(TARGETS foobillardplus RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/data/" DESTINATION data)
install(FILES
    AUTHORS COPYING INSTALL README README.md ChangeLog NEWS TODO OFL.txt
    DESTINATION "${CMAKE_INSTALL_DATADIR}/doc/foobillardplus"
    OPTIONAL
)
