#include "main.h"
#include <limits>

// Реализация методов класса Enterprise
Enterprise::Enterprise(int id, const std::string& name, const std::string& activity_type)
    : id(id), name(name), activity_type(activity_type) {}

void Enterprise::displayInfo() const {
    std::cout << COLOR_CYAN << "Предприятие #" << id << COLOR_RESET << std::endl;
    std::cout << "  Название: " << name << std::endl;
    std::cout << "  Тип деятельности: " << activity_type << std::endl;
    std::cout << "  Тип воздействия: " << impact_type << std::endl;
    std::cout << "  Контакты: " << contact_phone << " | " << contact_email << std::endl;
}

std::string Enterprise::toCSV() const {
    std::stringstream ss;
    ss << id << "," << name << "," << activity_type << "," << impact_type << ","
       << location.latitude << "," << location.longitude << ","
       << contact_phone << "," << contact_email;
    return ss.str();
}

Enterprise Enterprise::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    Enterprise enterprise(std::stoi(tokens[0]), tokens[1], tokens[2]);
    enterprise.impact_type = tokens[3];
    enterprise.location.latitude = std::stod(tokens[4]);
    enterprise.location.longitude = std::stod(tokens[5]);
    enterprise.contact_phone = tokens[6];
    enterprise.contact_email = tokens[7];
    
    return enterprise;
}

// Реализация методов класса Region
Region::Region(int id, const std::string& name, const std::string& admin_center)
    : id(id), name(name), admin_center(admin_center), basin_percentage(0) {}

void Region::displayInfo() const {
    std::cout << COLOR_GREEN << "Регион #" << id << COLOR_RESET << std::endl;
    std::cout << "  Название: " << name << std::endl;
    std::cout << "  Административный центр: " << admin_center << std::endl;
    std::cout << "  % территории бассейна: " << basin_percentage << "%" << std::endl;
}

std::string Region::toCSV() const {
    std::stringstream ss;
    ss << id << "," << name << "," << admin_center << "," << basin_percentage;
    return ss.str();
}

Region Region::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    Region region(std::stoi(tokens[0]), tokens[1], tokens[2]);
    region.basin_percentage = std::stod(tokens[3]);
    
    return region;
}

// Реализация методов класса Ecology
Ecology::Ecology(int river_id) : river_id(river_id), pollution_level(1), 
    chemical_pollution(0), biological_pollution(0), protected_species(false) {}

void Ecology::displayInfo() const {
    std::cout << COLOR_YELLOW << "Экологическая характеристика для реки #" << river_id << COLOR_RESET << std::endl;
    std::cout << "  Качество воды: " << water_quality << std::endl;
    std::cout << "  Уровень загрязнения: " << pollution_level << "/10" << std::endl;
    std::cout << "  Химическое загрязнение: " << chemical_pollution << " мг/л" << std::endl;
    std::cout << "  Биологическое загрязнение: " << biological_pollution << " мг/л" << std::endl;
    std::cout << "  Биоразнообразие: " << biodiversity_level << std::endl;
    std::cout << "  Охраняемые виды: " << (protected_species ? "да" : "нет") << std::endl;
    std::cout << "  Дата последнего обследования: " << last_inspection_date << std::endl;
}

double Ecology::calculateEcoIndex() const {
    double index = 10.0;
    
    // Ухудшение индекса в зависимости от уровня загрязнения
    index -= (pollution_level - 1) * 0.5;
    index -= chemical_pollution * 0.1;
    index -= biological_pollution * 0.1;
    
    // Улучшение индекса за биоразнообразие
    if (biodiversity_level == "high") index += 2;
    else if (biodiversity_level == "medium") index += 1;
    
    return std::max(0.0, std::min(10.0, index));
}

std::string Ecology::toCSV() const {
    std::stringstream ss;
    ss << river_id << "," << water_quality << "," << pollution_level << ","
       << chemical_pollution << "," << biological_pollution << ","
       << biodiversity_level << "," << protected_species << ","
       << last_inspection_date;
    return ss.str();
}

Ecology Ecology::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    Ecology ecology(std::stoi(tokens[0]));
    ecology.water_quality = tokens[1];
    ecology.pollution_level = std::stoi(tokens[2]);
    ecology.chemical_pollution = std::stod(tokens[3]);
    ecology.biological_pollution = std::stod(tokens[4]);
    ecology.biodiversity_level = tokens[5];
    ecology.protected_species = (tokens[6] == "1");
    ecology.last_inspection_date = tokens[7];
    
    return ecology;
}

// Реализация методов класса EconomicValue
EconomicValue::EconomicValue(int river_id) : river_id(river_id), 
    water_supply(false), energy_generation(false), fishing(false),
    navigation(false), irrigation(false), economic_benefit(0) {}

void EconomicValue::displayInfo() const {
    std::cout << COLOR_MAGENTA << "Народнохозяйственное значение для реки #" << river_id << COLOR_RESET << std::endl;
    std::cout << "  Использование: ";
    if (water_supply) std::cout << "водоснабжение ";
    if (energy_generation) std::cout << "энергетика ";
    if (fishing) std::cout << "рыболовство ";
    if (navigation) std::cout << "судоходство ";
    if (irrigation) std::cout << "орошение";
    std::cout << std::endl;
    std::cout << "  Экономическая польза: " << economic_benefit << " млн. руб." << std::endl;
    std::cout << "  Оценка рисков: " << risk_assessment << std::endl;
}

double EconomicValue::calculateTotalValue() const {
    double value = economic_benefit;
    
    // Дополнительные бонусы за разные виды использования
    if (water_supply) value += 50;
    if (energy_generation) value += 100;
    if (navigation) value += 75;
    
    return value;
}

