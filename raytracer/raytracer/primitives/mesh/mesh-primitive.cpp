#include "primitives/mesh/mesh-primitive.h"
#include "primitives/mesh/mesh-receiver.h"
#include "primitives/mesh/mesh-text-reader.h"
#include "primitives/primitives.h"
#include <fstream>
#include <Catch.h>
#include <easylogging++.h>

/*
    https://www.cplusplus.com/reference/fstream/ifstream/
    https://www.cplusplus.com/reference/fstream/filebuf/
*/

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;



/*
    class MeshReceiver
    {
        virtual void vertex(double x, double y, double z) = 0;

        virtual void normal(double x, double y, double z) = 0;

        virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) = 0;

        virtual void box(unsigned n_children) = 0;
    };
*/



class MeshImplementation : public MeshReceiver
{
public:
    std::vector<Primitive> all_primitives;
    std::vector<Point3D> all_points;

    void vertex(double x, double y, double z) override
    {
        Point3D vertex(x, y, z);
        all_points.push_back(vertex);
    }

    void normal(double x, double y, double z) override {}

    void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) override
    {
        all_primitives.push_back(primitives::triangle(all_points.at(vertex1), all_points.at(vertex2), all_points.at(vertex3)));
    }

    void box(unsigned n_children)
    {
        std::vector<Primitive> box_items;
        for (unsigned i = 0; i < n_children; i++)
        {
            box_items.push_back(all_primitives.back());
            all_primitives.pop_back();
        }
        Primitive thebox = bounding_box_accelerator(make_union(box_items));
        all_primitives.push_back(thebox);
    }
};



Primitive raytracer::primitives::mesh(const std::string& path)
{
    MeshImplementation meshImplementation;
    
    std::filebuf reader;
    reader.open(path, std::ios_base::in);
    CHECK(bool(reader.is_open())) << "Failed to open file at " << path;

    std::istream stream(&reader);
    read_text_mesh(stream, meshImplementation);

    reader.close();
    return meshImplementation.all_primitives.front();
    

}