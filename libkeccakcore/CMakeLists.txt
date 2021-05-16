set(SOURCES
	KeccakAux.h KeccakAux.cpp
	Farm.cpp Farm.h
	Miner.h Miner.cpp
)

include_directories(BEFORE ..)

add_library(ethcore ${SOURCES})
target_link_libraries(ethcore PUBLIC devcore ethash::ethash PRIVATE hwmon)

if(KECCAKCL)
	target_link_libraries(ethcore PRIVATE keccak-cl)
endif()
if(KECCAKCUDA)
	target_link_libraries(ethcore PUBLIC ethash-cuda)
endif()
if(KECCAKCPU)
	target_link_libraries(ethcore PUBLIC ethash-cpu)
endif()
