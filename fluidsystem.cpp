#include <omp.h>
#include "fluidsystem.hpp"
#include "sphere.hpp"
#include "node.hpp"
#include <iostream>
#include <QTime>
#include "environment.hpp"


FluidSystem::FluidSystem(node *parent_node, std::size_t max_particle_number, QOpenGLShaderProgram *program) :
    entity(parent_node),
    m_rest_density(0.01f),
    m_stiffness(10.1f),
    m_particle_masse(0.1f),
    m_particle_radius(0.1f),
    m_velocity_max(1.0f),
    m_particle_number(0),
    m_max_particle_number(max_particle_number),
    m_particle_positions(),
    m_particle_velocities(),
    m_program(program),
    m_vao(),
    m_position_buffer(),
    m_array_buffer(),
    m_index_buffer(QOpenGLBuffer::IndexBuffer),
    m_box_max(+1.0f, +1.0f, +1.0f),
    m_box_min(-1.0f, -1.0f, -1.0f),
    m_width(fabs(m_box_max.x() - m_box_min.x())),
    m_height(fabs(m_box_max.y() - m_box_min.y())),
    m_depth(fabs(m_box_max.z() - m_box_min.z()))
{
    initializeOpenGLFunctions();


    m_particle_positions.reserve(max_particle_number * 3);
    m_particle_velocities.reserve(max_particle_number * 3);
    m_particle_forces.reserve(max_particle_number * 3);
    m_particle_pressure.reserve(max_particle_number);
    m_particle_neighboors.resize(max_particle_number);
    m_particle_densities.resize(max_particle_number);

    m_position_buffer.create();
    m_velocity_buffer.create();
    m_array_buffer.create();
    m_index_buffer.create();
    m_vao.create();


    this->m_array_buffer.bind();
    this->m_array_buffer.allocate(sphere_vertices, sizeof(sphere_vertices));
    this->m_index_buffer.bind();
    this->m_index_buffer.allocate(sphere_indexes, sizeof(sphere_indexes));

    this->m_vao.bind();

    this->m_array_buffer.bind();
    quintptr offset = 0;
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(float) * 3);
    this->m_index_buffer.bind();

    this->m_vao.release();


//    while (m_particle_number < m_max_particle_number)
//    {
//        m_particle_number += 1;

//        float rand1 = (float)rand() / (float)RAND_MAX;
//        float rand2 = (float)rand() / (float)RAND_MAX;
//        float rand3 = (float)rand() / (float)RAND_MAX;

//        m_particle_positions.push_back(rand1 * 2.0f - 1.0f);
//        m_particle_positions.push_back(rand2 * 2.0f - 1.0f);
//        m_particle_positions.push_back(rand3 * 2.0f - 1.0f);

//        m_particle_velocities.push_back(0.0f);
//        m_particle_velocities.push_back(0.0f);
//        m_particle_velocities.push_back(0.0f);

//        m_particle_forces.push_back(0.0f);
//        m_particle_forces.push_back(0.0f);
//        m_particle_forces.push_back(0.0f);

//        m_particle_pressure.push_back(0.0f);

//    }

    for (int i = 0 ; i < m_max_particle_number ; ++i)
    {
        m_particle_neighboors[i].resize(m_max_particle_number);
    }

    m_grid.resize(m_depth / (m_particle_radius * 2)  + 1);

    for (int z = 0 ; z < m_depth / (m_particle_radius * 2.0f) ; ++z)
    {
        m_grid[z].resize(m_height / (m_particle_radius * 2.0f) + 1);
        for (int y = 0 ; y < m_height / (m_particle_radius * 2.0f) ; ++y)
        {
            m_grid[z][y].resize(m_width / (m_particle_radius * 2.0f) + 1);
            for (int x = 0 ; x < m_width / (m_particle_radius * 2.0f) ; ++x)
            {
                m_grid[z][y][x].m_particles.resize(m_max_particle_number);
            }
        }
    }
}

FluidSystem::~FluidSystem()
{
    m_position_buffer.destroy();
    this->m_array_buffer.destroy();
    this->m_index_buffer.destroy();
    this->m_vao.destroy();
}

