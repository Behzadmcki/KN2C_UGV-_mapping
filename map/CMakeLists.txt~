cmake_minimum_required(VERSION 2.8.3)
project(map)


set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)

find_package(Qt4 COMPONENTS QtCore QtGui QtNetWork )
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(qt_srcs
        src/main.cpp src/map.cpp )
set(qt_hdrs
       include/map.h)

qt4_automoc(${qt_srcs})
QT4_WRAP_CPP(qt_moc_srcs ${qt_hdrs})






find_package(    catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  cv_bridge
  image_transport
  geometry_msgs
  genmsg
  tf2_msgs
  std_msgs
)






catkin_package()

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
#/opt/ros/kinetic/include/opencv-3.3.1
)


include_directories(include ${catkin_INCLUDE_DIRS} ${qt_hdrs})
add_library(include ${qt_hdrs})
add_executable(map_image src/main.cpp ${qt_srcs} ${qt_moc_srcs})
target_link_libraries(map_image ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${X11_LIBRARIES} ${QT_LIBRARIES} -lpthread )


