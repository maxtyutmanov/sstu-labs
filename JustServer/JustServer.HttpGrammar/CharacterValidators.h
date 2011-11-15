#ifndef CHARACTER_VALIDATORS_H
#define CHARACTER_VALIDATORS_H

namespace JustServer {
namespace HttpGrammar {

    class CharacterValidators {
    public:
        //LWS - linear white space
        static bool IsLWS(char ch) {
            return ch == ' ' || ch == '\t';
        }

        static bool IsCR(char ch) {
            return ch == '\r';
        }

        static bool IsLF(char ch) {
            return ch == '\n';
        }

        static bool IsAlpha(char ch) {
            return isalpha(ch);
        }

        static bool IsCTL(char ch) {
            //127 - delete
            return ch < 32 || ch == 127;
        }

        static bool IsEof(char ch) {
            return ch == '\0';
        }

        static bool IsValidHeaderChar(char ch) {
            //any OCTET except CTLs but including LWS
            return !IsCTL(ch) || IsLWS(ch);
        }

        static bool Any(char ch) {
            return true;
        }

        static bool IsValidUriChar(char ch) {
            //TODO: strict check
            return isascii(ch) && !IsLWS(ch);
        }

        static bool IsH(char ch) {
            return ch == 'H';
        }

        static bool IsValidVersionChar(char ch) {
            return ch == 'H' || 
                ch == 'T' || 
                ch == 'P' || 
                ch == '/' || 
                ch == '.' || 
                isdigit(ch);
        }
    };

}
}

#endif