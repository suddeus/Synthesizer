cmake_minimum_required(VERSION 4.0)
project(keyboard_processing LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER /opt/homebrew/bin/avr-g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)

include(FetchContent)
FetchContent_Declare(
        etl
        GIT_REPOSITORY https://github.com/ETLCPP/etl.git
        GIT_TAG        20.38.14
)
FetchContent_MakeAvailable(etl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*
)

function(add_avr_firmware TARGET MCU F_CPU)
    add_executable(${TARGET}
            ${SOURCE_FILES}
            ${ARGN}
    )

    set_target_properties(${TARGET}
            PROPERTIES SUFFIX ".elf"
    )

    target_compile_definitions(${TARGET}
            PRIVATE F_CPU=${F_CPU}
    )

    target_compile_options(${TARGET} PRIVATE
            -mmcu=${MCU}
            -Os
            -Wall
            -Wextra
            -ffunction-sections
            -fdata-sections
    )

    target_link_options(${TARGET} PRIVATE
            -mmcu=${MCU}
            -Wl,--gc-sections
    )

    target_link_libraries(${TARGET} PRIVATE
        etl::etl
    )

    set(hex_file "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.hex")

    add_custom_command(TARGET ${TARGET} POST_BUILD
            BYPRODUCTS "${hex_file}"
            COMMAND "${AVR_OBJCOPY}" -O ihex -R .eeprom
            "$<TARGET_FILE:${TARGET}>" "${hex_file}"
            COMMAND "${AVR_SIZE}" "$<TARGET_FILE:${TARGET}>"
            VERBATIM
    )

    target_include_directories(${TARGET} PRIVATE
            ${PROJECT_SOURCE_DIR}/include
    )
endfunction()

add_subdirectory(examples/shift_register)