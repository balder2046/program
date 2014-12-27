#include <iostream>
#include <stdio.h>
#include <clang-c/Index.h>
int main()
{
    CXIndex index = clang_creatIndex(0,0);
    const char *args[] = {"."};
    int argNum = sizeof(args) / sizeof(*args);
    CXTranslationUnit tu = clang_parseTranslationUnit(index,"source.cpp",args,argNum,0,0,CXTranslation_None);
    unsigned int count = clang_getNumDiagnostics(tu);
    for (unsigned int i = 0; i < count; ++i)
    {
        CXDiagnostic diag = clang_getDiagnostic(i);
        
    }
    return 0;
}
