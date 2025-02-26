cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

#CMake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(
    -Werror
    -Wall
)
project(clipboard-task)
set(CMAKE_AUTOMOC ON)
find_package(X11 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
set(SOURCE_FILES__ 
    main.cxx 
    clipboard_qt.h 
    clipboard_qt.cxx
    clipboard_x11.h 
    clipboard_x11.cxx
)
list(TRANSFORM SOURCE_FILES__ PREPEND "src/")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES__})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets stdc++fs X11)
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#CPack
set(CMAKE_INSTALL_PREFIX /opt/${CMAKE_PROJECT_NAME})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}
        DESTINATION bin
        PERMISSIONS WORLD_EXECUTE OWNER_WRITE OWNER_READ)

execute_process(COMMAND mkdir ${CMAKE_CURRENT_BINARY_DIR}/symlink)
execute_process(COMMAND ln -s /opt/${CMAKE_PROJECT_NAME}/bin/${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/symlink/${CMAKE_PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/symlink/clipboard-task
        DESTINATION /usr/bin/
        PERMISSIONS WORLD_EXECUTE WORLD_READ)

set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_CONTACT "chicherin.alexey@ya.ru")
set(CPACK_PACKAGE_HOMEPAGE "https://github.com/alec-chicherini/clipboard-task")
set(CPACK_PACKAGE_ARCHITECTURE amd64)
set(CPACK_PACKAGE_VERSION 01.00)
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE})

if(${QT_VERSION_MAJOR} EQUAL 5)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS libqt5widgets5|libqt5widgets5t64 libqt5gui5|libqt5gui5t64 libqt5core5|libqt5core5a|libqt5core5t64 )
elseif(${QT_VERSION_MAJOR} EQUAL 6)
    set(CPACK_DEBIAN_PACKAGE_DEPENDS libqt6widgets6|libqt6widgets6t64 libqt6gui6|libqt6gui6t64 libqt6core6|libqt6core6t64 )
else()
    message(FATAL_ERROR "Qt${QT_VERSION_MAJOR} not supported")
endif()

include(CPack)