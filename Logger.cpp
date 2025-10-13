#include "Logger.h"
#include <filesystem>

std::string Logger::getRelativePath(const std::string& fullPath) {
    // HAVE TO FIX TO UNUVERSAL PATH!
    // std::string basePath = std::filesystem::current_path().string();
    std::string basePath = "/home/andrey/work/test/tg_video_toolbox/src/";
    if (fullPath.find(basePath) == 0) {
        return fullPath.substr(basePath.length());
    }
    return fullPath;
}

Logger::Logger() {
    try {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("bot.log", true);
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

        logger = std::make_shared<spdlog::logger>("bot_logger", spdlog::sinks_init_list{console_sink, file_sink});
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::debug);
        spdlog::register_logger(logger);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}