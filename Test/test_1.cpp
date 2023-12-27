#include <gtest/gtest.h>

#include "../Model/Player.h"
#include "../Model/Figure.h"
#include "../Model/Model.h"
#include "../Util/FiguresMatrix.h"

TEST(player_test, t1)
{
    Player player;

    ASSERT_EQ(player.get_elapsed_time(), 8 * 60);
    ASSERT_EQ(player.get_rating(), 0);

    player.set_name("Robert");
    player.set_time(3 * 60);
    player.set_rating(123);

    ASSERT_EQ(player.get_name(), "Robert");
    ASSERT_EQ(player.get_elapsed_time(), 3 * 60);
    ASSERT_EQ(player.get_rating(), 123);

    Player initialized_player("Dany", 112);

    ASSERT_EQ(initialized_player.get_name(), "Dany");
    ASSERT_EQ(initialized_player.get_rating(), 112);
    ASSERT_EQ(initialized_player.get_elapsed_time(), 8 * 60);
}

TEST(figure_test, t2)
{
    Figure *f1 = Figure().symbol_to_figure("pW");

    ASSERT_EQ(f1->get_name_of_figure(), "Pawn");
    ASSERT_EQ(f1->figure_to_symbol(), 'p');
    ASSERT_EQ(f1->get_color(), 0);

    Figure *f2 = Figure().symbol_to_figure("kB");

    ASSERT_EQ(f2->get_name_of_figure(), "King");
    ASSERT_EQ(f2->figure_to_symbol(), 'k');
    ASSERT_EQ(f2->get_color(), 1);

    int pos1 = Figure().create_position(1, 6);
    int pos2 = Figure().create_position(3, 3);

    ASSERT_EQ(pos1, Figure().create_position(1, 6));
    ASSERT_EQ(pos2, Figure().create_position(3, 3));

    std::vector<int> moves_1 = f1->array_moves(f1, pos1);
    std::vector<int> moves_2 = f2->array_moves(f2, pos2);

    std::vector<int> moves_1_pred = { Figure().create_position(0, 5), Figure().create_position(0, 6),
                                      Figure().create_position(0, 7)};

    std::vector<int> moves_2_pred = { Figure().create_position(2, 2), Figure().create_position(2, 3),
                                      Figure().create_position(2, 4), Figure().create_position(3, 2),
                                      Figure().create_position(3, 4), Figure().create_position(4, 2),
                                      Figure().create_position(4, 3), Figure().create_position(4, 4)};

    std::sort(moves_1.begin(), moves_1.end());
    std::sort(moves_2.begin(), moves_2.end());
    std::sort(moves_1_pred.begin(), moves_1_pred.end());
    std::sort(moves_2_pred.begin(), moves_2_pred.end());

    ASSERT_EQ(moves_1.size(), moves_1_pred.size()) << "Vectors x and y are of unequal length";
    ASSERT_EQ(moves_2.size(), moves_2_pred.size()) << "Vectors x and y are of unequal length";

    for (int i = 0; i < moves_1.size(); ++i)
        EXPECT_EQ(moves_1[i], moves_1_pred[i]) << "Vectors x and y differ at index " << i;

    for (int i = 0; i < moves_2.size(); ++i)
        EXPECT_EQ(moves_2[i], moves_2_pred[i]) << "Vectors x and y differ at index " << i;

    Figure *f3 = Figure().symbol_to_figure("rW");

    int pos_from = Figure().create_position(1, 1);
    int pos_to_1 = Figure().create_position(1, 7);
    int pos_to_2 = Figure().create_position(5, 1);
    int pos_to_3 = Figure().create_position(6, 2);

    ASSERT_EQ(f3->can_do_move(f3, pos_from, pos_to_1), true);
    ASSERT_EQ(f3->can_do_move(f3, pos_from, pos_to_2), true);
    ASSERT_EQ(f3->can_do_move(f3, pos_from, pos_to_3), false);

    std::ostringstream stream1;

    stream1 << f3;

    ASSERT_EQ(stream1.str(), "wRook");
}





void test_cout_text(const Matrix<int>& matr, const std::string &expected)
{
    std::ostringstream redirectStream;
    std::streambuf* coutBuffer = std::cout.rdbuf(redirectStream.rdbuf());

    matr.print();

    std::cout.rdbuf(coutBuffer);

    std::string output = redirectStream.str();

    EXPECT_EQ(output, expected);
}





TEST(matrix_test, t3)
{
    Matrix<int> m(3, 3);

    int value = 1;
    for (auto row = m.begin(); row != m.end(); ++row) {
        for (size_t col = 0; col < m.get_cols(); ++col) {
            (*row)[col] = value++;
        }
    }

    int k = 1;
    for (auto row : m) {
        for (size_t col = 0; col < m.get_cols(); ++col) {
            ASSERT_EQ(row[col], k);
            k++;
        }
    }

    Matrix<int> m1 = m.transpose();

    test_cout_text(m1, "\n1\t4\t7\t\n2\t5\t8\t\n3\t6\t9\t\n\n");

    m.add_row();

    m.at(3, 0) = 12;
    m.at(3, 1) = 13;
    m.at(3, 2) = 14;

    m.add_column();

    m.at(0, 3) = 20;
    m.at(1, 3) = 21;
    m.at(2, 3) = 22;
    m.at(3, 3) = 23;

    m.delete_row(1);
    m.delete_column(1);

    test_cout_text(m, "\n1\t3\t20\t\n7\t9\t22\t\n12\t14\t23\t\n\n");

    ASSERT_EQ(m.find_element(14), 7);

    ASSERT_EQ(m.get_cols(), 3);
    ASSERT_EQ(m.get_rows(), 3);

    m.at(0, 0) = 100;

    ASSERT_EQ(m.find_element(100), 0);
    ASSERT_EQ(m.at(0, 0), 100);

    ASSERT_THROW(m.delete_row(10), std::out_of_range);
    ASSERT_THROW(m.at(3, 0), std::out_of_range);

    int expectedValue = 1;
    for (const auto& element : m1)
        EXPECT_EQ(*element, expectedValue++);
}

