add_executable(placer
	placer_main.cpp
	Block.cpp
	Design.cpp
	Drawer.cpp
	Net.cpp
	FPGA.cpp
)

target_link_libraries(placer easygl X11)

