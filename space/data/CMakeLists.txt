
configure_file(plugins.cfg.in plugins.cfg)
configure_file(resources.cfg.in resources.cfg)

install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/plugins.cfg 
    ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg 
    space.layout
    star.particle
    Star.mesh
    StarSurface.png
    StellarMatter.material
    Planet.mesh
    earth.material
    earth.jpg
    mars.jpg
    select.material
    select.png
    fade_in.cg
    fade_out.cg
    blue.png
    red.png
    DESTINATION ${SPACE_DATA_INSTALL_DIR}
)