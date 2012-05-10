function test(message)
  print("Hello From Lua, " .. message)
end

function create_scene()
    manager = Space.ObjectManager:getSingleton()
    
    star1 = manager:createObject("Celestial/Star/Yellow/Sun")
    star1:setPosition(0,0,0)
    star1:setProperty('RotationSpeed', 10.0)
    star1:setProperty('RevolutionSpeed', 0.0)
    star1:setProperty('Size', 20)
    
    star2 = manager:createObject("Celestial/Star/Yellow/Alpha")
    star2:setPosition(900,0,0)
    star2:setProperty('RotationSpeed', 13)
    star2:setProperty('RevolutionSpeed', 0.01)
    star2:setProperty('Size', 17)
    
    p1 = manager:createObject("Celestial/Planet/Blue/Earth")
    p1:setParent(star1)
    p1:setPosition(100, 50, 0)
    p1:setProperty('Size', 4)
    p1:setProperty('RotationSpeed', 3)
    p1:setProperty('RevolutionSpeed', 0.1)
    
    p2 = manager:createObject("Celestial/Planet/Red/Mars")
    p2:setParent(star1)
    p2:setPosition(10, -30, 0)
    p2:setProperty('Size', 6)
    p2:setProperty('RotationSpeed', 2)
    p2:setProperty('RevolutionSpeed', 0.3)
    
    p3 = manager:createObject("Celestial/Planet/Blue/One")
    p3:setParent(star2)
    p3:setPosition(100, -30, 0)
    p3:setProperty('Size', 3)
    p3:setProperty('RotationSpeed', 5)
    p3:setProperty('RevolutionSpeed', 0.2)
    
    p4 = manager:createObject("Celestial/Planet/Red/Two")
    p4:setParent(star2)
    p4:setPosition(100, 0, 0)
    p4:setProperty('Size', 5)
    p4:setProperty('RotationSpeed', 4)
    p4:setProperty('RevolutionSpeed', 0.18)
    
    p5 = manager:createObject("Celestial/Planet/Red/Three")
    p5:setParent(star2)
    p5:setPosition(100, 100, 0)
    p5:setProperty('Size', 12)
    p5:setProperty('RotationSpeed', 4)
    p5:setProperty('RevolutionSpeed', 0.1)
    
    a1 = manager:createObject("Celestial/Belt/Asteroids/BeltOne")
    a1:setParent(star1)
    a1:setProperty('Size', 10)
    a1:setProperty('RotationSpeed', 0.04)
   
    return star1, star2, p1, p2, p3, p4, p5, a1
end