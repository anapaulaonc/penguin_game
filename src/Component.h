#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
using namespace std;
class GameObject;


class Component{
    public:
        Component(GameObject& associated);
        virtual ~Component();
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool virtual Is(string type) = 0;
    protected:
        GameObject& associated;
};

#endif