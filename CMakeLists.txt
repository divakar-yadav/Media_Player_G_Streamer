cmake_minimum_required(VERSION 3.16)

project(Media_Player VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt and required components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Set up translation files
set(TS_FILES Media_Player_en_US.ts)
set(PKG_CONFIG_PATH "C:/gstreamer/1.0/msvc_x86_64/lib/pkgconfig")

# GStreamer Integration: Set GStreamer path (adjust as needed)
set(GSTREAMER_DIR "C:/gstreamer/1.0/msvc_x86_64")

# GStreamer include directories
include_directories("${GSTREAMER_DIR}/include/gstreamer-1.0")
include_directories("${GSTREAMER_DIR}/include/glib-2.0")
include_directories("${GSTREAMER_DIR}/lib/glib-2.0/include")

# GStreamer link directories
link_directories("${GSTREAMER_DIR}/lib")

# Manually link GStreamer libraries for MSVC
set(GSTREAMER_LIBS
    "${GSTREAMER_DIR}/lib/gstreamer-1.0.lib"
    "${GSTREAMER_DIR}/lib/gobject-2.0.lib"
    "${GSTREAMER_DIR}/lib/glib-2.0.lib"
)

# Add the source files to the project
set(PROJECT_SOURCES
    Main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    VideoPlayer.cpp
    VideoPlayer.h
    ${TS_FILES}
)

# Add the executable for Qt6 or Qt5 based on the version
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Media_Player
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        SingleVideoPlayerScreen.h
        SingleVideoPlayerScreen.cpp
        DualVideoPlayerScreen.h
        DualVideoPlayerScreen.cpp
        CombinedVideoPlayerScreen.cpp
        CombinedVideoPlayerScreen.h
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Media_Player SHARED ${PROJECT_SOURCES})
    else()
        add_executable(Media_Player ${PROJECT_SOURCES})
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Link the necessary Qt libraries
target_link_libraries(Media_Player PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Link GStreamer libraries manually
target_link_libraries(Media_Player PRIVATE ${GSTREAMER_LIBS})

# Define properties for macOS or iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Media_Player)
endif()

set_target_properties(Media_Player PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install targets
include(GNUInstallDirs)
install(TARGETS Media_Player
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable for Qt
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Media_Player)
endif()
