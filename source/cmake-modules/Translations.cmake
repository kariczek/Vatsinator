file (GLOB TRANSLATION_SOURCES
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/translations/${CMAKE_PROJECT_NAME}-*.ts")

file (GLOB LANGUAGE_FILES
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/translations/*.language")

qt4_add_translation (vatsinator_TRANSLATIONS ${TRANSLATION_SOURCES})
