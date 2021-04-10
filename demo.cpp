#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/algorithm.h>
#include <CGAL/convex_hull_3_to_face_graph.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/draw_surface_mesh.h>
#include <fstream>
#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef K::Point_3                                              Point_3;
typedef CGAL::Delaunay_triangulation_3<K>                       Delaunay;
typedef Delaunay::Vertex_handle                                 Vertex_handle;
typedef CGAL::Surface_mesh<Point_3>                             Surface_mesh;

int main()
{
    int nb_points;
    std::cin >> nb_points;
    double radius = 1.0;
    CGAL::Random_points_in_sphere_3<Point_3> gen(radius);
    std::list<Point_3> points;
    std::copy_n(gen, nb_points, std::back_inserter(points));
    // generate points with the number of nb_points randomly in a sphere of radius 1.0
    
    Delaunay T;
    T.insert(points.begin(), points.end());
    std::list<Vertex_handle>  vertices;
    T.incident_vertices(T.infinite_vertex(), std::back_inserter(vertices));
    std::cout << "This convex hull of the "<< nb_points <<" points now has "
            << vertices.size() << " points on it." << std::endl;
    // insert them into the triangulation and keep the convex hull
    
    Surface_mesh m;
    CGAL::convex_hull_3_to_face_graph(T, m);
    // translate convex hull to surface_mesh

    CGAL::draw(m);
    std::ofstream outfile; 
    outfile.open("mesh.off");
    outfile << m;
    outfile.close();
    // draw the mesh and save into "mesh.off"

  return 0;
}
