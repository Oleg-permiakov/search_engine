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

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> contentDocuments;
    std::string content;
    auto &configPath = config["files"];
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

/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/

int ConverterJSON::GetResponsesLimit() {
    std::cout << "If you want to leave the number of requests equal to 5, type any keyboard" << std::endl;
    std::cout << "If you want to change the number of requests, enter  No" << std::endl;
    std::string requests;
    std::cin >> requests;
    if (requests == "No") {
        std::cout << "Enter the number of requests" << std::endl;
        std::cin >> config["max_responses"];
    }
    int numberRequests = config["max_responses"];
    return numberRequests;
}

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> ConverterJSON::GetRequests() {
    std::cout << "If you want to fill out requests from the program, type Yes" << std::endl;
    std::cout << "If you filled out the request.json file, press any key" << std::endl;
    std::string request;
    std::vector<std::string> requests;
    int numberRequests = GetResponsesLimit();
    nlohmann::json req;
    if (request == "Yes") {
        while (numberRequests >= 0) {
            if (numberRequests > 0) {
                std::cout << "Enter your request" << std::endl;
                std::cin >> request;
                requests.push_back(request);
                numberRequests--;
            }
            std::cout << "Request limit reached" << std::endl;
        }
        std::ofstream fileRequest("requests.json");
        if (fileRequest.is_open()) {
            fileRequest.clear();
        }
        req = {"requests", requests};
        fileRequest << req;
        fileRequest.close();
    } else {
        std::ifstream fileRequest("requests.json");
        fileRequest >> req;
        fileRequest.close();
        for (auto request1: req["requests"]) {
            requests.push_back(request1);
        }
    }
    return requests;
}

/**
* Положить в файл answers.json результаты поисковых запросов
*/

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float> >> ans) {
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
        ss<<std::setw(3)<<std::setfill('0')<<(i+1);
        strResult = "request"+ss.str();
        request = {{"result", requestSearh},{strResult, relev}};
        answer = {"answers", request};
    }
    std::ofstream fileAnswers("answers.json");
    if (fileAnswers.is_open()) {
        fileAnswers.close();
    }
    fileAnswers << answer;
    fileAnswers.close();
}


nlohmann::json ConverterJSON::getConfig() {
    return config;
}

void ConverterJSON::setConfig() {
    std::ifstream file("config.json");
    if (!std::filesystem::exists("config.json")) {
        throw std::invalid_argument("config file is missing");
    }
    file.open("config.json");
    file >> config;
    file.close();
    if (config["config"].empty()) {
        throw std::invalid_argument("config file is empty");
    } else if (config["config"]["version"] != "0.1") {
        throw std::invalid_argument("config.json has incorrect file version");
    }

    const std::string nameStart = config["config"]["name"];
    std::cout << nameStart << std::endl;
}