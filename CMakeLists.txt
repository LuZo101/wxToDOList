cmake_minimum_required(VERSION 3.27.2)
project(ToDoList)
set(SOURCE_FILES
    App.cpp
    MainFrame.cpp
    Task.cpp
)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# and for each of your dependent executable/library targets:
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