std::string EconomicValue::toCSV() const {
    std::stringstream ss;
    ss << river_id << "," << water_supply << "," << energy_generation << ","
       << fishing << "," << navigation << "," << irrigation << ","
       << economic_benefit << "," << risk_assessment;
    return ss.str();
}

EconomicValue EconomicValue::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    EconomicValue economic_value(std::stoi(tokens[0]));
    economic_value.water_supply = (tokens[1] == "1");
    economic_value.energy_generation = (tokens[2] == "1");
    economic_value.fishing = (tokens[3] == "1");
    economic_value.navigation = (tokens[4] == "1");
    economic_value.irrigation = (tokens[5] == "1");
    economic_value.economic_benefit = std::stod(tokens[6]);
    economic_value.risk_assessment = tokens[7];
    
    return economic_value;
}

// Реализация методов класса River
River::River(int id, const std::string& name) : id(id), name(name), 
    length_km(0), basin_area_km2(0), avg_flow_m3s(0) {}

void River::displayInfo() const {
    std::cout << COLOR_BLUE << "Река #" << id << ": " << name << COLOR_RESET << std::endl;
    std::cout << "  Длина: " << length_km << " км" << std::endl;
    std::cout << "  Площадь бассейна: " << basin_area_km2 << " км²" << std::endl;
    std::cout << "  Средний расход воды: " << avg_flow_m3s << " м³/с" << std::endl;
    std::cout << "  Координаты истока: " << source.latitude << ", " << source.longitude << std::endl;
    std::cout << "  Координаты устья: " << mouth.latitude << ", " << mouth.longitude << std::endl;
    std::cout << "  Количество регионов: " << region_ids.size() << std::endl;
    std::cout << "  Количество предприятий: " << enterprise_ids.size() << std::endl;
    std::cout << "  Связанные водоёмы: " << connected_water_bodies.size() << std::endl;
}

void River::addRegion(int region_id) {
    region_ids.push_back(region_id);
}

void River::addEnterprise(int enterprise_id) {
    enterprise_ids.push_back(enterprise_id);
}

void River::addWaterBody(const WaterBody& water_body) {
    connected_water_bodies.push_back(water_body);
}

std::string River::toCSV() const {
    std::stringstream ss;
    ss << id << "," << name << "," << length_km << "," << basin_area_km2 << ","
       << avg_flow_m3s << "," << source.latitude << "," << source.longitude << ","
       << mouth.latitude << "," << mouth.longitude;
    
    // Добавляем регионы
    ss << ",";
    for (size_t i = 0; i < region_ids.size(); ++i) {
        ss << region_ids[i];
        if (i < region_ids.size() - 1) ss << ";";
    }
    
    // Добавляем предприятия
    ss << ",";
    for (size_t i = 0; i < enterprise_ids.size(); ++i) {
        ss << enterprise_ids[i];
        if (i < enterprise_ids.size() - 1) ss << ";";
    }
    
    return ss.str();
}

River River::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    River river(std::stoi(tokens[0]), tokens[1]);
    river.length_km = std::stod(tokens[2]);
    river.basin_area_km2 = std::stod(tokens[3]);
    river.avg_flow_m3s = std::stod(tokens[4]);
    river.source.latitude = std::stod(tokens[5]);
    river.source.longitude = std::stod(tokens[6]);
    river.mouth.latitude = std::stod(tokens[7]);
    river.mouth.longitude = std::stod(tokens[8]);
    
    // Парсинг регионов
    std::stringstream regions_ss(tokens[9]);
    while (std::getline(regions_ss, token, ';')) {
        if (!token.empty()) {
            river.region_ids.push_back(std::stoi(token));
        }
    }
    
    // Парсинг предприятий
    std::stringstream enterprises_ss(tokens[10]);
    while (std::getline(enterprises_ss, token, ';')) {
        if (!token.empty()) {
            river.enterprise_ids.push_back(std::stoi(token));
        }
    }
    
    return river;
}

// Реализация методов класса RiverDatabase
RiverDatabase::RiverDatabase() : next_river_id(1), next_region_id(1), 
    next_enterprise_id(1), next_inspection_id(1) {}

void RiverDatabase::addRiver(const River& river) {
    rivers.push_back(river);
    if (river.id >= next_river_id) {
        next_river_id = river.id + 1;
    }
}

bool RiverDatabase::editRiver(int id, const River& updated_river) {
    for (auto& river : rivers) {
        if (river.id == id) {
            river = updated_river;
            return true;
        }
    }
    return false;
}

bool RiverDatabase::deleteRiver(int id) {
    auto it = std::remove_if(rivers.begin(), rivers.end(),
        [id](const River& river) { return river.id == id; });
    
    if (it != rivers.end()) {
        rivers.erase(it, rivers.end());
        
        // Также удаляем связанные экологические и экономические данные
        auto eco_it = std::remove_if(ecologies.begin(), ecologies.end(),
            [id](const Ecology& eco) { return eco.river_id == id; });
        ecologies.erase(eco_it, ecologies.end());
        
        auto econ_it = std::remove_if(economic_values.begin(), economic_values.end(),
            [id](const EconomicValue& econ) { return econ.river_id == id; });
        economic_values.erase(econ_it, economic_values.end());
        
        return true;
    }
    return false;
}

River* RiverDatabase::findRiver(int id) {
    for (auto& river : rivers) {
        if (river.id == id) {
            return &river;
        }
    }
    return nullptr;
}

