file(GLOB asst_routing_srcs "*.cpp"
)

add_executable(router ${asst_routing_srcs})
target_link_libraries(router easygl)
target_include_directories(router PUBLIC ".")