#include "cloth.hpp"
#include <QOpenGLFunctions>
#include "environment.hpp"
#include <QTime>

Cloth::Cloth(QOpenGLShaderProgram *prog, node *parent_node) :
    entity(parent_node),
    m_buffer(QOpenGLBuffer::VertexBuffer),
    m_buffer_index(QOpenGLBuffer::IndexBuffer),
    m_prog(prog),
    m_detach(false)
{
    initializeOpenGLFunctions();
}

Cloth::~Cloth()
{

}

void
Cloth::init(int height, int width, float distance)
{
    if (height < 2 || width < 2) return;

    m_particles.reserve(height * width);

    m_buffer.create();
    m_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer.bind();
    m_buffer.allocate(sizeof(float) * (8 * height * width * 2));

    m_buffer_index.create();
    m_buffer_index.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer_index.bind();
    m_buffer_index.allocate(sizeof(unsigned int) * (6 * (width - 1) * (height - 1) * 2));

    m_vao.create();

    m_vao.bind();
    m_buffer.bind();
    quintptr offset = 0;
    int vertexLocation = m_prog->attributeLocation("position");
    m_prog->enableAttributeArray(vertexLocation);
    m_prog->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(float) * 8);
    offset += 4 * sizeof(float);
    vertexLocation = m_prog->attributeLocation("normal");
    m_prog->enableAttributeArray(vertexLocation);
    m_prog->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(float) * 8);
    m_buffer_index.bind();
    m_vao.release();


    m_width = width;
    m_height = height;

    for (int y = 0 ; y < height ; ++y) {
        for (int x = 0 ; x < width ; ++x){
            Particle p;
            p.m_cloth = this;
            p.m_fixed = (y == 0 && x == 0) ||  (y == 0 && x == (width / 2)) || (y == 0 && x == (width - 1));
            p.m_position = QVector3D(x * distance - (width / 2.0f * distance), -y * distance, 0.0f);
            p.m_index = y * width + x;
            p.m_masse = 0.005f;
            m_particles.push_back(p);
        }
    }
    m_triangles.reserve((width - 1) * (height - 1) * 2);
    for (int y = 0 ; y < height - 1 ; ++y) {
        for (int x = 0 ; x < width - 1 ; ++x){
            Triangle t, t2;
            t.m_p0 = &m_particles[y * width + x];
            t.m_p1 = &m_particles[y * width + x + 1];
            t.m_p2 = &m_particles[(y + 1) * width + x];
            t2.m_p0 = &m_particles[(y + 1) * width + x];
            t2.m_p1 = &m_particles[y * width + x + 1];
            t2.m_p2 = &m_particles[(y + 1) * width + x + 1];
            m_triangles.push_back(t);
            m_triangles.push_back(t2);
        }
    }
    const float df = 40.0f;
    const float sf = 120.0f;
    const float df2 = 4.0f;
    const float sf2 = 40.0f;
    m_spring_dampers.reserve((width - 1) * height + (height - 1) * width + (width - 1) * (height - 1) * 2);
    for (int y = 0 ; y < height ; ++y) {
        for (int x = 0 ; x < width - 1 ; ++x){
            SpringDamper    sd;
            sd.m_p0 = &m_particles[y * width + x];
            sd.m_p1 = &m_particles[y * width + x + 1];
            sd.m_rest_length = 1.0f * distance;
            sd.m_damping_factor = df;
            sd.m_spring_constant = sf;
            m_spring_dampers.push_back(sd);
        }
    }
    for (int y = 0 ; y < height - 1; ++y) {
        for (int x = 0 ; x < width ; ++x){
            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 0) * width + x];
            sd.m_p1 = &m_particles[(y + 1) * width + x];
            sd.m_rest_length = 1.0f * distance;
            sd.m_damping_factor = df;
            sd.m_spring_constant = sf;
            m_spring_dampers.push_back(sd);
        }
    }
    for (int y = 0 ; y < height - 1; ++y) {
        for (int x = 0 ; x < width - 1; ++x){
            SpringDamper    sd;
            sd.m_p0 = &m_particles[y * width + x];
            sd.m_p1 = &m_particles[(y + 1) * width + x + 1];
            sd.m_rest_length = 1.4142 * distance;
            sd.m_damping_factor = df;
            sd.m_spring_constant = sf;
            m_spring_dampers.push_back(sd);
        }
    }
    for (int y = 0 ; y < height - 1; ++y) {
        for (int x = 0 ; x < width - 1; ++x){

            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 0) * width + x + 1];
            sd.m_p1 = &m_particles[(y + 1) * width + x];
            sd.m_rest_length = 1.4142 * distance;
            sd.m_damping_factor = df;
            sd.m_spring_constant = sf;
            m_spring_dampers.push_back(sd);

        }
    }

    for (int y = 0 ; y < height; ++y) {
        for (int x = 0 ; x < width - 2; ++x){

            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 0) * width + x];
            sd.m_p1 = &m_particles[(y + 0) * width + x + 2];
            sd.m_rest_length = 1.0f * 2.0f * distance;
            sd.m_damping_factor = df2;
            sd.m_spring_constant = sf2;
            m_spring_dampers.push_back(sd);

        }
    }

    for (int y = 0 ; y < height - 2; ++y) {
        for (int x = 0 ; x < width ; ++x){

            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 0) * width + x];
            sd.m_p1 = &m_particles[(y + 2) * width + x];
            sd.m_rest_length = 1.0f * 2.0f * distance;
            sd.m_damping_factor = df2;
            sd.m_spring_constant = sf2;
            m_spring_dampers.push_back(sd);

        }
    }

    for (int y = 0 ; y < height - 2; ++y) {
        for (int x = 0 ; x < width - 2 ; ++x){

            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 0) * width + x];
            sd.m_p1 = &m_particles[(y + 2) * width + x + 2];
            sd.m_rest_length = 1.4142f * 2.0f * distance;
            sd.m_damping_factor = df2;
            sd.m_spring_constant = sf2;
            m_spring_dampers.push_back(sd);

        }
    }

    for (int y = 0 ; y < height - 2; ++y) {
        for (int x = 0 ; x < width - 2 ; ++x){

            SpringDamper    sd;
            sd.m_p0 = &m_particles[(y + 2) * width + x];
            sd.m_p1 = &m_particles[(y + 0) * width + x + 2];
            sd.m_rest_length = 1.4142f * 2.0f * distance;
            sd.m_damping_factor = df2;
            sd.m_spring_constant = sf2;
            m_spring_dampers.push_back(sd);

        }
    }

}

