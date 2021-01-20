
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"



class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    ~ ViewerEtudiant()
    {
        delete [] foret;
        delete [] nuages;
        delete face;
        delete m;
    }

    int init();
    int render();
    int update( const float time, const float delta );


protected:

    Point* foret;
    Point* nuages;
    int nb_arbres, nb_nuages, i, j, l, n, h;

    //Tableau de transfo pour construction cubemap
    Transform* face;
    Mesh* m;

    Transform m_Tplane ;
    Transform m_Tmouton;

    Mesh m_quad;
    Mesh m_cube;
    Mesh m_triangle;
    Mesh m_disque;
    Mesh m_cylindre;
    Mesh m_cone;
    Mesh m_sphere;
    Mesh m_sphere_map;
    Mesh m_terrain;
    Mesh m_map;

    GLuint m_tex_terrain;
    GLuint m_tex_mur;
    GLuint m_tex_monde;
    GLuint m_tex_arbre;
    GLuint m_tex_nuages;
    GLuint m_tex_map;
    GLuint m_tex_zeppelin;
    GLuint m_tex_bois;
    GLuint m_tex_tuiles;
    GLuint m_tex_brique;
    GLuint m_tex_mouton;
    GLuint m_tex_face_mouton;

    void init_quad();
    void init_cube();
    void init_triangle();
    void init_disque();
    void init_cylindre();
    void init_cone();
    void init_sphere();
    void init_sphere_map();
    void init_terrain();
    void init_face_map(float x, float y, Mesh & m);
    void init_map();

    void draw_cube(const Transform& T, GLuint texture);
    void draw_triangle (const Transform& T, GLuint texture);
    void draw_disque(const Transform& T, GLuint texture);
    void draw_cylindre (const Transform& T, GLuint texture);
    void draw_cone (const Transform& T, GLuint texture);
    void draw_sphere (const Transform& T, GLuint texture);
    void draw_terrain (const Transform& T, GLuint texture);
    void draw_avion(const Transform& T, GLuint texture);
    void draw_dirigeable(const Transform& T, GLuint texture);
    void draw_quad(const Transform& T, GLuint texture);
    void draw_faces_billboard (const Transform& T, GLuint texture);
    void draw_billboard (const Transform& T, GLuint texture, Point tab[], int nb_elements);
    void draw_map (const Transform& T, GLuint texture);
    void draw_chalet (const Transform& T);
    void draw_mouton (const Transform& T);
    void draw_sphere_map(const Transform& T, GLuint texture);

};



#endif
