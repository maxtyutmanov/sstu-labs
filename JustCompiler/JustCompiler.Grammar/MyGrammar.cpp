#include "MyGrammar.h"
#include "CharacterValidators.h"
#include "ErrorCode.h"
#include "IntConstantTokenCreator.h"
#include "UnrecognizedTokenCreator.h"
#include "StringLiteralTokenCreator.h"
#include "SingleCharTokenCreator.h"
#include "WordTokenCreator.h"
#include "TokenTag.h"

using boost::shared_ptr;
using namespace JustCompiler::LexicalAnalyzer::TokenCreators;

namespace JustCompiler {
namespace LexicalAnalyzer {

    boost::shared_ptr<LexemeToTagMapping> MyGrammar::GetKeywordsMapping() {
        boost::shared_ptr<LexemeToTagMapping> kwMapping(new LexemeToTagMapping());

        kwMapping->AddPair(L"program", TokenTag::Program);
        kwMapping->AddPair(L"while", TokenTag::While);
        kwMapping->AddPair(L"for", TokenTag::For);
        kwMapping->AddPair(L"array", TokenTag::Array);
        kwMapping->AddPair(L"begin", TokenTag::Begin);
        kwMapping->AddPair(L"end", TokenTag::End);
        kwMapping->AddPair(L"int", TokenTag::Type_Int);
        kwMapping->AddPair(L"string", TokenTag::Type_String);

        return kwMapping;
    }

    boost::shared_ptr<LexemeToTagMapping> MyGrammar::GetStandardFuncMapping() {
        boost::shared_ptr<LexemeToTagMapping> sfMapping(new LexemeToTagMapping());

        sfMapping->AddPair(L"sqrt", TokenTag::Sqrt);
        sfMapping->AddPair(L"log", TokenTag::Log);
        sfMapping->AddPair(L"ln", TokenTag::Ln);
        sfMapping->AddPair(L"nearby", TokenTag::Nearby);

        return sfMapping;
    }

    boost::shared_ptr<LexemeToTagMapping> MyGrammar::GetSingleCharTokensMapping() {
        boost::shared_ptr<LexemeToTagMapping> sctMapping(new LexemeToTagMapping());

        sctMapping->AddPair(L"+", TokenTag::Plus);
        sctMapping->AddPair(L"-", TokenTag::Minus);
        sctMapping->AddPair(L"*", TokenTag::Asterisk);
        sctMapping->AddPair(L":", TokenTag::Colon);
        sctMapping->AddPair(L"_", TokenTag::Underscore);
        sctMapping->AddPair(L"/", TokenTag::Slash);
        sctMapping->AddPair(L"(", TokenTag::OpeningRoundBracket);
        sctMapping->AddPair(L")", TokenTag::ClosingRoundBracket);
        sctMapping->AddPair(L"{", TokenTag::OpeningBrace);
        sctMapping->AddPair(L"}", TokenTag::ClosingBrace);
        sctMapping->AddPair(L"=", TokenTag::Equals);
        sctMapping->AddPair(L"<", TokenTag::LessThan);
        sctMapping->AddPair(L">", TokenTag::GreaterThan);
        sctMapping->AddPair(L"[", TokenTag::OpeningSquareBracket);
        sctMapping->AddPair(L"]", TokenTag::ClosingSquareBracket);
        sctMapping->AddPair(L";", TokenTag::Semicolon);
        sctMapping->AddPair(L"\'", TokenTag::SingleQuotes);
        sctMapping->AddPair(L",", TokenTag::Comma);

        return sctMapping;
    }

    bool MyGrammar::ValidateCharsetInIdentifier(wchar_t ch) {
        return iswascii(ch);
    }

