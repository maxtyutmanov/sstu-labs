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
    wstring msg = L"����������� ������ (������ " + lexical_cast<wstring, int>(error->GetLineNumber()) + L", ������ " + lexical_cast<wstring, int>(error->GetCharNumber()) + L") ";

    switch (error->GetErrorCode()) {
    case ErrorCode::IdStartingWithDigit:
        msg += L"������������� �� ����� ���������� � �����";
        break;
    case ErrorCode::IdWithWrongCharset:
        msg += L"������������ �������������: � ��������������� ����������� ������ ��������� � �������� ��������� �����";
        break;
    case ErrorCode::IntConstantStartingWithZero:
        msg += L"���������� ���� � �������� ���������";
        break;
    case ErrorCode::TooLargeIntConstant:
        msg += L"������� ������� ����� ���������";
        break;
    case ErrorCode::TooLongIdentifier:
        msg += L"������� ������� �������������";
        break;
    case ErrorCode::UnknownLexeme:
        msg += L"����������� �������";
        break;
    case ErrorCode::UnterminatedComment:
        msg += L"���������� �����������";
        break;
    case ErrorCode::UnterminatedStringLiteral:
        msg += L"���������� ��������� �������";
        break;
    case ErrorCode::TooLargeRealConstant:
        msg += L"������� ������� ������������ ���������";
        break;
    case ErrorCode::RealConstantWrongFormat:
        msg += L"�������� ������ ������������ ��������� (����������� ����� � ������������� �������)";
    default:
        break;
    }

    return msg;
}

wstring ErrorsPresenter::GetErrorMessage(const PSyntaxError error) {
    wstring msg = L"�������������� ������ (������ " + lexical_cast<wstring, int>(error->GetLineNum()) + L", ������ " + lexical_cast<wstring, int>(error->GetCharNum()) + L") ";

    switch (error->GetErrorClass()) {
    case ErrorClass::TextAfterEndOfProgram:
        msg += L"�������� ����� ���������";
        break;
    case ErrorClass::TokenExpected:
        msg += GetMessageAboutExpectedToken(error);
        break;
    case ErrorClass::UnexpectedEndOfFile:
        msg += L"����������� ����� �����";
        break;
    case ErrorClass::UnexpectedToken: {
        PUnexpectedToken unexpToken = boost::dynamic_pointer_cast<UnexpectedToken, SyntaxError>(error);
        vector<int> expected = unexpToken->ExpectedTokenTags();
        msg += L"��������� ������ �������: ";

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
    wstring msg = L"������������� ������ (������ " + lexical_cast<wstring, int>(error->LineNum()) + L", ������ " + lexical_cast<wstring, int>(error->CharNum()) + L") ";
    
    wstring idName;

    switch (error->ErrorCode()) {
    case SemanticErrorCode::UndeclaredIdentifier: {
        PUndeclaredIdentifier undeclaredId = boost::dynamic_pointer_cast<UndeclaredIdentifier, SemanticError>(error);
        assert(undeclaredId.get() != NULL);
        idName = undeclaredId->GetId()->GetName();
        msg += L"������������� ������������� \"" + idName + L"\"";
        break;
                                                  }
    case SemanticErrorCode::Redefinition: {
        PRedefinition redef = boost::dynamic_pointer_cast<Redefinition, SemanticError>(error);
        assert(redef.get() != NULL);
        idName = redef->GetId()->GetName();
        msg += L"��������� ���������� �������������� \"" + idName + L"\"";
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
        return L"�������� ������ *";
    case TokenTag::Begin:
        return L"��������� begin";
    case TokenTag::ClosingBrace:
        return L"�������� ������ }";
    case TokenTag::ClosingRoundBracket:
        return L"�������� ������ )";
    case TokenTag::ClosingSquareBracket:
        return L"�������� ������ ]";
    case TokenTag::Colon:
        return L"�������� ������ :";
    case TokenTag::Comma:
        return L"�������� ������ ,";
    case TokenTag::Do:
        return L"��������� do";
    case TokenTag::Else:
        return L"��������� else";
    case TokenTag::End:
        return L"�������� end";
    case TokenTag::Equals:
        return L"�������� ���� =";
    case TokenTag::For:
        return L"��������� for";
    case TokenTag::GreaterThan:
        return L"�������� ���� >";
    case TokenTag::Identifier:
        return L"�������� �������������";
    case TokenTag::If:
        return L"��������� if";
    case TokenTag::IntConstant:
        return L"��������� ����� ���������";
    case TokenTag::LessThan:
        return L"�������� ���� <";
    case TokenTag::Minus:
        return L"�������� ���� -";
    case TokenTag::OpeningBrace:
        return L"�������� ������ {";
    case TokenTag::OpeningRoundBracket:
        return L"�������� ������ (";
    case TokenTag::OpeningSquareBracket:
        return L"�������� ������ [";
    case TokenTag::Plus:
        return L"�������� ���� +";
    case TokenTag::Program:
        return L"��������� program";
    case TokenTag::Quotes:
        return L"�������� ���� \"";
    case TokenTag::Read:
        return L"�������� �������� read";
    case TokenTag::RealConstant:
        return L"��������� ������������ ���������";
    case TokenTag::Semicolon:
        return L"�������� ������ ;";
    case TokenTag::SingleQuotes:
        return L"�������� ������ '";
    case TokenTag::Slash:
        return L"�������� ���� /";
    case TokenTag::StandardFunction:
        return L"�������� ����� ����������� �������";
    case TokenTag::Then:
        return L"��������� then";
    case TokenTag::To:
        return L"��������� to";
    case TokenTag::Type_Int:
        return L"��������� ���������� ���� integer";
    case TokenTag::Type_Real:
        return L"��������� ���������� ���� real";
    case TokenTag::Underscore:
        return L"�������� ������ _";
    case TokenTag::Var:
        return L"��������� var";
    case TokenTag::Write:
        return L"�������� �������� write";
    case SpecialTokenTag::Eof:
        return L"�������� ����� �����";
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
        return L"�������������";
    case TokenTag::If:
        return L"if";
    case TokenTag::IntConstant:
        return L"����� ���������";
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
        return L"������������ ���������";
    case TokenTag::Semicolon:
        return L";";
    case TokenTag::SingleQuotes:
        return L"'";
    case TokenTag::Slash:
        return L"/";
    case TokenTag::StandardFunction:
        return L"����������� �������";
    case TokenTag::Then:
        return L"then";
    case TokenTag::To:
        return L"to";
    case TokenTag::Type_Int:
        return L"���������� ���� integer";
    case TokenTag::Type_Real:
        return L"���������� ���� real";
    case TokenTag::Underscore:
        return L"_";
    case TokenTag::Var:
        return L"var";
    case TokenTag::Write:
        return L"write";
    case SpecialTokenTag::Eof:
        return L"����� �����";
    }
}