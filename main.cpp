/* Trabalho - Árvore B
   Nome: Mirelle Silva Vieira, RA: 0059636
   Nome: Raianny Magalhães Silva, RA: 0022116
*/

#include <iostream>
#include "btree.h"
#include "charserial.h"
#include "serialcurrency.h"
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    btree<serialcurrency, 3> disk("file.dat", "DTB", 3);
    char vetorpraInserir[20] = {')', '6', 'O', 'b', 'L', 'G', 'P', 'C', '3', '%', 'm', '(', 'H', 'W', 'Y', '&', 'k', '1', 'X', '-'};
    char vetorpraRemover[10] = {'C', 'm', '1', 'O', ')', 'W', 'Y', 'L', 'X', '('};



    //double inserting[21] = {5.50, 2.01, -5.33, 10.05, 21.13, 1.88, -3.14, 2.86, 37.55, 2.99, 34.31, 49.00, 38.26, 20.85, 23.02, 17.01, 14.92, 13.81, 39.89, -13.22, 7.20};

    charserial caractere;
    serialcurrency moeda(3.45), moeda2(4.56), moeda3(5.76), moeda4(6.78), moeda5(10.90), moeda6(4.50);
    //char valor;
    string op;
    int resp;

    if(disk.isOpen()){
        disk.insertKey(moeda);
        disk.insertKey(moeda2);
        disk.insertKey(moeda3);
        disk.insertKey(moeda4);
        disk.insertKey(moeda5);
        disk.insertKey(moeda6);
        disk.print();
    }

    disk.close();
/*
    if(disk.isOpen()){
        do{
            cout << "--------------------------\n"
                 << "Árvore B em Disco\n"
                 << "Selecione uma opção:\n\n"
                 << "1. Inserir um valor\n"
                 << "2. Remover um valor\n"
                 << "3. Pesquisar um valor\n"
                 << "4. Imprimir árvore\n"
                 << "5. Teste automatizado\n"
                 << "6. Sair\n\n"
                 << "Sua opção: ";
            cin >> resp;

            switch(resp){
                case 1:
                    cout << "Digite um valor: ";
                    cin >> valor;

                    if(disk.insertKey(moeda)){
                        disk.print();
                    }else{
                        cout << "Não foi possível inserir o valor!" << endl;
                    }
                    break;
                case 2:
                    cout << "Digite um valor: ";
                    cin >> valor;
                    moeda.setSerialCurrency(valor);
                    if(disk.remove(moeda)){
                        disk.print();
                    }else{
                        cout << "Não foi possível remover o valor!" << endl;
                    }
                    break;
                case 3:
                    cout << "Digite um valor: ";
                    cin >> valor;
                    moeda.setSerialCurrency(valor);
                    if(disk.search(moeda) >= 0){
                        cout << "O valor " << valor << " foi encontrado na árvore " << endl;
                    }else{
                        cout << "O valor " << valor << " não foi encontrado na árvore " << endl;
                    }
                    break;
                case 4:
                    disk.print();
                    break;

                case 5:
                    cout << endl
                         << "----------------------Efetuando as inserções--------------------"
                         << endl;
                    //for(int i = 0; i< 20; i++){
                      //  caractere.setValue(vetorpraInserir[i]);
                        //if(disk.insertKey(caractere)){
                          //  cout << "Mostrando após a Inserção de: " << vetorpraInserir[i] << endl;
                            //disk.print();
                        //}
               //     }
                    cout << endl
                         << "----------------------Efetuando as Remoções--------------------"
                         << endl;
                    //for(int i = 0; i< 10; i++){
                      //  caractere.setValue(vetorpraRemover[i]);
                        //if(disk.remove(caractere)){
                          //  cout << "Mostrando após a Remoção de: "<< vetorpraRemover[i] << endl;
                            //disk.print();
                   //     }
                 //   }
                    break;
                 case 6:
                    cout << "Encerrando o programa... ";
                    disk.close();
                    cout << "Concluído! " << endl;
                    return 0;
                    break;
                default:
                    cout << "Opção inválida! Tente novamente... " << endl;
                    break;
            }
    } while(true);
    }else{
        cerr << "Não foi possível abrir o arquivo! << endl;
    }*/
    return 0;
}