River* RiverDatabase::findRiverByName(const std::string& name) {
    for (auto& river : rivers) {
        if (river.name == name) {
            return &river;
        }
    }
    return nullptr;
}

void RiverDatabase::addRegion(const Region& region) {
    regions.push_back(region);
    if (region.id >= next_region_id) {
        next_region_id = region.id + 1;
    }
}

bool RiverDatabase::editRegion(int id, const Region& updated_region) {
    for (auto& region : regions) {
        if (region.id == id) {
            region = updated_region;
            return true;
        }
    }
    return false;
}

bool RiverDatabase::deleteRegion(int id) {
    auto it = std::remove_if(regions.begin(), regions.end(),
        [id](const Region& region) { return region.id == id; });
    
    if (it != regions.end()) {
        regions.erase(it, regions.end());
        return true;
    }
    return false;
}

Region* RiverDatabase::findRegion(int id) {
    for (auto& region : regions) {
        if (region.id == id) {
            return &region;
        }
    }
    return nullptr;
}

Region* RiverDatabase::findRegionByName(const std::string& name) {
    for (auto& region : regions) {
        if (region.name == name) return &region;
    }
    return nullptr;
}

void RiverDatabase::addEnterprise(const Enterprise& enterprise) {
    enterprises.push_back(enterprise);
    if (enterprise.id >= next_enterprise_id) {
        next_enterprise_id = enterprise.id + 1;
    }
}

bool RiverDatabase::editEnterprise(int id, const Enterprise& updated_enterprise) {
    for (auto& enterprise : enterprises) {
        if (enterprise.id == id) {
            enterprise = updated_enterprise;
            return true;
        }
    }
    return false;
}

bool RiverDatabase::deleteEnterprise(int id) {
    auto it = std::remove_if(enterprises.begin(), enterprises.end(),
        [id](const Enterprise& enterprise) { return enterprise.id == id; });
    
    if (it != enterprises.end()) {
        enterprises.erase(it, enterprises.end());
        return true;
    }
    return false;
}

Enterprise* RiverDatabase::findEnterprise(int id) {
    for (auto& enterprise : enterprises) {
        if (enterprise.id == id) {
            return &enterprise;
        }
    }
    return nullptr;
}

void RiverDatabase::setEcology(const Ecology& ecology) {
    // Удаляем старую запись, если есть
    auto it = std::remove_if(ecologies.begin(), ecologies.end(),
        [&ecology](const Ecology& eco) { return eco.river_id == ecology.river_id; });
    ecologies.erase(it, ecologies.end());
    
    // Добавляем новую
    ecologies.push_back(ecology);
}

Ecology* RiverDatabase::getEcology(int river_id) {
    for (auto& ecology : ecologies) {
        if (ecology.river_id == river_id) {
            return &ecology;
        }
    }
    return nullptr;
}

void RiverDatabase::setEconomicValue(const EconomicValue& economic_value) {
    // Удаляем старую запись, если есть
    auto it = std::remove_if(economic_values.begin(), economic_values.end(),
        [&economic_value](const EconomicValue& econ) { 
            return econ.river_id == economic_value.river_id; 
        });
    economic_values.erase(it, economic_values.end());
    
    // Добавляем новую
    economic_values.push_back(economic_value);
}

EconomicValue* RiverDatabase::getEconomicValue(int river_id) {
    for (auto& economic_value : economic_values) {
        if (economic_value.river_id == river_id) {
            return &economic_value;
        }
    }
    return nullptr;
}

std::vector<River*> RiverDatabase::findRiversByRegion(int region_id) {
    std::vector<River*> result;
    for (auto& river : rivers) {
        if (std::find(river.region_ids.begin(), river.region_ids.end(), region_id) != river.region_ids.end()) {
            result.push_back(&river);
        }
    }
    return result;
}

std::vector<River*> RiverDatabase::findRiversByWaterQuality(const std::string& quality) {
    std::vector<River*> result;
    for (auto& ecology : ecologies) {
        if (ecology.water_quality == quality) {
            River* river = findRiver(ecology.river_id);
            if (river) {
                result.push_back(river);
            }
        }
    }
    return result;
}

void RiverDatabase::generateEcologyReport() {
    std::cout << COLOR_YELLOW << STYLE_BOLD << "=== ОТЧЕТ ПО ЭКОЛОГИЧЕСКОМУ СОСТОЯНИЮ ===" << COLOR_RESET << std::endl;
    
    for (const auto& ecology : ecologies) {
        River* river = findRiver(ecology.river_id);
        if (river) {
            std::cout << "Река: " << river->name << std::endl;
            std::cout << "  Качество воды: " << ecology.water_quality << std::endl;
            std::cout << "  Уровень загрязнения: " << ecology.pollution_level << "/10" << std::endl;
            std::cout << "  Эко-индекс: " << std::fixed << std::setprecision(2) << ecology.calculateEcoIndex() << "/10" << std::endl;
            std::cout << "  Дата обследования: " << ecology.last_inspection_date << std::endl;
            std::cout << "---" << std::endl;
        }
    }
}

