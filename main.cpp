/*
    Algoritmos y Estructura de Datos
    Curso K1092  - Grupo 6
    Hora: Tarde - Noche
    Integrantes:
        Francisco Javier Azpitarte
        Alexis Cabo
        Jhonny Teran Claure
        Manuel Marcano Quijada
        Sebastian Rolando
        Tomas Ezama
*/
/* 13/08/20 -- Segunda Correccion (Profe, somos el equipo del archivo en UNIX)
    Las modificaciones entonces serían:
        - La constante de cantidad de países en vez de 20 debe ser 200 (doscientos)
        - Invertir el orden de lectura en el archivo de ParteDiario del día con el mes, ya que en las consignas primero es el mes y a continuación el día.
        - En las cadenas siempre se establece un lugar más, es decir si va a contener 20 caracteres le damos longitud física de 21, si es de 10 le damos 11.
        - La salida en los listados mejorar el alineamiento, las cadenas alineadas a la izquierda y los valores numéricos alineados a la derecha.
 * */

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>      // std::setw

using namespace std;
const int MAX_COUNTRY = 200;

const char COUNTRY_FILENAME[] = "Paises.txt";
const char COUNTRY_STATISTICS_FILENAME[] = "ParteDiario.txt";

const char HISOPADE_FILENAME[] = "ListadoHisopados.txt";
const char INFECTED_FILENAME[] = "ListadoInfectados.txt";
const char RECOVERED_FILENAME[] = "ListadoRecuperados.txt";
const char DEATH_FILENAME[] = "ListadoMuertes.txt";

struct countryStatistics {
    char countryName[21];
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
    int getTotal() const{
        return jan + feb + mar + aph + may + jun + jul;
    }
};

struct country {
    char countryName[21];
    char continent[11];
    int people;
    calendar hisopade;
    calendar infected;
    calendar recovered;
    calendar deaths;
    calendar getAtt(string peopleType){
        if (peopleType == "hisopade") {
            return hisopade;
        } else if (peopleType == "infected"){
            return infected;
        } else if (peopleType == "recovered"){
            return recovered;
        }
        return deaths;
    };
    float getPercent(calendar typeP) const {
        int total = float(typeP.getTotal());
        return ( total * 100 )/ float(people);
    };
};

int readCountryFile(ifstream &countryFile, country countries[]){
    short i = 0;
    if ( countryFile.is_open() ){
        while ( !countryFile.eof() && i < MAX_COUNTRY ){
            memset(&countries[i].infected, 0, sizeof(calendar));
            memset(&countries[i].hisopade, 0, sizeof(calendar));
            memset(&countries[i].recovered, 0, sizeof(calendar));
            memset(&countries[i].deaths, 0, sizeof(calendar));
            
            countryFile.get(countries[i].countryName, 21);
            countryFile.ignore();
            countryFile.get(countries[i].continent, 11);
            countryFile >> countries[i].people;
            countryFile.ignore();

            i++;
        }
    }
    return i;
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
}

