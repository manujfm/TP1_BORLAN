#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iomanip>      // std::setw

using namespace std;
const int MAX_COUNTRY = 20;

const char COUNTRY_FILENAME[] = "Paises.txt";
const char COUNTRY_STATISTICS_FILENAME[] = "ParteDiario.txt";

const char HISOPADE_FILENAME[] = "ListadoHisopados.txt";
const char INFECTED_FILENAME[] = "ListadoInfectados.txt";
const char RECOVERED_FILENAME[] = "ListadoRecuperados.txt";
const char DEATH_FILENAME[] = "ListadoMuertes.txt";


struct countryStatistics {
    char countryName[20];
    int day,
            month,
            infected,
            hisopade,
            recovered,
            deaths;
};


struct calendar {
    long int jan;
    long int feb;
    long int mar;
    long int aph;
    long int may;
    long int jun;
    long int jul;
    int getTotals() const{
        return jan + feb + mar + aph + may + jun + jul;
    }
};


struct country {
    char countryName[20];
    char continent[10];
    int people;
    calendar hisopade;
    calendar infected;
    calendar recovered;
    calendar deaths;
    float getPercent(calendar typeP) const {
        int total = float(typeP.getTotals());
        return ( total * 100 )/ float(people);
    };

    void printPeople() const {
        cout << " PAIS "<< countryName << endl;
        cout << " hisopados: "<< hisopade.jan << " - ";
        cout << " infectados: "<< infected.jan <<" - ";
        cout << " Recuperados: "<< recovered.jan << " - ";
        cout << " Muertos: "<< deaths.jan << endl;

        cout << " FEB hisopados: "<< hisopade.feb << " - ";
        cout << " FEB infectados: "<< infected.feb <<" - ";
        cout << " FEB Recuperados: "<< recovered.feb << " - ";
        cout << " FEB Muertos: "<< deaths.feb << endl;
    };
    void print() const {
        cout << " Pais: " << countryName << " - ";
        cout << " Continente: "<< continent << " - ";
        cout << " Poblacion: "<< people << endl;
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
//                    << setw(2) << rand() % 6 + 1 << " "
                    << setw(2) << 1 << " "
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
            memset(&countries[i].infected, 0, sizeof(calendar));
            memset(&countries[i].hisopade, 0, sizeof(calendar));
            memset(&countries[i].recovered, 0, sizeof(calendar));
            memset(&countries[i].deaths, 0, sizeof(calendar));
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


int findByCountry(country countries[], char countryName[], int arrayLength){
    string key(countryName);
    int first = 0, m;
    if (string(countries[first].countryName).compare(key) == 0)
        return first;
    if (string(countries[arrayLength - 1].countryName).compare(key) == 0)
        return arrayLength - 1;
    while (first < arrayLength){
        m = (first + arrayLength) / 2;
        if (string(countries[arrayLength].countryName).compare(key) == 0)
            return arrayLength;
        if (string(countries[first].countryName).compare(key) == 0)
            return first;
        string country_str(countries[m].countryName);

        if (key.compare(country_str) == 0)
            return m;
        if (country_str < key)
            first = m + 1;
        else
            arrayLength = m - 1;
    }
    return  -1;
}


void updateCountryData(country &cou, countryStatistics cs){
    switch ( cs.month ){
        case 1:{
            cou.infected.jan = cou.infected.jan + cs.infected ;
            cou.hisopade.jan = cou.hisopade.jan + cs.hisopade ;
            cou.recovered.jan =cou.recovered.jan + cs.recovered ;
            cou.deaths.jan   = cou.deaths.jan + cs.deaths ;
            break;
        }
        case 2: {
            cou.infected.feb =  cou.infected.feb + cs.infected ;
            cou.hisopade.feb =  cou.hisopade.feb + cs.hisopade ;
            cou.recovered.feb =  cou.recovered.feb + cs.recovered ;
            cou.deaths.feb =  cou.deaths.feb + cs.deaths ;
            break;
        }
        case 3: {
            cou.infected.mar =  cou.infected.mar + cs.infected;
            cou.hisopade.mar =  cou.hisopade.mar + cs.hisopade;
            cou.recovered.mar =  cou.recovered.mar + cs.recovered;
            cou.deaths.mar =  cou.deaths.mar + cs.deaths;
            break;
        }
        case 4:{
            cou.infected.aph =  cou.infected.aph + cs.infected ;
            cou.hisopade.aph =  cou.hisopade.aph + cs.hisopade ;
            cou.recovered.aph =  cou.recovered.aph + cs.recovered ;
            cou.deaths.aph   =  cou.deaths.aph + cs.deaths ;
            break;
        }
        case 5:{
            cou.infected.may =  cou.infected.may + cs.infected;
            cou.hisopade.may =  cou.hisopade.may + cs.hisopade;
            cou.recovered.may = cou.recovered.may + cs.recovered;
            cou.deaths.may   =  cou.deaths.may + cs.deaths;
            break;
        }
        case 6:{
            cou.infected.jun =  cou.infected.jun + cs.infected;
            cou.hisopade.jun =  cou.hisopade.jun + cs.hisopade;
            cou.recovered.jun = cou.recovered.jun + cs.recovered;
            cou.deaths.jun   =  cou.deaths.jun + cs.deaths;
            break;
        }
        case 7:
            cou.infected.jul = cou.infected.jul + cs.infected;
            cou.hisopade.jul =  cou.hisopade.jul + cs.hisopade;
            cou.recovered.jul = cou.recovered.jul + cs.recovered;
            cou.deaths.jul   =  cou.deaths.jul + cs.deaths ;
            break;
        }
//        cou.print();
}


bool readDailyCountry(ifstream &countryFile, country countries[]){
    bool res = false;
    short index;
    if ( countryFile.is_open() ){
        res = true;
        while (!countryFile.eof()){
            countryStatistics cst;
            countryFile.get(cst.countryName, 20);
            countryFile.ignore();
            countryFile >> cst.day       >> cst.month
                        >> cst.hisopade  >> cst.infected
                        >> cst.recovered >> cst.deaths;
            countryFile.ignore();
            if ( !countryFile.good() ){
                res = false;
                break;
            }
            index = findByCountry(countries, cst.countryName, MAX_COUNTRY);
            updateCountryData(countries[index], cst);
        }
    }
    return res;
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


void printTitle (ofstream &file, string typelist){
    file     << setw(50) << left << " "
             <<"Listado de " << typelist << endl
             <<"Nro." << setw(20) << left <<" Nom." << "Cant.Hab"
             << " ------------- Cantidad de Hisopados por Mes ------------- "
             << "     Cant.   " << "Porcentajes " << endl;
    file     << "Ord" << setw(20) << left << " País" << "                  "
             << "Ene     " << "Feb     "<< "Mar    "<< "Abr    "
             << "May     " << "Jun     "<< "Jul       "<< "Tot.   " << endl;
}


void openWriteFiles(ofstream &hisopade, ofstream &recovered, ofstream &deaths, ofstream &infected){
    hisopade.open(HISOPADE_FILENAME);
    recovered.open(RECOVERED_FILENAME);
    deaths.open(DEATH_FILENAME);
    infected.open(INFECTED_FILENAME);
}


void writeRow(ofstream &recovered, short index, calendar peopleInfo, country countryData){
    recovered << setw(4) << left << index + 1
             << setw(20)<< left << countryData.countryName
             << setw(9) << left << countryData.people
             << "       "
             << setw(8) << left << peopleInfo.jan
             << setw(8) << left << peopleInfo.feb
             << setw(8) << left << peopleInfo.mar
             << setw(8) << left << peopleInfo.aph
             << setw(8)<< left  << peopleInfo.may
             << setw(8)<< left  << peopleInfo.jun
             << setw(8) << left << peopleInfo.jul
             << setw(8)<< left  << peopleInfo.getTotals()
             << setw(8)<< left  << countryData.getPercent(peopleInfo) << endl;
}

void printFooter(ofstream &file,string typelist, float percent, int total){
    file << endl
         << endl
         << endl
         << "Cantidad Total de " << typelist
         << " a la fecha actual: " << total << endl
         << "Porcentaje  de " << typelist << ".....................: "<< percent << endl;
}


void genFiles(country countries[]){
    float percentH, percentR, percentI, percentD;
    int tH, tR, tI, tD;
    tH = tR = tI = tD = percentH = percentR = percentI = percentD = 0;
    ofstream hisopade, recovered, deaths, infected;
    openWriteFiles(hisopade, recovered, deaths, infected);

    printTitle(hisopade, "Hisopados");
    printTitle(recovered, "Recuperdos");
    printTitle(deaths, "Muertes");
    printTitle(infected, "Infectados");

    for( short i = 0; i < MAX_COUNTRY; i++ ){
        writeRow(recovered, i, countries[i].recovered, countries[i]);
        percentR += countries[i].getPercent(countries[i].recovered);
        tR += countries[i].recovered.getTotals();

        writeRow(hisopade, i, countries[i].hisopade, countries[i]);
        percentH += countries[i].getPercent(countries[i].hisopade);
        tH += countries[i].hisopade.getTotals();


        writeRow(deaths, i, countries[i].deaths, countries[i]);
        percentD += countries[i].getPercent(countries[i].deaths);
        tD += countries[i].deaths.getTotals();


        writeRow(infected, i, countries[i].infected, countries[i]);
        percentI += countries[i].getPercent(countries[i].infected);
        tI += countries[i].infected.getTotals();

    }

    printFooter(hisopade, "Hisopados", percentH, tH);
    printFooter(recovered, "Recuperados", percentR, tR);
    printFooter(deaths, "Muertes", percentD, tD);
    printFooter(infected, "Infectados", percentI, tI);

    hisopade.close();
    recovered.close();
    deaths.close();
    infected.close();
}


int main() {
    ifstream countryFile, statisticsFile;
    country countries[MAX_COUNTRY];

    cout << "Generando Archivos..." << endl;
//    genCountryFile();
//    genDailyCountryFile();


    cout << "Leyendo Archivos..." << endl;
    openFiles(countryFile, statisticsFile);
    readCountryFile(countryFile, countries);
    sortCountriesByCountry(countries, MAX_COUNTRY);
    readDailyCountry(statisticsFile, countries);


    cout << "Creando archivos..." << endl;
    genFiles(countries);


    closeFiles(countryFile, statisticsFile);
    return 0;
}
