//
//  TokenChooser.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#pragma once
#include "Writer.hpp"
#include "tokenDef.h"
#include "RegularExpressionAutomataManager.hpp"
#include <deque>
#include <map>

using namespace std;

class TokenChooser {
    Writer * w;
    std::deque<char> queue;
    map<std::string, int> keywords;
    RegularExpressionAutomataManager mng;
    //bool regularExpressionInProcess;
    
private:
    void decide();
    bool isCurrentFromIgnoreSet();
    void buildMap();
    void cleanBufferFromPrefixNumericKeywords();
    
public:
    TokenChooser();
    void accept(char c);
    
};