void readDailyCountry(ifstream &countryFile, country countries[], short cantCountries){
    short index;
    if ( countryFile.is_open() ){
        while (!countryFile.eof()){
            countryStatistics cst;
            countryFile.get(cst.countryName, 21);
            countryFile.ignore(1);
            countryFile >> cst.month    >> cst.day
                        >> cst.hisopade  >> cst.infected
                        >> cst.recovered >> cst.deaths;
            countryFile.ignore(1);
            index = findByCountry(countries, cst.countryName, cantCountries);
            updateCountryData(countries[index], cst);
        }
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

void sortCountriesByTotal(country myCountries[ ], int arrayLength, string typeP){
    short k = 0;
    bool order = false;
    do {
        k++;
        order = true;
        for ( short i = 0; i < arrayLength - k; i++){;
            if ( myCountries[i].getAtt(typeP).getTotal() < myCountries[i+1].getAtt(typeP).getTotal() ){
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
             << " ------------- Cantidad de "<< typelist << " por Mes ------------- "
             << "     Cant.   " << "Porcentajes " << endl;
    file     << "Ord" << setw(20) << left << " País" << "               "
             << "Ene" << "      Feb" << "     Mar"
             << "    Abr" << "     May" << "     Jun"
             << "     Jul"
             << "     Tot." << endl;
}

void openWriteFiles(ofstream &hisopade, ofstream &recovered, ofstream &deaths, ofstream &infected){
    hisopade.open(HISOPADE_FILENAME);
    recovered.open(RECOVERED_FILENAME);
    deaths.open(DEATH_FILENAME);
    infected.open(INFECTED_FILENAME);
}

void writeRow(ofstream &recovered, short index, calendar peopleInfo, country countryData){
    recovered << setw(3)  << right << index + 1
              << " "
              << setw(20) << left << countryData.countryName
              << setw(9)  << right << countryData.people
              << "   "
              << setw(7)  << right << peopleInfo.jan
              << setw(8)  << right << peopleInfo.feb
              << setw(8)  << right << peopleInfo.mar
              << setw(8)  << right << peopleInfo.aph
              << setw(8)  << right << peopleInfo.may
              << setw(8)  << right << peopleInfo.jun
              << setw(8)  << right << peopleInfo.jul
              << setw(8)  << right << peopleInfo.getTotal()
              << "   "
              << setw(12) << left  << countryData.getPercent(peopleInfo) << endl;
}

void printFooter(ofstream &file,string typelist, float percent, int total){
    file << endl
         << endl
         << endl
         << "Cantidad Total de " << typelist
         << " a la fecha actual: " << total << endl
         << "Porcentaje  de " << typelist << ".....................: "<< percent << endl;
}

void genFiles(country countries[], short cantCountries){
    float percentH, percentR, percentI, percentD;
    int tH, tR, tI, tD;
    int MAX_LISTADO = 10;
    tH = tR = tI = tD = percentH = percentR = percentI = percentD = 0;
    ofstream hisopade, recovered, deaths, infected;
    openWriteFiles(hisopade, recovered, deaths, infected);

    printTitle(hisopade, "Hisopados");
    printTitle(recovered, "Recuperados");
    printTitle(deaths, "Muertes");
    printTitle(infected, "Infectados");

    sortCountriesByTotal(countries, cantCountries, "hisopade");
    for( short i = 0; i < MAX_LISTADO; i++ ) {
        writeRow(hisopade, i, countries[i].hisopade, countries[i]);
        percentH += countries[i].getPercent(countries[i].hisopade);
        tH += countries[i].hisopade.getTotal();
    }


    sortCountriesByTotal(countries, cantCountries, "recovered");
    for( short i = 0; i < MAX_LISTADO; i++ ) {
        writeRow(recovered, i, countries[i].recovered, countries[i]);
        percentR += countries[i].getPercent(countries[i].recovered);
        tR += countries[i].recovered.getTotal();
    }

    sortCountriesByTotal(countries, cantCountries, "infected");
    for( short i = 0; i < MAX_LISTADO; i++ ) {
        writeRow(infected, i, countries[i].infected, countries[i]);
        percentI += countries[i].getPercent(countries[i].infected);
        tI += countries[i].infected.getTotal();
    }

    sortCountriesByTotal(countries, cantCountries, "deaths");
    for( short i = 0; i < MAX_LISTADO; i++ ) {
        writeRow(deaths, i, countries[i].deaths, countries[i]);
        percentD += countries[i].getPercent(countries[i].deaths);
        tD += countries[i].deaths.getTotal();

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
    short cantCountries;

    cout << "Leyendo Archivo Pais..." << endl;
    openFiles(countryFile, statisticsFile);
 
    cantCountries = readCountryFile(countryFile, countries);
    sortCountriesByCountry(countries, cantCountries);

    cout << "Leyendo Archivo Diario..." << endl;
    readDailyCountry(statisticsFile, countries, cantCountries);
 
    cout << "Creando archivos..." << endl;
    genFiles(countries, cantCountries);


    closeFiles(countryFile, statisticsFile);
    return 0;
}
