#ifndef DILEMMA_TOURNAMENT_H
#define DILEMMA_TOURNAMENT_H
#include "../GameMode.h"

class Tournament : public GameMode {
private:
    int currentSteps_;
    int currentRound_;
    std::map<std::string, std::string> scoreMap_;
    std::vector<int> scoresOfStrategies_;
    std::vector<std::shared_ptr<GameStrategy>> vectorWithStrategies_;
    int currentFirstIndex;
    int currentSecondIndex;
    int currentThirdIndex;
public:
    Tournament(int steps, std::string matrix, std::map<std::string, std::string> scoreMap, std::vector<std::shared_ptr<GameStrategy>> arrayWithStrategies);
    void printCurrentRound() const;
    void printMode() override;
    void viewMatrix() override;
    void viewWinner();
    void viewFinalProtocol();
    void updateMatrix(std::string current) override;
    void play() override;
    ~Tournament() override = default;
};


#endif //DILEMMA_TOURNAMENT_H
