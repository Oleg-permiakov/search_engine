//
// Created by Oleg on 06.12.2025.
//


#include "ConverterJSON.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>
#include <sstream>
#include <string>
#include <vector>


/**
 * Метод получения содержимого файлов
 * @return Возвращает список с содержимым файлов перечисленных
 * в config.json
 */

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    nlohmann::json config;
    std::ifstream file("../config.json");
    if (!std::filesystem::exists("../config.json")) {
        throw std::invalid_argument("config file is missing");
    }
    file.open("../config.json");
    file >> config;
    file.close();
    if (config["config"].empty()) {
        throw std::invalid_argument("config file is empty");
    } else if (config["config"]["version"] != "0.1") {
        throw std::invalid_argument("config.json has incorrect file version");
    }

    const std::string nameStart = config["config"]["name"];
    std::cout << nameStart << std::endl;

    std::vector<std::string> contentDocuments;
    std::string content;
    std::string contentFull;
    std::vector<std::string> configPath = config["files"];
    for (auto &filePath: configPath) {
        // std::string strPath = filePath;
        std::ifstream currentFile(filePath);
        if (!currentFile.is_open()) {
            std::cout << "Could not open file" << std::endl;
        }
        while (currentFile >> content) {
            contentFull = contentFull + " " + content;
        }
        contentDocuments.push_back(contentFull);
        contentFull = "";
        currentFile.close();
    }
    return contentDocuments;
}


int ConverterJSON::GetResponsesLimit() {
    nlohmann::json config;
    std::ifstream file("../config.json");
    // file.open("../config.json");
    file >> config;
    file.close();
    int numberRequests = config["config"]["max_responses"];
    return numberRequests;
}

/**
 * Метод получения запросов из файла requests.json
 * @return возвращает список запросов из файла requests.json
 */
std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> queries_input;
    nlohmann::json req;
    std::ifstream fileRequest("../requests.json");
    fileRequest >> req;
    fileRequest.close();
    for (auto &stringWord: req["requests"]) {
        queries_input.push_back(stringWord);
    }
    return queries_input;
}

/**
 * Положить в файл answers.json результаты поисковых запросов
 */

/*
* {
"answers": {
"request001": {
"result": "true",
"relevance": [
{ "docid": 0, "rank": 0.989 },
{ "docid": 1, "rank": 0.897 },
{ "docid": 2, "rank": 0.750 }
]
},"request002": {
"result": "true",
"relevance": [
{ "docid": 0, "rank": 0.769 }
]
},
"request003": {
"result": "false"
}
}
}
 */

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> ans) {
    nlohmann::json answer;
    nlohmann::json relivan;
    std::string strRequest;
    std::stringstream ss;
    for (int i = 0; i < ans.size(); ++i) {
        ss << std::setw(3) << std::setfill('0') << (i + 1);
        strRequest = "request" + ss.str();
        ss.str("");
        answer["answers"][strRequest]["relevance"] = nlohmann::json::array();
        for (int j = 0; j < ans[i].size(); ++j) {

            if (!ans[i].empty()) {
                answer["answers"][strRequest]["result"] = "true";
                relivan["docid"] = ans[i][j].docs_id;
                relivan["rank"] = ans[i][j].rank;
                answer["answers"][strRequest]["relevance"].push_back(relivan);
            }
        }
        if (answer["answers"][strRequest]["relevance"].empty()) {
            answer["answers"][strRequest].clear();
            answer["answers"][strRequest]["result"] = "false";
        }
    }

    std::ofstream fileAnswers("../answers.json");
    fileAnswers <<std::setw(4)<< answer;
    fileAnswers.close();
}
