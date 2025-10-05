#pragma once

#include "uifwddecls.hpp"
#include <memory>

class uinode{

    ImVec2 position;
    std::shared_ptr<zs::node> node;

public:
    uinode(std::shared_ptr<zs::node> innode) : node(innode) {}

    void draw(ImDrawList* drawlist,
        ImVec2 center,
        float width, 
        ImColor col, 
        float connectionradius = 20.0f, 
        ImColor conncol = {1.0f,1.0f,1.0f,1.0f}, 
        float connectionspacing = 0.5f);


    friend class uinodehash;
    friend class uinodeequal;

};