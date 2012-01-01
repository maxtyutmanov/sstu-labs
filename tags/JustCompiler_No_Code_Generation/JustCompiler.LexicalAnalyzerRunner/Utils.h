#pragma once
 
#include <string>

namespace JustCompilerLexicalAnalyzerRunner {

    void StringToStlWString ( System::String const^ s, std::wstring& os);
    System::String^ StlWStringToString (std::wstring const& os);
}