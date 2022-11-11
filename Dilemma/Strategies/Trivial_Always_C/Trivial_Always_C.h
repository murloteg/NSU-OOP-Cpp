#ifndef DILEMMA_TRIVIAL_ALWAYS_C_H
#define DILEMMA_TRIVIAL_ALWAYS_C_H
#include "../GameStrategy.h"

class TrivialAlwaysC : public GameStrategy {
public:
    TrivialAlwaysC(std::string configDirectory_);
    Choice vote() override;
    void printStrategyName() override;
    ~TrivialAlwaysC() override = default;
};


#endif //DILEMMA_TRIVIAL_ALWAYS_C_H
