//
// Created by illusory on 2024/11/22.
//

#ifndef CPP_LEARN_CIRCLE_H
#define CPP_LEARN_CIRCLE_H

const double PI = 3.14;

class CirCle {
public:
    int m_r;

    [[nodiscard]] double calculateZC() const {
        return 2 * PI * m_r;
    }
};


#endif //CPP_LEARN_CIRCLE_H
