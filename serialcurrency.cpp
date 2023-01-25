/* Trabalho - Árvore B
   Nome: Mirelle Silva Vieira, RA: 0059636
   Nome: Raianny Magalhães Silva, RA: 0022116
*/

#include "serialcurrency.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

serialcurrency::serialcurrency() : serializable(){ // Construtor padrão
    intPart = 0;
    fracPart = 0;
}

serialcurrency::serialcurrency(double value){ // Construtor paramétrico
    double aux;

    aux = modf(value, &intPart); // modf divide o valor recebido por parâmetro em duas partes
                                 // intPart recebe a parte inteira e aux recebe a parte fracionária

    setFracPart(aux); // A parte fracionária é atribuída de acordo com o valor de aux
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

bool serialcurrency::operator> (const serialcurrency &other) const{ // Sobrecarga do operador >
    if(getIntPart() != other.getIntPart()){
        return getIntPart() > other.getIntPart() && getFracPart() > other.getFracPart();
    } else{
        return getFracPart() > other.getFracPart();
    }
}

bool serialcurrency::operator>= (const serialcurrency &other) const{ // Sobrecarga do operador >=
    if(getIntPart() >= other.getIntPart()){
        return getFracPart() >= other.getFracPart();
    } else{
        return false;
    }
}

bool serialcurrency::operator!=(const serialcurrency &other) const{ // Sobrecarga do operador !=
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
    if(newFracPart > 0.99){ // Se a parte fracionária tiver mais de dois dígitos
        intPart++; //intPart é incrementada em uma unidade
        fracPart = newFracPart - 1 + fracPart; // fracPart vai ser o que sobrar
    } else{ // Caso contrário, o valor passado por parâmetro é simplesmente atribuído a fracPart
        fracPart = newFracPart;
    }
}

double serialcurrency::getFracPart() const{ // Acessor do atributo fracPart
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

string serialcurrency::getValue() const{ // Retorna o valor total, ou seja, a soma entre a parte inteira e a parte fracionária
    double num = intPart + fracPart;

    stringstream stream;

    stream << std::fixed << std::setprecision(2) << num; // A precisão é de duas casas decimais

    string aux = stream.str(); // stream é convertido para string

    return aux;
}

void serialcurrency::setSerialCurrency(double value){ // Estabelece o valor total, similar ao construtor paramétrico
    double aux;

    aux = modf(value, &intPart);

    setFracPart(aux);
}
