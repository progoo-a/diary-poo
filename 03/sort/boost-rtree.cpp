#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 3, bg::cs::cartesian> Point3D;
typedef std::pair<Point3D, int> Point3DWithID; // Stocke le point et un identifiant associé
typedef bgi::rtree<Point3DWithID, bgi::quadratic<16>> RTree3D;

int main() {
    // Créer un R-tree
    RTree3D rtree;

    // Ajouter des points 3D avec un ID
    rtree.insert(std::make_pair(Point3D(1.0, 2.0, 3.0), 1));
    rtree.insert(std::make_pair(Point3D(4.0, 5.0, 6.0), 2));
    rtree.insert(std::make_pair(Point3D(7.0, 8.0, 9.0), 3));

    // Point à rechercher dans le R-tree
    Point3D queryPoint(4.0, 5.0, 6.0);

    // Rechercher les 3 points les plus proches de queryPoint
    std::vector<Point3DWithID> result_n;
    rtree.query(bgi::nearest(queryPoint, 3), std::back_inserter(result_n));

    // Afficher les résultats
    std::cout << "Les 3 points les plus proches du point (" 
              << bg::get<0>(queryPoint) << ", "
              << bg::get<1>(queryPoint) << ", "
              << bg::get<2>(queryPoint) << ") sont :\n";
    
    for (const auto& value : result_n) {
        const Point3D& pt = value.first;
        std::cout << "Point ID: " << value.second << " ("
                  << bg::get<0>(pt) << ", "
                  << bg::get<1>(pt) << ", "
                  << bg::get<2>(pt) << ")\n";
    }

    return 0;
}
