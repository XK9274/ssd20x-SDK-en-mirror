# Install script for directory: /root/workspace/test/ssd2xx-demo/4.littlevgl/f_apps

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_demos_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_test_all_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_lib_png_test_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_lib_gif_test_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/f_game_2048/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_lib_split_jpg_test_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_lib_freetype_test_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/f_game_snake/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/lv_lib_bmp_test_app/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/f_tool_file_browser/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/4.littlevgl/f_apps/f_game_tetris/cmake_install.cmake")

endif()

