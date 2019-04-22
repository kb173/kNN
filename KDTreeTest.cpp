#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "KDTree.h"
#include "Statistics.h"
#include "KDTreePreparation.h"

SCENARIO("Items can be inserted", "[insert]") {

    GIVEN("An empty KDTree") {
        IKDTree *kdtree = new KDTree();

        REQUIRE(kdtree->getAllPoints().empty());

        WHEN("One 2-dimensional point is added") {

            std::shared_ptr newPoint = std::make_shared<Point>(Point(std::vector<double>({1, 1})));

            kdtree->insert(newPoint);
            std::list<std::shared_ptr<Point>> points = kdtree->getAllPoints();

            THEN("There is 1 point in the returned list of getAllPoints") {

                REQUIRE(points.size() == 1);

                THEN("That point is exactly the one which was added") {

                    REQUIRE(points.back()->getCoordinates() == std::vector<double>({1, 1}));

                }

            }
        }

        WHEN("A classified point (derived from point) is added") {
            std::shared_ptr newClassified = std::make_shared<ClassifiedPoint>(
                    ClassifiedPoint(std::vector<double>({1, 1}), 5));
            kdtree->insert(newClassified);
            std::list<std::shared_ptr<Point>> points = kdtree->getAllPoints();

            THEN("This point can be retrieved as a ClassifiedPoint") {

                std::shared_ptr<ClassifiedPoint> classified = std::dynamic_pointer_cast<ClassifiedPoint>(points.back());

                REQUIRE(classified->getClassification() == 5);

            }
        }

        WHEN("Two 2-dimensional points are added") {

            std::shared_ptr newPoint1 = std::make_shared<Point>(Point(std::vector<double>({1, 1})));
            kdtree->insert(newPoint1);

            std::shared_ptr newPoint2 = std::make_shared<Point>(Point(std::vector<double>({-1, -1})));
            kdtree->insert(newPoint2);

            std::list<std::shared_ptr<Point>> points = kdtree->getAllPoints();

            THEN("There are 2 points in the returned list of getAllPoints") {

                REQUIRE(points.size() == 2);

            }

        }

        WHEN("Five 2-dimensional points are added") {

            std::shared_ptr newPoint1 = std::make_shared<Point>(Point(std::vector<double>({1, 1})));
            kdtree->insert(newPoint1);

            std::shared_ptr newPoint2 = std::make_shared<Point>(Point(std::vector<double>({-1, -1})));
            kdtree->insert(newPoint2);

            std::shared_ptr newPoint3 = std::make_shared<Point>(Point(std::vector<double>({-2, -2})));
            kdtree->insert(newPoint3);

            std::shared_ptr newPoint4 = std::make_shared<Point>(Point(std::vector<double>({-3, -3})));
            kdtree->insert(newPoint4);

            std::shared_ptr newPoint5 = std::make_shared<Point>(Point(std::vector<double>({1, 1})));
            kdtree->insert(newPoint5);

            std::list<std::shared_ptr<Point>> points = kdtree->getAllPoints();

            THEN("There are 5 points in the returned list of getAllPoints") {

                REQUIRE(points.size() == 5);

            }

        }
    }
}

SCENARIO("Items can be searched", "[search]") {

    GIVEN("A KDTree with 5 points") {
        IKDTree *kdtree = new KDTree();

        std::shared_ptr newPoint1 = std::make_shared<Point>(Point(std::vector<double>({5, 5})));
        kdtree->insert(newPoint1);

        std::shared_ptr newPoint2 = std::make_shared<Point>(Point(std::vector<double>({-5, -5})));
        kdtree->insert(newPoint2);

        std::shared_ptr newPoint3 = std::make_shared<Point>(Point(std::vector<double>({-2, -2})));
        kdtree->insert(newPoint3);

        std::shared_ptr newPoint4 = std::make_shared<Point>(Point(std::vector<double>({10, -10})));
        kdtree->insert(newPoint4);

        std::shared_ptr newPoint5 = std::make_shared<Point>(Point(std::vector<double>({11, -8})));
        kdtree->insert(newPoint5);

        WHEN("Searching for one nearby point") {

            std::shared_ptr<Point> searchPoint = std::make_shared<Point>(Point(std::vector<double>({10, -9})));

            auto result = kdtree->search(searchPoint, 1);

            THEN("There is exactly one result") {
                REQUIRE(result.size() == 1);
            }

            THEN("The result is the expected point") {
                REQUIRE(result.front()->getCoordinates().front() == 10);
                REQUIRE(result.front()->getCoordinates().back() == -10);
            }

        }

        WHEN("Searching for two nearby points") {

            std::shared_ptr searchPoint = std::make_shared<Point>(Point(std::vector<double>({10, -9})));

            auto result = kdtree->search(searchPoint, 2);

            THEN("There are exactly two results") {
                REQUIRE(result.size() == 2);
            }

        }
    }
}

SCENARIO("Sorted insert", "[insert, sort]") {

    GIVEN("A KDTree with 5 points") {
        IKDTree *kdtree = new KDTree();
        std::list<std::shared_ptr<Point>> pointList = std::list<std::shared_ptr<Point>>();

        std::shared_ptr newPoint1 = std::make_shared<Point>(Point(std::vector<double>({1, 5})));
        std::shared_ptr newPoint2 = std::make_shared<Point>(Point(std::vector<double>({2, 1})));
        std::shared_ptr newPoint3 = std::make_shared<Point>(Point(std::vector<double>({3, 4})));
        std::shared_ptr newPoint4 = std::make_shared<Point>(Point(std::vector<double>({4, 2})));
        std::shared_ptr newPoint5 = std::make_shared<Point>(Point(std::vector<double>({5, 3})));

        pointList.push_back(newPoint1);
        pointList.push_back(newPoint2);
        pointList.push_back(newPoint3);
        pointList.push_back(newPoint4);
        pointList.push_back(newPoint5);

        KDTreePreparation().insertSorted(pointList, *kdtree);

        WHEN("Getting the points") {

            std::list<std::shared_ptr<Point>> points = kdtree->getAllPoints();

            THEN("The root (last point in the list) is the median") {
                REQUIRE(points.back()->getCoordinates() == newPoint1->getCoordinates());
            }

        }
    }
}