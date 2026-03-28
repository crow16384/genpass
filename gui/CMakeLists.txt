find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(GUI_TARGET genpass-gui)
set(GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${GUI_TARGET} WIN32 MACOSX_BUNDLE
    gui_app.cpp
    main_frame.cpp
)

target_link_libraries(${GUI_TARGET} PRIVATE ${LIB_NAME} ${wxWidgets_LIBRARIES})

if(APPLE)
  set(APP_ICON_ICNS ${CMAKE_CURRENT_BINARY_DIR}/AppIcon.icns)

  add_custom_command(
    OUTPUT ${APP_ICON_ICNS}
    COMMAND /bin/sh ${GUI_DIR}/macos/make_icns.sh ${APP_ICON_ICNS}
    DEPENDS ${GUI_DIR}/macos/make_icns.sh
    COMMENT "Generating AppIcon.icns for macOS bundle"
    VERBATIM
  )
  add_custom_target(genpass_gui_icon DEPENDS ${APP_ICON_ICNS})
  add_dependencies(${GUI_TARGET} genpass_gui_icon)

  target_sources(${GUI_TARGET} PRIVATE ${APP_ICON_ICNS})
  set_source_files_properties(${APP_ICON_ICNS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

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
