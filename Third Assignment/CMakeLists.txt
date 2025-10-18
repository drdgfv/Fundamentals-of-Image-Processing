cmake_minimum_required(VERSION 3.10)
project(FPI-AssignmentIII)

set(CMAKE_CXX_STANDARD 14)

# Encontra a biblioteca OpenCV instalada no sistema
find_package(OpenCV REQUIRED)

# Inclui os diretórios de cabeçalho do OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Cria o executável a partir do seu código-fonte
add_executable(videocap main.cpp video_cap.cpp video_cap.h)

# Linka seu executável com as bibliotecas do OpenCV
target_link_libraries(videocap ${OpenCV_LIBS})
