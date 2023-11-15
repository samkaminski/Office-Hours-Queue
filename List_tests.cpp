#include "List.hpp"
#include "unit_test_framework.hpp"


using namespace std;

// Test push front and back
TEST(test_push_front_and_back) {
    List<int> myList;
    myList.push_front(1);
    myList.push_back(2);
    ASSERT_EQUAL(myList.front(), 1);
    ASSERT_EQUAL(myList.back(), 2);
}

// Test pop front and back
TEST(test_pop_front_and_back) {
    List<int> myList;
    myList.push_front(1);
    myList.push_back(2);
    myList.pop_front();
    ASSERT_EQUAL(myList.front(), 2);
    myList.pop_back();
    ASSERT_TRUE(myList.empty());
}

// Test begin and end
TEST(test_begin_and_end) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    auto it = myList.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_TRUE(it == myList.end());
}

// Test insert (3 elements)
TEST(test_insert_3) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(4);
    auto it = myList.begin();
    ++it;
    myList.insert(it, 2);
    myList.insert(it, 3);
    ASSERT_EQUAL(myList.size(), 4);
    it = myList.begin();
    ++it; ++it;
    ASSERT_EQUAL(*it, 3);
}

// Test insert (2 elements)
TEST(test_insert_2) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(3);
    auto it = myList.begin();
    ++it;
    myList.insert(it, 2);
    ASSERT_EQUAL(myList.size(), 3);
    it = myList.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
}

// Test insert (1 element)
TEST(test_insert_1) {
    List<int> myList;
    myList.push_back(1);
    auto it = myList.begin();
    myList.insert(it, 2);
    ASSERT_EQUAL(myList.size(), 2);
    ASSERT_EQUAL(myList.front(), 2);
}

// Test erase (3 elements)
TEST(test_erase_3) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    auto it = myList.begin();
    ++it; ++it;
    myList.erase(it);
    ASSERT_EQUAL(myList.size(), 2);
}

// Test erase (2 elements)
TEST(test_erase_2) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    auto it = myList.begin();
    ++it;
    myList.erase(it);
    ASSERT_EQUAL(myList.size(), 1);
    ASSERT_EQUAL(myList.front(), 1);
}

// Test empty and size
TEST(test_empty_and_size) {
    List<int> myList;
    ASSERT_TRUE(myList.empty());
    myList.push_back(1);
    ASSERT_FALSE(myList.empty());
    ASSERT_EQUAL(myList.size(), 1);
}

// Test assignment operator (2 elements)
TEST(test_assignment_2) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    List<int> myList2;
    myList2 = myList;
    ASSERT_EQUAL(myList2.size(), 2);
    ASSERT_EQUAL(myList2.back(), 2);
}

// Test erase (1 element)
TEST(test_erase_1) {
    List<int> myList;
    myList.push_back(1);
    auto it = myList.begin();
    myList.erase(it);
    ASSERT_TRUE(myList.empty());
}

// Test assignment operator (1 element)
TEST(test_assignment_1) {
    List<int> myList;
    myList.push_back(1);
    List<int> myList2;
    myList2 = myList;
    ASSERT_EQUAL(myList2.size(), 1);
    ASSERT_EQUAL(myList2.front(), 1);
}

// Test iterator equality
TEST(test_iterator_equality) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    auto it1 = myList.begin();
    auto it2 = myList.begin();
    ASSERT_TRUE(it1 == it2);
    ++it2;
        // Test iterator equality (continued)
    ASSERT_FALSE(it1 == it2);
    ++it1;
    ASSERT_TRUE(it1 == it2);
}

// Test copy constructor
TEST(test_copy_constructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    List<int> copy(original);

    ASSERT_EQUAL(copy.size(), 2);
    ASSERT_EQUAL(copy.front(), 1);
    ASSERT_EQUAL(copy.back(), 2);
}

// Test iterator's big three (copy ctor, assignment operator, destructor)
TEST(test_iterator_big_three) {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);

    // Test copy constructor
    auto it1 = myList.begin();
    auto it2 = it1;
    ASSERT_TRUE(it1 == it2);

    // Test assignment operator
    ++it1;
    it2 = it1;
    ASSERT_TRUE(it1 == it2);

    // Destructor is implicit; if no crashes occur, likely correct
}

// Test memory management in destructor
TEST(test_destructor) {
    List<int>* myList = new List<int>();
    myList->push_back(1);
    delete myList;  
}

// Test copy constructor memory management
TEST(test_copy_constructor_memory) {
    List<int> original;
    for (int i = 0; i < 100; ++i) {
        original.push_back(i);
    }
    (void)List<int>(original); 
}

// Test assignment operator memory management
TEST(test_assignment_memory) {
    List<int> original, copy;
    for (int i = 0; i < 100; ++i) {
        original.push_back(i);
    }
    copy = original;  
}

// Test clearing a large list
TEST(test_clear_large_list) {
    List<int> myList;
    for (int i = 0; i < 1000; ++i) {
        myList.push_back(i);
    }
    myList.clear();  
}

// Main function provided by the unit_test_framework
TEST_MAIN()



TEST(test_stub) {
    test_push_front_and_back();
    test_pop_front_and_back();
    test_begin_and_end();
    test_insert_3();
    test_insert_2();
    test_insert_1();
    test_erase_3();
    test_erase_2();
    test_empty_and_size();
    test_assignment_2();
    test_erase_1();
    test_assignment_1();
    test_iterator_equality();
    test_copy_constructor();
    test_iterator_big_three();
    test_destructor();
    test_copy_constructor_memory();
    test_assignment_memory();
    test_clear_large_list();
    ASSERT_TRUE(true);
}