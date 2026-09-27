
add_executable(${CMAKE_PROJECT_NAME} main.cpp Entity.hpp EntityManager.hpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    ImGui-SFML::ImGui-SFML
    m
)
file(COPY "${RESOURCES_DIRECTORY}/" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
