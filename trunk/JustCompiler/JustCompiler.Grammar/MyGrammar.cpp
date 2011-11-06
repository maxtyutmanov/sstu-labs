#include "MyGrammar.h"
#include "CharacterValidators.h"
#include <ErrorCode.h>
#include <IntConstantTokenCreator.h>
#include <UnrecognizedTokenCreator.h>
#include <StringLiteralTokenCreator.h>
#include <SingleCharTokenCreator.h>
#include <WordTokenCreator.h>

using boost::shared_ptr;

LexerSettings MyGrammar::SetupLexerSettings() {
    LexemesDictionary keywords;

    keywords[L"program"] = TokenTag::Program;
    keywords[L"while"] = TokenTag::While;
    keywords[L"for"] = TokenTag::For;
    keywords[L"array"] = TokenTag::Array;
    keywords[L"begin"] = TokenTag::Begin;
    keywords[L"end"] = TokenTag::End;
    keywords[L"int"] = TokenTag::Type_Int;
    keywords[L"float"] = TokenTag::Type_Float;
    keywords[L"string"] = TokenTag::Type_String;

    LexemesDictionary standardFunctions;

    standardFunctions[L"sqrt"] = TokenTag::Sqrt;
    standardFunctions[L"log"] = TokenTag::Log;
    standardFunctions[L"ln"] = TokenTag::Ln;
    standardFunctions[L"nearby"] = TokenTag::Nearby;

    OneCharLexemesDictionary oneCharacterTokens;

    oneCharacterTokens[L'+'] = TokenTag::Plus;
    oneCharacterTokens[L'-'] = TokenTag::Minus;
    oneCharacterTokens[L'*'] = TokenTag::Asterisk;
    oneCharacterTokens[L':'] = TokenTag::Colon;
    oneCharacterTokens[L'_'] = TokenTag::Underscore;
    oneCharacterTokens[L'/'] = TokenTag::Slash;
    oneCharacterTokens[L'('] = TokenTag::OpeningRoundBracket;
    oneCharacterTokens[L')'] = TokenTag::ClosingRoundBracket;
    oneCharacterTokens[L'{'] = TokenTag::OpeningBrace;
    oneCharacterTokens[L'}'] = TokenTag::ClosingBrace;
    oneCharacterTokens[L'='] = TokenTag::Equals;
    oneCharacterTokens[L'<'] = TokenTag::LessThan;
    oneCharacterTokens[L'>'] = TokenTag::GreaterThan;
    oneCharacterTokens[L'['] = TokenTag::OpeningSquareBracket;
    oneCharacterTokens[L']'] = TokenTag::ClosingSquareBracket;
    oneCharacterTokens[L';'] = TokenTag::Semicolon;
    oneCharacterTokens[L'\''] = TokenTag::SingleQuotes;
    oneCharacterTokens[L','] = TokenTag::Comma;

    return LexerSettings(keywords, standardFunctions, oneCharacterTokens);
}

bool MyGrammar::ValidateCharsetInIdentifier(wchar_t ch) {
    return iswascii(ch);
}

auto_ptr<Lexer> MyGrammar::CreateLexer(const LexerSettings& settings, wistream& input) {
    shared_ptr<IntConstantTokenCreator> intConstantTokenCreator(new IntConstantTokenCreator());
    shared_ptr<UnrecognizedTokenCreator> unrecognizedTokenCreator(new UnrecognizedTokenCreator());
    shared_ptr<StringLiteralTokenCreator> stringLiteralTokenCreator(new StringLiteralTokenCreator());
    shared_ptr<SingleCharTokenCreator> singleCharTokenCreator(new SingleCharTokenCreator(settings));
    shared_ptr<WordTokenCreator> wordTokenCreator(new WordTokenCreator(settings, &MyGrammar::ValidateCharsetInIdentifier));

    //states

    shared_ptr<FaState> init(new FaState(L"Initial"));
    shared_ptr<FaState> insideNumber(new FaState(L"Inside integer constant"));
    shared_ptr<FaState> idStartingWithDigit(new FaState(L"Wrong identifier (starts with digit)"));
    shared_ptr<FaState> insideWord(new FaState(L"Inside word (keyword, standard function or identifier)"));
    shared_ptr<FaState> insideStringLiteral(new FaState(L"Inside a string literal"));
    shared_ptr<FaState> justReadSlash(new FaState(L"Just read the slash character"));
    shared_ptr<FaState> insideComment(new FaState(L"Inside comment"));
    shared_ptr<FaState> justReadAsteriskInComment(new FaState(L"Just read asterisk inside a comment"));

    auto_ptr<Lexer> pLexer(new Lexer(settings, init, input));

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