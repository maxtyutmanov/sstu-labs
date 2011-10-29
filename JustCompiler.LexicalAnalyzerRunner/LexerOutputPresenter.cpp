#include "LexerOutputPresenter.h"

TokenTablesContainer LexerOutputPresenter::WriteDescriptorText(vector<Token *> tokens, wostream& output) {
    TokenTable keywords;
    TokenTable standardFunctions;
    TokenTable separators;
    TokenTable constants;
    TokenTable identifiers;

    for (int i = 0; i < tokens.size(); ++i) {
        switch (tokens[i]->GetTag()) {
            case TokenTag::Program:
            case TokenTag::While:
            case TokenTag::For:
            case TokenTag::Array:
            case TokenTag::Begin:
            case TokenTag::End:
            case TokenTag::Type_Int:
            case TokenTag::Type_Float: 
            case TokenTag::Type_String: {
                int tokenId = keywords.Search(tokens[i]);

                output << L"<K1, " << tokenId << L"> ";
                break;
            }
            case TokenTag::Sqrt:
            case TokenTag::Log:
            case TokenTag::Ln:
            case TokenTag::Nearby: {
                int tokenId = standardFunctions.Search(tokens[i]);

                output << "<K2, " << tokenId << L"> ";
                break;
            }
            case TokenTag::Plus:
            case TokenTag::Minus:
            case TokenTag::Asterisk:
            case TokenTag::Colon:
            case TokenTag::Underscore:
            case TokenTag::Slash:
            case TokenTag::OpeningRoundBracket:
            case TokenTag::ClosingRoundBracket:
            case TokenTag::OpeningBrace:
            case TokenTag::ClosingBrace:
            case TokenTag::Equals:
            case TokenTag::LessThan:
            case TokenTag::GreaterThan:
            case TokenTag::OpeningSquareBracket:
            case TokenTag::ClosingSquareBracket:
            case TokenTag::Semicolon:
            case TokenTag::Quotes:
            case TokenTag::SingleQuotes:
            case TokenTag::Comma: {
                int tokenId = separators.Search(tokens[i]);

                output << L"<K3, " << tokenId << L"> ";
                break;
            }
            case TokenTag::IntConstant:
            case TokenTag::StringLiteral: {
                int tokenId = constants.Search(tokens[i]);

                output << L"<K4, " << tokenId << L"> ";
                break;
            }
            case TokenTag::Identifier: {
                int tokenId = identifiers.Search(tokens[i]);

                output << L"<K5, " << tokenId << L"> ";
                break;
            }
            case TokenTag::Newline:
                if (i == 0 || tokens[i - 1]->GetTag() != TokenTag::Newline) {
                    output << endl;
                }
                break;
            case TokenTag::Unrecognized:
                output << L"<???> ";
                break;
        }
    }

    TokenTablesContainer tablesContainer;
    tablesContainer.constants = constants;
    tablesContainer.identifiers = identifiers;
    tablesContainer.keywords = keywords;
    tablesContainer.separators = separators;
    tablesContainer.standardFunctions = standardFunctions;

    return tablesContainer;
}