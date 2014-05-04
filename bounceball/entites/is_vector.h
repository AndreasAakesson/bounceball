#ifndef ISVECTOR_H
#define ISVECTOR_H

#include <math.h> // PI, cos, sin etc.
const double TAU=M_PI*2;
class isVector {
    float speed_;
protected:
    // contains the velocity for x and y
    class vector_velocity {
        float x_;
        float y_;
    public:
        float x() { return x_; }
        float y() { return y_; }
        void x(float vel) { x_ = vel; }
        void y(float vel) { y_ = vel; }
        void invertX() { x_ = -x_; }
        void invertY() { y_ = -y_; }
    };
    vector_velocity velocity; // access to velocity
public:
    float speed() { return speed_; }
    void speed(float speed) { speed_ = speed; }
};


#endif // ISVECTOR_H
