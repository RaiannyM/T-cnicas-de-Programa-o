/*
#include "serialCurrency.h"
#include <iostream>

using namespace std;

serialCurrency::serialCurrency() : serializable(){ // Construtor padrão
    x = 0;
    y = 0;
}

serialCurrency::serialCurrency(int nx, int ny) : serializable(){ // Construtor paramétrico
    x = nx;
    if(ny >= 100){ // Se a parte fracionária possuir mais de dois dígitos,
                   // há um incremento de 1 unidade na parte inteira
        x++;
        y = ny - 100;
    }
}

serialCurrency::serialCurrency(const serialCurrency& other){ // Construtor de cópia
    x = other.getX();
    y = other.getY();
}

serialCurrency::~serialCurrency(){ // Destrutor

}

serialCurrency serialCurrency:::operator=(const serialCurrency& other){ // Sobrecarga do operador =
    if(this != &other){
        x = other.getX();
        y = other.getY();
        return *this;
    }
    return *this;
}

bool serialCurrency::operator==(const serialCurrency &other) const{ // Sobrecarga do operador ==
    return x = other.getX() && y == other.getY();
}

bool serialCurrency::operator<(const serialCurrency &other) const{ // Sobrecarga do operador <
    if(x == other.getX()) // Se as partes inteiras são iguais, o que irá diferenciar os valores
                          // será a parte fracionária
        return y < other.getY();
    else
        return x < other.getX();
}

bool serialCurrency::operator<=(const serialCurrency &other) const{ // Sobrecarga do operador <=

}

bool serialCurrency::operator!=(const serialCurrency &other) const{
    return x != other.getX() && y != other.getY();
}

void serialCurrency::setX(int nx){ // Modificador do atributo x
    x = nx;
}

int serialCurrency::getX() const{ // Acessor do atributo x
    return x;
}

void serialCurrency::setY(int ny){ // Modificador do atributo y
    if(ny >= 100){
        x++;
        y = ny - 100;
    }
}

string serialCurrency::toString(){ // Serialização
    string repr = "";

    repr += string(reintepret_cast<char*>(&x). sizeof(x));
    repr += string(reinterpret_cast<char*>(&y), sizeof(y));

    return repr;
}

void serialCurrency::fromString(){ // Serialização
    int pos;

    repr.copy(reintepret_cast<char*>(&))
}

// *** Não implementados
string serialCurrency::toXML(){
    return "";
}

void serialCurrency::fromXML(string repr){

}

string serialCurrency::toCSV(){
    return "";
}

void serialCurrency::fromCSV(string repr){

}

string serialCurrency::toJSON(){
    return "";
}

void serialCurrency::fromJSON(string repr){

}

// ***

unsigned long long int serialCurrency::size() const{
    return sizeof(x) + sizeof(y);
}
*/
