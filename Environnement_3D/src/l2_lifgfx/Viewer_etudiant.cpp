
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "math.h"
#include "draw.h"
#include "Viewer_etudiant.h"

using namespace std;

void ViewerEtudiant::init_triangle()
{
    m_triangle = Mesh (GL_TRIANGLES);

    m_triangle.normal(-1,0,0);

    m_triangle.texcoord(0.5,1);
    m_triangle.vertex(0,1,0);

    m_triangle.texcoord(0,0);
    m_triangle.vertex(0,0,-1);

    m_triangle.texcoord(0,1);
    m_triangle.vertex(0,0,1);

}

void ViewerEtudiant::init_cube()
{
    std::cout<<"init_cube"<<std::endl;


    //       4---5
    //      /|  /|
    //     7---6 |
    //     | 0-|-1
    //     |/  |/
    //     3---2


    // Sommets                     0           1           2       3           4           5       6           7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };

    // Faces                    0         1           2           3          4         5
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };

    // Normales
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };

    int i;

    m_cube = Mesh(GL_TRIANGLE_STRIP);
    m_cube.color( Color(1, 1, 1) );

    // Parcours des 6 faces
    for (i=0;i<6;i++)
    {

        m_cube.normal(n[i][0], n[i][1], n[i][2]);

        m_cube.texcoord(0,0);
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord(1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

        m_cube.restart_strip();
    }
}

void ViewerEtudiant::init_quad()
{
    m_quad = Mesh(GL_TRIANGLE_STRIP);

    m_quad.normal(0,0,1);

    m_quad.texcoord(0,0);
    m_quad.vertex(-1,-1,0);

    m_quad.texcoord(1,0);
    m_quad.vertex(1,-1,0);

    m_quad.texcoord(0,1);
    m_quad.vertex(-1,1,0);

    m_quad.texcoord(1,1);
    m_quad.vertex(1,1,0);
}

void ViewerEtudiant::init_disque()
{
    int nb_sommets = 20;
    m_disque = Mesh(GL_TRIANGLE_FAN);
    float theta = 0;
    float step = 2*M_PI/nb_sommets;
    m_disque.normal(0,-1,0);
    m_disque.texcoord(0.5,0.5);
    m_disque.vertex(0,0,0);

for (int i=0 ; i<=nb_sommets ; i++)
{
    theta = i*step;
    m_disque.texcoord(0.5+cos(theta)/2,0.5+sin(theta)/2);
    m_disque.vertex(cos(theta),0,sin(theta));
}
}

void ViewerEtudiant::init_cylindre()
{
    int nb_sommets = 20;
    float step = 2*M_PI/nb_sommets;
    float alpha = 0;
    m_cylindre = Mesh(GL_TRIANGLE_STRIP);
    for (int i=0 ; i<=nb_sommets ; i++)
    {
        alpha = i*step;
        m_cylindre.normal(Vector(cos(alpha),0,sin(alpha)));
        m_cylindre.texcoord(float(i)/nb_sommets,0);
        m_cylindre.vertex(Point(cos(alpha),-1,sin(alpha)));

        m_cylindre.normal(Vector(cos(alpha),0,sin(alpha)));
        m_cylindre.texcoord(float(i)/nb_sommets,1);
        m_cylindre.vertex(Point(cos(alpha),1,sin(alpha)));
    }
}

void ViewerEtudiant::init_cone()
{
    int nb_sommets = 20;
    float step = -2*M_PI/nb_sommets;
    float alpha = 0;
    m_cone = Mesh(GL_TRIANGLE_FAN);
    m_cone.vertex(0,3,0);
    m_cone.texcoord(0.5,1);
    m_cone.normal(0,1,0);

    for (int i=0 ; i<=nb_sommets ; i++)
    {
        alpha = i*step;
        m_cone.normal(Vector(cos(alpha),0,sin(alpha)));
        m_cone.texcoord(float(i)/nb_sommets,0);
        m_cone.vertex(Point(cos(alpha),0,sin(alpha)));
    }
}

