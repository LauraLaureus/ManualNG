//
//  TokenChooser.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "TokenChooser.hpp"

std::string concatenacionPalabrasClave = "sifincasofuncnuloparasinofinaliniciosalidaespaciodevuelvemientrasREALVECTORLETRAleeescribeglobal";


TokenChooser::TokenChooser(){
    this->w = new Writer();
    this->keywords = *new map<std::string, int>();
    buildMap();
    this->mng = *new RegularExpressionAutomataManager();
    //this->regularExpressionInProcess = false;
}

void TokenChooser::accept(char c){
    this->queue.push_back(c);
    if (isCurrentFromIgnoreSet()) this->queue.pop_back();
    
    if( this->queue.size() >= 2){
        decide();
    }
}

void TokenChooser::decide(){
    
    string str_queue(this->queue.begin(),this->queue.end());
    
    //si el contenido coincide, completamente con una palabra clave escribela.
    if(this->keywords.count(str_queue) != 0){
        this->w->writeToken(this->keywords[str_queue]);
        this->queue.clear();
    }
    
    //sino
    else{
        if (!this->mng.anyRegularExpresionInRightOrPartialState(str_queue))
            cleanBufferFromPrefixNumericKeywords();
    }
}

void TokenChooser::cleanBufferFromPrefixNumericKeywords(){
    
    string str_queue(this->queue.begin(),this->queue.end());
    char c = str_queue[0];
    
    switch (c) {
        case ';':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
            
        case '=':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '[':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case ']':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case ',':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '+':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '-':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '/':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '*':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '!':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '>':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '<':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '{':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '}':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case '(':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        case ')':
            this->w->writeToken(this->keywords[""]);
            this->queue.pop_front();
            break;
        default:
            break;
    }
}

bool TokenChooser::isCurrentFromIgnoreSet(){
    return queue.back() == ' ' || queue.back() == '\t' || queue.back() == '\n' ;
}


void TokenChooser::buildMap(){

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
}