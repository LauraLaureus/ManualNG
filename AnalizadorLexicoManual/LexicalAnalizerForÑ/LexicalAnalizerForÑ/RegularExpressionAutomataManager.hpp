//
//  RegularExpressionAutomataManager.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 11/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//
#pragma once
#include <string>

class RegularExpressionAutomataManager{

    /*For Automatas*/
    
public:
    
    bool anyRegularExpresionInRightOrPartialState(std::string);
    void write(std::string);
};

class RegularExpressionAutomata{
public:
    virtual int check(std::string str) = 0;
};


class RegularExpressionAutomataIdentificador : public RegularExpressionAutomata{

private:
    int initialState(std::string chain,bool write);
    
    
public:
    int check(std::string str){
        return initialState(str,false);
    };
};