#include "uimanager.hpp"

#include "uinode.hpp"
#include "node.hpp"

#include <typeinfo>
#include <iostream>

#define square(x) ((x) * (x))

std::shared_ptr<uinode> uimanager::addnode(zs::eval ineval, std::vector<zs::connection> connections){
    std::shared_ptr<zs::node> n = zs::node::create(ineval, connections);
    auto uin = std::make_shared<uinode>(n);
    uinodes.push_back(uin);
    uinodemap.insert({n, uin});
    return uin;
}

std::shared_ptr<uinode> uimanager::addnode(zs::evalfunction ineval, std::vector<zs::connection> connections){
    std::shared_ptr<zs::node> n = zs::node::create(ineval, connections);
    auto uin = std::make_shared<uinode>(n);
    uinodes.push_back(uin);
    uinodemap.insert({n, uin});
    return uin;
}

std::shared_ptr<zs::node> uimanager::getsimnode(std::shared_ptr<uinode> n) const{
    return n->node;
}

void uimanager::render(ImDrawList* drawlist) const{

    for(auto n : uinodes){

        n->draw(drawlist, nodewidth, nodeconnectionradius, nodeconnectioncolor, nodeconnectionspacingratio);
        for(int i = 0; i < n->node->getconnections().size(); i++){

            ImVec2 linestart = n->getinputposition(nodewidth, i, nodeconnectionradius, nodeconnectionspacingratio);
            auto outputnode = uinodemap.find(n->node->getconnections()[i].targetnode)->second;
            ImVec2 lineend = outputnode->getoutputposition(nodewidth, n->node->getconnections()[i].outputidx, nodeconnectionradius, nodeconnectionspacingratio);

            drawlist->AddLine(lineend, linestart, nodeconnectioncolor, nodeconnectionradius);

        }

    }

}

int getinteractionstatepriority(interactionstate state) {
    switch (state) {
        case interactionstate::DRAG_INPUT:   return 4;
        case interactionstate::DRAG_OUTPUT:  return 4;
        case interactionstate::DRAG_NODE:    return 3;
        case interactionstate::HOVER_INPUT:  return 2;
        case interactionstate::HOVER_OUTPUT: return 2;
        case interactionstate::HOVER_NODE:   return 1;
        default: return 0;
    }
}

ImVec2 operator-(const ImVec2& v1, const ImVec2& v2){
    return {v1.x - v2.x, v1.y - v2.y};
}

ImVec2 operator+(const ImVec2& v1, const ImVec2& v2){
    return {v1.x + v2.x, v1.y + v2.y};
}

void uimanager::handleinteraction(){

    if (isdragging && !ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        isdragging = false;
        relativedraggedelementpostomousepos = {0,0};
        handleuistateend();
        state.istate = interactionstate::NONE;
        state.node = nullptr;
        state.connectionindex = -1;
        previousstate = state;
        return;
    }
    
    if(!isdragging){

        uistate beststate;
        int bestpriority = 0;

        for(auto n : uinodes){

            uistate nodebodydetectedstate = handlenodebodyinteraction(n);
            int p = getinteractionstatepriority(nodebodydetectedstate.istate);
            if(p > bestpriority){
                beststate = nodebodydetectedstate; bestpriority = p;
            }
            for(int i = 0; i < n->node->getconnections().size(); i++){
                uistate nodeinputdetectedstate = handlenodeinputinteraction(n, i);
                p = getinteractionstatepriority(nodeinputdetectedstate.istate);
                if(p > bestpriority){
                    beststate = nodeinputdetectedstate; bestpriority = p;
                }
            }
            for(int o = 0; o < n->outputs; o++){
                uistate nodeoutputdetectedstate = handlenodeoutputinteraction(n, o);
                p = getinteractionstatepriority(nodeoutputdetectedstate.istate);
                if(p > bestpriority){
                    beststate = nodeoutputdetectedstate; bestpriority = p;
                }
            }

        }

        state = beststate;

        if(previousstate != state){
            handleuistateend();
            handleuistatebegin();
            previousstate = state;
        }
        else{
            handleuistatecontinue();
        }

    }
    else{
        handleuistatecontinue();
    }

}

