find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(GUI_TARGET genpass-gui)

add_executable(${GUI_TARGET} WIN32 MACOSX_BUNDLE
    gui_app.cpp
    main_frame.cpp
)

target_link_libraries(${GUI_TARGET} PRIVATE ${LIB_NAME} ${wxWidgets_LIBRARIES})

if(APPLE)
  set_target_properties(${GUI_TARGET} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "GenPass"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.genpass.gui"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
  )
  install(TARGETS ${GUI_TARGET} BUNDLE DESTINATION .)
elseif(WIN32)
  install(TARGETS ${GUI_TARGET} RUNTIME DESTINATION bin)
else()
  install(TARGETS ${GUI_TARGET} RUNTIME DESTINATION bin)
endif()
