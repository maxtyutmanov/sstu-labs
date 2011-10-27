#include "EchoDispatcher.h"
#include <NetworkService.h>
#include <iostream>
#include <locale>
using std::cin;
using std::cout;
using std::auto_ptr;


int main(int argc, char** argv) {
    cout.imbue(std::locale("rus_rus.866"));

    std::auto_ptr<IRequestDispatcher> dispatcher(new EchoDispatcher());
    NetworkService ns(dispatcher, "", 5555);
    
    ns.Start();

    cin.get();

    ns.Stop();

    return 0;
}