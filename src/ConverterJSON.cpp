//
// Created by Oleg on 06.12.2025.
//



#include "ConverterJSON.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <set>
#include <string>



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
    std::vector<std::string> configPath = config["files"];
    for (auto &filePath: configPath) {
        std::string strPath = filePath;
        std::ifstream currentFile(strPath);
        if (!currentFile.is_open()) {
            std::cout << "Could not open file" << std::endl;
        }
        while (currentFile >> content) {
            contentDocuments.push_back(content);
        }
        currentFile.close();
    }
    return contentDocuments;
}


int ConverterJSON::GetResponsesLimit() {
    nlohmann::json config;
    std::ifstream file("../config.json");
    file >> config;
    file.close();
    int numberRequests = config["max_responses"];
    return numberRequests;
}

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> ConverterJSON::GetRequests() {
    std::string request;
    std::vector<std::string> requests;
    std::vector<std::string> queries_input;
    nlohmann::json req;
    std::ifstream fileRequest("../requests.json");
    fileRequest >> req;
    fileRequest.close();
    for (auto &stringWord: req["requests"]) {
        requests.push_back(stringWord);
    }
        std::set<std::string> words;
    for (auto &stringWord: requests) {
        std::stringstream ss(stringWord);
        std::string word;
        while (ss >> word) {
            words.insert(word);
        }
    }
    for (const auto &word: words) {
        queries_input.push_back(word);
    }
    return queries_input;
}

/**
* Положить в файл answers.json результаты поисковых запросов
*/

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float> > > ans) {
    nlohmann::json answer;
    nlohmann::json relev;
    nlohmann::json request;
    std::string strResult;
    std::stringstream ss;

    bool requestSearh = true;

    for (int i = 0; i < ans.size(); i++) {
        if (!(ans[i].empty())) {
            requestSearh = true;
            for (int j = 0; j < ans[i].size(); ++j) {
                relev = {{"docid", ans[i][j].first}, {"rank", ans[i][j].second}};
            }
        } else {
            requestSearh = false;
        }
        ss << std::setw(3) << std::setfill('0') << (i + 1);
        strResult = "request" + ss.str();
        request = {{"result", requestSearh}, {strResult, relev}};
        answer = {"answers", request};
    }
    std::ofstream fileAnswers("../answers.json");
    if (fileAnswers.is_open()) {
        fileAnswers.close();
    }
    fileAnswers << answer;
    fileAnswers.close();
}
