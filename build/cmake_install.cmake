<<<<<<< HEAD
# Install script for directory: /home/augustin/Bureau/Depot Automate/Automate
=======
# Install script for directory: /afs/deptinfo-st.univ-fcomte.fr/users/abordy2/Bureau/TL/Automate
>>>>>>> 69e3364bf130ed31652e0c692140bba56ae22e13

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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
<<<<<<< HEAD
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
=======
>>>>>>> 69e3364bf130ed31652e0c692140bba56ae22e13
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/home/augustin/Bureau/Depot Automate/Automate/build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/afs/deptinfo-st.univ-fcomte.fr/users/abordy2/Bureau/TL/Automate/build/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 69e3364bf130ed31652e0c692140bba56ae22e13
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
