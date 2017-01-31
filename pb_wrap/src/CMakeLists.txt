project(pb_solvers)

include_directories(
  "../../pb_wrap/src"
  "${CMAKE_INCLUDE_PATH}/apbs"
  "${CMAKE_INCLUDE_PATH}/apbs/fem"
  "${CMAKE_INCLUDE_PATH}/apbs/mg"
  "${CMAKE_INCLUDE_PATH}/apbs/pmgc"
)
