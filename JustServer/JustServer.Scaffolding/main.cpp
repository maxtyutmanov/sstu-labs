#include "EchoDispatcher.h"
#include <NetworkService.h>
#include <memory>
using std::auto_ptr;

int main(int argc, char** argv) {
    auto_ptr<IRequestDispatcher> dispatcher(new EchoDispatcher());
    NetworkService ns(dispatcher, "", 5555);
    
    ns.Start();

    return 0;
}