void ViewerEtudiant::init_sphere()
{
    int divBeta = 26;
    int divAlpha = 13;
    float Beta, alpha1, alpha2;
    m_sphere = Mesh(GL_TRIANGLE_STRIP);
    for (int i=0 ; i<divAlpha ; i++)
    {
        alpha1 = -M_PI/2+float(i)*M_PI/divAlpha;
        alpha2 = -M_PI/2+float(i+1)*M_PI/divAlpha;

        for (int j=0 ; j<=divBeta ; j++)
        {
            Beta=float(j)*2.0*M_PI/divBeta;
            m_sphere.normal(Vector(cos(alpha1)*cos(Beta), sin(alpha1), cos(alpha1)*sin(Beta)));
            m_sphere.texcoord(1-Beta/(2.0*M_PI),0.5+alpha1/M_PI);
            m_sphere.vertex(Point(cos(alpha1)*cos(Beta), sin(alpha1), cos(alpha1)*sin(Beta)));

            m_sphere.normal(Vector(cos(alpha2)*cos(Beta), sin (alpha2), cos(alpha2)*sin(Beta)));
             m_sphere.texcoord(1-Beta/(2.0*M_PI),0.5+alpha2/M_PI);
            m_sphere.vertex(Point(cos(alpha2)*cos(Beta), sin (alpha2), cos(alpha2)*sin(Beta)));
        }
        m_sphere.restart_strip();
    }
}

Vector terrainNormal( const Image& im, const int i, const int j)
{
        int ip = i-1;
        int in = i+1;
        int jp = j-1;
        int jn = j+1;
        Point a (ip,im(ip,j).r,j);
        Point b (in,im(in,j).r,j);
        Point c (i,im(i,jp).r,jp);
        Point d (i,im(i,jn).r,jn);

        Vector e = normalize(b-a);
        Vector f = normalize(d-c);
        Vector g = cross (f,e);

        return g;
}

void ViewerEtudiant::init_terrain()
{

    m_terrain = Mesh(GL_TRIANGLE_STRIP);
    Image im = read_image("data/terrain/terrain_texture.png");
    for (int i=1 ; i<im.width()-2 ; i++)
        {
            for (int j=1 ; j<im.height()-1 ; j++)
            {
            m_terrain.normal(terrainNormal (im, i+1, j));
            m_terrain.texcoord(float(i+1)/im.width(),float(j)/im.height());
            m_terrain.vertex(Point(i+1,25.0*im(i+1,j).r,j));

            m_terrain.normal(terrainNormal (im, i, j));
            m_terrain.texcoord(float(i)/im.width(),float(j)/im.height());
            m_terrain.vertex(Point(i,25.0*im(i,j).r,j));
            }
        }

    m_terrain.restart_strip();


    nb_arbres =(rand()%40)+20;
    foret=new Point[nb_arbres];

    for (int k=0; k<nb_arbres; k++)
        {
        i=rand() %im.width();
        j=rand() %im.height();
        foret[k] = Point(i,im(i,j).r*25+1,j);
        }

    nb_nuages = (rand()%20)+10;
    nuages=new Point[nb_nuages];

    for (int k=0; k<nb_nuages; k++)
        {
        l = rand() %im.width();
        n = rand() %im.height();
        h = (rand() %40)+100;
        nuages[k] = Point(l,im(l,n).r*25+h,n);
    }
}

void ViewerEtudiant::init_face_map(float x, float y, Mesh & m_map)
{
    m_map = Mesh(GL_TRIANGLE_STRIP);

    m_map.normal(Vector(0,0,1));

    m_map.texcoord(x,y);
    m_map.vertex(-1,-1,0);

    m_map.texcoord(x+0.25,y);
    m_map.vertex(1,-1,0);

    m_map.texcoord(x,y+0.33);
    m_map.vertex( -1,1,0);

    m_map.texcoord(x+0.25,y+0.33);
    m_map.vertex(1,1,0);
}

