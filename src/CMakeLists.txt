

include(GenerateExportHeader)

# The common sources.
# Additional files are added below, as configured.
set(SOURCES
        acceptor.cpp
        connector.cpp
        datagram_socket.cpp
        error.cpp
        inet_address.cpp
        inet6_address.cpp
        socket.cpp
        stream_socket.cpp
)

# Additional sources (platform & config)

if (SOCKPP_WITH_UNIX_SOCKETS)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/unix/unix_address.cpp
    )
endif ()

if (SOCKPP_WITH_CAN)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/can_address.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/can_socket.cpp
    )
endif ()

if (SOCKPP_WITH_OPENSSL)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/openssl_certificate.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/openssl_context.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/openssl_socket.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/openssl_error.cpp
    )
elseif (SOCKPP_WITH_MBEDTLS)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/mbedtls_context.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/mbedtls_socket.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tls/mbedtls_error.cpp
    )
endif ()

# -- The shared library (if configured) ---

if (${SOCKPP_BUILD_SHARED})
    message(STATUS "Creating shared library")

    add_library(sockpp-shared SHARED ${SOURCES})

    add_library(Sockpp::sockpp-shared ALIAS sockpp-shared)
    add_library(Sockpp::sockpp ALIAS sockpp-shared)

    set_target_properties(sockpp-shared PROPERTIES
            OUTPUT_NAME sockpp
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
    )

    generate_export_header(sockpp-shared
            BASE_NAME sockpp
            EXPORT_FILE_NAME ${SOCKPP_GENERATED_DIR}/include/sockpp/export.h
    )
endif ()

# -- The static library (if configured) ---

if (${SOCKPP_BUILD_STATIC})
    message(STATUS "Creating static library")

    add_library(sockpp-static STATIC ${SOURCES})

    add_library(Sockpp::sockpp-static ALIAS sockpp-static)

    if (${SOCKPP_BUILD_SHARED})
        target_compile_definitions(sockpp-static PRIVATE SOCKPP_STATIC_DEFINE)
    else ()
        add_library(Sockpp::sockpp ALIAS sockpp-static)

        generate_export_header(sockpp-static
                BASE_NAME sockpp
                EXPORT_FILE_NAME ${SOCKPP_GENERATED_DIR}/include/sockpp/export.h
        )
    endif ()

    # On *nix systems, the static library can have the same base filename
    # as the shared library, thus 'libsockpp.a' for the static lib.
    # On Windows they need different names to tell the static lib from the
    # DLL import library.
    if (UNIX)
        set_target_properties(sockpp-static PROPERTIES OUTPUT_NAME sockpp)
    endif ()
endif ()

foreach (TARGET ${SOCKPP_TARGETS})
    target_include_directories(${TARGET} PUBLIC
            $<BUILD_INTERFACE:${SOCKPP_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${SOCKPP_GENERATED_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(${TARGET} PUBLIC ${LIBS_SYSTEM})

    # Secure TLS library (if one is configured)

    if (SOCKPP_WITH_OPENSSL)
        target_link_libraries(${TARGET} PUBLIC
                OpenSSL::SSL
                OpenSSL::Crypto
        )
    elseif (SOCKPP_WITH_MBEDTLS)
        target_link_libraries(${TARGET} PUBLIC
                MbedTLS::mbedtls
                MbedTLS::mbedcrypto
                MbedTLS::mbedx509
        )
    endif ()

    # --- Warnings ---

    target_compile_options(${TARGET} PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W3>
            $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -Wdocumentation>
            $<$<NOT:$<OR:$<CXX_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:Clang>>>:-Wall -Wextra -Wpedantic>
    )
endforeach ()

