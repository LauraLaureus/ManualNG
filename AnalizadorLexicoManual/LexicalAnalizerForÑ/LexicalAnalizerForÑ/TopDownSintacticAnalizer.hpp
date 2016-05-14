//
//  TopDownSintacticAnalizer.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 14/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef TopDownSintacticAnalizer_hpp
#define TopDownSintacticAnalizer_hpp

#include <stdio.h>
#include <stack>

#endif /* TopDownSintacticAnalizer_hpp */

using namespace std;

class TopDownSintacticAnalizer{
private:
    stack<int> stack;
    //TODO tabla de estados;
    
    void fullfillAnalysisTable();
public:
    void analice();
};