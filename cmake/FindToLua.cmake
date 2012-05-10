find_program (TOLUA_EXECUTABLE 
    NAMES tolua toluapp tolua++ 
    DOC "ToLua executable")

# handle the QUIETLY and REQUIRED arguments and set TINYXML_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "ToLua" DEFAULT_MSG TOLUA_EXECUTABLE )
