#pragma once

#include <string>
using std::wstring;

class FaState {
public:
    FaState(const wstring& name);

    wstring GetName() const;
private:
    wstring name;
};