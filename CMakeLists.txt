cmake_minimum_required(VERSION 3.16...3.21)

# Change obs-plugintemplate to your plugin's name in a machine-readable format
# (e.g.: obs-myawesomeplugin) and set
project(iklanlive-plugin VERSION 1.0.0)
add_library(${CMAKE_PROJECT_NAME}
    MODULE
    src/dialog/LoginDialog.ui
)

# Replace `Your Name Here` with the name (yours or your organization's) you want
# to see as the author of the plugin (in the plugin's metadata itself and in the
# installers)
set(PLUGIN_AUTHOR "Iklanlive")

# Replace `com.example.obs-plugin-template` with a unique Bundle ID for macOS
# releases (used both in the installer and when submitting the installer for
# notarization)
set(MACOS_BUNDLEID "com.example.${CMAKE_PROJECT_NAME}")

# Replace `me@contoso.com` with the maintainer email address you want to put in
# Linux packages
set(LINUX_MAINTAINER_EMAIL "me@mymailhost.com")

# Add your custom source files here - header files are optional and only
# required for visibility e.g. in Xcode or Visual Studio
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  src/plugin-main.cpp
  src/component/Menu.cpp
  src/component/Menu.h
  src/dialog/LoginDialog.cpp
  src/dialog/LoginDialog.h
  src/api/Auth/User.cpp
  src/api/Auth/User.h
  src/api/Auth/Login.cpp
  src/api/Auth/Login.h
  src/api/Config/PluginConfig.cpp
  src/api/Config/PluginConfig.h
)

# find_package(cpr CONFIG REQUIRED)
# target_link_libraries(main PRIVATE cpr::cpr)

include(FetchContent)
FetchContent_Declare(cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG ee7f91f5566b6279aadf6d0b1aaf56b11963f527
) # The commit hash for 1.8.2. Replace with the latest from: https://github.com/libcpr/cpr/releases

FetchContent_MakeAvailable(cpr)

target_link_libraries(iklanlive-plugin PRIVATE cpr::cpr)

include(FetchContent)
# Optional: set this to ON if your target publicly links to nlohmann_json and needs to install() 
# set(JSON_Install ON)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
  GIT_TAG v3.10.5)

FetchContent_MakeAvailable(json)

target_link_libraries(iklanlive-plugin PRIVATE
        nlohmann_json::nlohmann_json)

# /!\ TAKE NOTE: No need to edit things past this point /!\
if(!OS_LINUX)
  find_package(libobs REQUIRED)
  find_package(obs-frontend-api REQUIRED)
endif()

include(cmake/ObsPluginHelpers.cmake)
# find_qt(VERSION ${QT_VERSION} COMPONENTS Widgets Core)
find_package(Qt5 COMPONENTS Widgets Core)

configure_file(src/plugin-macros.h.in
  ${CMAKE_SOURCE_DIR}/src/plugin-macros.generated.h)

target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE src/plugin-macros.generated.h)

# --- Platform-independent build settings ---

if(OS_LINUX)
  target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
      /usr/include/obs
  )
else()
  target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/src
  )
endif()


if(!OS_LINUX)
target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE
     OBS::libobs
     OBS::obs-frontend-api
     Qt::Core
     Qt::Widgets)
else()
  target_link_libraries(
     ${CMAKE_PROJECT_NAME} PRIVATE
     Qt::Core
     Qt::Widgets)
endif()

set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

# --- End of section ---

# --- Windows-specific build settings and tasks ---
if(OS_WINDOWS)
  configure_file(cmake/bundle/windows/installer-Windows.iss.in
                 ${CMAKE_BINARY_DIR}/installer-Windows.generated.iss)

  if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /MP /d2FH4-)
  endif()
  # --- End of section ---

  # -- macOS specific build settings and tasks --
elseif(OS_MACOS)
  configure_file(cmake/bundle/macos/installer-macOS.pkgproj.in
                 ${CMAKE_BINARY_DIR}/installer-macOS.generated.pkgproj)

  set(MACOSX_PLUGIN_GUI_IDENTIFIER "${MACOS_BUNDLEID}")
  set(MACOSX_PLUGIN_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
  set(MACOSX_PLUGIN_SHORT_VERSION_STRING "1")

  target_compile_options(
    ${CMAKE_PROJECT_NAME}
    PRIVATE -Wall -Wextra -Werror-implicit-function-declaration -stdlib=libc++
      -fvisibility=default)

  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "")
  # --- End of section ---

  # --- Linux-specific build settings and tasks ---
else()
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)

  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "")
endif()
# --- End of section ---

setup_plugin_target(${CMAKE_PROJECT_NAME})