void ViewerEtudiant::init_map()
{
    int i = 60;
    m = new Mesh[6];

    face = new Transform[6];
    face[0] = Translation(Vector(0,i,-i))*Scale(i,i,i);
    face[1] = Translation(Vector(0,i,i))*RotationY(180)*Scale(i,i,i);
    face[2] = Translation(Vector(0,2*i,0))*RotationX(90)*Scale(i,i,i);
    face[3] = Rotation(Vector(1,0,0),-90)*Scale(i,i,i);
    face[4] = Translation(Vector(-i,i,0))*RotationY(90)*Scale(i,i,i);
    face[5] = Translation(Vector(i,i,0))*RotationY(-90)*Scale(i,i,i);

    init_face_map(0.25,0.33, m[0]);
    init_face_map(0.75,0.33, m[1]);
    init_face_map(0.25,0.66, m[2]);
    init_face_map(0.25,0, m[3]);
    init_face_map(0,0.33, m[4]);
    init_face_map(0.5,0.33, m[5]);
}

void ViewerEtudiant::init_sphere_map()
{
    int divBeta = 26;
    int divAlpha = 13;
    float Beta, alpha1, alpha2;
    m_sphere_map = Mesh(GL_TRIANGLE_STRIP);
    for (int i=0 ; i<divAlpha ; i++)
    {
        alpha1 = -M_PI/2+float(i)*M_PI/divAlpha;
        alpha2 = -M_PI/2+float(i+1)*M_PI/divAlpha;

        for (int j=0 ; j<=divBeta ; j++)
        {
            Beta = float(j)*2.0*M_PI/divBeta;

            m_sphere_map.normal(Vector(cos(alpha1)*cos(Beta), sin(alpha1), cos(alpha1)*sin(Beta)));
            m_sphere_map.texcoord(Beta/(2.0*M_PI),0.5-alpha1/M_PI);
            m_sphere_map.vertex(Point(-cos(alpha1)*cos(Beta), -sin(alpha1), -cos(alpha1)*sin(Beta)));

            m_sphere_map.normal(Vector(cos(alpha2)*cos(Beta), sin (alpha2), cos(alpha2)*sin(Beta)));
             m_sphere_map.texcoord(Beta/(2.0*M_PI),0.5-alpha2/M_PI);
            m_sphere_map.vertex(Point(-cos(alpha2)*cos(Beta), -sin (alpha2), -cos(alpha2)*sin(Beta)));
        }
        m_sphere_map.restart_strip();
    }
}

void ViewerEtudiant::draw_quad(const Transform& T, GLuint texture)
{
    gl.model(T);
    gl.texture(texture);
    gl.draw(m_quad);
}

void ViewerEtudiant::draw_triangle(const Transform& T, GLuint texture)
{
    gl.model(T);
    gl.texture(texture);
    gl.draw(m_triangle);
}

void ViewerEtudiant::draw_cube(const Transform& T,GLuint texture)
{
    gl.model(T);
    gl.texture(texture);
    gl.draw(m_cube);
}

void ViewerEtudiant::draw_disque(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.model(T);
    gl.draw(m_disque);
}

void ViewerEtudiant::draw_cylindre (const Transform& T, GLuint texture)
{
    gl.texture(texture);

    gl.model(T);
    gl.draw(m_cylindre);

    gl.model(T*Translation(0,-1,0));
    gl.draw(m_disque);

    gl.model(T*Translation(0,1,0)*RotationX(180));
    gl.draw(m_disque);
}

void ViewerEtudiant::draw_cone(const Transform& T, GLuint texture)
{
    gl.texture(texture);

    gl.model(T);
    gl.draw(m_cone);

    gl.model(T);
    gl.draw(m_disque);
}

void ViewerEtudiant::draw_sphere(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.model(T);
    gl.draw(m_sphere);
}

void ViewerEtudiant::draw_sphere_map(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.model(T);
    gl.draw(m_sphere_map);
}

void ViewerEtudiant::draw_avion (const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.model(T*Scale(1,1,10));
    gl.draw(m_sphere);

    gl.texture(texture);
    gl.model(T*Translation(0,0,2)*Scale(10,0.1,1));
    gl.draw(m_cube);

    gl.texture(texture);
    gl.model(T*Translation(0,0,-6)*Scale(2.5,0.1,1));
    gl.draw(m_cube);
}

void ViewerEtudiant::draw_dirigeable (const Transform& T, GLuint texture)
{
    gl.texture(texture);

    gl.model(T*Scale(10,5,4));
    gl.draw(m_sphere);

    gl.model(T*Translation(-10,0,0)*RotationZ(-90)*Scale(4,5,0.2));
    gl.draw(m_cone);

    gl.model(T*Translation(-10,0,0)*RotationX(90)*RotationZ(-90)*Scale(4,5,0.2));
    gl.draw(m_cone);

    gl.model(T*Translation(0,-4.5,0)*Scale(5,1,1));
    gl.draw(m_cube);
}