void RiverDatabase::generateEconomicReport() {
    std::cout << COLOR_MAGENTA << STYLE_BOLD << "=== ОТЧЕТ ПО НАРОДНОХОЗЯЙСТВЕННОМУ ЗНАЧЕНИЮ ===" << COLOR_RESET << std::endl;
    
    for (const auto& economic_value : economic_values) {
        River* river = findRiver(economic_value.river_id);
        if (river && economic_value.calculateTotalValue() > 0) {
            std::cout << "Река: " << river->name << std::endl;
            std::cout << "  Общая ценность: " << std::fixed << std::setprecision(2) 
                     << economic_value.calculateTotalValue() << " млн. руб." << std::endl;
            std::cout << "  Использование: ";
            if (economic_value.water_supply) std::cout << "водоснабжение ";
            if (economic_value.energy_generation) std::cout << "энергетика ";
            if (economic_value.fishing) std::cout << "рыболовство ";
            if (economic_value.navigation) std::cout << "судоходство ";
            if (economic_value.irrigation) std::cout << "орошение";
            std::cout << std::endl;
            std::cout << "  Оценка рисков: " << economic_value.risk_assessment << std::endl;
            std::cout << "---" << std::endl;
        }
    }
}

void RiverDatabase::generateRegionalReport() {
    std::cout << COLOR_GREEN << STYLE_BOLD << "=== СВОДНЫЙ ОТЧЕТ ПО РЕГИОНАМ ===" << COLOR_RESET << std::endl;
    
    for (const auto& region : regions) {
        auto region_rivers = findRiversByRegion(region.id);
        if (!region_rivers.empty()) {
            std::cout << "Регион: " << region.name << std::endl;
            std::cout << "  Количество рек: " << region_rivers.size() << std::endl;
            
            double total_length = 0;
            double total_area = 0;
            
            for (const auto& river : region_rivers) {
                total_length += river->length_km;
                total_area += river->basin_area_km2;
            }
            
            std::cout << "  Средняя длина рек: " << std::fixed << std::setprecision(2) 
                     << total_length / region_rivers.size() << " км" << std::endl;
            std::cout << "  Средняя площадь бассейна: " << std::fixed << std::setprecision(2)
                     << total_area / region_rivers.size() << " км²" << std::endl;
            std::cout << "---" << std::endl;
        }
    }
}

void RiverDatabase::generateRiskReport() {
    std::cout << COLOR_RED << STYLE_BOLD << "=== ОТЧЕТ ПО РИСКАМ ЗАГРЯЗНЕНИЯ ===" << COLOR_RESET << std::endl;
    
    for (const auto& ecology : ecologies) {
        if (ecology.pollution_level >= 7) { // Высокий уровень загрязнения
            River* river = findRiver(ecology.river_id);
            if (river) {
                std::cout << "ВЫСОКИЙ РИСК: " << river->name << std::endl;
                std::cout << "  Уровень загрязнения: " << ecology.pollution_level << "/10" << std::endl;
                std::cout << "  Качество воды: " << ecology.water_quality << std::endl;
                
                // Находим предприятия в этой реке
                std::cout << "  Предприятия на реке: ";
                for (int enterprise_id : river->enterprise_ids) {
                    Enterprise* enterprise = findEnterprise(enterprise_id);
                    if (enterprise) {
                        std::cout << enterprise->name << " (" << enterprise->activity_type << ") ";
                    }
                }
                std::cout << std::endl << "---" << std::endl;
            }
        }
    }
}

bool RiverDatabase::exportToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Экспорт рек
    file << "#Rivers" << std::endl;
    for (const auto& river : rivers) {
        file << river.toCSV() << std::endl;
    }
    
    // Экспорт регионов
    file << "#Regions" << std::endl;
    for (const auto& region : regions) {
        file << region.toCSV() << std::endl;
    }
    
    // Экспорт предприятий
    file << "#Enterprises" << std::endl;
    for (const auto& enterprise : enterprises) {
        file << enterprise.toCSV() << std::endl;
    }
    
    // Экспорт экологических данных
    file << "#Ecology" << std::endl;
    for (const auto& ecology : ecologies) {
        file << ecology.toCSV() << std::endl;
    }
    
    // Экспорт экономических данных
    file << "#Economic" << std::endl;
    for (const auto& economic_value : economic_values) {
        file << economic_value.toCSV() << std::endl;
    }
    
    file.close();
    return true;
}

// Реализация методов класса ConsoleUI
ConsoleUI::ConsoleUI() : current_user("Администратор") {}

void ConsoleUI::printHeader(const std::string& title) {
    std::cout << std::endl;
    std::cout << COLOR_CYAN << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║" << STYLE_BOLD << std::setw(58) << std::left << (" " + title) << COLOR_RESET << COLOR_CYAN << "║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << COLOR_RESET << std::endl;
}

void ConsoleUI::printMenu() {
    printHeader("СИСТЕМА УЧЕТА РЕК");
    
    std::cout << COLOR_GREEN << "Текущий пользователь: " << current_user << COLOR_RESET << std::endl;
    std::cout << COLOR_YELLOW << "Статистика: " << database.getRiverCount() << " рек, " 
              << database.getRegionCount() << " регионов, " 
              << database.getEnterpriseCount() << " предприятий" << COLOR_RESET << std::endl;
    std::cout << std::endl;
    
    std::cout << COLOR_WHITE << STYLE_BOLD << "ГЛАВНОЕ МЕНЮ:" << COLOR_RESET << std::endl;
    std::cout << COLOR_BLUE << " 1" << COLOR_RESET << " - Добавить реку" << std::endl;
    std::cout << COLOR_BLUE << " 2" << COLOR_RESET << " - Редактировать реку" << std::endl;
    std::cout << COLOR_BLUE << " 3" << COLOR_RESET << " - Удалить реку" << std::endl;
    std::cout << COLOR_BLUE << " 4" << COLOR_RESET << " - Управление экологическими характеристиками" << std::endl;
    std::cout << COLOR_BLUE << " 5" << COLOR_RESET << " - Управление предприятиями" << std::endl;
    std::cout << COLOR_BLUE << " 6" << COLOR_RESET << " - Управление регионами" << std::endl;
    std::cout << COLOR_BLUE << " 7" << COLOR_RESET << " - Просмотр рек по региону" << std::endl;
    std::cout << COLOR_BLUE << " 8" << COLOR_RESET << " - Поиск рек" << std::endl;
    std::cout << COLOR_BLUE << " 9" << COLOR_RESET << " - Генерация отчетов" << std::endl;
    std::cout << COLOR_BLUE << "10" << COLOR_RESET << " - Экспорт данных" << std::endl;
    std::cout << COLOR_BLUE << "11" << COLOR_RESET << " - Просмотр всех рек" << std::endl;
    std::cout << COLOR_BLUE << "12" << COLOR_RESET << " - Загрузить тестовые данные" << std::endl;
    std::cout << COLOR_RED << " 0" << COLOR_RESET << " - Выход" << std::endl;
    std::cout << std::endl;
}

