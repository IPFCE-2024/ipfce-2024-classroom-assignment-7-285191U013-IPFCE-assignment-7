#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vector>

extern "C" {
#include "stack.h"
#include "taylor_sine.h"
}

#include <cmath>

#define pi 3.14159265358979323846   // Define pi for comparison

TEST_CASE("taylor_sine") {
  // const double pi = M_PI; removed as it is already defined
  const double precision = 0.0001;
  std::vector<std::pair<double, int>> scenarios = {
    {pi, 8},
    {pi / 2.0, 10},
    {0, 1},
    {pi / 4.0, 6},
    {0.005, 3},
  };
  for (const auto &[x, n] : scenarios) {
    REQUIRE_THAT(taylor_sine(x, n), Catch::Matchers::WithinAbs(std::sin(x), precision));
  }
}

TEST_CASE("initialize", "[stack]") {
  stack s;
  initialize(&s);
  REQUIRE(s.head == nullptr); // changed from NULL to nullptr
}

TEST_CASE("empty", "[stack]") {
  stack s;
  s.head = NULL;
  REQUIRE(empty(&s));
  node n;
  n.data = 1;
  n.next = NULL;
  s.head = &n;
  REQUIRE(!empty(&s));
}

TEST_CASE("full", "[stack]") {
  stack s;
  s.head = NULL;
  REQUIRE(!full(&s));
  node n;
  n.data = 1;
  n.next = NULL;
  s.head = &n;
  REQUIRE(!full(&s));
}

TEST_CASE("push", "[stack]") {
  stack s;
  s.head = NULL;
  int x = 1;
  push(x, &s);
  REQUIRE(s.head != nullptr); // changed from NULL to nullptr
  REQUIRE(s.head->data == x);
  int y = 2;
  push(y, &s);
  REQUIRE(s.head->next != nullptr); // changed from NULL to nullptr
  REQUIRE(s.head->data == y);
}

TEST_CASE("pop", "[stack]") {
  stack s;
  s.head = NULL;
  int x = 1;
  node *n = (node*) malloc(sizeof(node));
  n->data = x;
  n->next = s.head;
  s.head = n;
  int y = pop(&s);
  REQUIRE(x == y);
  REQUIRE(s.head == nullptr); // changed from NULL to nullptr
}

TEST_CASE("stack", "[stack]") {
    stack s;
    initialize(&s);
    REQUIRE(empty(&s));
    REQUIRE(!full(&s));
    push(1, &s);
    REQUIRE(!empty(&s));
    REQUIRE(!full(&s));
    push(2, &s);
    REQUIRE(!empty(&s));
    push(3, &s);
    int x1 = pop(&s);
    int x2 = pop(&s);
    int x3 = pop(&s);
    REQUIRE(x1 == 3);
    REQUIRE(x2 == 2);
    REQUIRE(x3 == 1);
    REQUIRE(empty(&s));
    REQUIRE(!full(&s));  
}