void uimanager::handleuistateend(){
    switch(previousstate.istate){
        case interactionstate::NONE:
            std::cout << "->NONE->";
            break;
        case interactionstate::HOVER_NODE:
            std::cout << "->HOVER_NODE->";
            previousstate.node->setColor(ImColor(0.9f,0.9f,0.0f,1.0f));
            break;
        case interactionstate::HOVER_INPUT:
            std::cout << "->HOVER_INPUT->";
            nodeconnectioncolor = ImColor(0.2f,0.2f,0.2f,1.0f);
            break;
        case interactionstate::HOVER_OUTPUT:
            std::cout << "->HOVER_OUTPUT->";
            nodeconnectioncolor = ImColor(0.2f,0.2f,0.2f,1.0f);
            break;
        case interactionstate::DRAG_NODE:
            std::cout << "->DRAG_NODE->";
            previousstate.node->setColor(ImColor(0.9f,0.9f,0.0f,1.0f));
            break;
        case interactionstate::DRAG_INPUT:
            std::cout << "->DRAG_INPUT->";
            nodeconnectioncolor = ImColor(0.2f,0.2f,0.2f,1.0f);
            break;
        case interactionstate::DRAG_OUTPUT:
            std::cout << "->DRAG_OUTPUT->";
            nodeconnectioncolor = ImColor(0.2f,0.2f,0.2f,1.0f);
            break;
    }
}

void uimanager::handleuistatebegin(){
    switch(state.istate){
        case interactionstate::NONE:
            std::cout << "NONE\n";
            break;
        case interactionstate::HOVER_NODE:
            std::cout << "HOVER_NODE\n";
                state.node->setColor(ImColor(0.5f, 0.0f, 0.5f));
            break;
        case interactionstate::HOVER_INPUT:
            std::cout << "HOVER_INPUT\n";
            nodeconnectioncolor = ImColor(0.5f, 0.0f, 0.0f);
            break;
        case interactionstate::HOVER_OUTPUT:
            std::cout << "HOVER_OUTPUT\n";
            nodeconnectioncolor = ImColor(0.0f, 0.0f, 0.5f);
            break;
        case interactionstate::DRAG_NODE:
            std::cout << "DRAG_NODE\n";
            isdragging = true;
            state.node->setColor(ImColor(1.0f, 0.0f, 1.0f));
            break;
        case interactionstate::DRAG_INPUT:
            std::cout << "DRAG_INPUT\n";
            isdragging = true;
            nodeconnectioncolor = ImColor(1.0f, 0.0f, 0.0f);
            break;
        case interactionstate::DRAG_OUTPUT:
            std::cout << "DRAG_OUTPUT\n";
            isdragging = true;
            nodeconnectioncolor = ImColor(0.0f, 0.0f, 1.0f);
            break;
    }
}

void uimanager::handleuistatecontinue(){
    switch(state.istate){
        case interactionstate::NONE:
            std::cout << "->NONE->\n";
            break;
        case interactionstate::HOVER_NODE:
            std::cout << "->HOVER_NODE->\n";
            break;
        case interactionstate::HOVER_INPUT:
            std::cout << "->HOVER_INPUT->\n";
            break;
        case interactionstate::HOVER_OUTPUT:
            std::cout << "->HOVER_OUTPUT->\n";
            break;
        case interactionstate::DRAG_NODE:
            std::cout << "->DRAG_NODE->\n";
            state.node->setposition(ImGui::GetMousePos() + relativedraggedelementpostomousepos);
            break;
        case interactionstate::DRAG_INPUT:
            std::cout << "->DRAG_INPUT->\n";
            break;
        case interactionstate::DRAG_OUTPUT:
            std::cout << "->DRAG_OUTPUT->\n";
            break;
    }
}

bool ismousehoveringcircle(ImVec2 position, float radius){
    ImVec2 point = ImGui::GetMousePos();
    return square(point.x - position.x) + square(point.y - position.y) <= square(radius);
}