void ConsoleUI::printSuccess(const std::string& message) {
    std::cout << COLOR_GREEN << "✓ " << message << COLOR_RESET << std::endl;
}

void ConsoleUI::printError(const std::string& message) {
    std::cout << COLOR_RED << "✗ Ошибка: " << message << COLOR_RESET << std::endl;
}

void ConsoleUI::printWarning(const std::string& message) {
    std::cout << COLOR_YELLOW << "⚠ " << message << COLOR_RESET << std::endl;
}

void ConsoleUI::printInfo(const std::string& message) {
    std::cout << COLOR_CYAN << "ℹ " << message << COLOR_RESET << std::endl;
}

int ConsoleUI::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Некорректный ввод. Пожалуйста, введите целое число.");
        } else if (value < min || value > max) {
            printError("Значение вне допустимого диапазона.");
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double ConsoleUI::getDoubleInput(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Некорректный ввод. Пожалуйста, введите число.");
        } else if (value < min || value > max) {
            printError("Значение вне допустимого диапазона.");
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::string ConsoleUI::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin >> std::ws, value);
    return value;
}


Coordinates ConsoleUI::getCoordinatesInput(const std::string& prompt) {
    std::cout << prompt << std::endl;
    double lat = getDoubleInput("  Широта: ");
    double lon = getDoubleInput("  Долгота: ");
    return Coordinates(lat, lon);
}

void ConsoleUI::addRiver() {
    printHeader("ДОБАВЛЕНИЕ НОВОЙ РЕКИ");
    
    std::string name = getStringInput("Название реки: ");
    if (name.empty()) {
        printError("Название не может быть пустым.");
        return;
    }
    
    // Создаем новую реку
    River river(database.getAllRivers().size() + 1, name);
    
    river.length_km = getDoubleInput("Длина реки (км): ", 0.1, 10000.0);
    river.basin_area_km2 = getDoubleInput("Площадь бассейна (км²): ", 0.1, 1000000.0);
    river.avg_flow_m3s = getDoubleInput("Средний расход воды (м³/с): ", 0.1, 100000.0);
    
    std::cout << "Координаты истока:" << std::endl;
    river.source = getCoordinatesInput("");
    
    std::cout << "Координаты устья:" << std::endl;
    river.mouth = getCoordinatesInput("");
    const auto regions = database.getAllRegions();
    if (regions.empty()) {
        printWarning("В базе нет регионов. Сначала добавьте регионы (меню: 6).");
    } else {
        std::cout << "Выберите регионы для реки (введите ID, 0 - закончить):\n";
        for (const auto& r : regions) {
            std::cout << "  " << r.id << " - " << r.name << "\n";
        }

        while (true) {
            int rid = getIntInput("ID региона (0 - завершить): ", 0, 1000000);
            if (rid == 0) break;

            // проверка что регион существует
            if (!database.findRegion(rid)) {
                printError("Регион с таким ID не найден.");
                continue;
            }

            // защита от дублей
            if (std::find(river.region_ids.begin(), river.region_ids.end(), rid) == river.region_ids.end()) {
                river.addRegion(rid);
            } else {
                printWarning("Этот регион уже добавлен.");
            }
        }
    }
    
    database.addRiver(river);
    printSuccess("Река '" + name + "' успешно добавлена!");
}

void ConsoleUI::editRiver() {
    printHeader("РЕДАКТИРОВАНИЕ РЕКИ");
    
    viewRivers();
    
    if (database.getRiverCount() == 0) {
        return;
    }
    
    int river_id = getIntInput("Введите ID реки для редактирования: ", 1, database.getRiverCount());
    
    River* river = database.findRiver(river_id);
    if (!river) {
        printError("Река с указанным ID не найдена.");
        return;
    }
    
    displayRiverDetails(river_id);
    
    std::cout << "Введите новые данные (оставьте пустым для сохранения текущего значения):" << std::endl;
    
    std::string new_name = getStringInput("Новое название [" + river->name + "]: ");
    if (!new_name.empty()) {
        river->name = new_name;
    }
    
    std::string new_length = getStringInput("Новая длина [" + std::to_string(river->length_km) + "]: ");
    if (!new_length.empty()) {
        river->length_km = std::stod(new_length);
    }
    
    printSuccess("Данные реки обновлены!");
}

