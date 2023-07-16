add_executable(${PROJECT_NAME}_test)

target_sources(${PROJECT_NAME}_test
  PRIVATE
    src/webdriver_test.cpp
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}_test
  PUBLIC
    ${CMAKE_PROJECT_NAME}::${PROJECT_NAME}
    GTest::gtest
)

add_test(NAME "Webdriver tests"
  COMMAND ${PROJECT_NAME}_test
)
