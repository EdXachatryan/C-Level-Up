#ifndef HANDLERS_H
#define HANDLERS_H

inline void handler1(std::string msg)
{
    utilities::syncPrint("Handler h1 =  " + msg);
}

inline void handler2(std::string msg)
{
    utilities::syncPrint("Handler h2 = " + msg);
}

#endif