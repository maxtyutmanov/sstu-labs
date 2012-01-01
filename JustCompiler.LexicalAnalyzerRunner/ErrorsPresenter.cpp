#include "ErrorsPresenter.h"
#include <ErrorCode.h>
#include <SemanticErrorCode.h>
#include <UndeclaredIdentifier.h>
#include <TokenExpected.h>
#include <UnexpectedToken.h>
#include <boost/lexical_cast.hpp>
#include <TokenTag.h>
#include <Redefinition.h>
#include <SpecialTokenTag.h>

using boost::lexical_cast;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer::Errors;
using namespace JustCompiler::SemanticAnalyzer;
using namespace JustCompiler::SemanticAnalyzer::Errors;

wstring ErrorsPresenter::GetErrorMessage(const PLexicalError error) {
    wstring msg = L"Лексическая ошибка (Строка " + lexical_cast<wstring, int>(error->GetLineNumber()) + L", символ " + lexical_cast<wstring, int>(error->GetCharNumber()) + L") ";

    switch (error->GetErrorCode()) {
    case ErrorCode::IdStartingWithDigit:
        msg += L"Идентификатор не может начинаться с цифры";
        break;
    case ErrorCode::IdWithWrongCharset:
        msg += L"Некорректный идентификатор: в идентификаторах допускаются только заглавные и строчные латинские буквы";
        break;
    case ErrorCode::IntConstantStartingWithZero:
        msg += L"Лидирующий ноль в числовой константе";
        break;
    case ErrorCode::TooLargeIntConstant:
        msg += L"Слишком большая целая константа";
        break;
    case ErrorCode::TooLongIdentifier:
        msg += L"Слишком длинный идентификатор";
        break;
    case ErrorCode::UnknownLexeme:
        msg += L"Неизвестная лексема";
        break;
    case ErrorCode::UnterminatedComment:
        msg += L"Незакрытый комментарий";
        break;
    case ErrorCode::UnterminatedStringLiteral:
        msg += L"Незакрытый строковый литерал";
        break;
    case ErrorCode::TooLargeRealConstant:
        msg += L"Слишком большая вещественная константа";
        break;
    case ErrorCode::RealConstantWrongFormat:
        msg += L"Неверный формат вещественной константы (допускаются числа с фиксированной запятой)";
    default:
        break;
    }

    return msg;
}

wstring ErrorsPresenter::GetErrorMessage(const PSyntaxError error) {
    wstring msg = L"Синтаксическая ошибка (Строка " + lexical_cast<wstring, int>(error->GetLineNum()) + L", символ " + lexical_cast<wstring, int>(error->GetCharNum()) + L") ";

    switch (error->GetErrorClass()) {
    case ErrorClass::TextAfterEndOfProgram:
        msg += L"Ожидался конец программы";
        break;
    case ErrorClass::TokenExpected:
        msg += GetMessageAboutExpectedToken(error);
        break;
    case ErrorClass::UnexpectedEndOfFile:
        msg += L"Неожиданный конец файла";
        break;
    case ErrorClass::UnexpectedToken: {
        PUnexpectedToken unexpToken = boost::dynamic_pointer_cast<UnexpectedToken, SyntaxError>(error);
        vector<int> expected = unexpToken->ExpectedTokenTags();
        msg += L"Ожидалась другая лексема: ";

        for (size_t i = 0; i < expected.size() - 1; ++i) {
            msg += GetTokenName(expected[i]) + L", ";
        }

        if (expected.size() > 0) {
            msg += GetTokenName(expected[expected.size() - 1]);
        }

        
        break;
                                      }
    default:
        break;
    }

    return msg;
}

wstring ErrorsPresenter::GetErrorMessage(const PSemanticError error) {
    wstring msg = L"Семантическая ошибка (Строка " + lexical_cast<wstring, int>(error->LineNum()) + L", символ " + lexical_cast<wstring, int>(error->CharNum()) + L") ";
    
    wstring idName;

    switch (error->ErrorCode()) {
    case SemanticErrorCode::UndeclaredIdentifier: {
        PUndeclaredIdentifier undeclaredId = boost::dynamic_pointer_cast<UndeclaredIdentifier, SemanticError>(error);
        assert(undeclaredId.get() != NULL);
        idName = undeclaredId->GetId()->GetName();
        msg += L"Необъявленный идентификатор \"" + idName + L"\"";
        break;
                                                  }
    case SemanticErrorCode::Redefinition: {
        PRedefinition redef = boost::dynamic_pointer_cast<Redefinition, SemanticError>(error);
        assert(redef.get() != NULL);
        idName = redef->GetId()->GetName();
        msg += L"Повторное объявление идентификатора \"" + idName + L"\"";
        break;
                                          }
    default:
        break;
    }

    return msg;
}

