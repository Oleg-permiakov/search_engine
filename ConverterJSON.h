//
// Created by Oleg on 06.12.2025.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H


#include <nlohmann/json.hpp>
#include <vector>


class ConverterJSON {
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> ans);

    nlohmann::json getConfig();
    void setConfig();



private:
    
    nlohmann::json config;
    nlohmann::json answers;
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H