#pragma once

namespace ImTrcr {
namespace Imaging {

    //Represents a point in two dimensional space that has real numbers as its coordinates
    class Point2F {
    public:
        Point2F(float x, float y);

        float GetX() const;
        void SetX(float x);
        float GetY() const;
        void SetY(float y);
    private:
        float x;
        float y;
    };

}
}