void
FluidSystem::update(float elapsed)
{


    static float total = 0.0f;

    total += elapsed;

    if (m_particle_number < m_max_particle_number && (total < 6.0f || total > 10.0f)) {
        int imax = 2;
        float radius = 0.1f;
        float y_radius = 0.0f;
        if (total > 10.0f) {
            imax = m_max_particle_number - m_particle_number;
            radius = (m_box_max.x() - m_box_min.x()) / 3.0f;
            y_radius = 0.1f;
        }
        for (int i = 0 ; i < imax && m_particle_number < m_max_particle_number ; ++i)
        {
            m_particle_number += 1;

            float rand1 = (float)rand() / (float)RAND_MAX;
            float rand2 = (float)rand() / (float)RAND_MAX;
            float rand3 = (float)rand() / (float)RAND_MAX;

//            m_particle_positions.push_back(rand1 * 2.0f - 1.0f);
//            m_particle_positions.push_back(rand2 * 2.0f - 1.0f);
//            m_particle_positions.push_back(rand3 * 2.0f - 1.0f);

            m_particle_positions.push_back((m_box_max.x() - m_box_min.x()) / 2.0f + m_box_min.x() + (rand1 - 0.5f) * radius);
            m_particle_positions.push_back(m_box_max.y() - y_radius + (rand2 - 0.5f) * y_radius);
            m_particle_positions.push_back((m_box_max.z() - m_box_min.z()) / 2.0f + m_box_min.z() + (rand3 - 0.5f) * radius);

            m_particle_velocities.push_back(0.0f);
            m_particle_velocities.push_back(-160.0f);
            m_particle_velocities.push_back(0.0f);

            m_particle_forces.push_back(0.0f);
            m_particle_forces.push_back(0.0f);
            m_particle_forces.push_back(0.0f);

            m_particle_pressure.push_back(0.0f);

        }
    }


    elapsed = 0.005f;

    if (0.005 > 0.4f * (m_particle_radius / m_velocity_max)) {
        elapsed = 0.4f * (m_particle_radius / m_velocity_max);
    }

    const int max_z = m_depth / (m_particle_radius * 2);
    const int max_y = m_height / (m_particle_radius * 2);
    const int max_x = m_width / (m_particle_radius * 2);

    for (int z = 0 ; z < m_depth / (m_particle_radius * 2) ; ++z)
    {
        for (int y = 0 ; y < m_height / (m_particle_radius * 2) ; ++y)
        {
            for (int x = 0 ; x < m_width / (m_particle_radius * 2) ; ++x)
            {
                m_grid[z][y][x].m_particles.resize(0);
            }
        }
    }

    for (int i = 0 ; i < m_max_particle_number ; ++i)
    {
        m_particle_neighboors[i].resize(0);
    }

    const int x_offset = fabs(m_box_min.x()) / (m_particle_radius * 2);
    const int y_offset = fabs(m_box_min.y()) / (m_particle_radius * 2);
    const int z_offset = fabs(m_box_min.z()) / (m_particle_radius * 2);


    const float     field_force = 0.1f;
    const float     friction_force = 0.9f;
    const float     MAX_VELOCITY = 1000000.0f;

    auto w = [](float xi, float xj, float h) -> float {

        auto f = [](float q) -> float {
            if (0.0f <= q && q < 1.0f)
                return (3.0f / (2.0f * M_PI)) * ((2.0f / 3.0f) - q * q + (1.0f / 2.0f) * q * q * q);
            else if (1.0f <= q && q < 2.0f)
                return (3.0f / (2.0f * M_PI)) * ((1.0f / 6.0f) * (2 - q) * (2 - q) * (2 - q));
            return 0.0f;
        };

        float q = fabs(xi - xj) / h;
        return 1.0f / (h * h * h) * f(q);
    };

    auto wv = [](QVector3D xi, QVector3D xj, float h) -> float {
        auto f = [](float q) -> float {
            if (0.0f <= q && q < 1.0f)
                return (3.0f / (2.0f * M_PI)) * ((2.0f / 3.0f) - q * q + (1.0f / 2.0f) * q * q * q);
            else if (1.0f <= q && q < 2.0f)
                return (3.0f / (2.0f * M_PI)) * ((1.0f / 6.0f) * (2 - q) * (2 - q) * (2 - q));
            return 0.0f;
        };
        float q = (xi - xj).length() / h;
        return 1.0f / (h * h * h) * f(q);
    };



    for (std::size_t i = 0 ; i < m_particle_number ; ++i)
    {
        // left && right
        if (m_particle_positions[i * 3 + 0] - m_particle_radius < m_box_min.x()) {
            if (m_particle_positions[i * 3 + 0] < m_box_min.x()) {
                m_particle_positions[i * 3 + 0] = m_box_min.x();
//                m_particle_velocities[i * 3 + 0] = 0.0f;
//                m_particle_velocities[i * 3 + 1] = 0.0f;
//                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_forces[i * 3 + 0] += w(m_particle_positions[i * 3 + 0], m_box_min.x(), m_particle_radius) * field_force;
//            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
//            m_particle_velocities[i * 3 + 2] = m_particle_velocities[i * 3 + 2] * friction_force; // friction
        }
        if (m_particle_positions[i * 3 + 0] + m_particle_radius > m_box_max.x()) {
            if (m_particle_positions[i * 3 + 0] > m_box_max.x()) {
                m_particle_positions[i * 3 + 0] = m_box_max.x();
//                m_particle_velocities[i * 3 + 0] = 0.0f;
//                m_particle_velocities[i * 3 + 1] = 0.0f;
//                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_forces[i * 3 + 0] -= w(m_particle_positions[i * 3 + 0], m_box_max.x(), m_particle_radius) * field_force;
//            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
//            m_particle_velocities[i * 3 + 2] = m_particle_velocities[i * 3 + 2] * friction_force; // friction
        }

        // bottom && top
        if (m_particle_positions[i * 3 + 1] - m_particle_radius < m_box_min.y()) {
            if (m_particle_positions[i * 3 + 1] < m_box_min.y()) {
                m_particle_positions[i * 3 + 1] = m_box_min.y();
//                m_particle_velocities[i * 3 + 0] = 0.0f;
//                m_particle_velocities[i * 3 + 1] = 0.0f;
//                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_forces[i * 3 + 1] += w(m_particle_positions[i * 3 + 1], m_box_min.y(), m_particle_radius) * field_force;
            //            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
//            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
//            m_particle_velocities[i * 3 + 2] = m_particle_velocities[i * 3 + 2] * friction_force; // friction
        }
        if (m_particle_positions[i * 3 + 1] + m_particle_radius > m_box_max.y()) {
            if (m_particle_positions[i * 3 + 1] > m_box_max.y()) {
                m_particle_positions[i * 3 + 1] = m_box_max.y();
                m_particle_velocities[i * 3 + 0] = 0.0f;
                m_particle_velocities[i * 3 + 1] = 0.0f;
                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_forces[i * 3 + 1] -= w(m_particle_positions[i * 3 + 1], m_box_max.y(), m_particle_radius) * field_force;
            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
            m_particle_velocities[i * 3 + 2] = m_particle_velocities[i * 3 + 2] * friction_force; // friction
        }

        // front && back
        if (m_particle_positions[i * 3 + 2] - m_particle_radius < m_box_min.z()) {
            if (m_particle_positions[i * 3 + 2] < m_box_min.z()) {
                m_particle_positions[i * 3 + 2] = m_box_min.z();
                m_particle_velocities[i * 3 + 0] = 0.0f;
                m_particle_velocities[i * 3 + 1] = 0.0f;
                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
            m_particle_forces[i * 3 + 2] += w(m_particle_positions[i * 3 + 2], m_box_min.z(), m_particle_radius) * field_force;
        }
        if (m_particle_positions[i * 3 + 2] + m_particle_radius > m_box_max.z()) {
            if (m_particle_positions[i * 3 + 2] > m_box_max.z()) {
                m_particle_positions[i * 3 + 2] = m_box_max.z();
                m_particle_velocities[i * 3 + 0] = 0.0f;
                m_particle_velocities[i * 3 + 1] = 0.0f;
                m_particle_velocities[i * 3 + 2] = 0.0f;
            }
            m_particle_velocities[i * 3 + 0] = m_particle_velocities[i * 3 + 0] * friction_force; // friction
            m_particle_velocities[i * 3 + 1] = m_particle_velocities[i * 3 + 1] * friction_force; // friction
            m_particle_velocities[i * 3 + 2] = m_particle_velocities[i * 3 + 2] * friction_force; // friction
            m_particle_forces[i * 3 + 2] -= w(m_particle_positions[i * 3 + 2], m_box_max.z(), m_particle_radius) * field_force;
        }

        int z = m_particle_positions[i * 3 + 2] / (m_particle_radius * 2) + z_offset;
        int y = m_particle_positions[i * 3 + 1] / (m_particle_radius * 2) + y_offset;
        int x = m_particle_positions[i * 3 + 0] / (m_particle_radius * 2) + x_offset;


        if (x < 0) x = 0;
        else if (x > m_width / (m_particle_radius * 2)) x = m_width / (m_particle_radius * 2);

        if (y < 0) y = 0;
        else if (y > m_height / (m_particle_radius * 2)) y = m_height / (m_particle_radius * 2);

        if (z < 0) z = 0;
        else if (z > m_depth / (m_particle_radius * 2)) z = m_depth / (m_particle_radius * 2);

        m_grid[z][y][x].m_particles.push_back(i);

    }


    QTime   timer;


    timer.start();

#pragma omp parallel for
    for (std::size_t i = 0 ; i < m_particle_number ; ++i)
    {
        QVector3D   pos = QVector3D(m_particle_positions[i * 3 + 0], m_particle_positions[i * 3  + 1], m_particle_positions[i * 3  + 2]);

        const int z = m_particle_positions[i * 3 + 2] / (m_particle_radius * 2) + z_offset;
        const int y = m_particle_positions[i * 3 + 1] / (m_particle_radius * 2) + y_offset;
        const int x = m_particle_positions[i * 3 + 0] / (m_particle_radius * 2) + x_offset;


        float   density = 0.0f;

        for (int zi = -1 ; zi < 2 ; ++zi)
        {
            if (z + zi > max_z - 1 || z + zi < 0) continue;
            for (int yi = -1 ; yi < 2 ; ++yi)
            {
                if (y + yi > max_y - 1 || y + yi < 0) continue;
                for (int xi = -1 ; xi < 2 ; ++xi)
                {
                    if (x + xi > max_x - 1 || x + xi < 0) continue;
                    for (std::size_t p = 0 ; p < m_grid[z + zi][y + yi][x + xi].m_particles.size() ; ++p)
                    {
                        int ni = m_grid[z + zi][y + yi][x + xi].m_particles[p];
                        if (i == ni) continue;
                        QVector3D   opos = QVector3D(m_particle_positions[ni * 3 + 0], m_particle_positions[ni * 3  + 1], m_particle_positions[ni * 3  + 2]);
                        if (pos.distanceToPoint(opos) <= m_particle_radius * 2)
                        {
                            density += wv(pos, opos, m_particle_radius) * m_particle_masse;
                            m_particle_neighboors[i].push_back(ni);
                        }
                    }
                }
            }
        }

        float d = density / m_rest_density;
        m_particle_pressure[i] = m_stiffness * (d * d * d * d * d * d * d - 1.0f);
        m_particle_densities[i] = density;
    }

    int t2 = timer.elapsed();

//    std::cout << t2 << std::endl;

    for (std::size_t i = 0 ; i < m_particle_number ; ++i)
    {

        QVector3D v = QVector3D(m_particle_velocities[i * 3 + 0], m_particle_velocities[i * 3 + 1], m_particle_velocities[i * 3 + 2]);
        QVector3D pos = QVector3D(m_particle_positions[i * 3 + 0], m_particle_positions[i * 3 + 1], m_particle_positions[i * 3 + 2]);
        QVector3D   delta_p = QVector3D(0.0f, 0.0f, 0.0f);
        QVector3D   delta_v = QVector3D(0.0f, 0.0f, 0.0f);


        float pi = m_particle_densities[i];

        for (int j = 0 ; j < m_particle_neighboors[i].size() ; ++j)
        {
            std::size_t ni = m_particle_neighboors[i][j];
            if (ni == i) std::cout << "eerrrorr" << std::endl;
            QVector3D ppos = QVector3D(m_particle_positions[ni * 3 + 0], m_particle_positions[ni * 3 + 1], m_particle_positions[ni * 3 + 2]);

            QVector3D pvel = QVector3D(m_particle_velocities[ni * 3 + 0], m_particle_velocities[ni * 3 + 1], m_particle_velocities[ni * 3 + 2]);

//            delta_p += m_particle_pressure[ni] * (ppos - pos);
            float pj = m_particle_pressure[ni];
            float mj = m_particle_masse;

            const QVector3D e = (ppos - pos).normalized();

            delta_p += (pi / (pi * pi) + pj / (pj * pj)) * mj * wv(pos, ppos, m_particle_radius) * e;

            delta_v += pvel;
        }
        if (m_particle_densities[i] == 0.0f) m_particle_densities[i] = 0.001f;
        QVector3D   pressure_force = -m_particle_densities[i] * delta_p;
        QVector3D   viscosity_force = m_particle_masse * 0.0001f * delta_v * delta_v;

//        qDebug() << pressure_force;

        m_particle_forces[i * 3 + 0] += pressure_force.x();
        m_particle_forces[i * 3 + 1] += pressure_force.y();
        m_particle_forces[i * 3 + 2] += pressure_force.z();

        m_particle_forces[i * 3 + 0] += viscosity_force.x();
        m_particle_forces[i * 3 + 1] += viscosity_force.y();
        m_particle_forces[i * 3 + 2] += viscosity_force.z();
    }

    m_velocity_max = 0.0f;

    for (std::size_t i = 0 ; i < m_particle_number ; ++i)
    {
        QVector3D   force = QVector3D(m_particle_forces[i * 3 + 0], m_particle_forces[i * 3  + 1], m_particle_forces[i * 3  + 2]);
        force += Environment::gravity;

        QVector3D   velocity = QVector3D(m_particle_velocities[i * 3 + 0], m_particle_velocities[i * 3  + 1], m_particle_velocities[i * 3  + 2]);

        QVector3D   acceleration = (1.0f / m_particle_masse) * force;

        velocity += acceleration * elapsed;
        QVector3D   position = velocity * elapsed;

        if (velocity.x() > MAX_VELOCITY) velocity.setX(MAX_VELOCITY);
        else if (velocity.x() < -MAX_VELOCITY) velocity.setX(-MAX_VELOCITY);

        if (velocity.y() > MAX_VELOCITY) velocity.setY(MAX_VELOCITY);
        else if (velocity.y() < -MAX_VELOCITY) velocity.setY(-MAX_VELOCITY);

        if (velocity.z() > MAX_VELOCITY) velocity.setZ(MAX_VELOCITY);
        else if (velocity.z() < -MAX_VELOCITY) velocity.setZ(-MAX_VELOCITY);


        m_particle_velocities[i * 3 + 0] = velocity.x();
        m_particle_velocities[i * 3 + 1] = velocity.y();
        m_particle_velocities[i * 3 + 2] = velocity.z();

        if (velocity.length() > m_velocity_max)
            m_velocity_max = velocity.length();

        m_particle_positions[i * 3 + 0] += position.x();
        m_particle_positions[i * 3 + 1] += position.y();
        m_particle_positions[i * 3 + 2] += position.z();

        m_particle_forces[i * 3 + 0] = 0.0f;
        m_particle_forces[i * 3 + 1] = 0.0f;
        m_particle_forces[i * 3 + 2] = 0.0f;

    }
//    std::cout << "after : " << m_velocity_max << std::endl;
}

void
FluidSystem::render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model)
{
    this->m_vao.bind();

    this->m_position_buffer.bind();
    this->m_position_buffer.allocate(m_particle_positions.data(), m_particle_positions.size() * sizeof(float));

    quintptr offset = 0;
    int vertexLocation = m_program->attributeLocation("offset_position");
    m_program->enableAttributeArray(vertexLocation);
    m_program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 0);
    glVertexAttribDivisor(vertexLocation, 1);

    this->m_velocity_buffer.bind();
    this->m_velocity_buffer.allocate(m_particle_velocities.data(), m_particle_velocities.size() * sizeof(float));

    offset = 0;
    vertexLocation = m_program->attributeLocation("velocity");
    m_program->enableAttributeArray(vertexLocation);
    m_program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 0);
    glVertexAttribDivisor(vertexLocation, 1);

    m_velocity_max = 40.0f;

    m_program->bind();
    m_program->setUniformValue("mvp", projection * view * model);
    m_program->setUniformValue("m", model);
    m_program->setUniformValue("v", view);

    m_program->setUniformValue("radius", m_particle_radius);
    m_program->setUniformValue("velocity_max", m_velocity_max);

    m_program->setUniformValue("lights[0].position", QVector3D(3.0, 0.0, -3));
    m_program->setUniformValue("lights[1].position", QVector3D(-3.0, 0.0, -3.0));
    m_program->setUniformValue("lights[0].ambient", QVector3D(0.1, 0.1, 0.1));
    m_program->setUniformValue("lights[1].ambient", QVector3D(0.1, 0.1, 0.1));
    m_program->setUniformValue("lights[0].diffuse", QVector3D(0.5, 0.5, 0.5));
    m_program->setUniformValue("lights[1].diffuse", QVector3D(0.5, 0.5, 0.5));
    m_program->setUniformValue("lights[0].specular", QVector3D(1.0, 1.0, 1.0));
    m_program->setUniformValue("lights[1].specular", QVector3D(1.0, 1.0, 1.0));

    glDrawElementsInstanced(GL_TRIANGLES, 360, GL_UNSIGNED_SHORT, 0, m_particle_number);
    this->m_vao.release();
}