void ViewerEtudiant::draw_terrain(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.model(T);
    gl.draw(m_terrain);
    draw_billboard(T, m_tex_arbre, foret, nb_arbres);
    draw_billboard(T, m_tex_nuages, nuages, nb_nuages);
}

void ViewerEtudiant::draw_faces_billboard(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    gl.alpha(0.9f);
    int nb_faces=4;
    for (int i=0 ; i<=nb_faces ; i++)
        draw_quad(T*Translation(0,0.7,0)*RotationY(i*90), texture);

    gl.alpha();
}

void ViewerEtudiant::draw_billboard(const Transform& T, GLuint texture, Point tab[], int nb_elements)
{
    for (int k=0 ; k<nb_elements ; k++)
        draw_faces_billboard(T*Translation(Vector(tab[k]))*Scale(9,9,9), texture);
}

void ViewerEtudiant::draw_map(const Transform& T, GLuint texture)
{
    gl.texture(texture);
    for (int i=0 ; i<6 ; i++)
    {
        gl.model(T*face[i]);
        gl.draw(m[i]);
    }
}

void ViewerEtudiant::draw_chalet(const Transform& T)
{
    draw_cube(T,m_tex_bois);
    draw_cube(T*Translation(0.7,1.8,0.1)*Scale(0.2,0.5,0.2),m_tex_brique);

    draw_triangle(T*RotationZ(-40)*Translation(-1.45,0.06,0)*Scale(3,1.7,1.08),m_tex_tuiles);
    draw_triangle(T*RotationZ(40)*Translation(1.45,0.06,0)*RotationY(180)*Scale(3,1.7,1.08),m_tex_tuiles);
    draw_triangle(T*RotationX(40)*Translation(0,0.06,-1.45)*RotationY(-90)*Scale(3,1.7,1.08),m_tex_tuiles);
    draw_triangle(T*RotationX(-40)*Translation(0,0.06,1.45)*RotationY(90)*Scale(3,1.7,1.08),m_tex_tuiles);

}

void ViewerEtudiant::draw_mouton(const Transform& T)
{
    draw_cube(T*Scale(1,1,1.5)*Translation(0,0,-1),m_tex_mouton);
    draw_cube(T*Translation(0,1,0)*Scale(0.6,0.6,0.6),m_tex_mouton);
    draw_cube(T*Translation(0.5,-1,-0.7)*Scale(0.25,0.7,0.25),m_tex_mouton);
    draw_cube(T*Translation(0.5,-1,-2.4)*Scale(0.25,0.7,0.25),m_tex_mouton);
    draw_cube(T*Translation(-0.5,-1,-0.7)*Scale(0.25,0.7,0.25),m_tex_mouton);
    draw_cube(T*Translation(-0.5,-1,-2.4)*Scale(0.25,0.7,0.25),m_tex_mouton);
    draw_cube(T*Translation(0,1,0.7)*Scale(0.6,0.6,0.1),m_tex_face_mouton);
}

int ViewerEtudiant::init()
{
    Viewer::init();

    m_camera.lookat(Point(0,0,0), 150);

    init_quad();
    init_cube();
    init_triangle();
    init_disque();
    init_cylindre();
    init_cone();
    init_sphere();
    init_sphere_map();
    init_terrain();
    init_map();


    m_tex_terrain = read_texture (0, smart_path("data/terrain/terrain_texture.png"));
    m_tex_mur = read_texture(0, smart_path("data/mur.png")) ;
    m_tex_monde = read_texture(0, smart_path("data/monde.jpg")) ;;
    m_tex_arbre = read_texture(0, smart_path("data/billboard/arbre3.png")) ;;
    m_tex_nuages = read_texture(0, smart_path("data/billboard/nuage.png")) ;;
    m_tex_map = read_texture (0, smart_path("data/cubemap/mountain.png")) ;;
    m_tex_zeppelin = read_texture(0, smart_path("data/zeppelin.jpg")) ;;
    m_tex_bois = read_texture(0, smart_path("data/bois.jpg")) ;;
    m_tex_tuiles = read_texture(0, smart_path("data/tuiles.jpg")) ;;
    m_tex_brique = read_texture(0, smart_path("data/brique.jpg")) ;;
    m_tex_face_mouton = read_texture(0, smart_path("data/facemouton.jpeg")) ;;
    m_tex_mouton = read_texture(0, smart_path("data/mouton.jpg")) ;;

    return 0;
}

