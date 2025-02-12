# Initial project settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(union-member-access-ub-test "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# MSVC configure fallback
if(MSVC)
  message(FATAL_ERROR "Don't use msvc for this target, MSVC version: ${MSVC_VERSION}, toolset version: ${MSVC_TOOLSET_VERSION}")
# GCC and Clang compile options
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Using asan, ubsan
  target_compile_options(union-member-access-ub-test PRIVATE -fno-omit-frame-pointer -fsanitize=address,undefined -fstack-protector)
  target_link_options(union-member-access-ub-test    PRIVATE -fno-omit-frame-pointer -fsanitize=address,undefined -fstack-protector)
  # Setup warning level
  target_compile_options(union-member-access-ub-test PRIVATE -Wall -Wextra -Wpedantic)
endif()
