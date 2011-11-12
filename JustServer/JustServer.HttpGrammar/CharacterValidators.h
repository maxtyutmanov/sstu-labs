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

        static bool IsAlpha(char ch) {
            return isalpha(ch);
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