TEST(figures_matrix, t4)
{
    FiguresMatrix fm(8, 8);

    EXPECT_THROW(fm.move_figure(Figure().create_position(7, 0), Figure().create_position(6, 0)), std::logic_error);

    fm.move_figure(Figure().create_position(6, 0),
                   Figure().create_position(5 , 0));

    ASSERT_EQ(fm.at(6, 0), nullptr);
    ASSERT_EQ(fm.at(5, 0)->figure_to_symbol(), 'p');
    ASSERT_EQ(fm.at(5, 0)->get_color(), 0);

    EXPECT_NO_THROW(fm.move_figure(Figure().create_position(7, 0), Figure().create_position(6, 0)));

    EXPECT_NO_THROW(fm.move_figure(Figure().create_position(6, 3), Figure().create_position(4, 3)));
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 3)), true);
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 2)), false);
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 4)), false);

    EXPECT_NO_THROW(fm.move_figure(Figure().create_position(1, 2), Figure().create_position(3, 2)));
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 3)), true);
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 2)), true);
    ASSERT_EQ(fm.can_do_move(Figure().create_position(4, 3), Figure().create_position(3, 4)), false);

    ASSERT_EQ(fm.find_king(1), Figure().create_position(0, 4));
    ASSERT_EQ(fm.find_king(0), Figure().create_position(7, 4));

    Figure *f1 = Figure().symbol_to_figure("nB");
    Figure *f2 = Figure().symbol_to_figure("rW");

    ASSERT_EQ(fm.get_figure(Figure().create_position(0, 1))->get_name_of_figure(), f1->get_name_of_figure());
    ASSERT_EQ(fm.get_figure(Figure().create_position(0, 1))->get_color(), f1->get_color());
    ASSERT_EQ(fm.get_figure(Figure().create_position(6, 0))->get_name_of_figure(), f2->get_name_of_figure());
    ASSERT_EQ(fm.get_figure(Figure().create_position(6, 0))->get_color(), f2->get_color());

    ASSERT_EQ(fm.is_check_multi_threading(0), false);
    ASSERT_EQ(fm.is_check_multi_threading(1), false);
    ASSERT_EQ(fm.is_checkmate_multi_threading(0), false);
    ASSERT_EQ(fm.is_checkmate_multi_threading(1), false);
    ASSERT_EQ(fm.is_stalemate_multi_threading(0), false);
    ASSERT_EQ(fm.is_stalemate_multi_threading(1), false);
}


TEST(model_test, t5)
{
    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    // sf::RenderWindow window(sf::VideoMode(800, 600), "Chess");
    sf::RenderWindow window;

    FiguresMatrix fm(8, 8);
    Field view_field(window, fm, name_whites, name_blacks);
    Model model(view_field, name_whites, name_blacks,
                rating_whites, rating_blacks);

    std::string game_his_1 = "1. pf2,f4 ng8,h6\n2. ke1,f2";
    model.set_game_history(game_his_1);

    ASSERT_EQ(model.get_state(), States::move_blacks);
    ASSERT_EQ(model.get_situation(), Situations::nothing);

    model.make_move(Figure().create_position(2, 7), Figure().create_position(4, 6));
    model.draw_situation_if_needed(0);

    ASSERT_EQ(model.get_state(), States::move_whites);
    ASSERT_EQ(model.get_situation(), Situations::check);

    std::string game_his_2 = "1. pc2,c4 ph7,h5\n"
                             "2. ph2,h4 pa7,a5\n"
                             "3. qd1,a4 ra8,a6\n"
                             "4. qa4,a5 ra6,h6\n"
                             "5. qa5,c7 pf7,f6\n"
                             "6. qc7,d7 ke8,f7\n"
                             "7. qd7,b7 qd8,d3\n"
                             "8. qb7,b8 qd3,h7\n"
                             "9. qb8,c8 kf7,g6";
    model.set_game_history(game_his_2);

    ASSERT_EQ(model.get_state(), States::move_whites);
    ASSERT_EQ(model.get_situation(), Situations::nothing);

    model.make_move(Figure().create_position(0, 2), Figure().create_position(2, 4));
    model.draw_situation_if_needed(0);

    ASSERT_EQ(model.get_state(), States::game_over);
    ASSERT_EQ(model.get_situation(), Situations::stalemate);

    std::string game_his_3 = "1. pf2,f4 pe7,e5\n"
                             "2. pg2,g4";
    model.set_game_history(game_his_3);

    ASSERT_EQ(model.get_state(), States::move_blacks);
    ASSERT_EQ(model.get_situation(), Situations::nothing);

    model.make_move(Figure().create_position(0, 3), Figure().create_position(4, 7));
    model.draw_situation_if_needed(0);

    ASSERT_EQ(model.get_state(), States::game_over);
    ASSERT_EQ(model.get_situation(), Situations::checkmate);
}
