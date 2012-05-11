
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
    materials/asteroid.png
    materials/stevecube.jpg
    
    materials/box_bk.png
    materials/box_fr.png
    materials/box_lf.png
    materials/box_rt.png
    materials/box_up.png
    materials/box_dn.png
    
    materials/star.particle
    materials/star.material
    materials/planet.material
    materials/probe.material
    
    materials/fade_in.cg
    materials/fade_out.cg
    
    materials/select.png
    materials/select.material
    
    DESTINATION ${SPACE_DATA_INSTALL_DIR}/materials
)

install (FILES
    meshes/Planet.mesh
    meshes/Star.mesh
    meshes/Probe.mesh
    DESTINATION ${SPACE_DATA_INSTALL_DIR}/meshes
)
