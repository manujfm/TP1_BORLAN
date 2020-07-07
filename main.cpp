#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;
const int MAX_COUNTRY = 20;
const string COUNTRY_FILENAME = "/home/manu/UTN/TP1_BORLAN/Paises.txt";
const string COUNTRY_STATISTICS_FILENAME = "/home/manu/UTN/TP1_BORLAN/ParteDiario.txt";

struct country {
    char countryName[20];
    char continent[10];
    int people;
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
    FILE *countryFile;
    int i;
    struct country countries[MAX_COUNTRY];
    string countries_names[MAX_COUNTRY] = {"Venezuela","Bolivia","Peru","Argentina","Uruguay","Paraguay","Colombia","Espa�a","Paris","Italia","Portugal","Mexico","Panama","China","Japon","Rusia","Canada","Brasil","Chile","Inglaterra"};
    string continent[MAX_COUNTRY] = {"America","America","America","America","America","America","America","Europa","Europa","Europa","Europa","America","America","Asia","Asia","Asia","America","America","America","Europa"};
    countryFile = fopen(COUNTRY_FILENAME.c_str(), "wb");
    if (countryFile != NULL){
        for (i = 0; i< MAX_COUNTRY; i++) {
            memset(&countries[i], 0, sizeof(country));
            strcpy(countries[i].countryName, countries_names[i].c_str());
            strcpy(countries[i].continent, continent[i].c_str());
            countries[i].people = rand() % 3000000 + 5000000;
            fwrite(&countries[i], sizeof(struct country), 1, countryFile);
         }
    }
    fclose(countryFile);
}

void genDailyCountryFile(){
    FILE *countryFile;
    int i;
    struct countryStatistics countries[MAX_COUNTRY];
    string countries_names[MAX_COUNTRY] = {"Venezuela","Bolivia","Peru","Argentina","Uruguay","Paraguay","Colombia","Espa�a","Paris","Italia","Portugal","Mexico","Panama","China","Japon","Rusia","Canada","Brasil","Chile","Inglaterra"};
    countryFile = fopen(COUNTRY_STATISTICS_FILENAME.c_str(), "wb");
    if (countryFile != NULL){
        for (i = 0; i< MAX_COUNTRY; i++) {
            memset(&countries[i], 0, sizeof(country));

            strcpy(countries[i].countryName, countries_names[i].c_str());
            countries[i].day = rand() % 31 + 1;
            countries[i].month = rand() % 12 + 1;
            countries[i].infected = rand() % 3000000 + 5000000;
            countries[i].hisopade = rand() % 3000000 + 5000000;
            countries[i].recovered = rand() % 3000000 + 5000000;
            countries[i].deaths = rand() % 3000000 + 5000000;
            fwrite(&countries[i], sizeof(struct countryStatistics), 1, countryFile);
            countries[i].print();
        }
    }
    fclose(countryFile);
}

bool readCountryFile(FILE *countryFile, country countries[]){
    int i = 0;
    bool couldRead = false;
    countryFile = fopen(COUNTRY_FILENAME.c_str(), "r+b");
    if (countryFile != NULL){
        couldRead = true;
        while (!feof(countryFile) && i < MAX_COUNTRY){
          memset(&countries[i], 0, sizeof(country));
          fread(&countries[i], sizeof(struct country), 1, countryFile);
          i++;
        }
    }
    fclose(countryFile);
    return couldRead;
}

bool readDailyCountry(FILE *countryFile, countryStatistics countries[]){
    int i = 0;
    bool couldRead = false;
    countryFile = fopen(COUNTRY_STATISTICS_FILENAME.c_str(), "r+b");
    if (countryFile != NULL){
        couldRead = true;
        while (!feof(countryFile) && i < MAX_COUNTRY){
          memset(&countries[i], 0, sizeof(countryStatistics));
          fread(&countries[i], sizeof(struct countryStatistics), 1, countryFile);
          i++;
        }
    }
    fclose(countryFile);
    return couldRead;
}


void openFiles(FILE **countryFile, FILE **statisticsFile){
    *countryFile = fopen("Paises.txt", "r+b");
    *statisticsFile = fopen("Paises.txt", "r+b");
}

void closeFiles(FILE **countryFile, FILE **statisticsFile){
    fclose(*countryFile);
    fclose(*statisticsFile);
}

int main() {
    FILE *countryFile, *statisticsFile;
    country countries[MAX_COUNTRY];
    countryStatistics countriesPart[MAX_COUNTRY];
    int i;
    cout << "Generando Archivos..." << endl;
    genCountryFile();
    genDailyCountryFile();

    cout << "Leyendo Archivos..." << endl;
    openFiles(&countryFile, &statisticsFile);
    readCountryFile(countryFile, countries);
    readDailyCountry(statisticsFile, countriesPart);




    cout << "Printing" << endl;
    for ( i=0; i< MAX_COUNTRY; i++ ){
        countriesPart[i].print();
    }
    closeFiles(&countryFile, &statisticsFile);
    return 0;
}
