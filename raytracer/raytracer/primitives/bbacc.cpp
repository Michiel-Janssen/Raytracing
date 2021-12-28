#include "primitives/bbacc.h"


namespace {

	class BoundingBoxAccelerator : public raytracer::primitives::_private_::PrimitiveImplementation
	{
		public:
			math::Box box;
			raytracer::Primitive primitiveField;

			BoundingBoxAccelerator(raytracer::Primitive primitive) : primitiveField{primitive}, box(primitive->bounding_box()) {}

			math::Box bounding_box() const override {
				return box;
			}

			std::vector<std::shared_ptr<raytracer::Hit>> find_all_hits(const math::Ray& ray) const override {
				if (box.is_hit_by(ray)) {
					return primitiveField->find_all_hits(ray);
				}
				return std::vector<std::shared_ptr<raytracer::Hit>>();
			}
	};
}

raytracer::Primitive raytracer::primitives::bounding_box_accelerator(const Primitive primitive)
{
	return Primitive(std::make_shared<BoundingBoxAccelerator>(primitive));
}