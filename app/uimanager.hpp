#pragma once

#include "uifwddecls.hpp"
#include "uinode.hpp"
#include "node.hpp"
#include "evalfunction.hpp" // so eval functions are accessible when including this header which requires them to create nodes

#include <unordered_map>
#include <memory>
#include <vector>

enum class interactionstate{
    NONE,
    HOVER_NODE,
    HOVER_INPUT,
    HOVER_OUTPUT,
    DRAG_NODE,
    DRAG_INPUT,
    DRAG_OUTPUT
};

struct uistate {

    interactionstate istate = interactionstate::NONE;
    std::shared_ptr<uinode> node = nullptr;
    int connectionindex = -1;
    
    bool operator==(const uistate& u2){
        return istate == u2.istate && node == u2.node && connectionindex == u2.connectionindex;
    }
    bool operator!=(const uistate& u2){
        return !operator==(u2);
    }

};

class uimanager{

    uistate state;
    uistate previousstate;
    bool isdragging = false;
    ImVec2 relativedraggedelementpostomousepos = {0,0};

    std::vector<std::shared_ptr<uinode>> uinodes;
    std::unordered_map<std::shared_ptr<zs::node>, std::shared_ptr<uinode>> uinodemap;

    uistate handlenodebodyinteraction(std::shared_ptr<uinode>);
    uistate handlenodeinputinteraction(std::shared_ptr<uinode>, int idx);
    uistate handlenodeoutputinteraction(std::shared_ptr<uinode>, int idx);

    void handleuistateend();
    void handleuistatebegin();
    void handleuistatecontinue();
public:
    float nodewidth = 70.0f;
    float nodeconnectionradius = 20.0f;
    ImColor nodeconnectioncolor = ImColor(0.2f,0.2f,0.2f,1.0f);
    float nodeconnectionspacingratio = 0.5f;

    std::shared_ptr<uinode> addnode(zs::eval ineval, std::vector<zs::connection> connections = {});
    std::shared_ptr<uinode> addnode(zs::evalfunction ineval, std::vector<zs::connection> connections = {});

    std::shared_ptr<zs::node> getsimnode(std::shared_ptr<uinode>) const;

    void render(ImDrawList*) const;
    void handleinteraction();

};