void
Cloth::update(float elapsed)
{
    QTime t;
    t.start();


//    this->m_node->get_transform().rotate(1, QVector3D(0, 1, 0));
    QMatrix4x4 m = this->m_node->get_transform().world_matrix();
    QMatrix4x4 mi = m.inverted();
    QVector3D   ppos = QVector3D(0.0, -2, 0.0f);
    float dt = elapsed / 30.0f;
    for (int i = 0 ; i < 30 ; ++i) {
        QTime t2;
        t2.start();

        for (int i = 0 ; i < m_particles.size() ; ++i)
        {
            Particle    &p = m_particles[i];
            p.add_force(Environment::gravity * p.m_masse);
        }
        for (int i = 0 ; i < m_triangles.size() ; ++i)
        {
            Triangle    &t = m_triangles[i];
            t.compute_aero(Environment::wind);
        }
        for (int i = 0 ; i < m_spring_dampers.size() ; ++i)
        {
            SpringDamper &sd = m_spring_dampers[i];
            sd.compute_force();
        }
        for (int i = 0 ; i < m_particles.size() ; ++i)
        {
            Particle    &p = m_particles[i];
            p.update(dt);
            QVector3D   ppp = m * p.m_position;
            if (ppp.y() < ppos.y()) {
                QVector3D pppp = (mi * ppos);
                p.m_position.setY(pppp.y());
                p.m_velocity = -p.m_velocity * 0.01f;
            }
        }
//        qDebug() << t2.elapsed();

    }

//    qDebug() << t.elapsed();

}


