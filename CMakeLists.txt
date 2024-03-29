PROJECT(KWWidgetsTest)

# If we are not in the KWWidgets source tree, make sure we can find KWWidgets
# as an external package, and use it. If you are using this CMakeLists.txt 
# file to create your own application based on KWWidgets, you only need the
# FIND_PACKAGE(...) and INCLUDE(...) commands. 


#IF(NOT VTK_SOURCE_DIR)
#  FIND_PACKAGE(VTK REQUIRED)
#  INCLUDE(${VTK_USE_FILE})
#ENDIF(NOT VTK_SOURCE_DIR)

IF(NOT KWWidgets_SOURCE_DIR)
  FIND_PACKAGE(KWWidgets REQUIRED)
  INCLUDE(${KWWidgets_USE_FILE})
ENDIF(NOT KWWidgets_SOURCE_DIR)

IF(NOT ITK_SOURCE_DIR)
  FIND_PACKAGE(ITK REQUIRED)
  INCLUDE(${ITK_USE_FILE})
ENDIF(NOT ITK_SOURCE_DIR)


SET(TARGET_BASE_NAME "KW${PROJECT_NAME}")

# We define several classes in this example, and we want to be able to use
# their C++ methods as callbacks for our user interface. To do so, we need to 
# create a library and wrap it automatically for the Tcl language, which
# is used as a bridge between C++ objects at run-time. Note that an
# initialization function is automatically created in this library to allow
# classes and C++ methods to be used as commands and callbacks inside the Tcl
# interpreter; do *not* forget to call this function right after you 
# initialize the Tcl interpreter in your application. The name of this 
# function is built from the library name in lower-case (except for the first
# letter) and suffixed with "_Init" (for example: 
# KWMedicalImageViewerExampleLib => Kwmedicalimageviewerexamplelib_Init)
# This whole process is required to use C++ methods as callbacks; it is not
# needed if you use VTK's C++ command/observer pattern directly, which is
# demonstrated in KWWidgets's C++ 'Callbacks' example.

SET(LIB_NAME "KWWidgetsTestLib")
SET(LIB_SRCS 
  vtkKWMyWindow.cxx  
  )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE("${KWWidgets_CMAKE_DIR}/KWWidgetsWrappingMacros.cmake")
KWWidgets_WRAP_TCL(${LIB_NAME} LIB_TCL_SRCS "${LIB_SRCS}" "")

# Create the library. The library is built in static mode for convenience. 
# Check the 'Callbacks' example for more information about building it in
# shared mode, i.e. without the STATIC keyword (Win32 compilers requires
# an additional header file to setup DLL export symbols correctly).

ADD_LIBRARY(${LIB_NAME} STATIC ${LIB_TCL_SRCS} ${LIB_SRCS})
TARGET_LINK_LIBRARIES(
${LIB_NAME} 
${KWWidgets_LIBRARIES} 
${ITK_LIBRARIES} 
#${VTK_LIBRARIES}
)

# The name of our executable and the corresponding source file.

SET(EXE_NAME "${TARGET_BASE_NAME}")
SET(EXE_SRCS "Main.cxx" )

# On Win32 platforms, let's create a .rc resource file to setup a decent
# application icon as well as some additional information in the "Version"
# tab of the properties panel.

IF(WIN32 AND NOT BORLAND AND NOT CYGWIN)
  INCLUDE("${KWWidgets_CMAKE_DIR}/KWWidgetsResourceMacros.cmake")
  SET(RC_FILENAME "${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.rc")
  KWWidgets_CREATE_RC_FILE(
    RC_FILENAME "${RC_FILENAME}"
    RC_APPLICATION_NAME "${EXE_NAME}"
    RC_COMPANY_NAME "Kitware, Inc.")
ENDIF(WIN32 AND NOT BORLAND AND NOT CYGWIN)

# This example uses some files from the KWWidgets distribution tree.
# Let's configure KWWidgets's vtkKWWidgetsPaths.h.in into our
# own header file so that we can find the paths to KWWidgets files.

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
CONFIGURE_FILE(
  ${KWWidgets_TEMPLATES_DIR}/vtkKWWidgetsPaths.h.in 
  ${CMAKE_CURRENT_BINARY_DIR}/vtkKWWidgetsPaths.h)

# Create the executable, and link it against the KWWidgets libraries and our
# own library.

ADD_EXECUTABLE(${EXE_NAME} WIN32 ${EXE_SRCS}  ${WIDGETS_SRCS} ${WIDGETS_VTK_SRCS} ${RC_FILENAME})
TARGET_LINK_LIBRARIES(
  ${EXE_NAME} 
  ${LIB_NAME} 
#  vtkRendering
#  vtkGraphics
#  vtkImaging
#  vtkIO
#  vtkCommon
#  vtkHybrid
#  vtkFiltering 
)
 


# If we are building this example as a standalone external project:
# - Generate a few small scripts (.bat, .sh, .csh) that can be sourced to set
# the various environments variables (PATH, TCLLIBPATH, LD_LIBRARY_PATH, etc.) 
# required by this executable and its known third-party dependencies (VTK, ITK,
# SOV, KWWidgets, etc.).
# - Generate a lightweight C launcher for this *specific* executable: It sets
# the above environment variables before launching the executable itself.

IF(NOT KWWidgets_SOURCE_DIR)
  INCLUDE("${KWWidgets_CMAKE_DIR}/KWWidgetsPathsMacros.cmake")
  KWWidgets_GENERATE_SETUP_PATHS_SCRIPTS("${CMAKE_CURRENT_BINARY_DIR}")
  SET(LAUNCHER_EXE_NAME "${EXE_NAME}Launcher")
  KWWidgets_GENERATE_SETUP_PATHS_LAUNCHER(
    "${CMAKE_CURRENT_BINARY_DIR}" "${LAUNCHER_EXE_NAME}" "" "${EXE_NAME}")
ENDIF(NOT KWWidgets_SOURCE_DIR)

# If needed, copy the Tcl/Tk support files required at run-time 
# to initialize Tcl/Tk. This is only triggered if VTK was built
# against a Tcl/Tk static library.

INCLUDE("${KWWidgets_CMAKE_DIR}/KWWidgetsTclTkMacros.cmake")
IF(NOT KWWidgets_SOURCE_DIR)
  KWWidgets_COPY_TCL_TK_SUPPORT_FILES("${PROJECT_BINARY_DIR}/lib")
ENDIF(NOT KWWidgets_SOURCE_DIR)

# Install the example target. If you are using this CMakeLists.txt file
# to create your own application based on KWWidgets, you can most likely 
# omit this section or change the installation directory, unless you want
# to install your application right where KWWidgets is already installed.

IF(KWWidgets_BUILD_EXAMPLES)
  INSTALL_TARGETS(${KWWidgets_INSTALL_BIN_DIR} ${EXE_NAME})
ENDIF(KWWidgets_BUILD_EXAMPLES)

# Register this example as a test. Our executable supports a --test
# configuration option so that it can be run non-interactively as a test.
# If you are using this CMakeLists.txt file to create your own application
# based on KWWidgets, you should omit this section, unless your application
# supports that feature too and you checked how the macro is working.

IF(BUILD_TESTING)
  INCLUDE("${KWWidgets_CMAKE_DIR}/KWWidgetsTestingMacros.cmake")
  KWWidgets_ADD_TEST_FROM_C_EXAMPLE(KWWidgets-${PROJECT_NAME} ${EXE_NAME})
ENDIF(BUILD_TESTING)

