#include "uinode.hpp"

#include "node.hpp"

ImVec2 uinode::getinputposition(float width, int idx, float connectionradius, float connectionspacing) const{

    float connspacingactual = connectionspacing*connectionradius*2;
    float connectionx = position.x - 0.5f*width;
    float connectiony = position.y - 0.5f*(node->getconnections().size() - 1)*(2*connectionradius + connspacingactual) + idx*(2*connectionradius + connspacingactual);
    return {connectionx, connectiony};

}

ImVec2 uinode::getoutputposition(float width, int idx, float connectionradius, float connectionspacing) const{

    float connspacingactual = connectionspacing*connectionradius*2;
    float connectionx = position.x + 0.5f*width;
    float connectiony = position.y - 0.5f*(outputs - 1)*(2*connectionradius + connspacingactual) + idx*(2*connectionradius + connspacingactual);
    return {connectionx, connectiony};

}

ImVec2 uinode::getposition() const{
    return position;
}

void uinode::setposition(ImVec2 p){
    position = p;
}

ImColor uinode::getcolor() const{
    return color;
}

void uinode::setColor(ImColor c){
    color = c;
}

void uinode::draw(ImDrawList* drawlist,
    float width, 
    float connectionradius, 
    ImColor conncol, 
    float connectionspacing){

    float connspacingactual = connectionspacing*connectionradius*2;
    int baseheighton = std::max((int)node->getconnections().size(), outputs);
    float height = baseheighton*2*connspacingactual + (baseheighton+1)*connspacingactual;

    ImVec2 topleft({position.x - 0.5f*width, position.y - 0.5f*height});
    ImVec2 bottomright({position.x + 0.5f*width, position.y + 0.5f*height});
    drawlist->AddRectFilled(topleft, bottomright, color, connectionradius);

    for(int i = 0; i < node->getconnections().size(); i++){

        ImVec2 inputposition = getinputposition(width, i, connectionradius, connectionspacing);
        drawlist->AddCircleFilled(inputposition, connectionradius, conncol, 32);

    }

    for(int i = 0; i < outputs; i++){

        ImVec2 outputposition = getoutputposition(width, i, connectionradius, connectionspacing);
        drawlist->AddCircleFilled(outputposition, connectionradius, conncol, 32);

    }
}