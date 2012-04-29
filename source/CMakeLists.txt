set (vatsinator_TARGET
	vatsinator
)

if (MINGW)
	set(vatsinator_TARGET
		${vatsinator_TARGET}.exe)
endif (MINGW)

set (vatsinator_SRCS
	VatsinatorApplication.cpp
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	set (vatsinator_SRCS
		${vatsinator_SRCS} MemoryTracker.cpp
	)
endif (CMAKE_BUILD_TYPE MATCHES Debug)



set (vatsinator_MOC_SRCS
	VatsinatorApplication.h
)

set (vatsinator_SUBDIRS
	db
	network
	settings
	ui
	vatsimdata
)

qt4_wrap_cpp (vatsinator_MOC_FILES ${vatsinator_MOC_SRCS})

include (cmake/macros.cmake)


configure_file (${CMAKE_CURRENT_SOURCE_DIR}/vatsinator-version.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTNETWORK TRUE)

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(${QT_DEFINITIONS})

add_executable (${vatsinator_TARGET} WIN32
	main.cpp
	${vatsinator_SRCS}
	${vatsinator_MOC_FILES}
)

if (MINGW)
	set (vatsinator_LIBS
		mingw32
		${OPENGL_gl_LIBRARY}
		${QT_QTCORE_LIBRARY}
		${QT_QTGUI_LIBRARY}
		${QT_QTOPENGL_LIBRARY}
		${QT_QTNETWORK_LIBRARY}
	)
else (MINGW)
	# set -DPREFIX for defines.h
	set (CMAKE_CXX_FLAGS
		${CMAKE_CXX_FLAGS} -DPREFIX=\\"${CMAKE_INSTALL_PREFIX}\\"
	)

	set (vatsinator_LIBS
		${QT_LIBRARIES}
		${OPENGL_LIBRARY}
	)
endif (MINGW)

foreach (DIR ${vatsinator_SUBDIRS})
	add_subdirectory (${DIR})
	add_dependencies (${vatsinator_TARGET}
		${DIR}
	)
endforeach (DIR)
	
target_link_libraries (${vatsinator_TARGET}
	-Wl,--start-group
	-Wl,--whole-archive
	${vatsinator_SUBDIRS}
	-Wl,--no-whole-archive
	-Wl,--end-group
)

target_link_libraries (${vatsinator_TARGET} ${vatsinator_LIBS})

install(PROGRAMS
	${CMAKE_CURRENT_BINARY_DIR}/vatsinator
	DESTINATION bin)