#include "Logger.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string Logger::getRelativePath(const std::string& fullPath) {
    if (!m_basePath.empty() && fullPath.find(m_basePath) == 0) {
        return fullPath.substr(m_basePath.length());
    }
    return fullPath;
}

Logger::Logger() {
    std::string logDir = "logs";
    std::string logFile = "app.log";
    m_basePath = "./";

    std::ifstream configFile("cpp-logger/logger_config.json");
    if (configFile.is_open()) {
        json config;
        configFile >> config;

        logDir = config["log_dir"];
        logFile = config["log_file"];
        m_basePath = config["base_path"];
    }

    std::filesystem::create_directories(logDir);
    std::string logPath = logDir + "/" + logFile;

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath, true);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    logger = std::make_shared<spdlog::logger>("app_logger",
                                              spdlog::sinks_init_list{console_sink, file_sink});
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::debug);
    spdlog::register_logger(logger);
}