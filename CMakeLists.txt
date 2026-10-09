cmake_minimum_required(VERSION 3.15)
project(ZCasino C)

include(GenerateG3A)
find_package(Gint 2.1 REQUIRED)

set(SOURCES src/casino.c)

add_executable(z_casino ${SOURCES})
target_compile_options(z_casino PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(z_casino Gint::Gint)

generate_g3a(TARGET z_casino OUTPUT "Z_Casino.g3a"
    NAME "Z Casino"
    ICONS icon-uns.png icon-sel.png
)

add_executable(boot_test src/boot_test.c)
target_compile_options(boot_test PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(boot_test Gint::Gint)

generate_g3a(TARGET boot_test OUTPUT "Boot_Test.g3a"
    NAME "Boot"
    ICONS icon-uns.png icon-sel.png
)
