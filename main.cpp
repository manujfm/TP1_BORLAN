#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iomanip>      // std::setw

using namespace std;
const int MAX_COUNTRY = 20;
const string COUNTRY_FILENAME = "/home/manu/UTN/TP1_BORLAN/Paises.txt";
const string COUNTRY_STATISTICS_FILENAME = "/home/manu/UTN/TP1_BORLAN/ParteDiario.txt";

struct calendar {
    long int jan;
    long int feb;
    long int mar;
    long int aph;
    long int may;
    long int jun;
    long int jul;
};

struct country {
    char countryName[20];
    char continent[10];
    long long int people;
    calendar hisopade;
    calendar infected;
    calendar recovery;
    calendar deaths;
    void print() const {
        cout << " Pais: " << countryName << " - ";
        cout << " Continente: "<< continent << " - ";
        cout << " Personas: "<< people << endl;
    }
};

void genCountryFile(){
    ofstream countryFile;
    string countries_names[MAX_COUNTRY] = {"Venezuela","Bolivia","Peru","Argentina","Uruguay","Paraguay","Colombia","Espana","Paris","Italia","Portugal","Mexico","Panama","China","Japon","Rusia","Canada","Brasil","Chile","Inglaterra"};
    string continent[MAX_COUNTRY] = {"America","America","America","America","America","America","America","Europa","Europa","Europa","Europa","America","America","Asia","Asia","Asia","America","America","America","Europa"};
    int i;
    countryFile.open(COUNTRY_FILENAME);
    if (countryFile.is_open()){
        for (i = 0; i < MAX_COUNTRY; i++) {
            int people = rand() % 300000000 + 500000000;
            countryFile
            << setw(20) << left << countries_names[i] << " "
            << setw(10) << continent[i]               << " "
            << people << endl;
         }
    }
    countryFile.close();
}

void genDailyCountryFile(){
    ofstream countryFile;
    string countries_names[MAX_COUNTRY] = {"Venezuela","Bolivia","Peru","Argentina","Uruguay","Paraguay","Colombia","Espana","Paris","Italia","Portugal","Mexico","Panama","China","Japon","Rusia","Canada","Brasil","Chile","Inglaterra"};
    int i;
    countryFile.open(COUNTRY_STATISTICS_FILENAME);
    if (countryFile.is_open()){
        for (i = 0; i < MAX_COUNTRY; i++) {
            countryFile
                    << setw(20) << left << countries_names[i] << " "
                    << setw(2) << rand() % 31 + 1 << " "
                    << setw(2) << rand() % 6 + 1 << " "
                    << setw(4) << rand() % 100 + 1000 << " "
                    << setw(4) << rand() % 100 + 1000 << " "
                    << setw(4) << rand() % 100 + 1000 << " "
                    << setw(4) << rand() % 100 + 1000 << endl;
        }
    }
    countryFile.close();
}

bool readCountryFile(ifstream &countryFile, country countries[]){
    bool res = false;
    if ( countryFile.is_open() ){
        res = true;
        for ( short i = 0; i < MAX_COUNTRY; i++ ){
            countryFile.get(countries[i].countryName, 20);
            countryFile.ignore();
            countryFile.get(countries[i].continent, 10);
            countryFile >> countries[i].people;
            countryFile.ignore();
            if (!countryFile.good()){
                res = countryFile.good();
                break;
            }
        }
    }
    return res;
}

//  Cantidad de Hisopados,
//  Cantidad de Infectados,
//  Cantidad de Recuperados,
//  Cantidad de Fallecidos;
bool readDailyCountry(ifstream &countryFile, country countries[]){
    bool res = false;
    if ( countryFile.is_open() ){

    }
}


void openFiles(ifstream &countryFile, ifstream &statisticsFile){
    countryFile.open(COUNTRY_FILENAME);
    statisticsFile.open(COUNTRY_STATISTICS_FILENAME);
}

void closeFiles(ifstream &countryFile, ifstream &statisticsFile){
    countryFile.close();
    statisticsFile.close();
}

void change(country &country1, country &country2){
    country countryAux = country1;
    country1 = country2;
    country2 = countryAux;
}

void sortCountriesByCountry(country myCountries[ ], int arrayLength){
    short k = 0;
    bool order = false;
    do {
        k++;
        order = true;
        for ( short i = 0; i < arrayLength - k; i++){
            string country1(myCountries[i].countryName);
            string country2(myCountries[i+1].countryName);
            if ( country1 > country2 ){
                change(myCountries[i], myCountries[i+1]);
                order = false;
            };
        }
    } while (!order);
}

int main() {
    ifstream countryFile, statisticsFile;
    country countries[MAX_COUNTRY];

    cout << "Generando Archivos..." << endl;
    genCountryFile();
    genDailyCountryFile();


    cout << "Leyendo Archivos..." << endl;
    openFiles(countryFile, statisticsFile);
    readCountryFile(countryFile, countries);
    sortCountriesByCountry(countries, MAX_COUNTRY);
    readDailyCountry(statisticsFile, countries);

    for ( int i = 0; i< MAX_COUNTRY; i++){
        countries[i].print();
    }


//
//
//
//
//    cout << "Printing" << endl;

    closeFiles(countryFile, statisticsFile);
    return 0;
}
