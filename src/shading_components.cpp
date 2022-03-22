#include <shading_components.hpp>

using namespace renderer;

// point : object's point
color renderer::lighting(const material& mtrl, const pointLight& light, const tuple& point, const tuple& eyev, const tuple& normv)
{
    // combine the surface color with th light's color/intensity
    auto effectiveColor = mtrl.color_m * light.intensity_m;
    // find the direction to the light source
    auto lightv = normalize(light.position_m - point); 
    // compute the ambient contribution
    auto ambient = effectiveColor * mtrl.ambient_m;

    // lightDnorm represents the cosine of the angle between the light vector and normv
    auto lightDnorm = glm::dot(lightv, normv);
    // ambient and specular would be black in such a situation
    if(lightDnorm <= 0) return ambient;
    // else compute the diffuse contribution
    auto diffuse = effectiveColor * mtrl.diffuse_m * lightDnorm;

    auto reflectv = reflect(-lightv, normv);
    auto reflectDeye = glm::dot(reflectv, eyev);
    if(reflectDeye <= 0) return ambient + diffuse;
    // else compute the specular contribution
    float factor = std::pow(reflectDeye, mtrl.shininess_m);
    // vector * scalar * scalar
    auto specular = light.intensity_m * mtrl.specular_m * factor;
    return ambient + diffuse + specular;
}