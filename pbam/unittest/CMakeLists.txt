# Set gtest properties
include_directories("${source_dir}/include")

file(GLOB SRCS *.cpp)

include_directories("../src")
include_directories("../../pb_shared/src")
include_directories("../../pb_shared/unittest")

ADD_EXECUTABLE(pbamtest
  ../src/ASolver.cpp
  ../../pb_shared/src/BaseBD.cpp
  ../../pb_shared/src/BaseElectro.cpp
  ../../pb_shared/src/BaseSys.cpp
  ../src/BDAM.cpp
  ../../pb_shared/src/BesselCalc.cpp
  ../../pb_shared/src/Constants.cpp
  ../src/ElectrostaticsAM.cpp
  ../src/PhysCalcAM.cpp
  ../../pb_shared/src/ReExpCalc.cpp
  ../../pb_shared/src/SHCalc.cpp
  ../src/SystemAM.cpp
  ../../pb_shared/src/setup.cpp
  main.cpp
  )

TARGET_LINK_LIBRARIES(pbamtest
    Threads::Threads
    ${GTEST_BOTH_LIBRARIES}
)

add_test(NAME pbamtest
         COMMAND pbamtest)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
# install(TARGETS pbamtest DESTINATION bin)
