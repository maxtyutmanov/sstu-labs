#pragma once

#include "Global.h"
#include "CharValidationRule.h"
#include "FaState.h"
#include "TokenCreator.h"
#include "ReadAction.h"
#include <memory>
#include <boost/shared_ptr.hpp>
using std::auto_ptr;
using boost::shared_ptr;


class FaTransition {
public:
    FaTransition(
        shared_ptr<FaState> from, 
        shared_ptr<FaState> to,
        CharValidationRule validationRule,
        ReadAction::Enum readAction) {

        Init(from, to, validationRule, readAction, shared_ptr<TokenCreator>(), 0);
    }

    FaTransition(
        shared_ptr<FaState> from, 
        shared_ptr<FaState> to,
        CharValidationRule validationRule,
        ReadAction::Enum readAction,
        shared_ptr<TokenCreator> tokenCreator) {

        Init(from, to, validationRule, readAction, tokenCreator, 0);
    }

    FaTransition(
        shared_ptr<FaState> from, 
        shared_ptr<FaState> to,
        CharValidationRule validationRule,
        ReadAction::Enum readAction,
        int errorCode) {

        Init(from, to, validationRule, readAction, shared_ptr<TokenCreator>(), errorCode);
    }

    shared_ptr<FaState> From() const {
        return from;
    }

    shared_ptr<FaState> To() const {
        return to;
    }

    bool IsCharValid(char_type inputChar) const {
        return validationRule(inputChar);
    }

    ReadAction::Enum GetReadAction() const {
        return readAction;
    }

    shared_ptr<TokenCreator> GetTokenCreator() const {
        return tokenCreator;
    }

    int ErrorCode() const {
        return errorCode;
    }

protected:
    void Init(
        shared_ptr<FaState> from, 
        shared_ptr<FaState> to, 
        CharValidationRule validationRule,
        ReadAction::Enum readAction,
        shared_ptr<TokenCreator> 
        tokenCreator, 
        int errorCode) {

        this->from = from;
        this->to = to;
        this->validationRule = validationRule;
        this->readAction = readAction;
        this->tokenCreator = tokenCreator;
        this->errorCode = errorCode;
    }

private:
    shared_ptr<FaState> from;
    shared_ptr<FaState> to;
    shared_ptr<TokenCreator> tokenCreator;
    int errorCode;
    
    CharValidationRule validationRule;
    ReadAction::Enum readAction;
};