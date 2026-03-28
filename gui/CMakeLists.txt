find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(GUI_TARGET genpass-gui)
set(GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ICON_ICNS ${GUI_DIR}/AppIcon.icns)

add_executable(${GUI_TARGET} WIN32 MACOSX_BUNDLE
    gui_app.cpp
    main_frame.cpp
)

target_link_libraries(${GUI_TARGET} PRIVATE ${LIB_NAME} ${wxWidgets_LIBRARIES})

if(APPLE)
  if(NOT EXISTS ${APP_ICON_ICNS})
    execute_process(
      COMMAND /bin/sh ${GUI_DIR}/macos/make_icns.sh
      WORKING_DIRECTORY ${GUI_DIR}
      RESULT_VARIABLE ICON_GEN_RESULT
      OUTPUT_QUIET
      ERROR_QUIET
    )
  endif()

  if(EXISTS ${APP_ICON_ICNS})
    target_sources(${GUI_TARGET} PRIVATE ${APP_ICON_ICNS})
    set_source_files_properties(${APP_ICON_ICNS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  endif()

  set_target_properties(${GUI_TARGET} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "GenPass"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.genpass.gui"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    MACOSX_BUNDLE_ICON_FILE "AppIcon.icns"
  )
  install(TARGETS ${GUI_TARGET} BUNDLE DESTINATION .)
elseif(WIN32)
  install(TARGETS ${GUI_TARGET} RUNTIME DESTINATION bin)
else()
  install(TARGETS ${GUI_TARGET} RUNTIME DESTINATION bin)
endif()
