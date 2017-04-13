#include <iostream>
#include <csdbg/csdbg.hpp>
#include "hello.h"

using namespace std;
using namespace csdbg;

int foo()
{
    throw csdbg::exception("o pateras einai anthropos");
}

int main(int argc, char **argv)
{
    util::init(argc, argv);
    cout << "hello, o pateras den einai spiti\n";
    
    tracer *iface = tracer::interface();
    if ( unlikely(iface == NULL) )
        ; // abort
    try {
        foo();   
    } catch (csdbg::exception &x) {
        cout << x << "\r\n" << *iface << "\r\n";
    }
    iface->unwind();
    
}