void ConsoleUI::deleteRiver() {
    printHeader("УДАЛЕНИЕ РЕКИ");
    
    viewRivers();
    
    if (database.getRiverCount() == 0) {
        return;
    }
    
    int river_id = getIntInput("Введите ID реки для удаления: ", 1, database.getRiverCount());
    
    River* river = database.findRiver(river_id);
    if (!river) {
        printError("Река с указанным ID не найдена.");
        return;
    }
    
    std::string confirm = getStringInput("Вы уверены, что хотите удалить реку '" + river->name + "'? (y/N): ");
    if (confirm == "y" || confirm == "Y") {
        if (database.deleteRiver(river_id)) {
            printSuccess("Река успешно удалена!");
        } else {
            printError("Ошибка при удалении реки.");
        }
    } else {
        printInfo("Удаление отменено.");
    }
}

void ConsoleUI::viewRivers() {
    printHeader("СПИСОК ВСЕХ РЕК");
    
    const auto& rivers = database.getAllRivers();
    if (rivers.empty()) {
        printInfo("В базе данных нет рек.");
        return;
    }
    
    for (const auto& river : rivers) {
        river.displayInfo();
        std::cout << std::endl;
    }
}

void ConsoleUI::searchRivers() {
    printHeader("ПОИСК РЕК");
    
    std::cout << "Критерии поиска:" << std::endl;
    std::cout << COLOR_BLUE << "1" << COLOR_RESET << " - По названию" << std::endl;
    std::cout << COLOR_BLUE << "2" << COLOR_RESET << " - По качеству воды" << std::endl;
    std::cout << COLOR_BLUE << "3" << COLOR_RESET << " - По использованию" << std::endl;
    
    int choice = getIntInput("Выберите критерий поиска: ", 1, 3);
    
    switch (choice) {
        case 1: {
            std::string name = getStringInput("Введите название реки: ");
            River* river = database.findRiverByName(name);
            if (river) {
                displayRiverDetails(river->id);
            } else {
                printError("Река с названием '" + name + "' не найдена.");
            }
            break;
        }
        case 2: {
            std::cout << "Качество воды:" << std::endl;
            std::cout << "1 - Отличное" << std::endl;
            std::cout << "2 - Хорошее" << std::endl;
            std::cout << "3 - Удовлетворительное" << std::endl;
            std::cout << "4 - Плохое" << std::endl;
            
            int quality_choice = getIntInput("Выберите качество воды: ", 1, 4);
            std::string quality;
            switch (quality_choice) {
                case 1: quality = "excellent"; break;
                case 2: quality = "good"; break;
                case 3: quality = "fair"; break;
                case 4: quality = "poor"; break;
            }
            
            auto rivers = database.findRiversByWaterQuality(quality);
            if (rivers.empty()) {
                printInfo("Реки с указанным качеством воды не найдены.");
            } else {
                std::cout << "Найдено рек: " << rivers.size() << std::endl;
                for (const auto& river : rivers) {
                    river->displayInfo();
                    std::cout << std::endl;
                }
            }
            break;
        }
    }
}

void ConsoleUI::manageEcology() {
    printHeader("УПРАВЛЕНИЕ ЭКОЛОГИЧЕСКИМИ ХАРАКТЕРИСТИКАМИ");
    
    viewRivers();
    
    if (database.getRiverCount() == 0) {
        return;
    }
    
    int river_id = getIntInput("Введите ID реки: ", 1, database.getRiverCount());
    
    River* river = database.findRiver(river_id);
    if (!river) {
        printError("Река с указанным ID не найдена.");
        return;
    }
    
    Ecology* existing_ecology = database.getEcology(river_id);
    Ecology ecology(river_id);
    
    if (existing_ecology) {
        ecology = *existing_ecology;
        std::cout << "Текущие данные:" << std::endl;
        existing_ecology->displayInfo();
        std::cout << std::endl;
    }
    
    std::cout << "Введите новые данные:" << std::endl;
    
    std::cout << "Качество воды:" << std::endl;
    std::cout << "1 - Отличное" << std::endl;
    std::cout << "2 - Хорошее" << std::endl;
    std::cout << "3 - Удовлетворительное" << std::endl;
    std::cout << "4 - Плохое" << std::endl;
    
    int quality_choice = getIntInput("Выберите качество воды: ", 1, 4);
    switch (quality_choice) {
        case 1: ecology.water_quality = "excellent"; break;
        case 2: ecology.water_quality = "good"; break;
        case 3: ecology.water_quality = "fair"; break;
        case 4: ecology.water_quality = "poor"; break;
    }
    
    ecology.pollution_level = getIntInput("Уровень загрязнения (1-10): ", 1, 10);
    ecology.chemical_pollution = getDoubleInput("Химическое загрязнение (мг/л): ", 0, 1000);
    ecology.biological_pollution = getDoubleInput("Биологическое загрязнение (мг/л): ", 0, 1000);
    
    std::cout << "Уровень биоразнообразия:" << std::endl;
    std::cout << "1 - Высокий" << std::endl;
    std::cout << "2 - Средний" << std::endl;
    std::cout << "3 - Низкий" << std::endl;
    
    int bio_choice = getIntInput("Выберите уровень биоразнообразия: ", 1, 3);
    switch (bio_choice) {
        case 1: ecology.biodiversity_level = "high"; break;
        case 2: ecology.biodiversity_level = "medium"; break;
        case 3: ecology.biodiversity_level = "low"; break;
    }
    
    std::string protected_input = getStringInput("Наличие охраняемых видов (y/n): ");
    ecology.protected_species = (protected_input == "y" || protected_input == "Y");
    
    ecology.last_inspection_date = getStringInput("Дата последнего обследования: ");
    
    database.setEcology(ecology);
    printSuccess("Экологические характеристики обновлены!");
}

