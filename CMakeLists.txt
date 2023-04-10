cmake_minimum_required(VERSION 3.16)

project(ContactsDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)


qt_add_executable(appContactsDisplay
    main.cpp contactitems.h contactitems.cpp
    contactsthread.h contactsthread.cpp
)


if(ANDROID)
    set_property(TARGET Qt::Core APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
        QT_ANDROID_EXPORTED_TARGET=appContactsDisplay) # Change "MyApp" to your target in set_target_properties()
    set_property(TARGET Qt::Core APPEND PROPERTY INTERFACE_COMPILE_FEATURES
        cxx_std_17)
endif()


qt_add_resources(appContactsDisplay "android"
    PREFIX /
    FILES
        android/AndroidManifest.xml
        android/build.gradle
        android/src/com/example/contactsdisplay/MainActivity.java
)


qt_add_qml_module(appContactsDisplay
    URI ContactsDisplay
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES ContactItem.qml
)

set_target_properties(appContactsDisplay PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

#set_property(TARGET appContactsDisplay APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

target_link_libraries(appContactsDisplay
    PRIVATE Qt6::Quick
)
target_link_libraries(appContactsDisplay PRIVATE Qt6::Core)

install(TARGETS appContactsDisplay
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})



#target_include_directories(appContactsDisplay PRIVATE ${android})
