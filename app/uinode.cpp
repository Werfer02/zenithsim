#include "uinode.hpp"

#include "node.hpp"

void uinode::draw(ImDrawList* drawlist,
    ImVec2 center,
    float width, 
    ImColor col, 
    float connectionradius, 
    ImColor conncol, 
    float connectionspacing){

    float connspacingactual = connectionspacing*connectionradius*2;
    float height = node->getconnections().size()*2*connspacingactual + (node->getconnections().size()+1)*connspacingactual;

    ImVec2 topleft({center.x - 0.5f*width, center.y - 0.5f*height});
    ImVec2 bottomright({center.x + 0.5f*width, center.y + 0.5f*height});
    drawlist->AddRectFilled(topleft, bottomright, col, connectionradius);

    for(int i = 0; i < node->getconnections().size(); i++){

        float connectionx = center.x - 0.5f*width;
        float connectiony = center.y - 0.5f*(node->getconnections().size() - 1)*(2*connectionradius + connspacingactual) + i*(2*connectionradius + connspacingactual);

        drawlist->AddCircleFilled({connectionx, connectiony}, connectionradius, conncol, 32);

    }
}