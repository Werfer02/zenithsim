#pragma once

#include "uifwddecls.hpp"
#include "node.hpp"
#include <memory>

class uinode{

    ImVec2 position = {0.0f,0.0f};
    ImColor color = ImColor(0.9f,0.9f,0.0f,1.0f);
    std::shared_ptr<zs::node> node;
    int outputs = node->getvalidoutputcount();

public:
    uinode(std::shared_ptr<zs::node> innode) : node(innode) {}

    ImVec2 getinputposition(float width, int idx, float connectionradius, float connectionspacing) const;
    ImVec2 getoutputposition(float width, int idx, float connectionradius, float connectionspacing) const;

    ImVec2 getposition() const;
    ImColor getcolor() const;

    void setposition(ImVec2);
    void setColor(ImColor);

    void draw(ImDrawList* drawlist,
        float width,
        float connectionradius, 
        ImColor conncol, 
        float connectionspacing);


    friend class uimanager;

};