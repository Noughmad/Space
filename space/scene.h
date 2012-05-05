#ifndef SPACE_SCENE_H
#define SPACE_SCENE_H

class Object;
namespace Space {

class Scene
{
public:
    Scene();
    virtual ~Scene();
    
    void addObject(Object* object);
    
};

}

#endif // SPACE_SCENE_H
