# Install script for directory: /root/workspace/test/ssd2xx-demo

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
  include("/root/workspace/test/ssd2xx-demo/build/0.common/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/1.watchdog/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/2.panel/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/3.framebuffer/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/5.wifi/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/6.audio/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/7.gpio/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/8.pwm/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/9.uart/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/10.video/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/11.mi_gfx/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/12.mi_disp/cmake_install.cmake")
  include("/root/workspace/test/ssd2xx-demo/build/13.uuid/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/workspace/test/ssd2xx-demo/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
