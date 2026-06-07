cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(projects-managment-system)

option(BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)

file(GLOB_RECURSE ALL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM ALL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

if(BUILD_TESTS)
    add_executable(app ${ALL_SRC})
    target_include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
else()
    list(APPEND ALL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

    add_executable(app ${ALL_SRC}
            src/helpers/byte-stream/queue-serialization.hpp
            src/helpers/byte-stream/priority-queue-serialization.hpp
            src/data/inbox-task-file-repository.cpp
            src/data/inbox-task-file-repository.hpp
            src/data/todo-task-file-repository.hpp
            src/data/user-repository.hpp
            src/data/inbox-task-repository.hpp
            src/data/todo-task-repository.hpp
            src/service/task-service-impl.hpp
            src/data/in-progress-task-repository.hpp
            src/data/done-task-repository.hpp
            src/data/done-task-file-repository.hpp
            src/data/done-task-file-repository.cpp
            src/data/in-progress-task-file-repository.hpp
            src/data/in-progress-task-file-repository.cpp
            src/dtos/create-task-dto.hpp
            src/entities/task-component.hpp
            src/entities/task-component.cpp
            src/dtos/move-task-to-todo-dto.hpp
            src/dtos/create-subtask-dto.hpp
            src/dtos/move-subtask-to-todo-dto.hpp
            src/service/task-service-impl.cpp
            src/service/proxy/security-task-proxy.hpp
            src/service/auth-service.hpp
            src/service/auth-service.cpp
            src/service/task-service.hpp
            src/service/proxy/security-task-proxy.cpp
            src/service/user-service.hpp
            src/service/user-service-impl.hpp
            src/service/user-service-impl.cpp
            src/dtos/create-user-dto.hpp
            src/dtos/user-dto.hpp
            src/service/proxy/security-user-proxy.hpp
            src/service/proxy/security-user-proxy.cpp
            src/service/proxy/base-security-proxy.hpp
            src/ui/ui-context.hpp
            src/ui/states/ui-state.hpp
            src/ui/states/login-state.hpp
            src/ui/states/login-state.cpp
            src/ui/states/session-state.hpp
            src/ui/ui-context.cpp
            src/helpers/ui/task-string-builder.hpp
            src/helpers/ui/task-string-builder.cpp
            src/ui/states/session-state.cpp)
    target_include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