bool ismousehoveringroundedrectangle(ImVec2 position, ImVec2 dimensions, float radius){
    ImVec2 point = ImGui::GetMousePos();

    if(point.x < (position.x - dimensions.x*0.5f) || point.x > (position.x + dimensions.x*0.5f)
    || point.y < (position.y - dimensions.y*0.5f) || point.y > (position.y + dimensions.y*0.5f)) return false;

    ImVec2 toplefttallrect =     {position.x - (dimensions.x*0.5f - radius), position.y - dimensions.y*0.5f};
    ImVec2 bottomrighttallrect = {position.x + (dimensions.x*0.5f - radius), position.y + dimensions.y*0.5f};
    ImVec2 topleftwiderect =     {position.x - dimensions.x*0.5f, position.y - (dimensions.y*0.5f - radius)};
    ImVec2 bottomrightwiderect = {position.x + dimensions.x*0.5f, position.y + (dimensions.y*0.5f - radius)};

    if(ImGui::IsMouseHoveringRect(toplefttallrect, bottomrighttallrect) || ImGui::IsMouseHoveringRect(topleftwiderect, bottomrightwiderect)) return true;

    ImVec2 topleftcirclepos =     {position.x - (dimensions.x*0.5f - radius), position.y - (dimensions.y*0.5f - radius)};
    ImVec2 toprightcirclepos =    {position.x + (dimensions.x*0.5f - radius), position.y - (dimensions.y*0.5f - radius)};
    ImVec2 bottomleftcirclepos =  {position.x - (dimensions.x*0.5f - radius), position.y + (dimensions.y*0.5f - radius)};
    ImVec2 bottomrightcirclepos = {position.x + (dimensions.x*0.5f - radius), position.y + (dimensions.y*0.5f - radius)};

    if(ismousehoveringcircle(topleftcirclepos, radius)
    || ismousehoveringcircle(toprightcirclepos, radius)
    || ismousehoveringcircle(bottomleftcirclepos, radius)
    || ismousehoveringcircle(bottomrightcirclepos, radius)) return true;

    return false;

}

uistate uimanager::handlenodebodyinteraction(std::shared_ptr<uinode> n){
    uistate detectedstate;

    float connspacingactual = nodeconnectionspacingratio*nodeconnectionradius*2;
    int baseheighton = std::max((int)n->node->getconnections().size(), n->outputs);
    float height = baseheighton*2*connspacingactual + (baseheighton+1)*connspacingactual;

    if(ismousehoveringroundedrectangle(n->position, {nodewidth, height}, nodeconnectionradius)){
        detectedstate.node = n;
        detectedstate.connectionindex = -1;
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
            detectedstate.istate = interactionstate::DRAG_NODE;
            relativedraggedelementpostomousepos = n->getposition() - ImGui::GetMousePos();
        }
        else{
            detectedstate.istate = interactionstate::HOVER_NODE;
        }
    }
    return detectedstate;
}

uistate uimanager::handlenodeinputinteraction(std::shared_ptr<uinode> n, int idx){
    uistate detectedstate;

    ImVec2 inputpos = n->getinputposition(nodewidth, idx, nodeconnectionradius, nodeconnectionspacingratio);
    if(ismousehoveringcircle(inputpos, nodeconnectionradius)){
        detectedstate.node = n;
        detectedstate.connectionindex = idx;
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
            detectedstate.istate = interactionstate::DRAG_INPUT;
            relativedraggedelementpostomousepos = n->getinputposition(nodewidth, idx, nodeconnectionradius, nodeconnectionspacingratio) - ImGui::GetMousePos();
        }
        else{
            detectedstate.istate = interactionstate::HOVER_INPUT;
        }
    }
    return detectedstate;
}

uistate uimanager::handlenodeoutputinteraction(std::shared_ptr<uinode> n, int idx){
    uistate detectedstate;

    ImVec2 outputpos = n->getoutputposition(nodewidth, idx, nodeconnectionradius, nodeconnectionspacingratio);
    if(ismousehoveringcircle(outputpos, nodeconnectionradius)){
        detectedstate.node = n;
        detectedstate.connectionindex = idx;
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
            detectedstate.istate = interactionstate::DRAG_OUTPUT;
            relativedraggedelementpostomousepos = n->getoutputposition(nodewidth, idx, nodeconnectionradius, nodeconnectionspacingratio) - ImGui::GetMousePos();
        }
        else{
            detectedstate.istate = interactionstate::HOVER_OUTPUT;
        }
    }
    return detectedstate;
}