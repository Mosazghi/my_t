cmake_minimum_required(VERSION 3.7)
project(my_t)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/mosa/Qt/6.7.2/gcc_64/lib/cmake")

add_executable(${PROJECT_NAME} main.cpp)


set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

set(SOURCES
    main.cpp
    mainwindow.cpp
    console.cpp
    serialmanager.cpp
    settingsdialog.cpp
    toolbarmanager.cpp
    chartmanager.cpp
    resources.qrc
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets SerialPort Charts)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::SerialPort Qt6::Charts)

qt_standard_project_setup() # <-- 

install(TARGETS ${PROJECT_NAME}
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
) # <-- 

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script}) # <-- 
