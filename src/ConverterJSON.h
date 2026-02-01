//
// Created by Oleg on 06.12.2025.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#pragma once

#include "nlohmann/json.hpp"
#include <vector>
#include <string>


class ConverterJSON {
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> ans);

};


#endif //SEARCH_ENGINE_CONVERTERJSON_H