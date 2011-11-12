#include "HttpRequestGrammar.h"
#include "CharacterValidators.h"
#include "HttpVerbTokenCreator.h"
#include "UriTokenCreator.h"

namespace JustServer {
namespace HttpGrammar {

    auto_ptr<Lexer> HttpRequestGrammar::CreateLexer() {
        vector<string> allowedHttpVerbs;
        allowedHttpVerbs.push_back("GET");

        //token creators

        shared_ptr<HttpVerbTokenCreator> httpVerbTokenCreator(new HttpVerbTokenCreator(allowedHttpVerbs));
        shared_ptr<UriTokenCreator> uriTokenCreator(new UriTokenCreator());

        //states
        
        shared_ptr<FaState> inError(new FaState("Error encountered"));
        shared_ptr<FaState> waitingForVerb(new FaState("Waiting for HTTP verb"));
        shared_ptr<FaState> insideVerb(new FaState("Inside HTTP verb"));
        shared_ptr<FaState> waitingForUrl(new FaState("Waiting for URL"));
        shared_ptr<FaState> insideUrl(new FaState("Inside URL"));
        shared_ptr<FaState> waitingForVersion(new FaState("Waiting for HTTP version"));
        shared_ptr<FaState> insideVersion(new FaState("Reading HTTP version"));
        shared_ptr<FaState> waitingForCR(new FaState("Waiting for carriage return"));
        shared_ptr<FaState> waitingForLF(new FaState("Waiting for line feed"));
        shared_ptr<FaState> justReadLF(new FaState("Just read line feed"));
        shared_ptr<FaState> waitingForSecondLF(new FaState("Waiting for the second newline in succession"));

        //TODO: implement grammar definition for HTTP request message
        auto_ptr<Lexer> pLexer(new Lexer(waitingForVerb));

        //skipping the rest of the message if we've encountered an error in it
        pLexer->AddTransition(FaTransition(
            inError, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore));

        #pragma region transitions from "waiting for verb"

        pLexer->AddTransition(FaTransition(
            waitingForVerb, waitingForVerb, 
            &CharacterValidators::IsLWS, 
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForVerb, insideVerb,
            &CharacterValidators::IsAlpha,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            waitingForVerb, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));   //we don't distinguish different types of errors. -1 means "ERROR". That's all.

        #pragma endregion

        #pragma region transitions from "inside verb"

        pLexer->AddTransition(FaTransition(
            insideVerb, insideVerb,
            &CharacterValidators::IsAlpha,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            insideVerb, waitingForUrl,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore,
            httpVerbTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideVerb, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "waiting for url"

        pLexer->AddTransition(FaTransition(
            waitingForUrl, waitingForUrl,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForUrl, insideUrl,
            &CharacterValidators::IsValidUriChar,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            waitingForUrl, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore));

        #pragma endregion

        #pragma region transitions from "inside URL"

        pLexer->AddTransition(FaTransition(
            insideUrl, insideUrl,
            &CharacterValidators::IsValidUriChar,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            insideUrl, waitingForVersion,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore,
            uriTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideUrl, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "waiting for version"

        pLexer->AddTransition(FaTransition(
            waitingForVersion, waitingForVersion,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForVersion, insideVersion,
            &CharacterValidators::IsH,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            waitingForVersion, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "inside version"



        #pragma endregion

        return pLexer;
    }

}
}