wstring ErrorsPresenter::GetMessageAboutExpectedToken(const PSyntaxError error) {
    assert(error->GetErrorClass() == ErrorClass::TokenExpected);

    const PTokenExpected tokenExpectedError = boost::dynamic_pointer_cast<TokenExpected, SyntaxError>(error);

    assert(tokenExpectedError.get() != NULL);

    switch (tokenExpectedError->ExpectedTokenTag()) {
    case TokenTag::Asterisk:
        return L"ожидался символ *";
    case TokenTag::Begin:
        return L"ожидалось begin";
    case TokenTag::ClosingBrace:
        return L"ожидался символ }";
    case TokenTag::ClosingRoundBracket:
        return L"ожидался символ )";
    case TokenTag::ClosingSquareBracket:
        return L"ожидался символ ]";
    case TokenTag::Colon:
        return L"ожидался символ :";
    case TokenTag::Comma:
        return L"ожидался символ ,";
    case TokenTag::Do:
        return L"ожидалось do";
    case TokenTag::Else:
        return L"ожидалось else";
    case TokenTag::End:
        return L"ожидался end";
    case TokenTag::Equals:
        return L"ожидался знак =";
    case TokenTag::For:
        return L"ожидалось for";
    case TokenTag::GreaterThan:
        return L"ожидался знак >";
    case TokenTag::Identifier:
        return L"ожидался идентификатор";
    case TokenTag::If:
        return L"ожидалось if";
    case TokenTag::IntConstant:
        return L"ожидалась целая константа";
    case TokenTag::LessThan:
        return L"ожидался знак <";
    case TokenTag::Minus:
        return L"ожидался знак -";
    case TokenTag::OpeningBrace:
        return L"ожидался символ {";
    case TokenTag::OpeningRoundBracket:
        return L"ожидался символ (";
    case TokenTag::OpeningSquareBracket:
        return L"ожидался символ [";
    case TokenTag::Plus:
        return L"ожидался знак +";
    case TokenTag::Program:
        return L"ожидалось program";
    case TokenTag::Quotes:
        return L"ожидался знак \"";
    case TokenTag::Read:
        return L"ожидался оператор read";
    case TokenTag::RealConstant:
        return L"ожидалась вещественная константа";
    case TokenTag::Semicolon:
        return L"ожидался символ ;";
    case TokenTag::SingleQuotes:
        return L"ожидался символ '";
    case TokenTag::Slash:
        return L"ожидался знак /";
    case TokenTag::StandardFunction:
        return L"ожидался вызов стандартной функции";
    case TokenTag::Then:
        return L"ожидалось then";
    case TokenTag::To:
        return L"ожидалось to";
    case TokenTag::Type_Int:
        return L"ожидалось объявление типа integer";
    case TokenTag::Type_Real:
        return L"ожидалось объявление типа real";
    case TokenTag::Underscore:
        return L"ожидался символ _";
    case TokenTag::Var:
        return L"ожидалось var";
    case TokenTag::Write:
        return L"ожидался оператор write";
    case SpecialTokenTag::Eof:
        return L"ожидался конец файла";
    }

    return L"";
}

wstring ErrorsPresenter::GetTokenName(const int tokenTag) {
        switch (tokenTag) {
    case TokenTag::Asterisk:
        return L"*";
    case TokenTag::Begin:
        return L"begin";
    case TokenTag::ClosingBrace:
        return L"}";
    case TokenTag::ClosingRoundBracket:
        return L")";
    case TokenTag::ClosingSquareBracket:
        return L"]";
    case TokenTag::Colon:
        return L":";
    case TokenTag::Comma:
        return L",";
    case TokenTag::Do:
        return L"do";
    case TokenTag::Else:
        return L"else";
    case TokenTag::End:
        return L"end";
    case TokenTag::Equals:
        return L"=";
    case TokenTag::For:
        return L"for";
    case TokenTag::GreaterThan:
        return L">";
    case TokenTag::Identifier:
        return L"идентификатор";
    case TokenTag::If:
        return L"if";
    case TokenTag::IntConstant:
        return L"целая константа";
    case TokenTag::LessThan:
        return L"<";
    case TokenTag::Minus:
        return L"-";
    case TokenTag::OpeningBrace:
        return L"{";
    case TokenTag::OpeningRoundBracket:
        return L"(";
    case TokenTag::OpeningSquareBracket:
        return L"[";
    case TokenTag::Plus:
        return L"+";
    case TokenTag::Program:
        return L"program";
    case TokenTag::Quotes:
        return L"\"";
    case TokenTag::Read:
        return L"read";
    case TokenTag::RealConstant:
        return L"вещественная константа";
    case TokenTag::Semicolon:
        return L";";
    case TokenTag::SingleQuotes:
        return L"'";
    case TokenTag::Slash:
        return L"/";
    case TokenTag::StandardFunction:
        return L"стандартная функция";
    case TokenTag::Then:
        return L"then";
    case TokenTag::To:
        return L"to";
    case TokenTag::Type_Int:
        return L"объявление типа integer";
    case TokenTag::Type_Real:
        return L"объявление типа real";
    case TokenTag::Underscore:
        return L"_";
    case TokenTag::Var:
        return L"var";
    case TokenTag::Write:
        return L"write";
    case SpecialTokenTag::Eof:
        return L"конец файла";
    }
}