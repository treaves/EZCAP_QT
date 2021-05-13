# src/main/cpp/lib

# ######################################################################################################################
# ##########                                      Library Source Files                                        ##########
set(SOURCES
    disktools.cpp
    dllqhyccd.cpp
    downloadCapThread.cpp
    downloadFocThread.cpp
    downloadPreThread.cpp
)

set(HEADERS
    CyAPI.hpp
    CyUSB30_def.hpp
    disktools.hpp
    dllqhyccd.hpp
    downloadCapThread.hpp
    downloadFocThread.hpp
    downloadPreThread.hpp
    myStruct.hpp
    qhyccdstruct.hpp
)

add_library(ezcap STATIC ${SOURCES} ${HEADERS})

target_link_libraries(
  ezcap
  PUBLIC Qt5::Core
  PRIVATE project_warnings project_options
)
target_include_directories(ezcap PUBLIC ${CMAKE_CURRENT_LIST_DIR})
