# src/main/cpp/gui

# ######################################################################################################################
# ##########                                          Source Files                                            ##########
set(UIS
    ui/about.ui
    ui/cameraChooser.ui
    ui/cfwControl.ui
    ui/cfwSetup.ui
    ui/darkFrameTool.ui
    ui/ezCap.ui
    ui/favorite.ui
    ui/fitHeader.ui
    ui/managementMenu.ui
    ui/phdLink.ui
    ui/planner.ui
    ui/readmode.ui
    ui/tempControl.ui
)

set(SOURCES
    borderLayout.cpp
    delegate.cpp
    main.cpp
    mainMenu.cpp
    ui/about.cpp
    ui/cameraChooser.cpp
    ui/cfwControl.cpp
    ui/cfwSetup.cpp
    ui/darkFrameTool.cpp
    ui/ezCap.cpp
    ui/favorite.cpp
    ui/fitHeader.cpp
    ui/managementMenu.cpp
    ui/phdLink.cpp
    ui/planner.cpp
    ui/readmode.cpp
    ui/tempControl.cpp
)

set(HEADERS
    borderLayout.hpp
    delegate.hpp
    mainMenu.hpp
    ui/about.hpp
    ui/cameraChooser.hpp
    ui/cfwControl.hpp
    ui/cfwSetup.hpp
    ui/darkframetool.hpp
    ui/ezCap.hpp
    ui/favorite.hpp
    ui/fitHeader.hpp
    ui/managementMenu.hpp
    ui/phdLink.hpp
    ui/planner.hpp
    ui/readmode.hpp
    ui/tempControl.hpp
)

# ######################################################################################################################
# ##########                                       Executable Creation                                        ##########
if(APPLE)
  set(CMAKE_MACOSX_BUNDLE 1)
  set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

  set(MACOSX_BUNDLE_BUNDLE_NAME EXCap_Qt)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.qhyccd.EZCap_Qt")
  set(MACOSX_BUNDLE_INFO_STRING "An application to interact with QHYCCD Cameras")
  set(MACOSX_BUNDLE_ICON_FILE "Icon.icns")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${${PROJECT}_VERSION}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${${PROJECT}_MAJOR}.${${PROJECT}_MINOR}.${${PROJECT}_PATCH}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${${PROJECT}_VERSION}")

  set(ICON "${RESOURCES_DIRECTORY}/images/ezcap.icns")
  # put the icon into the Resources directory of the App bundle.
  set_source_files_properties(${ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  add_executable(EZCap_Qt MACOSX_BUNDLE ${HEADERS} ${SOURCES} ${UIS} ${RESOURCES} ${ICON})
else()
  add_executable(EZCap_Qt ${HEADERS} ${SOURCES} ${UIS} ${RESOURCES})
endif()

target_include_directories(EZCap_Qt PRIVATE ${OpenCV_INCLUSE_DIRS} ${CFITSIO_INCLUDE_DIRS})
target_link_libraries(
  EZCap_Qt
  PUBLIC Qt5::Core Qt5::Widgets
  PRIVATE ezcap project_warnings project_options ${OpenCV_LIBS} ${CFITSIO_LIBRARIES}
)

target_compile_features(EZCap_Qt PUBLIC cxx_nullptr cxx_lambdas)

# ######################################################################################################################
# ##########                                   Install & Apple app support                                    ##########
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

install(
  TARGETS EZCap_Qt
  DESTINATION .
  COMPONENT Runtime
)

if(APPLE)
  # Get reference to deployqt
  get_target_property(uic_location Qt5::uic IMPORTED_LOCATION)
  get_filename_component(_dir ${uic_location} DIRECTORY)
  set(deployqt "${_dir}/macdeployqt")
  if(NOT EXISTS ${deployqt})
    message(FATAL_ERROR "Failed to locate deployqt executable: [${deployqt}]")
  endif()

  # Execute deployqt during package creation See https://doc.qt.io/qt-5/osx-deployment.html#macdeploy
  install(CODE "set(deployqt \"${deployqt}\")" COMPONENT Runtime)
  install(CODE [===[
   execute_process(COMMAND "${deployqt}" "${CMAKE_INSTALL_PREFIX}/ROMControl.app")
   ]===] COMPONENT Runtime
  )

  set(CPACK_GENERATOR "DragNDrop")
  include(CPack)
endif()

# ######################################################################################################################
# ##########                                         CMake debugging                                          ##########
# #################### Troubleshoot cmake variables
# ~~~
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
# #################### Troubleshoot cmake variables
# ~~~
