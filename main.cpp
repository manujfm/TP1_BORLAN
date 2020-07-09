#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iomanip>      // std::setw

using namespace std;
const int MAX_COUNTRY = 20;
const string COUNTRY_FILENAME = "/home/manu/UTN/TP1_BORLAN/Paises.txt";
const string COUNTRY_STATISTICS_FILENAME = "/home/manu/UTN/TP1_BORLAN/ParteDiario.txt";

struct country {
    char countryName[20];
    char continent[10];
    long long int people;
    void print() const {
        cout << " Pais: " << countryName << " - ";
        cout << " Continente: "<< continent << " - ";
        cout << " Personas: "<< people << endl;
    }
};

struct countryStatistics {
    char countryName[20];
    int day,
        month,
        infected,
        hisopade,
        recovered,
        deaths;
    void print() const {
        cout << " Pais: " << countryName << " - ";
        cout << " Fecha: "<< day << "/" << month << " - ";
        cout << " Infectados: "<< infected ;
        cout << " hisopados: "<< hisopade ;
        cout << " Curados: "<< recovered ;
        cout << " Muertes: "<< deaths << endl;
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
                    << setw(2) << rand() % 12 + 1 << " "
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

//bool readDailyCountry(ifstream &countryFile, countryStatistics countries[]){
//    int i = 0;
//    bool couldRead = false;
//    countryFile = fopen(COUNTRY_STATISTICS_FILENAME.c_str(), "r+b");
//    if (countryFile != NULL){
//        couldRead = true;
//        while (!feof(countryFile) && i < MAX_COUNTRY){
//          memset(&countries[i], 0, sizeof(countryStatistics));
//          fread(&countries[i], sizeof(struct countryStatistics), 1, countryFile);
//          i++;
//        }
//    }
//    fclose(countryFile);
//    return couldRead;
//}


void openFiles(ifstream &countryFile, ifstream &statisticsFile){
    countryFile.open(COUNTRY_FILENAME);
    statisticsFile.open(COUNTRY_STATISTICS_FILENAME);
}

void closeFiles(ifstream &countryFile, ifstream &statisticsFile){
    countryFile.close();
    statisticsFile.close();
}

int main() {
    ifstream countryFile, statisticsFile;
    country countries[MAX_COUNTRY];
    countryStatistics countriesPart[MAX_COUNTRY];
    cout << "Generando Archivos..." << endl;
    genCountryFile();
    genDailyCountryFile();
    cout << "Leyendo Archivos..." << endl;
    openFiles(countryFile, statisticsFile);
    readCountryFile(countryFile, countries);

    for (short i = 0; i < MAX_COUNTRY; i++ )
        countries[i].print();
//    readDailyCountry(statisticsFile, countriesPart);
//
//
//
//
//    cout << "Printing" << endl;

    closeFiles(countryFile, statisticsFile);
    return 0;
}
