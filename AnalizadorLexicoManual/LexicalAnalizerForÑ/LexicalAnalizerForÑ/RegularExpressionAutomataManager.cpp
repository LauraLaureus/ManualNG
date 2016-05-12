//
//  RegularExpressionAutomataManager.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 11/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "RegularExpressionAutomataManager.hpp"

RegularExpressionAutomataManager::RegularExpressionAutomataManager(){
    this->id = *new RegularExpressionAutomataIdentificador();
}

int RegularExpressionAutomataManager::anyRegularExpresionInRightOrPartialState(std::string chain,bool write){
    /*
     TODO: 
        lanzar todos los automatas y desde que uno de 0 o 1 devolver true en otro caso devolver false.
     */
    int n;
    
    
    n = id.check(chain,write);
    if(n  > -1){
        lastActive = 1;
        return n;
    }
    
    return -1;
}

int RegularExpressionAutomataManager::getLastIndexFromLastActive(){

    switch (lastActive) {
        case 1:
            return id.getLastIndex();
            break;
    }
    
    return 0;
}


///////////////////ID_ Automata

int RegularExpressionAutomataIdentificador::initialState(std::string chain,bool write){

    if (std::isalpha(chain[0])) {
        return State1(chain,1,write);
    }
    return -1;
}

int RegularExpressionAutomataIdentificador::State1(std::string chain,int index,bool write){
    
    //Continue processing chain
    if (std::isalnum(chain[index])) {
        if(chain.size()-1 == index && write){
            this->identifier = chain;
            return 0;
        }
        else if (chain.size()-1 == index) return 1;
        return State1(chain,index+1,write);
    }
    else if(index < chain.size()){
        this->identifier = chain;
        this->lastIndex = index;
        return 2;
    }
    
    return -1;
    
}


std::string RegularExpressionAutomataIdentificador::getIdentifier(){
    if (lastIndex != 0) {
        std::string id (this->identifier.begin(),this->identifier.begin()+lastIndex);
        return id;
    }
    return this->identifier;
}

int RegularExpressionAutomataIdentificador::getLastIndex(){
    return this->lastIndex;
}