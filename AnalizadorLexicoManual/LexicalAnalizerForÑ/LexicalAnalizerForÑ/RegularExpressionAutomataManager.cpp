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

bool RegularExpressionAutomataManager::anyRegularExpresionInRightOrPartialState(std::string chain){
    /*
     TODO: 
        lanzar todos los automatas y desde que uno de 0 o 1 devolver true en otro caso devolver false.
     */
    if(id.check(chain)) return true;
    return false;
}

int RegularExpressionAutomataIdentificador::initialState(std::string chain,bool write){

    if (std::isalpha(chain[0])) {
        return State1(chain,1,write);
    }
    return -1;
}

int RegularExpressionAutomataIdentificador::State1(std::string chain,int index,bool write){
    
    
    if (std::isalnum(chain[0])) {
        if(chain.size()-1 == index) return 1;
        return State1(chain,index+1,write);
    }
    return -1;
    
}
