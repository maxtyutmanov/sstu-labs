#include "TokenTable.h"
#include <Identifier.h>
#include <IntConstant.h>
#include <StringLiteral.h>
#include <boost/lexical_cast.hpp>
#include <iomanip>

int TokenTable::Search(Token *t) {
    for (int i = 0; i < tokens.size(); ++i) {
        if (*t == *tokens[i]) {
            return i;
        }
    }

    tokens.push_back(t);

    return tokens.size() - 1;
}

void TokenTable::WriteToStream(const LexerSettings& lexerSettings, wostream& output) {
    for (int i = 0; i < tokens.size(); ++i) {
        wstring rightCell;

        switch (tokens[i]->GetTag()) {
        case TokenTag::Identifier:
            rightCell = ((Identifier *)tokens[i])->GetName();
            break;
        case TokenTag::IntConstant:
            rightCell = boost::lexical_cast<wstring, int>(((IntConstant *)tokens[i])->GetValue());
            break;
        case TokenTag::StringLiteral:
            rightCell = ((StringLiteral *)tokens[i])->GetText();
            break;
        case TokenTag::Space:
            rightCell = L"пробел";
            break;
        default:
            wstring lexeme;
            wchar_t singleCharLexeme;

            if (lexerSettings.GetKeyword(tokens[i]->GetTag(), &lexeme)) {
                rightCell = lexeme;
            }
            else if (lexerSettings.GetStandardFunction(tokens[i]->GetTag(), &lexeme)) {
                rightCell = lexeme;
            }
            else if (lexerSettings.GetSingleCharLexeme(tokens[i]->GetTag(), &singleCharLexeme)) {
                rightCell.push_back(singleCharLexeme);
            }
            else {
                rightCell = L"???";
            }
        }
        

        output << setw(5) << left << i << L"|  " << rightCell << endl;
    }
}