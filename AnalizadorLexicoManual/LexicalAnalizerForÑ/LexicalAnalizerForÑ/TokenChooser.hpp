//
//  TokenChooser.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#pragma once //Definirlo todo en la cabecera por el template
#include "Scanner.hpp"
#include "tokenDef.h"
#include "RegularExpressionAutomataManager.hpp"
#include <deque>
#include <map>

using namespace std;


template <class D> class Symbol{
   
public:
    
    int token;
    D value;
    
    Symbol(int t, D v){
        this->token = t;
        this->value = v;
    }
};

/*--------------------------------->TOKENCHOSER<------------------------------*/
template <class D> class TokenChooser {
    std::deque<char> queue;
    std::deque<Symbol<D>> output;
    map<std::string, int> keywords;
    RegularExpressionAutomataManager mng;
    bool regularExpressionInProcess;
    Scanner* s;

    
public:
    TokenChooser(std::string path){
        this->keywords = *new map<std::string, int>();
        buildMap();
        this->mng = *new RegularExpressionAutomataManager();
        this->regularExpressionInProcess = false;
        this->s = new Scanner(path.c_str());
        this->output = *new std::deque<Symbol<D>>();
    }
    
    void accept(char c){
        this->queue.push_back(c);
        decide();
    }
    
    Symbol<D> nextToken(){
        while (output.size() == 0 && (*s).hasNext()){
            char c = (*s).nextChar();
            accept(c);
        }
        return output[0];
    };
    
private:
    void decide(){
        
        bool endOfToken = false;
        if (isCurrentFromIgnoreSet() && !regularExpressionInProcess){
            this->queue.pop_back();
            endOfToken = true;
        }
        
        string str_queue(this->queue.begin(),this->queue.end());
        
        //si el contenido coincide, completamente con una palabra clave escribela.
        if(this->keywords.count(str_queue) != 0){
            output.push_back(*new Symbol<int>(keywords[str_queue]),keywords[str_queue]);
            this->queue.clear();
            return;
        }
        
        //sino
        else if (str_queue.size() >=2){
            int n = this->mng.anyRegularExpresionInRightOrPartialState(str_queue,endOfToken);
            if ( n  < 0)
                cleanBufferFromPrefixNumericKeywords();
            else if (n == 0){
                this->queue.clear();
            }
            else if (n == 1){
                regularExpressionInProcess = true;
            }
            else if (n == 2){
                int index = this->mng.getLastIndexFromLastActive();
                //Escribe identificador
                output.push_back(*new Symbol<std::string>(keywords[IDENTIFICADOR],str_queue));
                this->queue.erase(this->queue.begin(), this->queue.begin()+index);
                regularExpressionInProcess = false;
            }
            else if (n == 3){
                int index = this->mng.getLastIndexFromLastActive();
                output.push_back(*new Symbol<std::string>(keywords[CADENA],str_queue));
                this->queue.erase(this->queue.begin(), this->queue.begin()+index);
                regularExpressionInProcess = false;
            }
        }
 
    };
    
    
    
    bool isCurrentFromIgnoreSet(){
        return queue.back() == ' ' || queue.back() == '\t' || queue.back() == '\n' || queue.back() == '\b' ;

    };
    
    
    
    void buildMap(){
        
        this->keywords["REAL"] = TIPOREAL;
        this->keywords["VECTOR"] = TIPOVECTOR;
        this->keywords[";"] = PUNTOYCOMA;
        this->keywords["="] = ASIGNACION;
        this->keywords["["] = ABRECORCHETES;
        this->keywords["]"] = CIERRACORCHETES;
        this->keywords[","] = COMA;
        this->keywords["espacio"] = RESERVAESPACIOVECTOR;
        this->keywords["+"] = SUMA;
        this->keywords["-"] = RESTA;
        this->keywords["/"] = DIVISION;
        this->keywords["*"] = MULTIPLICACION;
        this->keywords["||"] = OR;
        this->keywords["&&"] = AND;
        this->keywords["!"] = NOT;
        this->keywords["=="] = IGUAL_QUE;
        this->keywords["!="] = DISTINTO_QUE;
        this->keywords[">"] = MAYOR_QUE;
        this->keywords[">="] = MAYOR_O_IGUAL_QUE;
        this->keywords["<"] = MENOR_QUE;
        this->keywords["<="] = MENOR_O_IGUAL_QUE;
        this->keywords["lee"] = LEER;
        this->keywords["escribe"] = ESCRIBIR;
        this->keywords["func"] = COMIENZAFUNCION;
        this->keywords["inicio"] = INICIO;
        this->keywords["}"] = CIERRALLAVES;
        this->keywords["{"] = ABRELLAVES;
        this->keywords["global"] = GLOBAL;
        this->keywords[")"] = CIERRAPARENTESIS;
        this->keywords["("] = ABREPARENTESIS;
        this->keywords["devuelve"] = DEVUELVE;
        this->keywords["si"] = SI;
        this->keywords["mientras"] = MIENTRAS;
        this->keywords["parar"] = PARAR;
        this->keywords["llama"] = CALL;
    
    };
    
    
    void cleanBufferFromPrefixNumericKeywords(){
        
        string str_queue( queue.begin(), queue.end());
        char c = str_queue[0];
        
        switch (c) {
            case ';':
                 output.push_back(*new Symbol<int>(keywords[";"],keywords[";"]));
                 queue.pop_front();
                break;
                
            case '=':
                 output.push_back(*new Symbol<int>(keywords["="],keywords["="]));
                 queue.pop_front();
                break;
            case '[':
                 output.push_back(*new Symbol<int>(keywords["["],keywords["["]));
                 queue.pop_front();
                break;
            case ']':
                 output.push_back(*new Symbol<int>(keywords["]"],keywords["]"]));
                 queue.pop_front();
                break;
            case ',':
                 output.push_back(*new Symbol<int>(keywords[","],keywords[","]));
                 queue.pop_front();
                break;
            case '+':
                 output.push_back(*new Symbol<int>(keywords["+"],keywords["+"]));
                 queue.pop_front();
                break;
            case '-':
                output.push_back(*new Symbol<int>(keywords["-"],keywords["-"]));
                 queue.pop_front();
                break;
            case '/':
                 output.push_back(*new Symbol<int>(keywords["/"],keywords["/"]));
                 queue.pop_front();
                break;
            case '*':
                 output.push_back(*new Symbol<int>(keywords["*"],keywords["*"]));
                 queue.pop_front();
                break;
            case '!':
                output.push_back(*new Symbol<int>(keywords["!"],keywords["!"]));
                 queue.pop_front();
                break;
            case '>':
                 output.push_back(*new Symbol<int>(keywords[">"],keywords[">"]));
                 queue.pop_front();
                break;
            case '<':
                 output.push_back(*new Symbol<int>(keywords["<"],keywords["<"]));
                 queue.pop_front();
                break;
            case '{':
                 output.push_back(*new Symbol<int>(keywords["{"],keywords["{"]));
                 queue.pop_front();
                break;
            case '}':
                 output.push_back(*new Symbol<int>(keywords["}"],keywords["}"]));
                 queue.pop_front();
                break;
            case '(':
                 output.push_back(*new Symbol<int>(keywords["("],keywords["("]));
                 queue.pop_front();
                break;
            case ')':
                 output.push_back(*new Symbol<int>(keywords[")"],keywords[")"]));
                 queue.pop_front();
                break;
            default:
                break;
        }
    };
    
    
};