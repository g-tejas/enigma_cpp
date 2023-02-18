# Include directories (Imgui and extensions)
set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMPLOT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/implot)
set(IMCMD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/imgui_command_palette)


# ImGui files
file(GLOB IMGUI_SOURCES ${IMGUI_INCLUDE_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${IMGUI_INCLUDE_DIR}/*.h)

set(IMGUI_BACKENDS_DIR ${IMGUI_INCLUDE_DIR}/backends)
set(IMGUI_BACKEND_SOURCES
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl2.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp)
set(IMGUI_BACKEND_HEADERS
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl2.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.h)

# ImPlot files
file(GLOB IMPLOT_SOURCES ${IMPLOT_INCLUDE_DIR}/*.cpp)
file(GLOB IMPLOT_HEADERS ${IMPLOT_INCLUDE_DIR}/*.h)

# ImCmd files
file(GLOB IMCMD_SOURCES ${IMCMD_INCLUDE_DIR}/*.cpp)
file(GLOB IMCMD_HEADERS ${IMCMD_INCLUDE_DIR}/*.h)

add_library(imgui STATIC
    ${IMGUI_SOURCES} ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_HEADERS} ${IMGUI_BACKEND_SOURCES}
    ${IMPLOT_SOURCES} ${IMPLOT_HEADERS}
    ${IMCMD_SOURCES} ${IMCMD_HEADERS}
)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories(imgui PUBLIC
    ${IMGUI_INCLUDE_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${IMPLOT_INCLUDE_DIR}
    ${IMCMD_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)

target_link_libraries(imgui
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES})

set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(imgui PROPERTIES FOLDER external)

set(IMGUI_LIBRARIES imgui)
