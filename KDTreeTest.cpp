#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "KDTree.h"

SCENARIO("Items can be inserted", "[insert]" ) {

    GIVEN("An empty KDTree") {
        IKDTree *kdtree = new KDTree();

        REQUIRE(kdtree->getAllPoints().empty());

        WHEN("One 2-dimensional point is added") {

            kdtree->insert(Point(std::vector<double>(1, 1)));
            std::list<Point> points = kdtree->getAllPoints();

            THEN("There is 1 point in the returned list of getAllPoints") {

                REQUIRE(points.size() == 1);

                THEN("That point is exactly the one which was added") {

                    REQUIRE(points.back().getCoordinates() == std::vector<double>(1, 1));

                }

            }
        }

        WHEN("Two 2-dimensional points are added") {

            kdtree->insert(Point(std::vector<double>({1, 1})));
            kdtree->insert(Point(std::vector<double>({-1, -1})));
            std::list<Point> points = kdtree->getAllPoints();

            THEN("There are 2 points in the returned list of getAllPoints") {

                REQUIRE(points.size() == 2);

            }

        }

        WHEN("Seven 2-dimensional points are added") {

            kdtree->insert(Point(std::vector<double>({1, 1})));
            kdtree->insert(Point(std::vector<double>({-1, -1})));
            kdtree->insert(Point(std::vector<double>({-1, -2})));
            kdtree->insert(Point(std::vector<double>({10, 10})));
            kdtree->insert(Point(std::vector<double>({20, 20})));
            kdtree->insert(Point(std::vector<double>({30, 30})));
            kdtree->insert(Point(std::vector<double>({-5, 5})));
            std::list<Point> points = kdtree->getAllPoints();

            THEN("There are 2 points in the returned list of getAllPoints") {

                REQUIRE(points.size() == 7);

            }

        }
    }
}