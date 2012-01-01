#include "Utils.h"

namespace JustCompilerLexicalAnalyzerRunner {

    using namespace std;
    using namespace System;
    using namespace System::Runtime::InteropServices;

    void StringToStlWString ( System::String const^ s, std::wstring& os) {
        String^ string = const_cast<String^>(s);
        const wchar_t* chars = reinterpret_cast<const wchar_t*>((Marshal::StringToHGlobalUni(string)).ToPointer());
        os = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }

    System::String^ StlWStringToString (std::wstring const& os) {
        String^ str = gcnew String(os.c_str());
        return str;
    }

}