#include <gmock/gmock.h>
#include "tree.h"

class TreeTest : public testing::Test {

public:
    // used to test dfs_fold
    static std::string to_string(const std::string &acc, const Tree<int> &node) {
        return acc + std::to_string(node.get_value()) + " ";
    }
};

TEST_F(TreeTest, TestCreateEmpty) {
    Tree<int> tree;
    ASSERT_TRUE(tree.is_leaf());
}

TEST_F(TreeTest, TestCreateSingleNode) {
    Tree<int> tree {3};
    ASSERT_EQ(3, tree.get_value());
    ASSERT_TRUE(tree.is_leaf());
}

TEST_F(TreeTest, TestCreateSingleLayer) {
    Tree<int> tree;
    tree.add_child(Tree<int> {3});
    tree.add_child(Tree<int> {4});

    ASSERT_FALSE(tree.is_leaf());

    auto children = tree.get_children();
    ASSERT_EQ(3, children[0].get_value());
    ASSERT_EQ(4, children[1].get_value());
}

TEST_F(TreeTest, TestCreateTwoLayers) {
    Tree<int> first_node;
    first_node.add_child(Tree<int> {2});
    first_node.add_child(Tree<int> {5});

    Tree<int> tree;
    tree.add_child(first_node);

    ASSERT_FALSE(tree.is_leaf());

    auto children = tree.get_children();
    auto first_child = children[0];

    ASSERT_FALSE(first_child.is_leaf());

    auto grandchildren = first_child.get_children();
    auto first_grandchild = grandchildren[0];
    auto second_grandchild = grandchildren[1];

    ASSERT_TRUE(first_grandchild.is_leaf());
    ASSERT_EQ(2, first_grandchild.get_value());
    ASSERT_TRUE(second_grandchild.is_leaf());
    ASSERT_EQ(5, second_grandchild.get_value());
}

TEST_F(TreeTest, TestDFS) {
    Tree<int> first_node {4};
    first_node.add_child(Tree<int>{2});
    first_node.add_child(Tree<int>{5});

    Tree<int> second_node {3};
    second_node.add_child(Tree<int>{8});
    second_node.add_child(Tree<int>{7});

    Tree<int> tree {9};
    tree.add_child(first_node);
    tree.add_child(second_node);

    auto result = tree.dfs_fold<std::string>(to_string, std::string {});

    ASSERT_EQ(result, "9 4 2 5 3 8 7 ");
}

TEST_F(TreeTest, TestDFSSingleNode) {
    Tree<int> tree {4};

    auto result = tree.dfs_fold<std::string>(to_string, std::string {});

    ASSERT_EQ(result, "4 ");
}
