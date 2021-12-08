

struct mys {
    mys(float l) { f = l; };
    float f;

    bool operator<(const mys& right) const {
        return f > right.f;
    }
};

#include "A_Star_Pathfinding.h"
int main() {
    A_Star_Pathfinding_Undefined path;
    int p = 5;
    path.FindPath(Vector2<int>(5, 5), Vector2<int>(11, 5));
    path.PrintPath();
    //std::priority_queue<mys> p;
    //p.push(mys(5));
    //p.push(mys(1));
    //p.push(mys(2));
    //p.push(mys(1));
    //p.push(mys(3));
    //p.push(mys(8));
    //mys l = p.top();
    //std::cout << p.top()
    return 0;
}
