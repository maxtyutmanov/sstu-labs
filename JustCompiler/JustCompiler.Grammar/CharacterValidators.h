#pragma once

#include <tchar.h>

namespace JustCompiler {
namespace LexicalAnalyzer {

    class CharacterValidators {
    public:
        static bool IsAlpha(wchar_t ch) {
            return iswalpha(ch);
        }

        static bool IsAsciiAlpha(wchar_t ch) {
            return iswascii(ch);
        }

        static bool IsDigit(wchar_t ch) {
            return iswdigit(ch);
        }

        static bool IsSpace(wchar_t ch) {
            return ch == L'';
        }

        static bool IsEof(wchar_t ch) {
            return ch == L'\0';
        }

        static bool IsNewline(wchar_t ch) {
            return ch == L'\n' || ch == L'\r';
        }

        static bool IsNewlineOrEof(wchar_t ch) {
            return IsNewline(ch) || IsEof(ch);
        }

        static bool IsSpaceTabOrNewline(wchar_t ch) {
            return ch == L' ' || ch == L'\t' || IsNewline(ch);
        }

        static bool IsNotAsciiNorDigit(wchar_t ch) {
            return !IsAsciiAlpha(ch) && !IsDigit(ch);
        }

        static bool IsAsciiAlphaOrDigit(wchar_t ch) {
            return IsAsciiAlpha(ch) || IsDigit(ch);
        }

        static bool IsAlphaNonAscii(wchar_t ch) {
            return !IsAsciiAlpha(ch) && iswalpha(ch);
        }

        static bool IsAlphaOrDigit(wchar_t ch) {
            return iswalpha(ch) || IsDigit(ch);
        }

        static bool IsNotAlphaNorDigit(wchar_t ch) {
            return !iswalpha(ch) && !IsDigit(ch);
        }

        static bool IsDoubleQuotes(wchar_t ch) {
            return ch == L'"';
        }

        static bool IsNotNewline(wchar_t ch) {
            return !IsNewline(ch);
        }

        static bool IsSlash(wchar_t ch) {
            return ch == L'/';
        }

        static bool IsNotSlash(wchar_t ch) {
            return !IsSlash(ch);
        }

        static bool IsAsterisk(wchar_t ch) {
            return ch == L'*';
        }

        static bool IsNotAsterisk(wchar_t ch) {
            return !IsAsterisk(ch);
        }

        static bool IsNotAsteriskNorSlash(wchar_t ch) {
            return IsNotAsterisk(ch) && IsNotSlash(ch);
        }

        static bool Any(wchar_t ch) {
            return true;
        }
    };

}
}