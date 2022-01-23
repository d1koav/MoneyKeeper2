cmake_minimum_required(VERSION 3.15)
project(kurs LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



#Укажите путь до папки с библиотеками QT ("папка, куда был установлен QT"/"версия QT"/"mingw или msvc папка"/)
set(CMAKE_PREFIX_PATH /Users/vladislavdyakov/Qt/1/5.15.2/clang_64)
find_package(Qt5 COMPONENTS Widgets Core Gui Sql REQUIRED)

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        *.db)
add_executable(kurs ${SOURCE_FILES})
target_link_libraries(kurs PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Sql)
#
#FIND_PACKAGE(Doxygen)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)





install(FILES ${QM} DESTINATION bin)

install(TARGETS kurs DESTINATION bin)

install(FILES ${PROJECT_SOURCE_DIR}/project.db DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/documentation/ DESTINATION bin/docs/)

install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Sql> DESTINATION bin)


install(FILES $<TARGET_FILE:Qt5::QSQLiteDriverPlugin> DESTINATION bin/sqldrivers)

install(FILES $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> DESTINATION bin/platforms)
install(FILES $<TARGET_FILE:Qt5::QWindowsDirect2DIntegrationPlugin> DESTINATION bin/platforms)
