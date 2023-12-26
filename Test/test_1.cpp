#include <gtest/gtest.h>

#include "../Model/Player.h"
#include "../Model/Figure.h"
// #include "../Model/Model.h"
#include "../Util/FiguresMatrix.h"

TEST(constructor_test, opene_test)
{
    Player player;

    ASSERT_EQ(8, 8 * 1);
}