int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);

    Viewer::render();

   /* draw_cube(Identity(), m_tex_arbre);
    draw_disque(Identity()*Translation(-5,0,-5)*RotationX(180), m_tex_mur);
    draw_cylindre(Identity()*Translation(-10,0,-10), m_tex_mur);
    draw_cone(Identity()*Translation(5,0,5), m_tex_mur);
    draw_sphere(Identity()*Translation(10,0,10), m_tex_monde);
    draw_triangle(Identity()*Translation(15,0,15),m_tex_mur);

    //draw_avion(m_Tplane*RotationY(90)*Scale(0.4,0.4,0.4), m_tex_pacman);

    //draw_sphere_map(Identity()*Scale(140,140,140), m_tex_monde);*/

    draw_mouton(m_Tmouton*RotationY(90));
    draw_mouton(m_Tmouton*RotationY(90)*Translation(10,0,10));
    draw_terrain(Identity()*Scale(0.65,0.65,0.65)*Translation(-96,1,-96), m_tex_terrain);
    draw_dirigeable(m_Tplane*Translation(10,65,-20)*Scale(0.8,0.8,0.8), m_tex_zeppelin);
    draw_chalet(Identity()*Translation(18,12,27)*Scale(4,4,4));
    draw_map(Identity(), m_tex_map);

    return 1;
}

int ViewerEtudiant::update( const float time, const float delta )
{

    float ts = time/1000.0;
    float ts2 = time/150.0;

    float angleRot = 360.0/15.0;
    int te = int(ts);
    int te2 = int (ts2);

    m_Tplane = RotationZ(angleRot*te);
    m_Tmouton = RotationZ(angleRot*te2);

    int ite = te%m_anim.nb_points();
    int ite2 = te2%m_anim.nb_points();

    Vector pos = Vector(m_anim[ite]);
    Vector pos2= Vector(m_anim[ite2]);

    m_Tplane = Translation(pos);
    m_Tmouton = Translation(pos2);

    int ite_suiv = (ite+1)%m_anim.nb_points();
    int ite_suiv2 = (ite2+1)%m_anim.nb_points();

    Point p0 = m_anim[ite];
    Point p1 = m_anim[ite_suiv];
    Point p0_2 = m_anim[ite2];
    Point p1_2 = m_anim[ite_suiv2];

    float poids = ts - te;
    float poids2 = ts2-te2;

    pos = Vector(p0) + (Vector(p1) - Vector(p0))*poids;
    pos2 = Vector(p0_2) + (Vector(p1_2) - Vector(p0_2))*poids2;


    m_Tplane = Translation(pos);
    m_Tmouton = Translation(pos2);

    int ite_ter = (ite_suiv+1)%m_anim.nb_points();
    int ite_ter2 = (ite_suiv2+1)%m_anim.nb_points();


    Point p2 = m_anim[ite_ter];
    Point p2_2 = m_anim[ite_ter2];

    Vector pos_suiv = Vector(p1) + (Vector(p2) - Vector(p1))*poids;
    Vector dir = normalize(pos_suiv - pos);
    Vector up = Vector(0,1,0);
    Vector codir = cross(dir,up);

    Vector pos_suiv2 = Vector(p1_2) + (Vector(p2_2) - Vector(p1_2))*poids2;
    Vector dir2 = normalize(pos_suiv2 - pos2);
    Vector codir2 = cross(dir2,up);

    m_Tplane = Transform(dir,up,codir,pos);
    m_Tmouton = Transform(dir2,up,codir2,pos2)*Translation(0,cos(ts2*1.5),0);

    return 0;

}

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}

int main( int argc, char **argv )
{
    srand((unsigned int)time(NULL));
    ViewerEtudiant v;
    v.run();
    return 0;
}
