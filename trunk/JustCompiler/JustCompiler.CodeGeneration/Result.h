#pragma once

#include <string>

namespace JustCompiler {
namespace CodeGeneration {

    class Result {
    public:
        Result(const std::string& place) 
            : place(place) {}

        std::string GetPlace() const {
            return place;
        }

    private:
        std::string place;
    };

}
}