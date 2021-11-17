cmake_minimum_required(VERSION 3.5)

project(contactino LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(contactino SHARED
    contactino.cpp
)

set_target_properties(contactino PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(contactino PRIVATE CONTACT_LIBRARY)
