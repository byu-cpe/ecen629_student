file(GLOB asst1_srcs "*.cpp"
)

add_executable(asst1 ${asst1_srcs})
target_link_libraries(asst1 easygl)
target_include_directories(asst1 PUBLIC ".")