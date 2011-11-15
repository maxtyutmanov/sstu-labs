#include "HttpRequestGrammar.h"
#include "CharacterValidators.h"
#include "HttpVerbTokenCreator.h"
#include "UriTokenCreator.h"
#include "HeaderTokenCreator.h"
#include "HttpTextTokenCreator.h"
#include "TokenTag.h"

namespace JustServer {
namespace HttpGrammar {

    auto_ptr<Lexer> HttpRequestGrammar::CreateLexer() {
        #pragma region token creators

        shared_ptr<HttpTextTokenCreator> httpVerbTokenCreator(new HttpTextTokenCreator(TokenTag::HttpVerb));
        shared_ptr<UriTokenCreator> uriTokenCreator(new UriTokenCreator());
        shared_ptr<HttpTextTokenCreator> httpVersionTokenCreator(new HttpTextTokenCreator(TokenTag::HttpVersion));
        shared_ptr<HeaderTokenCreator> headerTokenCreator(new HeaderTokenCreator());
        shared_ptr<HttpTextTokenCreator> requestBodyTokenCreator(new HttpTextTokenCreator(TokenTag::Body));
        

        #pragma endregion

        #pragma region finite automaton states
        
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
        shared_ptr<FaState> beforeBody(new FaState("Before HTTP request body"));
        shared_ptr<FaState> insideBody(new FaState("Inside the body of HTTP request"));
        shared_ptr<FaState> insideHeader(new FaState("Inside header"));

        #pragma endregion

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
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

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

        pLexer->AddTransition(FaTransition(
            insideVersion, insideVersion,
            &CharacterValidators::IsValidVersionChar,
            ReadAction::RemoveFromBuffer_AddToLexeme));
            
        pLexer->AddTransition(FaTransition(
            insideVersion, waitingForCR,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore,
            httpVersionTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideVersion, waitingForLF,
            &CharacterValidators::IsCR,
            ReadAction::RemoveFromBuffer_Ignore,
            httpVersionTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideVersion, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "waiting for CR"

        pLexer->AddTransition(FaTransition(
            waitingForCR, waitingForCR,
            &CharacterValidators::IsLWS,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForCR, waitingForLF,
            &CharacterValidators::IsCR,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForCR, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "waitingForLF"

        pLexer->AddTransition(FaTransition(
            waitingForLF, justReadLF,
            &CharacterValidators::IsLF,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForLF, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "just read LF"

        pLexer->AddTransition(FaTransition(
            justReadLF, waitingForSecondLF,
            &CharacterValidators::IsCR,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            justReadLF, insideHeader,
            &CharacterValidators::IsValidHeaderChar,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            justReadLF, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "waiting for second LF"

        pLexer->AddTransition(FaTransition(
            waitingForSecondLF, beforeBody,
            &CharacterValidators::IsLF,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            waitingForSecondLF, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "inside header"

        pLexer->AddTransition(FaTransition(
            insideHeader, insideHeader,
            &CharacterValidators::IsValidHeaderChar,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        pLexer->AddTransition(FaTransition(
            insideHeader, waitingForLF,
            &CharacterValidators::IsCR,
            ReadAction::RemoveFromBuffer_Ignore,
            headerTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideHeader, inError,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_Ignore,
            -1));

        #pragma endregion

        #pragma region transitions from "before body"

        //TODO: why are we waiting for the verb???

        pLexer->AddTransition(FaTransition(
            beforeBody, waitingForVerb,
            &CharacterValidators::IsEof,
            ReadAction::RemoveFromBuffer_Ignore));

        pLexer->AddTransition(FaTransition(
            beforeBody, insideBody,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        #pragma endregion

        #pragma region transitions from "inside body"

        //TODO: why are we waiting for the verb???

        #pragma warning "IsEof is not reliable enough, because there may be \0 character in request body's contents!"

        pLexer->AddTransition(FaTransition(
            insideBody, waitingForVerb,
            &CharacterValidators::IsEof,
            ReadAction::RemoveFromBuffer_Ignore,
            requestBodyTokenCreator));

        pLexer->AddTransition(FaTransition(
            insideBody, insideBody,
            &CharacterValidators::Any,
            ReadAction::RemoveFromBuffer_AddToLexeme));

        #pragma endregion

        return pLexer;
    }

}
}