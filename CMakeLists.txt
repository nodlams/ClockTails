cmake_minimum_required(VERSION 2.6)

project(ClockTails)

SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 1)
SET(${PROJECT_NAME}_PATCH_LEVEL 0) 

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

if (CMAKE_COMPILER_IS_GNUCXX)
	SET(BASE_C_FLAGS "-std=c++0x -Wall")
	SET(CMAKE_C_FLAGS_DEBUG "${BASE_C_FLAGS} -g -pg -DDEBUG")
	SET(CMAKE_CXX_FLAGS_DEBUG "${BASE_C_FLAGS} -g -pg -DDEBUG")
	SET(CMAKE_C_FLAGS_RELEASE "${BASE_C_FLAGS} -Wno-deprecated -O3 -fomit-frame-pointer -DNDEBUG")
	SET(CMAKE_CXX_FLAGS_RELEASE "${BASE_C_FLAGS} -Wno-deprecated -O3 -fomit-frame-pointer -DNDEBUG")
	SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
endif()

AUX_SOURCE_DIRECTORY(. SOURCES)

add_executable(clocktails ${SOURCES})
target_link_libraries(clocktails boost_program_options)