void ConsoleUI::manageEnterprises() {
    printHeader("УПРАВЛЕНИЕ ПРЕДПРИЯТИЯМИ");
    
    std::cout << "Опции:" << std::endl;
    std::cout << COLOR_BLUE << "1" << COLOR_RESET << " - Добавить предприятие" << std::endl;
    std::cout << COLOR_BLUE << "2" << COLOR_RESET << " - Просмотреть все предприятия" << std::endl;
    
    int choice = getIntInput("Выберите опцию: ", 1, 2);
    
    if (choice == 1) {
        std::string name = getStringInput("Название предприятия: ");
        std::string activity_type = getStringInput("Тип деятельности: ");
        
        Enterprise enterprise(database.getAllEnterprises().size() + 1, name, activity_type);
        
        std::cout << "Тип воздействия:" << std::endl;
        std::cout << "1 - Точечный" << std::endl;
        std::cout << "2 - Рассеянный" << std::endl;
        
        int impact_choice = getIntInput("Выберите тип воздействия: ", 1, 2);
        enterprise.impact_type = (impact_choice == 1) ? "point" : "diffuse";
        
        std::cout << "Координаты расположения:" << std::endl;
        enterprise.location = getCoordinatesInput("");
        
        enterprise.contact_phone = getStringInput("Контактный телефон: ");
        enterprise.contact_email = getStringInput("Контактный email: ");
        
        database.addEnterprise(enterprise);
        printSuccess("Предприятие '" + name + "' успешно добавлено!");
    } else {
        const auto& enterprises = database.getAllEnterprises();
        if (enterprises.empty()) {
            printInfo("В базе данных нет предприятий.");
        } else {
            for (const auto& enterprise : enterprises) {
                enterprise.displayInfo();
                std::cout << std::endl;
            }
        }
    }
}

void ConsoleUI::manageRegions() {
    printHeader("УПРАВЛЕНИЕ РЕГИОНАМИ");
    
    std::cout << "Опции:" << std::endl;
    std::cout << COLOR_BLUE << "1" << COLOR_RESET << " - Добавить регион" << std::endl;
    std::cout << COLOR_BLUE << "2" << COLOR_RESET << " - Просмотреть все регионы" << std::endl;
    
    int choice = getIntInput("Выберите опцию: ", 1, 2);
    
    if (choice == 1) {
        std::string name = getStringInput("Название региона: ");
        std::string admin_center = getStringInput("Административный центр: ");
        
        Region region(database.getAllRegions().size() + 1, name, admin_center);
        region.basin_percentage = getDoubleInput("Процент территории бассейна в регионе: ", 0, 100);
        
        database.addRegion(region);
        printSuccess("Регион '" + name + "' успешно добавлен!");
    } else {
        const auto& regions = database.getAllRegions();
        if (regions.empty()) {
            printInfo("В базе данных нет регионов.");
        } else {
            for (const auto& region : regions) {
                region.displayInfo();
                std::cout << std::endl;
            }
        }
    }
}

void ConsoleUI::viewRiversByRegion() {
    printHeader("ПРОСМОТР РЕК ПО РЕГИОНУ");
    
    const auto& regions = database.getAllRegions();
    if (regions.empty()) {
        printInfo("В базе данных нет регионов.");
        return;
    }
    
    for (const auto& region : regions) {
        region.displayInfo();
    }
    
    std::string input = getStringInput("Введите ID региона или название: ");

    int region_id = 0;
    Region* region_ptr = nullptr;

    if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
        region_id = std::stoi(input);
        region_ptr = database.findRegion(region_id);
    } else {
        region_ptr = database.findRegionByName(input);
    }

    if (!region_ptr) {
        printError("Регион не найден.");
        return;
    }

    auto rivers = database.findRiversByRegion(region_ptr->id);
    if (rivers.empty()) {
        printInfo("В указанном регионе нет рек.");
    } else {
        std::cout << "Реки в регионе:" << std::endl;
        for (const auto& river : rivers) {
            river->displayInfo();
            std::cout << std::endl;
        }
    }
}

void ConsoleUI::generateReports() {
    printHeader("ГЕНЕРАЦИЯ ОТЧЕТОВ");
    
    std::cout << "Типы отчетов:" << std::endl;
    std::cout << COLOR_BLUE << "1" << COLOR_RESET << " - Отчет по экологическому состоянию" << std::endl;
    std::cout << COLOR_BLUE << "2" << COLOR_RESET << " - Отчет по народнохозяйственному значению" << std::endl;
    std::cout << COLOR_BLUE << "3" << COLOR_RESET << " - Сводный отчет по регионам" << std::endl;
    std::cout << COLOR_BLUE << "4" << COLOR_RESET << " - Отчет по рискам загрязнения" << std::endl;
    
    int choice = getIntInput("Выберите тип отчета: ", 1, 4);
    
    switch (choice) {
        case 1:
            database.generateEcologyReport();
            break;
        case 2:
            database.generateEconomicReport();
            break;
        case 3:
            database.generateRegionalReport();
            break;
        case 4:
            database.generateRiskReport();
            break;
    }
}

void ConsoleUI::manageImportExport() {
    printHeader("ЭКСПОРТ ДАННЫХ");
    
    std::cout << "Опции:" << std::endl;
    std::cout << COLOR_BLUE << "1" << COLOR_RESET << " - Экспорт в CSV" << std::endl;
    
    int choice = getIntInput("Выберите опцию: ", 1, 2);
    
    if (choice == 1) {
        std::string filename = getStringInput("Введите имя файла для экспорта: ");
        if (database.exportToCSV(filename)) {
            printSuccess("Данные успешно экспортированы в файл '" + filename + "'");
        } else {
            printError("Ошибка при экспорте данных.");
        }
    }
}

