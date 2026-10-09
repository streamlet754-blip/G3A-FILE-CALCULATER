cmake_minimum_required(VERSION 3.15)
project(PhysicsApp C)

include(GenerateG3A)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
    src/main.c
)

add_executable(physics_app ${SOURCES})
target_compile_options(physics_app PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(physics_app Gint::Gint)

generate_g3a(TARGET physics_app OUTPUT "Physics_Revision.g3a"
    NAME "Physics Revision"
    ICONS icon-uns.png icon-sel.png
)

add_executable(boot_test src/boot_test.c)
target_compile_options(boot_test PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(boot_test Gint::Gint)

generate_g3a(TARGET boot_test OUTPUT "Physics_Boot_Test.g3a"
    NAME "Physics Boot Test"
    ICONS icon-uns.png icon-sel.png
)
