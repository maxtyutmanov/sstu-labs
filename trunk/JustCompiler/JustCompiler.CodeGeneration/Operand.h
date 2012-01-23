#pragma once

#include "Variable.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace JustCompiler {
namespace CodeGeneration {

    struct OperandType {
        enum Enum {
            Variable,
            IntValue,
            RealValue,
            Label
        };
    };

    class Operand {
    public:
        virtual OperandType::Enum GetType() const = 0;
        virtual std::wstring ToString() const = 0;
    };

    typedef boost::shared_ptr<Operand> POperand;

    class VariableOperand : public Operand {
    public:
        VariableOperand(const Variable& var) 
            :var(var) { }

        virtual OperandType::Enum GetType() const {
            return OperandType::Variable;
        }

        virtual std::wstring ToString() const {
            return var.GetName();
        }
    private:
        Variable var;
    };

    typedef boost::shared_ptr<VariableOperand> PVariableOperand;

    class IntOperand : public Operand {
    public:
        IntOperand(int value)
            : value(value) {}

        virtual OperandType::Enum GetType() const {
            return OperandType::IntValue;
        }

        virtual std::wstring ToString() const {
            return boost::lexical_cast<std::wstring, int>(value);
        }
    private:
        int value;
    };

    typedef boost::shared_ptr<IntOperand> PIntOperand;

    class RealOperand : public Operand {
    public:
        RealOperand(double value)
            : value(value) {}

        virtual OperandType::Enum GetType() const {
            return OperandType::RealValue;
        }

        virtual std::wstring ToString() const {
            return boost::lexical_cast<std::wstring, double>(value);
        }
    private:
        double value;
    };

    typedef boost::shared_ptr<RealOperand> PRealOperand;

    class LabelOperand : public Operand {
    public:
        LabelOperand(const std::wstring& labelName)
            : labelName(labelName) {}

        virtual OperandType::Enum GetType() const {
            return OperandType::Label;
        }

        virtual std::wstring ToString() const {
            return labelName;
        }
    private:
        std::wstring labelName;
    };

    typedef boost::shared_ptr<LabelOperand> PLabelOperand;
}
}