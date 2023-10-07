#include "hit.hpp"

Hit::Hit() : t(0), triangle_id(-1), bary(Vector()) {

}

Hit::Hit(double _t, int t_id, Vector b) : t(_t), triangle_id(t_id), bary(b) {

}

Hit::operator bool() const {
    return triangle_id >= 0;
}





//EOF