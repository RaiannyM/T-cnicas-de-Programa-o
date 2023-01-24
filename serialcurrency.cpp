#include "serialcurrency.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

serialcurrency::serialcurrency() : serializable(){ // Construtor padrão
    intPart = 0;
    fracPart = 0;
}

serialcurrency::serialcurrency(double value){ // Construtor paramétrico
    double aux;

    aux = modf(value, &intPart);

    setFracPart(aux);
}

serialcurrency::serialcurrency(const serialcurrency& other){ // Construtor de cópia
    intPart = other.getIntPart();
    setFracPart(other.getFracPart());
}

serialcurrency::~serialcurrency(){ // Destrutor

}

serialcurrency serialcurrency::operator=(const serialcurrency& other){ // Sobrecarga do operador =
    serialcurrency aux(other);

    if(this == &other){
        return *this;
    }

    intPart = other.getIntPart();
    setFracPart(other.getFracPart());

    return aux;
}

bool serialcurrency::operator==(const serialcurrency &other) const{ // Sobrecarga do operador ==
    if(getIntPart() != other.getIntPart()){
        return false;
    } else{
        return getFracPart() == other.getFracPart();
    }
}

bool serialcurrency::operator<(const serialcurrency &other) const{ // Sobrecarga do operador <
    if(getIntPart() != other.getIntPart()){
        return getIntPart() < other.getIntPart() && getFracPart() < other.getFracPart();
    } else{
        return getFracPart() < other.getFracPart();
    }
}

bool serialcurrency::operator<= (const serialcurrency &other) const{ // Sobrecarga do operador <=
    if(getIntPart() <= other.getIntPart()){
        return getFracPart() <= other.getFracPart();
    } else{
        return false;
    }
}

bool serialcurrency::operator> (const serialcurrency &other) const{
    if(getIntPart() != other.getIntPart()){
        return getIntPart() > other.getIntPart() && getFracPart() > other.getFracPart();
    } else{
        return getFracPart() > other.getFracPart();
    }
}

bool serialcurrency::operator>= (const serialcurrency &other) const{
    if(getIntPart() >= other.getIntPart()){
        return getFracPart() >= other.getFracPart();
    } else{
        return false;
    }
}

bool serialcurrency::operator!=(const serialcurrency &other) const{
    if(getIntPart() != other.getIntPart()){
        return true;
    } else{
        return getFracPart() != other.getFracPart();
    }
}

void serialcurrency::setIntPart(double newIntPart){ // Modificador do atributo intPart
    intPart = newIntPart;
}

double serialcurrency::getIntPart() const{ // Acessor do atributo intPart
    return intPart;
}

void serialcurrency::setFracPart(double newFracPart){; // Modificador do atributo fracPart
    if(newFracPart > 0.99){
        intPart++;
        fracPart = newFracPart - 1 + fracPart;
    } else{
        fracPart = newFracPart;
    }
}

double serialcurrency::getFracPart() const{
    return fracPart;
}

string serialcurrency::toString(){ // Serialização
    string repr = "";

    repr += string(reinterpret_cast<char*>(&intPart), sizeof(intPart));
    repr += string(reinterpret_cast<char*>(&fracPart), sizeof(fracPart));

    return repr;
}

void serialcurrency::fromString(string repr){ // Deserialização
    int pos = 0;

    repr.copy(reinterpret_cast<char*>(&intPart), sizeof(intPart), pos);
    pos += sizeof(intPart);
    repr.copy(reinterpret_cast<char*>(&fracPart), sizeof(fracPart), pos);
}

unsigned long long int serialcurrency::size() const{ // Calcula o tamanho de um objeto da classe serialCurrency
    return sizeof(intPart) + sizeof(fracPart);
}

double serialcurrency::getSerialCurrency(){
    double num;

    num = getIntPart() + getFracPart();

    return num;
}

void serialcurrency::setSerialCurrency(double value){
    double aux;

    aux = modf(value, &intPart);

    setFracPart(aux);
}
