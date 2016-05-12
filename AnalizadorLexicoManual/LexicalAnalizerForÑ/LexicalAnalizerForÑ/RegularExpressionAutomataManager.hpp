//
//  RegularExpressionAutomataManager.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 11/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//
#pragma once
#include <string>



class RegularExpressionAutomata{
public:
    virtual int check(std::string str,bool write) = 0;
};


class RegularExpressionAutomataIdentificador : public RegularExpressionAutomata{
    
private:
    int initialState(std::string chain,bool write);
    int State1(std::string chain,int index,bool write);
    std::string identifier;
    int lastIndex = 0;
    
public:
    int check(std::string str,bool write){
        return initialState(str,false);
    };
    
    std::string getIdentifier();
    int getLastIndex();
};




class RegularExpressionAutomataManager{

    int lastActive;
    RegularExpressionAutomataIdentificador id;
    /*For Automatas*/
    
public:
    RegularExpressionAutomataManager();
    int anyRegularExpresionInRightOrPartialState(std::string,bool);
    int getLastIndexFromLastActive();
};