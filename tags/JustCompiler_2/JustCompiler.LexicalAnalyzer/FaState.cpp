#include "FaState.h"

FaState::FaState(const wstring& name) {
    this->name = name;
}

wstring FaState::GetName() const {
    return name;
}