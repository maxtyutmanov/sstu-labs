#include "ErrorsPresenter.h"
#include <ErrorCode.h>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;

ErrorsPresenter::ErrorsPresenter(const LexerSettings& settings) {
    this->settings = settings;
}

wstring ErrorsPresenter::GetErrorMessage(const LexicalError& error) {
    wstring msg = L"(������ " + lexical_cast<wstring, int>(error.GetLineNumber()) + L", ������ " + lexical_cast<wstring, int>(error.GetCharNumber()) + L") ";

    switch (error.GetErrorCode()) {
    case ErrorCode::IdStartingWithDigit:
        msg += L"������������� �� ����� ���������� � �����";
        break;
    case ErrorCode::IdWithWrongCharset:
        msg += L"������������ �������������: � ��������������� ����������� ������ ��������� � �������� ��������� �����";
        break;
    case ErrorCode::IntConstantStartingWithZero:
        msg += L"���������� ���� � ����� ���������";
        break;
    case ErrorCode::TooLargeIntConstant:
        msg += L"������� ������� ����� ��������� (����������� ���������� ��������: " + lexical_cast<wstring, int>(INT_MAX) + L")";
        break;
    case ErrorCode::TooLongIdentifier:
        msg += L"������� ������� ������������� (����������� �� ����� " + lexical_cast<wstring, int>(settings.GetMaxIdentifierLength()) + L" ��������)";
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
    default:
        msg += L"����������� ������";
        break;
    }

    return msg;
}