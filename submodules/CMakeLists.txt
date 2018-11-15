# Add submodules needed by project

## GLFW
set(BUILD_SHARED_LIBS ON CACHE BOOL "Yes, build shared libs for GLFW")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples for GLFW")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Don't build tests for GLFW")
set(GLFW_INSTALL OFF CACHE BOOL "Don't generate install target for GLFW")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Don't generate docs for GLFW")
add_subdirectory(glfw)

## GLEW
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "Don't build the static glew library")
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Don't build the multi context glew library")
add_subdirectory(glew-cmake)

## GLM
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "Compile GLM with C++17 support")
set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "Enable FastMath feature for GLM")
set(GLM_TEST_ENABLE OFF CACHE BOOL "Don't build tests for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE2 ON CACHE BOOL "Enable SSE2 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE3 ON CACHE BOOL "Enable SSE3 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSSE3 ON CACHE BOOL "Enable SSSE3 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE4_1 ON CACHE BOOL "Enable SSE 4.1 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE4_2 ON CACHE BOOL "Enable SSE 4.2 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "Enable AVX optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "Enable AVX2 optimizations for GLM")
add_subdirectory(glm)

## SOIL
add_subdirectory(Simple-OpenGL-Image-Library)
