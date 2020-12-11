add_library(Math add.cpp add.h)

install(TARGETS Math DESTINATION lib)
install(FILES add.h DESTINATION include)

