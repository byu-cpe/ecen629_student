file(GLOB asst_routing_srcs 
    asst_routing.cpp
    Design.cpp
    Drawer.cpp
    FPGA.cpp
    FpgaTile.cpp
    RRNode.cpp
    Net.cpp
)

add_executable(router ${asst_routing_srcs})
target_link_libraries(router easygl)
target_include_directories(router PUBLIC ".")