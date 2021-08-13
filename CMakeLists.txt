cmake_minimum_required (VERSION 2.6)

project (fg_saitek)
set(CMAKE_CXX_STANDARD 17)

add_executable(fg_saitek 
	src/Config.cpp  
	src/FGGeneric.cpp  
	src/fg_saitek.cpp  
	src/SaitekGeneric.cpp
	src/SaitekSuperPanel.cpp  
	src/SaitekSwitch.cpp
	src/SaitekRadio.cpp
	
	)

	
target_link_libraries(fg_saitek stdc++fs)