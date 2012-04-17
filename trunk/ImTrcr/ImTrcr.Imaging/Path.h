#pragma once

#include "Primitive.h"
#include "Point2F.h"
#include <vector>

namespace ImTrcr {
namespace Imaging {
namespace Primitives {

    class PathCommand {
    public:
        enum Type {
            MoveTo,
            QuadraticBezierTo,
            ClosePath
        };

    private:
        std::vector<Point2F> points;
    };

    class Path : public Primitive {
    public:
        Path(ArgbQuad color);

        void AddCommand(const PathCommand& command);

        const std::vector<PathCommand>& GetCommands() const;
    private:
        std::vector<PathCommand> commands;
    };

}
}
}