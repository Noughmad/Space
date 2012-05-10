function (GENERATE_TOLUA_BINDINGS _package_name _pkgfile _dependencies)
    set (_outfile_h "${CMAKE_CURRENT_BINARY_DIR}/lua_${_package_name}.h")
    set (_outfile_cpp "${CMAKE_CURRENT_BINARY_DIR}/lua_${_package_name}.cpp")
    set (_dependencies ${_dependencies} ${_pkgfile})
    
    add_custom_command(
        OUTPUT ${_outfile_cpp} ${_outfile_h}
        COMMAND ${TOLUA_EXECUTABLE} -n ${_package_name}
                                    -o ${_outfile_cpp}
                                    -H ${_outfile_h}
                                    ${_pkgfile}
        COMMENT "Generating Lua bindings for pagkage ${_package_name}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${_dependencies}
    )
endfunction (GENERATE_TOLUA_BINDINGS)