file(GLOB asst_routing_srcs "*.cpp"
)

add_executable(asst_routing ${asst_routing_srcs})
target_link_libraries(asst_routing easygl)
target_include_directories(asst_routing PUBLIC ".")