#include "gmock/gmock.h"
#include "interpreter.h"

class InterpreterTest : public testing::Test {
private:
    std::shared_ptr<Interpreter> interpreter;
public:

    InterpreterTest() {
        Parser parser;
        interpreter = std::make_shared<Interpreter>(parser);
    }

    std::string eval(const std::string &string) {
        return interpreter->eval(string)->toString();
    }

    double evalNum(const std::string &string) {
        return std::stod(eval(string));
    }
};

TEST_F(InterpreterTest, TestEval) {
    ASSERT_EQ(evalNum("(+ 30 5 12)"), 47);
    ASSERT_EQ(evalNum("(* (+ 2.3 0.2) 2)"), 5);
}