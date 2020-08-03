add_executable(UnitTests_ShuntingYard main.cpp ${PROJECT_SOURCE_DIR}/ShuntingYardCore/ShuntingYardCalculator.cpp ShuntingYardUtilsTests.cpp ShuntingYardCalculatorUnitTests.cpp)

target_compile_features(UnitTests_ShuntingYard PRIVATE cxx_std_17)
set_target_properties(UnitTests_ShuntingYard PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_ShuntingYard
        PUBLIC
        ${PROJECT_SOURCE_DIR}/ShuntingYardCore)

target_link_libraries(UnitTests_ShuntingYard gtest gmock)

add_test(NAME UnitTests_ShuntingYard COMMAND UnitTests_ShuntingYard)

#######################################################################################################

add_executable(IntegrationTests_ShuntingYard main.cpp ${PROJECT_SOURCE_DIR}/ShuntingYardCore/ShuntingYardCalculator.cpp ShuntingYardIntegrationTests.cpp)

target_compile_features(IntegrationTests_ShuntingYard PRIVATE cxx_std_17)
set_target_properties(IntegrationTests_ShuntingYard PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(IntegrationTests_ShuntingYard
        PUBLIC
        ${PROJECT_SOURCE_DIR}/ShuntingYardCore)

target_link_libraries(IntegrationTests_ShuntingYard gtest gmock)

add_test(NAME IntegrationTests_ShuntingYard
        COMMAND IntegrationTests_ShuntingYard)