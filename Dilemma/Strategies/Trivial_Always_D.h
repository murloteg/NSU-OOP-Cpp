#ifndef DILEMMA_TRIVIAL_ALWAYS_D_H
#define DILEMMA_TRIVIAL_ALWAYS_D_H
#include "GameStrategy.h"

class TrivialAlwaysD : public GameStrategy {
public:
    TrivialAlwaysD();
    Choice vote() override;
    ~TrivialAlwaysD() override = default;
};


#endif //DILEMMA_TRIVIAL_ALWAYS_D_H
