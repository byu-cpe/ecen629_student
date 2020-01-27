file(GLOB placer_srcs "*.cpp"
)


add_executable(placer ${placer_srcs})
target_link_libraries(placer easygl X11 umfpack)

#target_include_directories(asst2 PUBLIC .)
#target_include_directories(asst2 PUBLIC ../../SuiteSparse/include/)
#target_include_directories(asst2 PUBLIC ../../SuiteSparse/UMFPACK/Include/)
