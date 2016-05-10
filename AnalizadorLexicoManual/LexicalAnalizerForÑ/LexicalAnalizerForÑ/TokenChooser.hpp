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
#include <deque>


class TokenChooser {
    Writer * w;
    std::deque<char> queue;
    bool regularExpressionInProcess;
    
private:
    void decide();
    bool isCurrentWhiteSpace();
    bool isCurrentPartOfKeyword();
    bool checkFirstOrderKeyWords();
    int completeKeyword();
    
public:
    TokenChooser();
    void accept(char c);
    
};