#include "ErrorsPresenter.h"
#include <ErrorCode.h>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;

ErrorsPresenter::ErrorsPresenter(const LexerSettings& settings) {
    this->settings = settings;
}

wstring ErrorsPresenter::GetErrorMessage(const LexicalError& error) {
    wstring msg = L"(Строка " + lexical_cast<wstring, int>(error.GetLineNumber()) + L", символ " + lexical_cast<wstring, int>(error.GetCharNumber()) + L") ";

    switch (error.GetErrorCode()) {
    case ErrorCode::IdStartingWithDigit:
        msg += L"Идентификатор не может начинаться с цифры";
        break;
    case ErrorCode::IdWithWrongCharset:
        msg += L"Некорректный идентификатор: в идентификаторах допускаются только заглавные и строчные латинские буквы";
        break;
    case ErrorCode::IntConstantStartingWithZero:
        msg += L"Лидирующий ноль в целой константе";
        break;
    case ErrorCode::TooLargeIntConstant:
        msg += L"Слишком большая целая константа (максимально допустимое значение: " + lexical_cast<wstring, int>(INT_MAX) + L")";
        break;
    case ErrorCode::TooLongIdentifier:
        msg += L"Слишком длинный идентификатор (допускается не более " + lexical_cast<wstring, int>(settings.GetMaxIdentifierLength()) + L" символов)";
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
    default:
        msg += L"Лексическая ошибка";
        break;
    }

    return msg;
}