void ConsoleUI::displayRiverDetails(int river_id) {
    River* river = database.findRiver(river_id);
    if (!river) {
        printError("Река не найдена.");
        return;
    }
    
    printHeader("ДЕТАЛЬНАЯ ИНФОРМАЦИЯ О РЕКЕ: " + river->name);
    river->displayInfo();
    
    // Показываем экологические характеристики
    Ecology* ecology = database.getEcology(river_id);
    if (ecology) {
        std::cout << std::endl;
        ecology->displayInfo();
    }
    
    // Показываем экономическое значение
    EconomicValue* economic_value = database.getEconomicValue(river_id);
    if (economic_value) {
        std::cout << std::endl;
        economic_value->displayInfo();
    }
}

void ConsoleUI::populateTestData() {
    printHeader("ЗАГРУЗКА ТЕСТОВЫХ ДАННЫХ");
    
    // Добавляем регионы
    Region region1(1, "Московская область", "Москва");
    region1.basin_percentage = 15.5;
    database.addRegion(region1);
    
    Region region2(2, "Тверская область", "Тверь");
    region2.basin_percentage = 22.3;
    database.addRegion(region2);
    
    // Добавляем предприятия
    Enterprise enterprise1(1, "Мосводоканал", "коммунальные службы");
    enterprise1.impact_type = "point";
    enterprise1.location = Coordinates(55.7558, 37.6173);
    enterprise1.contact_phone = "+7-495-123-45-67";
    enterprise1.contact_email = "info@mosvodokanal.ru";
    database.addEnterprise(enterprise1);
    
    Enterprise enterprise2(2, "Завод Сталь", "промышленность");
    enterprise2.impact_type = "point";
    enterprise2.location = Coordinates(56.8587, 35.9176);
    enterprise2.contact_phone = "+7-4822-55-66-77";
    enterprise2.contact_email = "office@zavodstal.ru";
    database.addEnterprise(enterprise2);
    
    // Добавляем реки
    River river1(1, "Волга");
    river1.length_km = 3530;
    river1.basin_area_km2 = 1360000;
    river1.avg_flow_m3s = 8060;
    river1.source = Coordinates(57.2516, 32.4681);
    river1.mouth = Coordinates(45.6935, 47.8500);
    river1.addRegion(1);
    river1.addRegion(2);
    river1.addEnterprise(1);
    river1.addEnterprise(2);
    database.addRiver(river1);
    
    River river2(2, "Ока");
    river2.length_km = 1500;
    river2.basin_area_km2 = 245000;
    river2.avg_flow_m3s = 1258;
    river2.source = Coordinates(52.3606, 36.2356);
    river2.mouth = Coordinates(55.3875, 43.8139);
    river2.addRegion(1);
    database.addRiver(river2);
    
    // Добавляем экологические характеристики
    Ecology ecology1(1);
    ecology1.water_quality = "good";
    ecology1.pollution_level = 4;
    ecology1.chemical_pollution = 12.5;
    ecology1.biological_pollution = 8.2;
    ecology1.biodiversity_level = "high";
    ecology1.protected_species = true;
    ecology1.last_inspection_date = "2024-01-15";
    database.setEcology(ecology1);
    
    Ecology ecology2(2);
    ecology2.water_quality = "fair";
    ecology2.pollution_level = 6;
    ecology2.chemical_pollution = 25.8;
    ecology2.biological_pollution = 15.3;
    ecology2.biodiversity_level = "medium";
    ecology2.protected_species = false;
    ecology2.last_inspection_date = "2024-02-20";
    database.setEcology(ecology2);
    
    // Добавляем экономические значения
    EconomicValue economic1(1);
    economic1.water_supply = true;
    economic1.energy_generation = true;
    economic1.fishing = true;
    economic1.navigation = true;
    economic1.irrigation = true;
    economic1.economic_benefit = 1250.5;
    economic1.risk_assessment = "medium";
    database.setEconomicValue(economic1);
    
    EconomicValue economic2(2);
    economic2.water_supply = true;
    economic2.fishing = true;
    economic2.navigation = true;
    economic2.economic_benefit = 450.2;
    economic2.risk_assessment = "low";
    database.setEconomicValue(economic2);
    
    printSuccess("Тестовые данные успешно загружены!");
    std::cout << "Добавлено: 2 реки, 2 региона, 2 предприятия" << std::endl;
}

void ConsoleUI::run() {
    printHeader("СИСТЕМА УЧЕТА РЕК - ЗАПУСК");
    std::cout << "Добро пожаловать в систему учета рек!" << std::endl;
    
    bool running = true;
    while (running) {
        printMenu();
        
        int choice = getIntInput("Выберите пункт меню: ", 0, 12);
        
        switch (choice) {
            case 0:
                running = false;
                printSuccess("До свидания!");
                break;
            case 1:
                addRiver();
                break;
            case 2:
                editRiver();
                break;
            case 3:
                deleteRiver();
                break;
            case 4:
                manageEcology();
                break;
            case 5:
                manageEnterprises();
                break;
            case 6:
                manageRegions();
                break;
            case 7:
                viewRiversByRegion();
                break;
            case 8:
                searchRivers();
                break;
            case 9:
                generateReports();
                break;
            case 10:
                manageImportExport();
                break;
            case 11:
                viewRivers();
                break;
            case 12:
                populateTestData();
                break;
        }
        
        if (choice != 0) {
            std::cout << std::endl;
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.get();
        }
    }
}

int main() {
    // Установка локали для корректного отображения кириллицы
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    ConsoleUI app;
    app.run();
    
    return 0;
}