
configure_file(plugins.cfg.in plugins.cfg)
configure_file(resources.cfg.in resources.cfg)

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg 
    ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg 
    DESTINATION ${SPACE_DATA_INSTALL_DIR}
)

install (FILES ui/space.layout DESTINATION ${SPACE_DATA_INSTALL_DIR}/ui)

install (FILES 
    materials/blue.png
    materials/red.png
    materials/yellow.png
    
    materials/earth.jpg
    materials/mars.jpg
    materials/star_surface.png
    
    materials/star.particle
    materials/star.material
    materials/planet.material
    
    materials/fade_in.cg
    materials/fade_out.cg
    
    materials/select.png
    materials/select.material
    
    DESTINATION ${SPACE_DATA_INSTALL_DIR}/materials
)

install (FILES
    meshes/Planet.mesh
    meshes/Planet.mesh.xml
    meshes/Star.mesh
    meshes/Star.mesh.xml
    DESTINATION ${SPACE_DATA_INSTALL_DIR}/meshes
)