void
Cloth::render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model)
{
    QTime t;
    t.start();
    QVector<float>  m_vertices;
    QVector<unsigned int>  m_indices;

    for (int i = 0 ; i < m_particles.size() ; ++i)
    {
        Particle &p = m_particles[i];
        p.m_normal = QVector3D(0.0f, 0.0f, 0.0f);
    }

    for (int i = 0 ; i < m_triangles.size() ; ++i)
    {
        Triangle &t = m_triangles[i];
        t.compute_normal();
    }

    for (int i = 0 ; i < m_particles.size() ; ++i)
    {
        Particle &p = m_particles[i];
        p.m_normal.normalize();
    }


    m_vertices.reserve(m_particles.size() * 8 * 2 + 8 * 4);
    for (int i = 0 ; i < m_particles.size() ; ++i)
    {
        Particle &p = m_particles[i];
        m_vertices.push_back(p.m_position.x());
        m_vertices.push_back(p.m_position.y());
        m_vertices.push_back(p.m_position.z());
        m_vertices.push_back(1.0f);

        m_vertices.push_back(p.m_normal.x());
        m_vertices.push_back(p.m_normal.y());
        m_vertices.push_back(p.m_normal.z());
        m_vertices.push_back(0.0f);
    }
    for (int i = 0 ; i < m_particles.size() ; ++i)
    {
        Particle &p = m_particles[i];
        m_vertices.push_back(p.m_position.x());
        m_vertices.push_back(p.m_position.y());
        m_vertices.push_back(p.m_position.z());
        m_vertices.push_back(1.0f);

        m_vertices.push_back(-p.m_normal.x());
        m_vertices.push_back(-p.m_normal.y());
        m_vertices.push_back(-p.m_normal.z());
        m_vertices.push_back(0.0f);
    }


    m_indices.reserve(m_triangles.size() * 6);
    for (int i = 0 ; i < m_triangles.size() ; ++i)
    {
        m_indices.push_back(m_triangles[i].m_p0->m_index);
        m_indices.push_back(m_triangles[i].m_p1->m_index);
        m_indices.push_back(m_triangles[i].m_p2->m_index);

        m_indices.push_back(m_triangles[i].m_p2->m_index + m_particles.size());
        m_indices.push_back(m_triangles[i].m_p1->m_index + m_particles.size());
        m_indices.push_back(m_triangles[i].m_p0->m_index + m_particles.size());
    }

    m_buffer.bind();
    m_buffer.write(0, m_vertices.data(), m_vertices.size() * sizeof(float));
    m_buffer_index.bind();
    m_buffer_index.write(0, m_indices.data(), m_indices.size() * sizeof(unsigned int));

    m_prog->bind();
    m_prog->setUniformValue("mvp", projection * view * model);
    m_prog->setUniformValue("m", model);
    m_prog->setUniformValue("v", view);

    m_prog->setUniformValue("lights[0].position", QVector3D(3.0, 0.0, -3));
    m_prog->setUniformValue("lights[1].position", QVector3D(-3.0, 0.0, -3.0));
    m_prog->setUniformValue("lights[0].ambient", QVector3D(0.1, 0.0, 0.0));
    m_prog->setUniformValue("lights[1].ambient", QVector3D(0.0, 0.1, 0.0));
    m_prog->setUniformValue("lights[0].diffuse", QVector3D(0.5, 0.0, 0.0));
    m_prog->setUniformValue("lights[1].diffuse", QVector3D(0.0, 0.5, 0.0));
    m_prog->setUniformValue("lights[0].specular", QVector3D(1.0, 1.0, 1.0));
    m_prog->setUniformValue("lights[1].specular", QVector3D(1.0, 1.0, 1.0));

    m_vao.bind();
    glEnable(GL_CULL_FACE);
//   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
//    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    m_vao.release();

//    qDebug() << t.elapsed();
}
