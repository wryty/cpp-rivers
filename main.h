#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>
#include <algorithm>
#include <climits>

// Цвета для консоли
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// Стили текста
#define STYLE_BOLD    "\033[1m"
#define STYLE_UNDERLINE "\033[4m"

// Структуры данных
struct Address {
    std::string street;
    std::string city;
    std::string postal_code;
    std::string country;
};

struct Coordinates {
    double latitude;
    double longitude;
    
    Coordinates(double lat = 0, double lon = 0) : latitude(lat), longitude(lon) {}
};

struct Inspection {
    int id;
    std::string date;
    std::string inspector;
    std::string results;
    std::string recommendations;
};

struct WaterBody {
    int id;
    std::string name;
    std::string type; // "lake", "pond", "tributary"
    Coordinates coordinates;
    double area_km2;
    std::string connection_type;
};

class Enterprise {
public:
    int id;
    std::string name;
    std::string activity_type;
    std::string impact_type; // "point", "diffuse"
    Coordinates location;
    Address address;
    std::string contact_phone;
    std::string contact_email;
    
    Enterprise(int id, const std::string& name, const std::string& activity_type);
    void displayInfo() const;
    std::string toCSV() const;
    static Enterprise fromCSV(const std::string& csvLine);
};

class Region {
public:
    int id;
    std::string name;
    std::string admin_center;
    double basin_percentage;
    
    Region(int id, const std::string& name, const std::string& admin_center);
    void displayInfo() const;
    std::string toCSV() const;
    static Region fromCSV(const std::string& csvLine);
};

class Ecology {
public:
    int river_id;
    std::string water_quality; // "excellent", "good", "fair", "poor"
    int pollution_level; // 1-10 scale
    double chemical_pollution;
    double biological_pollution;
    std::string biodiversity_level; // "high", "medium", "low"
    bool protected_species;
    std::string last_inspection_date;
    std::vector<std::string> pollution_sources;
    
    Ecology(int river_id);
    void displayInfo() const;
    double calculateEcoIndex() const;
    std::string toCSV() const;
    static Ecology fromCSV(const std::string& csvLine);
};

class EconomicValue {
public:
    int river_id;
    bool water_supply;
    bool energy_generation;
    bool fishing;
    bool navigation;
    bool irrigation;
    std::vector<int> dependent_enterprises;
    double economic_benefit; // in millions
    std::string risk_assessment; // "low", "medium", "high"
    
    EconomicValue(int river_id);
    void displayInfo() const;
    double calculateTotalValue() const;
    std::string toCSV() const;
    static EconomicValue fromCSV(const std::string& csvLine);
};

class River {
public:
    int id;
    std::string name;
    double length_km;
    double basin_area_km2;
    double avg_flow_m3s;
    Coordinates source;
    Coordinates mouth;
    std::vector<int> region_ids;
    std::vector<int> enterprise_ids;
    std::vector<WaterBody> connected_water_bodies;
    
    River(int id, const std::string& name);
    void displayInfo() const;
    void addRegion(int region_id);
    void addEnterprise(int enterprise_id);
    void addWaterBody(const WaterBody& water_body);
    std::string toCSV() const;
    static River fromCSV(const std::string& csvLine);
};

// Класс для управления базой данных
class RiverDatabase {
private:
    std::vector<River> rivers;
    std::vector<Region> regions;
    std::vector<Enterprise> enterprises;
    std::vector<Ecology> ecologies;
    std::vector<EconomicValue> economic_values;
    std::vector<Inspection> inspections;
    
    int next_river_id;
    int next_region_id;
    int next_enterprise_id;
    int next_inspection_id;
    
    // Приватные методы для работы с файлами
    bool saveToCSV(const std::string& filename, const std::vector<std::string>& data);
    std::vector<std::string> loadFromCSV(const std::string& filename);
    
public:
    RiverDatabase();
    
    // CRUD операции для рек
    void addRiver(const River& river);
    bool editRiver(int id, const River& updated_river);
    bool deleteRiver(int id);
    River* findRiver(int id);
    River* findRiverByName(const std::string& name);
    
    // CRUD операции для регионов
    void addRegion(const Region& region);
    bool editRegion(int id, const Region& updated_region);
    bool deleteRegion(int id);
    Region* findRegion(int id);
    
    // CRUD операции для предприятий
    void addEnterprise(const Enterprise& enterprise);
    bool editEnterprise(int id, const Enterprise& updated_enterprise);
    bool deleteEnterprise(int id);
    Enterprise* findEnterprise(int id);
    
    // Работа с экологическими характеристиками
    void setEcology(const Ecology& ecology);
    Ecology* getEcology(int river_id);
    
    // Работа с экономическими значениями
    void setEconomicValue(const EconomicValue& economic_value);
    EconomicValue* getEconomicValue(int river_id);
    
    // Поиск и фильтрация
    std::vector<River*> findRiversByRegion(int region_id);
    Region* findRegionByName(const std::string& name);
    std::vector<River*> findRiversByWaterQuality(const std::string& quality);
    std::vector<River*> findRiversByUsage(const std::string& usage_type);
    
    // Отчеты
    void generateEcologyReport();
    void generateEconomicReport();
    void generateRegionalReport();
    void generateRiskReport();
    
    // Импорт/экспорт
    bool exportToCSV(const std::string& filename);
    bool importFromCSV(const std::string& filename);
    bool exportToJSON(const std::string& filename);
    bool importFromJSON(const std::string& filename);

    // Генерация идентификаторов
    int getNextRiverId() { return next_river_id++; }
    int getNextRegionId() { return next_region_id++; }
    int getNextEnterpriseId() { return next_enterprise_id++; }
    
    // Получение списков
    std::vector<River> getAllRivers() const { return rivers; }
    std::vector<Region> getAllRegions() const { return regions; }
    std::vector<Enterprise> getAllEnterprises() const { return enterprises; }
    
    // Статистика
    int getRiverCount() const { return rivers.size(); }
    int getRegionCount() const { return regions.size(); }
    int getEnterpriseCount() const { return enterprises.size(); }
};

// Класс для пользовательского интерфейса
class ConsoleUI {
private:
    RiverDatabase database;
    std::string current_user;
    
    void printHeader(const std::string& title);
    void printMenu();
    void printSuccess(const std::string& message);
    void printError(const std::string& message);
    void printWarning(const std::string& message);
    void printInfo(const std::string& message);
    
    // Методы ввода данных
    int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
    double getDoubleInput(const std::string& prompt, double min = -1e9, double max = 1e9);
    std::string getStringInput(const std::string& prompt);
    Coordinates getCoordinatesInput(const std::string& prompt);
    
    // Операции с реками
    void addRiver();
    void editRiver();
    void deleteRiver();
    void viewRivers();
    void searchRivers();
    
    // Операции с экологическими характеристиками
    void manageEcology();
    
    // Операции с предприятиями
    void manageEnterprises();
    
    // Операции с регионами
    void manageRegions();
    
    // Поиск и отчеты
    void viewRiversByRegion();
    void generateReports();
    
    // Импорт/экспорт
    void manageImportExport();
    
    // Вспомогательные методы
    void displayRiverDetails(int river_id);
    void populateTestData();
    
public:
    ConsoleUI();
    void run();
};

#endif
