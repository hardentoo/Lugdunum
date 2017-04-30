#pragma once

#include <cstdint>
#include <vector>

#include <lug/Graphics/Export.hpp>
#include <lug/Graphics/Resource.hpp>
#include <lug/Graphics/Render/Material.hpp>
#include <lug/Math/Vector.hpp>

namespace lug {
namespace Graphics {
namespace Render {

class LUG_GRAPHICS_API Mesh : public Resource {
public:
    struct PrimitiveSet {
        struct Attribute {
            enum class Type : uint8_t {
                Indice,
                Position,
                Normal,
                TexCoord,
                Tangent
            } type;

            struct Buffer {
                char* data{nullptr};
                uint32_t size{0};
            } buffer;
        };

        enum class Mode : uint8_t {
            Points = 0,
            Lines = 1,
            LineLoop = 2,
            LineStrip = 3,
            Triangles = 4,
            TriangleStrip = 5,
            TriangleFan = 6
        } mode{Mode::Triangles};

        std::vector<Attribute> attributes;

        Attribute* position{nullptr};
        Attribute* normal{nullptr};
        std::vector<Attribute*> texCoords{};
        Attribute* tangent{nullptr};
        Attribute* indices{nullptr};

        Material* material{nullptr};

        void* _data{nullptr}; // Specific to each Renderer
    };

public:
    Mesh(const std::string& name);

    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;

    virtual ~Mesh() = default;

    const std::string& getName() const;
    void setName(const std::string &name);

protected:
    std::string _name;
    std::vector<PrimitiveSet> _primitiveSets;
};

#include <lug/Graphics/Render/Mesh.inl>

} // Render
} // Graphics
} // lug
