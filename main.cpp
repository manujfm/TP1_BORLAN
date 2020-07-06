#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int MAX_COUNTRY = 20;
const string COUNTRY_FILENAME = "Paises.txt";
const string COUNTRY_STATISTICS_FILENAME = "ParteDiario.txt";

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
        infecteds,
        hisopades,
        recovereds,
        deads;
    void print() const {
        cout << " Pais: " << countryName << " - ";
        cout << " Fecha: "<< day << "/" << month << " - ";
        cout << " Infectados: "<< infecteds ;
        cout << " hisopados: "<< hisopades ;
        cout << " Curados: "<< recovereds ;
        cout << " Muertes: "<< deads << endl;
    }
};

void genCountryFile(){
    FILE *countryFile;
    int i;
    struct country countries[MAX_COUNTRY];
    string countries_names[MAX_COUNTRY] = {"Venezuela","Bolivia","Peru","Argentina","Uruguay","Paraguay","Colombia","España","Paris","Italia","Portugal","Mexico","Panama","China","Japon","Rusia","Canada","Brasil","Chile","Inglaterra"};
    string continet[MAX_COUNTRY] = {"America","America","America","America","America","America","America","Europa","Europa","Europa","Europa","America","America","Asia","Asia","Asia","America","America","America","Europa"};
    countryFile = fopen(COUNTRY_FILENAME.c_str(), "wb");
    if (countryFile != NULL){
        for (i = 0; i< MAX_COUNTRY; i++) {
            memset(&countries[i], 0, sizeof(country));
            strcpy(countries[i].countryName, countries_names[i].c_str());
            strcpy(countries[i].continent, continet[i].c_str());
            countries[i].people = 3000;
            fwrite(&countries[i], sizeof(struct country), 1, countryFile);
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
        while (!feof(countryFile)){
          memset(&countries[i], 0, sizeof(country));
          fread(&countries[i], sizeof(struct country), 1, countryFile);
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

int main() {
    FILE *countryFile, *statisticsFile;
    struct country countries[MAX_COUNTRY];
    int i;
    cout << "Generando Archivos..." << endl;
    genCountryFile();
    openFiles(&countryFile, &statisticsFile);
    readCountryFile(countryFile, countries);
    cout << "---- PRINTING ----" << endl;
    for ( i=0; i< MAX_COUNTRY; i++ ){
        countries[i].print();
    }
    return 0;
}
