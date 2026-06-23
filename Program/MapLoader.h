#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "body.h" // Pos 用

struct EnemySpawnInfo {
    int id;
    int level;
    Pos pos;
};

struct MapData {
    int stage;
    int map;
    std::vector<EnemySpawnInfo> enemies;
};

class MapLoader {
public:
    static std::vector<MapData> LoadFromFile(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs) {
            throw std::runtime_error("ファイルを開けません: " + filename);
        }

        std::vector<MapData> maps;
        std::string line;

        // これでやると# Stage1 Map1 みたいなコメント行や空行が来るとバグるみたい
        // ひどい
        // while (ifs >> stage >> map >> enemyCount)
        while (std::getline(ifs, line)) {
            // 空行やコメント行をスキップ
            if (line.empty() || line[0] == '#') continue;

            std::istringstream iss(line);
            MapData mapData;
            int enemyCount;

            // 1行目: stage, map
            iss >> mapData.stage >> mapData.map;
            if (!iss) continue;

            // 2行目: 敵数
            do {
                if (!std::getline(ifs, line)) return maps;
            } while (line.empty() || line[0] == '#'); // コメントなら飛ばす
            enemyCount = std::stoi(line);

            // 敵データ
            for (int i = 0; i < enemyCount; i++) {
                do {
                    if (!std::getline(ifs, line)) break;
                } while (line.empty() || line[0] == '#');

                std::istringstream enemyIss(line);
                EnemySpawnInfo info;
                int x, y;
                enemyIss >> info.id >> info.level >> x >> y;
                info.pos = Pos(x, y);
                mapData.enemies.push_back(info);
            }

            maps.push_back(mapData);
        }

        return maps;
    }
};