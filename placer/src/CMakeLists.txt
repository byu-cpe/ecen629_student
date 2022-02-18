add_executable(placer
	placer_main.cpp
	APEdge.cpp
	Block.cpp
	Design.cpp
	Drawer.cpp
	Net.cpp
)

target_link_libraries(placer easygl ${UMFPACK_LIB})