    auto_ptr<Lexer> MyGrammar::CreateLexer() {
        shared_ptr<IntConstantTokenCreator> intConstantTokenCreator(new IntConstantTokenCreator());
        shared_ptr<UnrecognizedTokenCreator> unrecognizedTokenCreator(new UnrecognizedTokenCreator());
        shared_ptr<StringLiteralTokenCreator> stringLiteralTokenCreator(new StringLiteralTokenCreator());
        shared_ptr<SingleCharTokenCreator> singleCharTokenCreator(new SingleCharTokenCreator(GetSingleCharTokensMapping()));
        shared_ptr<WordTokenCreator> wordTokenCreator(new WordTokenCreator(
            GetKeywordsMapping(), 
            GetStandardFuncMapping(), 
            &MyGrammar::ValidateCharsetInIdentifier, 
            14));

        //states

        shared_ptr<FaState> init(new FaState(L"Initial"));
        shared_ptr<FaState> insideNumber(new FaState(L"Inside integer constant"));
        shared_ptr<FaState> idStartingWithDigit(new FaState(L"Wrong identifier (starts with digit)"));
        shared_ptr<FaState> insideWord(new FaState(L"Inside word (keyword, standard function or identifier)"));
        shared_ptr<FaState> insideStringLiteral(new FaState(L"Inside a string literal"));
        shared_ptr<FaState> justReadSlash(new FaState(L"Just read the slash character"));
        shared_ptr<FaState> insideComment(new FaState(L"Inside comment"));
        shared_ptr<FaState> justReadAsteriskInComment(new FaState(L"Just read asterisk inside a comment"));

        auto_ptr<Lexer> pLexer(new Lexer(init));

        #pragma region transitions from "init"

        pLexer->AddTransition(FaTransition(
            init, init, 
            &CharacterValidators::IsSpaceTabOrNewline, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            init, insideNumber, 
            &CharacterValidators::IsDigit, 
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            init, insideWord, 
            &CharacterValidators::IsAlpha, 
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            init, insideStringLiteral, 
            &CharacterValidators::IsDoubleQuotes, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            init, justReadSlash, 
            &CharacterValidators::IsSlash, 
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            init, init,
            &CharacterValidators::IsEof,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            init, init,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_AddToLexeme,
            singleCharTokenCreator));

        #pragma endregion

        #pragma region transitions from "inside word"

        pLexer->AddTransition(FaTransition(
            insideWord, insideWord, 
            &CharacterValidators::IsAlphaOrDigit, 
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            insideWord, init, 
            &CharacterValidators::Any, 
            ReadAction::KeepInBuffer_Ignore,
            wordTokenCreator));

        #pragma endregion

        #pragma region transitions from "inside number"

        pLexer->AddTransition(FaTransition(
            insideNumber, insideNumber,
            &CharacterValidators::IsDigit,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            insideNumber, idStartingWithDigit, 
            &CharacterValidators::IsAlpha, 
            ReadAction::RemoveFromBuffer_ClearLexeme, //throwing away what we've read so far
            ErrorCode::IdStartingWithDigit));

        pLexer->AddTransition(FaTransition(
            insideNumber, init, 
            &CharacterValidators::Any, 
            ReadAction::KeepInBuffer_Ignore, 
            intConstantTokenCreator));

        #pragma endregion

        #pragma region transitions from "id starting with digit"

        pLexer->AddTransition(FaTransition(
            idStartingWithDigit, idStartingWithDigit, 
            &CharacterValidators::IsAlphaOrDigit, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            idStartingWithDigit, init, 
            &CharacterValidators::Any, 
            ReadAction::KeepInBuffer_Ignore));

        #pragma endregion

        #pragma region transitions from "inside string literal"

        pLexer->AddTransition(FaTransition(
            insideStringLiteral, init, 
            &CharacterValidators::IsNewlineOrEof, 
            ReadAction::RemoveFromBuffer_ClearLexeme, 
            ErrorCode::UnterminatedStringLiteral));

        pLexer->AddTransition(FaTransition(
            insideStringLiteral, init, 
            &CharacterValidators::IsDoubleQuotes, 
            ReadAction::RemoveFromBuffer_Ignore, 
            stringLiteralTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideStringLiteral, insideStringLiteral, 
            &CharacterValidators::Any, 
            ReadAction::RemoveFromBuffer_AddToLexeme));

        #pragma endregion

        #pragma region transitions from "just read slash"

        //yep, it's a comment
        pLexer->AddTransition(FaTransition(
            justReadSlash, insideComment, 
            &CharacterValidators::IsAsterisk, 
            ReadAction::RemoveFromBuffer_ClearLexeme)); //HACK: clear lexeme - this is the bad idea

        //it turned out to be just a slash, not a comment
        pLexer->AddTransition(FaTransition(
            justReadSlash, init, 
            &CharacterValidators::Any,
            ReadAction::KeepInBuffer_Ignore, 
            singleCharTokenCreator));
    
        #pragma endregion

        #pragma region transitions from "inside comment"

        pLexer->AddTransition(FaTransition(
            insideComment, justReadAsteriskInComment, 
            &CharacterValidators::IsAsterisk, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            insideComment, init, 
            &CharacterValidators::IsEof, 
            ReadAction::RemoveFromBuffer_Ignore, 
            ErrorCode::UnterminatedComment));

        pLexer->AddTransition(FaTransition(
            insideComment, insideComment, 
            &CharacterValidators::Any, 
            ReadAction::RemoveFromBuffer_Ignore));

        #pragma endregion

        #pragma region transitions from "just read asterisk in comment"
    
        pLexer->AddTransition(FaTransition(
            justReadAsteriskInComment, init, 
            &CharacterValidators::IsSlash, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            justReadAsteriskInComment, init, 
            &CharacterValidators::IsEof, 
            ReadAction::RemoveFromBuffer_Ignore, 
            ErrorCode::UnterminatedComment));

        pLexer->AddTransition(FaTransition(
            justReadAsteriskInComment, justReadAsteriskInComment, 
            &CharacterValidators::IsAsterisk, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            justReadAsteriskInComment, insideComment, 
            &CharacterValidators::Any, 
            ReadAction::RemoveFromBuffer_Ignore));
    
        #pragma endregion

        return pLexer;
    }

}
}