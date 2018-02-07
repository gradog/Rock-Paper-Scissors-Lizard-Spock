//
// main.cpp
// Created by Guillermo Romero Alonso
//

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

int main (){
    
    // VARIABLES
    string human, machine, rules, line;
    bool known;
    srand (time (NULL));
    
    
    // INPUT
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    
    
    // LEO REGISTROS
    ifstream logRd, tmpRd;
    
    
    logRd.open ("log.txt");
    
    if (logRd.is_open ()){
        logRd >> line;
        known = false;
        
        while (!known && line != "XXX"){
            if (line == user){
                known = true;
                
                // comprueba la contrase–a
                logRd >> line;
                int i = 2;
                while(i != 0 && line != pass) {
                    cout << "Incorrect password, " << i << " tries left" << endl;
                    cout << "Password: ";
                    cin >> pass;
                    i--;
                }
                
                if (line != pass){
                    cout << "Sorry, you have triewd many times. Game blocked" << endl;
                    cout << "Exiting..." << endl;
                    return 0;
                }
            }
            else{
                logRd >> line;
            }
        }
        logRd.close();
        
        
        // NUEVO JUGADOR
        ofstream tempWr, logWr;
        logRd.open("log.txt");
        tempWr.open ("tmp.txt");
        
        if (!known && tempWr.is_open ()){
            logRd >> line;
            
            // copy log.txt to temp.txt
            while (line != "XXX"){
                tempWr << line << endl;
                logRd >> line;
                tempWr << line << endl;
                logRd >> line;
            }
            tempWr << "XXX";
            tempWr.close ();
            logRd.close ();
            
            
            logWr.open ("log.txt");
            tmpRd.open ("tmp.txt");
            
            if ((logWr.is_open ()) && (tmpRd.is_open ())){
                tmpRd >> line;
                while (line != "XXX"){
                    logWr << line << endl;
                    tmpRd >> line;
                }
                logWr << user << endl;
                logWr << pass << endl;
                logWr << "XXX";
            }
            tmpRd.close ();
            logWr.close ();
        }
    }
    
    
    // MENU INICIO
    int option, wonCount = 0, lostCount = 0, tiedCount = 0;
    
    cout << "1 - Play Game" << endl;
    cout << "2 - Read Rules" << endl;
    cout << "0 - Exit" << endl;
    cout << "Option: ";
    cin >> option;
    
    
    typedef enum {stone, paper, scissors, lizard, spock} tElemento;
    tElemento elem;
    int seed;
    
    while (option != 0 ){
        
        if (option == 1){
            // PC SELECCIONA ALEATORIAMENTE
            seed = rand() % 5;
            elem = tElemento (seed);
            switch (seed){
                case stone: machine = "stone";
                    break;
                case paper: machine = "paper";
                    break;
                case scissors: machine = "scissors";
                    break;
                case lizard: machine = "lizard";
                    break;
                case spock: machine = "spock";
                    break;
            }
            
            
            // COMPRUEBA ELEMENTO
            known = false;
            while (!known){
                cout << "Choose an element (stone, paper, scissors, lizard, spock): ";
                cin >> human;
                
                if (human == "stone" || human == "paper" || human == "scissors" || human == "lizard" || human == "spock"){
                    cout << "Machine option: " << machine << endl;
                    cout << "Human option: " << human << endl;
                    known = true;
                }
                else {
                    cout << "Unknown option. Try again" << endl;
                }
            }
            
            
            if (human != machine){
                
                // GANO
                if (human == "stone" && (machine == "scissors" || machine == "lizard")
                    || human == "paper" && (machine == "stone" || machine == "spock")
                    || human == "scissors" && (machine == "paper" || machine == "lizard")
                    || human == "lizard" && (machine == "paper" || machine == "spock")
                    || human == "spock" && (machine == "stone" || machine == "scissors")) {
                    cout << "........." << endl;
                    cout << "You win! :)" << endl;
                    wonCount++;
                }
                
                // PIERDO
                if (human == "stone" && (machine == "paper" || machine == "spock")
                    || human == "paper" && (machine == "scissors" || machine == "lizard")
                    || human == "scissors" && (machine == "stone" || machine == "spock")
                    || human == "lizard" && (machine == "stone" || machine == "scissors")
                    || human == "spock" && (machine == "paper" || machine == "lizard")) {
                    cout << "........." << endl;
                    cout << "I win!" << endl;
                    lostCount++;
                }
                
            }
            // EMPATE
            else {
                (human == machine);
                cout << ". . . . . . . . ." << endl;
                cout << "Tie!" << endl;
                tiedCount++;
            }
        }
        
        
        // MUESTRA REGLAS
        ifstream txtRules;
        
        if (option == 2){
            txtRules.open ("rules.txt");
            if (txtRules.is_open ()){
                txtRules >> rules;
                while (rules != "XXX"){
                    getline(txtRules, rules);
                    cout << rules << endl;
                    txtRules >> rules;
                }
            }
            txtRules.close();
            cout << endl;
        }
        
        
        // MENU INICIO
        cout << "1 - Play Game" << endl;
        cout << "2 - Read Rules" << endl;
        cout << "0 - Exit" << endl;
        cout << "Option: ";
        cin >> option;
    }
    
    // MUETRA RESULTADOS
    cout << "Games won: " << wonCount << endl;
    cout << "Games tied: " << tiedCount << endl;
    cout << "Games lost: " << lostCount << endl;
    cout << "See you!" << endl;
    
    return 0;
}



