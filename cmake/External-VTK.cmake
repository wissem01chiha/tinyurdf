cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
   message(FATAL_ERROR "Unable to find the VTK build folder.")
   message(WARNING "Default build VTK is not supported ; manual installation is required.")
else()
   message(STATUS "VTK Found : ${VTK_DIR}")
endif()

find_package(VTK COMPONENTS 
   CommonColor
   CommonCore
   FiltersSources
   IOImage
   InteractionStyle
   RenderingContextOpenGL2
   RenderingCore
   RenderingFreeType
   RenderingGL2PSOpenGL2
   RenderingOpenGL2
   RenderingUI
)

# Prevent a "command line is too long" failure in Windows.
if(WIN32)
   set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
endif(WIN32)