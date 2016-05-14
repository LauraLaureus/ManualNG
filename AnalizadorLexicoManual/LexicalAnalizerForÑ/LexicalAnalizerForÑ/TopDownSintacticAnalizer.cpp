//
//  TopDownSintacticAnalizer.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 14/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "TopDownSintacticAnalizer.hpp"


void TopDownSintacticAnalizer::analice(){
    int token, topStack;
    stack.push(ENDOFSTACK);
    stack.push(ROOT);
    while (topStack != ENDOFSTACK) {
        
        topStack = stack.top();
        token = lang.nextToken();
        
        if(isTerminal(topStack)|| topStack == ENDOFSTACK){
            
            if(topStack == token){
                stack.pop();
                token = lang.nextToken();
            }else{
                printf("ERROR");
            }
        }else{
            if(table(topStack,token).existARule()){
                Rule rule = table.getRule(topStack,token);
                stack.pop();
                for(int i = 0; i < table.rule; i++){
                    stack.push(rule.nextToken());
                }
            }else{
                printf("ERROR");
            }
        }
    }
}