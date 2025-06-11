cmake_minimum_required( VERSION 3.28 )
project( interfaces.out )

add_executable( ${PROJECT_NAME} main.cpp loghandler.cpp logger.cpp logfilter.cpp )
