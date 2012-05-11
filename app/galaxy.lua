function test(message)
  print("Hello From Lua, " .. message)
end

function create_scene()
    manager = Space.ObjectManager:getSingleton()
    
    print("one")
    
    star1 = manager:createObject("Celestial/Star/Yellow/Sun")
    star1:setPosition(0,0,0)
    star1:set('RotationSpeed', 10.0)
    star1:set('RevolutionSpeed', 0.0)
    star1:set('Size', 20)
    
    print("two")
    
    star2 = manager:createObject("Celestial/Star/Yellow/Alpha")
    star2:setPosition(900,0,0)
    star2:set('RotationSpeed', 13)
    star2:set('RevolutionSpeed', 0.01)
    star2:set('Size', 17)
    
    p1 = manager:createObject("Celestial/Planet/Blue/Earth")
    p1:setParent(star1)
    p1:setPosition(100, 50, 0)
    p1:set('Size', 4)
    p1:set('RotationSpeed', 3)
    p1:set('RevolutionSpeed', 0.1)
    
    p2 = manager:createObject("Celestial/Planet/Red/Mars")
    p2:setParent(star1)
    p2:setPosition(10, -30, 0)
    p2:set('Size', 6)
    p2:set('RotationSpeed', 2)
    p2:set('RevolutionSpeed', 0.3)
    
    p3 = manager:createObject("Celestial/Planet/Blue/One")
    p3:setParent(star2)
    p3:setPosition(100, -30, 0)
    p3:set('Size', 3)
    p3:set('RotationSpeed', 5)
    p3:set('RevolutionSpeed', 0.2)
    
    p4 = manager:createObject("Celestial/Planet/Red/Two")
    p4:setParent(star2)
    p4:setPosition(100, 0, 0)
    p4:set('Size', 5)
    p4:set('RotationSpeed', 4)
    p4:set('RevolutionSpeed', 0.18)
    
    p5 = manager:createObject("Celestial/Planet/Red/Three")
    p5:setParent(star2)
    p5:setPosition(100, 100, 0)
    p5:set('Size', 12)
    p5:set('RotationSpeed', 4)
    p5:set('RevolutionSpeed', 0.1)
    
    a1 = manager:createObject("Celestial/Belt/Asteroids/BeltOne")
    a1:setParent(star1)
    a1:set('Size', 10)
    a1:set('RotationSpeed', 0.04)
   
    return star1, star2, p1, p2, p3, p4, p5, a1
end