# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Yash/esp/esp-idf/components/bootloader/subproject"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/tmp"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/src"
  "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Projects/Coding/ESP32/Smart_Switches/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
